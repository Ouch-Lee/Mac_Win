
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/GPIO/gpio.h"
#include "./BSP/LCD/lcd.h"
#include "./USMART/usmart.h"
#include "./BSP/KEY/key.h"
#include "./BSP/CAN/can.h"
#include "./BSP/CTRL/motor_ctrl.h"
#include "./BSP/EXTI/exti.h"
#include "./SYSTEM/tim/tim.h"
#include "./BSP/KF/kf.h"
#include "./BSP/ADC/adc.h"
#include "./BSP/DMA/dma.h"
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/* USER CODE BEGIN PV */


static uint8_t motor_IDs[8] = {1, 2, 3, 4, 5, 6, 7, 8};
static float init_angle[8] = {160.00f, 0.00f, -110.00f, -115.00f, 0.00f, 20.00f, 0.00f, 186.00f}; // change the para to change init angle
//static uint16_t iqControl[2] = {15,20};
static uint16_t iqControl = 15;
static uint32_t speedControl = 150;
//static uint32_t txMailBox;
float CAN_sending_para[12];  // �洢Ҫ�����Ӷ˵�12���Ƕ� 0-3��Ӧ����4�������4,5Ϊ�����������룻6-11��Ӧ����
float received_data[8]; // store message from motor
float motor_anlge_offset[8];
uint8_t output[24];   // ��������λ������24λ����

// about encoder
static float encoder_angle[6];  // ʵ����Ҫ�ĽǶ��ǵ�2 3 4 5��Ԫ��
typedef enum {
    AT_THETA_0,
    MOVING_TO_THETA_1,
    AT_THETA_1,
//    RETURNING_TO_THETA_0,
    // ��������ת����״̬
    MOVING_TO_THETA_0 // ��THETA_1��THETA_0�ƶ�
} EncoderState;



//static double encoder_angle_KF = 0;
//int Direction;//����������
/* USER CODE END PV */

//KalmanFilter KF_1;

// encoder + adc ��ز���
#define ADC_DMA_BUF_SIZE        50 * 6      /* ADC DMA�ɼ� BUF��С, Ӧ����ADCͨ������������ */
uint16_t g_adc_dma_buf[ADC_DMA_BUF_SIZE];   /* ADC DMA BUF */
extern uint8_t g_adc_dma_sta;               /* DMA����״̬��־, 0, δ���; 1, ����� */


//void processEncoder();
void prepare_working(float *init_angle);
void updateEncoderAngle(uint16_t *last_cnt, int *opt_cnt, double *encoder_angle);
void update_encoder_angle();
void send_CAN_array(); 
void send_CAN_num(uint32_t can_id);
void print_sent_data(float *data, int size);
void send_double_data_via_can(double data[], uint32_t id);
void display_encoder_angle();
void float_2_uint16(float *CAN_sending_para, uint8_t *output);


bool is_at_theta(float current, float target, float error_range) {
    return fabs(current - target) < error_range;
}

int main(void)
{
	
	/* commond  */

    
    HAL_Init();                             /* ��ʼ��HAL�� */
    sys_stm32_clock_init(336, 8, 2, 7);     /* ����ʱ��,168Mhz */
    delay_init(168);                        /* ��ʱ��ʼ�� */
    usart_init(115200);                     /* ���ڳ�ʼ��Ϊ115200 */
    usmart_dev.init(84);                    /* ��ʼ��USMART */
		encoder_init(); 
		MX_TIM5_Init();
		HAL_TIM_Encoder_Start(&htim5, TIM_CHANNEL_ALL);
//		KalmanFilter_init(&KF_1, 0.1, 16);
		
    CAN_Config(); // init can
		// params for encoder
		adc_nch_dma_init((uint32_t)&g_adc_dma_buf);
		adc_nch_dma_enable(ADC_DMA_BUF_SIZE);   /* ����ADC DMA��ͨ���ɼ� */
	
		uint16_t cnt = 0;
    uint16_t last_cnt = 0;
    int opt_cnt = 0;
		uint32_t can_id = 0x1;
		    uint16_t i, j;
    uint16_t adcx;
    uint32_t sum;
		float temp;
		delay_ms(1000);
		
		
		// prepare to start work
		prepare_working(init_angle);
		// tigger to torque mode
		uint8_t trigger_count_arr[2] = {0,0};  // ��¼����������̵Ĵ���
		float range[2] = {30.00, 30.00}; // pincher �����˶��Ƕ��г�
		float theta_0[2] = {0.00, 0.00}; // ��ʼλ�ö�Ӧ���۶�׼����
		update_encoder_angle();
		theta_0[0] = encoder_angle[4];
		theta_0[1] = encoder_angle[5];
		float theta_1[2];
		theta_1[0] = theta_0[0] - range[0];
		theta_1[1] = theta_0[1] - range[1];
		EncoderState state[2] = {AT_THETA_0, AT_THETA_0};
//		printf("Starting encoder movement detection.\n");
//		printf("\r\n init angles for 4 encoders: %f, %f, %f, %f", encoder_angle[0], encoder_angle[1], encoder_angle[4], encoder_angle[5]);

		while (1) {
//			break;
				update_encoder_angle();  // ���ڸ��������������ĽǶ�
				for (int encoder_id = 0; encoder_id < 2; encoder_id++) {
						float current_angle = encoder_angle[encoder_id + 4];
						// ͨ���ĸ�״̬�л����жϱ������Ƿ����δ���
						switch(state[encoder_id]) {
								case AT_THETA_0:
										if (current_angle < theta_0[encoder_id] - (theta_0[encoder_id] - theta_1[encoder_id]) / 2) {
												state[encoder_id] = MOVING_TO_THETA_1;
										}
										break;
								case MOVING_TO_THETA_1:
										if (is_at_theta(current_angle, theta_1[encoder_id], 4)) { // ������ΧΪ4��
												state[encoder_id] = AT_THETA_1;
												trigger_count_arr[encoder_id]++;
//												printf("\r\n encoder %d arrive %d time", encoder_id, trigger_count_arr[encoder_id]);
										}
										break;
								case AT_THETA_1:
										if (current_angle > theta_1[encoder_id] + (theta_0[encoder_id] - theta_1[encoder_id]) / 2) {
												state[encoder_id] = MOVING_TO_THETA_0; // ����ת������THETA_1��THETA_0�ƶ�
										}
										break;
								case MOVING_TO_THETA_0:
										if (is_at_theta(current_angle, theta_0[encoder_id], 4)) {
												state[encoder_id] = AT_THETA_0;
										}
										break;
						}
				}
				// ��������������Ƿ��Ѵﵽtheta_1����
				if (trigger_count_arr[0] >= 2 && trigger_count_arr[1] >= 2) {
//						printf("Both encoders reached theta_1 twice. Exiting loop.\n");
						// ͬʱ��8��������л�Ϊ����ģʽ
						for(int i=0; i<8;i++){
								motor_torque_control(motor_IDs[i], 0);
								HAL_Delay(50);
						}
						break;
				}
		}
		
			HAL_Delay(6000); // ����ҡ��5s
		for(int i=0; i<8;i++){
								motor_torque_control(motor_IDs[i], 0);
								HAL_Delay(50);
							}

		
		while (1)
    {	
				update_encoder_angle();
//				display_encoder_angle();
//				printf("\r\n");
//				delay_ms(1000);
				

				// test CAN and motor
				
			
				// �������forѭ������ȡ��8������ĽǶȲ�����received_data[8]��
				for(int i=0; i<8; i++){
					read_multi_angle(motor_IDs[i]);
//					HAL_Delay(10); // �ȿ������͵�CAN�����Ƿ���ȷ=>ͨ��
				}
				// ��Ҫ����һ����ʼƫ��  TODO;
				for(int i = 0; i < 8; i++) {
						motor_anlge_offset[i] = received_data[i] - init_angle[i]; // ִ��A[i] - B[i]�Ĳ���
					}
			
				// ��motor_anlge_offset��ֵ��sending_para��
				for (int i = 0; i < 4; ++i) {
					CAN_sending_para[i] = motor_anlge_offset[i];
				}
				for (int i = 4, j = 6; i < 8; ++i, ++j) {
					 CAN_sending_para[j] = motor_anlge_offset[i];
				}
				// ��encoder_angle����ĵ�3�͵�4��Ԫ�ظ�ֵ��CAN_sending_para�ĵ�4�͵�5��Ԫ��
				CAN_sending_para[4] = encoder_angle[0]; //  roll_1 ������
				CAN_sending_para[5] = encoder_angle[4]; //  pincher_1 ������

				// ��encoder_angle����ĵ�5�͵�6��Ԫ�ظ�ֵ��CAN_sending_para�ĵ�10�͵�11��Ԫ��
				CAN_sending_para[10] = encoder_angle[1]; 
				CAN_sending_para[11] = encoder_angle[5];
				send_CAN_array();
//				print_sent_data(CAN_sending_para, 12);
				float_2_uint16(CAN_sending_para, output);  // ��float����תΪ uint8_t
				User_UART_Send_ADC();
//				HAL_Delay(500);


    }
}

/**
 * @brief       ��ʼ�����˵��,�����е��̶�λ��
 *   @note      
 * @param       void
 * @retval      void
 */
void prepare_working(float *init_angle)
{	

	int32_t init_angle_32[8];
	for(int q=0; q<8;q++){
			init_angle_32[q] = (int32_t)(init_angle[q] * 100.0f);
			motor_multi_angl_control(motor_IDs[q], init_angle_32[q], 100);
			HAL_Delay(20);
//		printf("\r\n times: %d", init_angle_32[q]); 
	}
}
/**
 * @brief       ���Թ�����������ʾ�������Ƕ�
 *   @note      
 * @param       void
 * @retval      void
 */
void display_encoder_angle() {
    int i;
    printf("Encoder Angles:\n");
    for (i = 0; i < 6; ++i) {
        printf("Channel %d: %.2f degrees\n", i, encoder_angle[i]);
    }
}


/**
 * @brief       ���°��ģ�������������º��������ڸ��²��������µĽǶ�
 *   @note      
 * @param       void
 * @retval      void
 */
void update_encoder_angle() {
    if (g_adc_dma_sta == 1) {
        int j, i;
        int sum;
        float adcx, temp;
        for (j = 0; j < 6; j++) {  // ������ͨ��
            sum = 0; /* ���� */
            for (i = 0; i < ADC_DMA_BUF_SIZE / 6; i++) {  // ÿ��ͨ���ɼ���10������,����10���ۼ�
                sum += g_adc_dma_buf[( 6 * i) + j];  /* ��ͬͨ����ת�������ۼ� */
            }
            adcx = sum / (ADC_DMA_BUF_SIZE / 6);    /* ȡƽ��ֵ */
            temp = (adcx / 4096) * 360;      /* ��ȡ�����Ĵ�С����ʵ�ʵ�ѹֵ */
            encoder_angle[j] = temp;  // ��������Ԫ��
        }

        g_adc_dma_sta = 0;  /* ���DMA�ɼ����״̬��־ */
        adc_nch_dma_enable(ADC_DMA_BUF_SIZE);   /* ������һ��ADC DMA��ͨ���ɼ� */
    }
}
void updateEncoderAngle(uint16_t *last_cnt, int *opt_cnt, double *encoder_angle) {
    uint16_t cnt = __HAL_TIM_GET_COUNTER(&htim5);
    int diff_cnt = cnt - *last_cnt;
    if (abs(diff_cnt) > 10) {
        diff_cnt = (cnt - *last_cnt) / 1024;
    }

    *opt_cnt += diff_cnt;
    *encoder_angle = (double) *opt_cnt * 360 / 1024;
    *last_cnt = cnt;
}




void send_CAN_num(uint32_t can_id){
		uint8_t data_to_send[8];
		 double d = CAN_sending_para[2];
		for (int j = 0; j < 8; j++) {
            data_to_send[j] = *((uint8_t *)&d + j);
        }
			uint8_t send_status = can_send_msg(can_id, data_to_send, 8);
				
				if (send_status != 0) {
            // ������ʧ�ܵ����
            printf("fail to send \r\n");
        }
}

void send_CAN_array() {
				
    for (int i = 0; i < 12; i++) {
				uint32_t can_id = MASTER_SLAVE_ID + i; // ����Ψһ��CAN ID
        uint8_t data_to_send[4]; // floatռ��4�ֽ�
        // ��CAN_sending_para�����л�ȡfloatֵ
        float value = CAN_sending_para[i];

        // �����ϵͳ�У���Ҫ���ֽ�˳��ת
        for (int j = 0; j < sizeof(float); j++) {
            data_to_send[j] = *(((uint8_t *) &value) + (sizeof(float) - 1 - j));
        }

        // ����can_send_msg��������
        if (can_send_msg(can_id, data_to_send, sizeof(data_to_send)) != 0) {
            // ����ʧ�ܵĴ����߼�
            break;
        }
//				HAL_Delay(20);
    }
//		printf("\r\n send done");
}

void print_sent_data(float *data, int size) {
		printf("Data: ");
    for (int i = 0; i < size; ++i) {
        printf("%f ", data[i]);
    }
		printf(" . \n");
		
}


void float_2_uint16(float *CAN_sending_para, uint8_t *output) {
    // ��Ϊÿ��floatֵ��Ҫ2���ֽ����洢�������ܹ���Ҫ24���ֽ�
    for (int i = 0; i < 12; ++i) {
        // �������뵽���������
//				printf("\r\n");
        int rounded_value = (int)round(CAN_sending_para[i]);
//			printf("%d : %d  ", i, rounded_value);
				int rounded_value_abs = abs(rounded_value);
        // ������ת��Ϊ�����ֽ�
        // ���������ִ洢�ڵ�һ���ֽ�
        output[2 * i] = (uint8_t)(rounded_value_abs >> 8); // �洢��8λ
        // ���������ֵ�ʣ�ಿ�ִ洢�ڵڶ����ֽ�
        output[2 * i + 1] = (uint8_t)(rounded_value_abs & 0xFF); // �洢��8λ

        // ��������Ǹ����������λ����Ϊ1
        if (rounded_value < 0) {
            output[2 * i] |= 0x80; // �������λ
        }
    }
}

