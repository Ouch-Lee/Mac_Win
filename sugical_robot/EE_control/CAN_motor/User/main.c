
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
float CAN_sending_para[12];  // 存储要发给从端的12个角度 0-3对应左手4个电机，4,5为左手两个编码；6-11对应右手
float received_data[8]; // store message from motor
float motor_anlge_offset[8];
uint8_t output[24];   // 用于向上位机发送24位数据

// about encoder
static float encoder_angle[6];  // 实际需要的角度是第2 3 4 5个元素
typedef enum {
    AT_THETA_0,
    MOVING_TO_THETA_1,
    AT_THETA_1,
//    RETURNING_TO_THETA_0,
    // 增加逆向转动的状态
    MOVING_TO_THETA_0 // 从THETA_1向THETA_0移动
} EncoderState;



//static double encoder_angle_KF = 0;
//int Direction;//编码器方向
/* USER CODE END PV */

//KalmanFilter KF_1;

// encoder + adc 相关参数
#define ADC_DMA_BUF_SIZE        50 * 6      /* ADC DMA采集 BUF大小, 应等于ADC通道数的整数倍 */
uint16_t g_adc_dma_buf[ADC_DMA_BUF_SIZE];   /* ADC DMA BUF */
extern uint8_t g_adc_dma_sta;               /* DMA传输状态标志, 0, 未完成; 1, 已完成 */


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

    
    HAL_Init();                             /* 初始化HAL库 */
    sys_stm32_clock_init(336, 8, 2, 7);     /* 设置时钟,168Mhz */
    delay_init(168);                        /* 延时初始化 */
    usart_init(115200);                     /* 串口初始化为115200 */
    usmart_dev.init(84);                    /* 初始化USMART */
		encoder_init(); 
		MX_TIM5_Init();
		HAL_TIM_Encoder_Start(&htim5, TIM_CHANNEL_ALL);
//		KalmanFilter_init(&KF_1, 0.1, 16);
		
    CAN_Config(); // init can
		// params for encoder
		adc_nch_dma_init((uint32_t)&g_adc_dma_buf);
		adc_nch_dma_enable(ADC_DMA_BUF_SIZE);   /* 启动ADC DMA多通道采集 */
	
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
		uint8_t trigger_count_arr[2] = {0,0};  // 记录到达最大量程的次数
		float range[2] = {30.00, 30.00}; // pincher 最大的运动角度行程
		float theta_0[2] = {0.00, 0.00}; // 初始位置对应凹槽对准电线
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
				update_encoder_angle();  // 用于更新两个编码器的角度
				for (int encoder_id = 0; encoder_id < 2; encoder_id++) {
						float current_angle = encoder_angle[encoder_id + 4];
						// 通过四个状态切换，判断编码器是否两次触发
						switch(state[encoder_id]) {
								case AT_THETA_0:
										if (current_angle < theta_0[encoder_id] - (theta_0[encoder_id] - theta_1[encoder_id]) / 2) {
												state[encoder_id] = MOVING_TO_THETA_1;
										}
										break;
								case MOVING_TO_THETA_1:
										if (is_at_theta(current_angle, theta_1[encoder_id], 4)) { // 假设误差范围为4度
												state[encoder_id] = AT_THETA_1;
												trigger_count_arr[encoder_id]++;
//												printf("\r\n encoder %d arrive %d time", encoder_id, trigger_count_arr[encoder_id]);
										}
										break;
								case AT_THETA_1:
										if (current_angle > theta_1[encoder_id] + (theta_0[encoder_id] - theta_1[encoder_id]) / 2) {
												state[encoder_id] = MOVING_TO_THETA_0; // 逆向转动，从THETA_1向THETA_0移动
										}
										break;
								case MOVING_TO_THETA_0:
										if (is_at_theta(current_angle, theta_0[encoder_id], 4)) {
												state[encoder_id] = AT_THETA_0;
										}
										break;
						}
				}
				// 检查两个编码器是否都已达到theta_1两次
				if (trigger_count_arr[0] >= 2 && trigger_count_arr[1] >= 2) {
//						printf("Both encoders reached theta_1 twice. Exiting loop.\n");
						// 同时将8个电机都切换为自由模式
						for(int i=0; i<8;i++){
								motor_torque_control(motor_IDs[i], 0);
								HAL_Delay(50);
						}
						break;
				}
		}
		
			HAL_Delay(6000); // 让他摇个5s
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
				
			
				// 经过这个for循环，获取了8个电机的角度并存在received_data[8]中
				for(int i=0; i<8; i++){
					read_multi_angle(motor_IDs[i]);
//					HAL_Delay(10); // 先看看发送的CAN数据是否正确=>通过
				}
				// 需要处理一个初始偏置  TODO;
				for(int i = 0; i < 8; i++) {
						motor_anlge_offset[i] = received_data[i] - init_angle[i]; // 执行A[i] - B[i]的操作
					}
			
				// 将motor_anlge_offset赋值到sending_para中
				for (int i = 0; i < 4; ++i) {
					CAN_sending_para[i] = motor_anlge_offset[i];
				}
				for (int i = 4, j = 6; i < 8; ++i, ++j) {
					 CAN_sending_para[j] = motor_anlge_offset[i];
				}
				// 将encoder_angle数组的第3和第4个元素赋值给CAN_sending_para的第4和第5个元素
				CAN_sending_para[4] = encoder_angle[0]; //  roll_1 编码器
				CAN_sending_para[5] = encoder_angle[4]; //  pincher_1 编码器

				// 将encoder_angle数组的第5和第6个元素赋值给CAN_sending_para的第10和第11个元素
				CAN_sending_para[10] = encoder_angle[1]; 
				CAN_sending_para[11] = encoder_angle[5];
				send_CAN_array();
//				print_sent_data(CAN_sending_para, 12);
				float_2_uint16(CAN_sending_para, output);  // 把float数据转为 uint8_t
				User_UART_Send_ADC();
//				HAL_Delay(500);


    }
}

/**
 * @brief       初始化主端电机,并运行到固定位置
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
 * @brief       调试过程中用于显示编码器角度
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
 * @brief       最新版的模拟量编码器更新函数，用于更新并储存最新的角度
 *   @note      
 * @param       void
 * @retval      void
 */
void update_encoder_angle() {
    if (g_adc_dma_sta == 1) {
        int j, i;
        int sum;
        float adcx, temp;
        for (j = 0; j < 6; j++) {  // 遍历个通道
            sum = 0; /* 清零 */
            for (i = 0; i < ADC_DMA_BUF_SIZE / 6; i++) {  // 每个通道采集了10次数据,进行10次累加
                sum += g_adc_dma_buf[( 6 * i) + j];  /* 相同通道的转换数据累加 */
            }
            adcx = sum / (ADC_DMA_BUF_SIZE / 6);    /* 取平均值 */
            temp = (adcx / 4096) * 360;      /* 获取计算后的带小数的实际电压值 */
            encoder_angle[j] = temp;  // 更新数组元素
        }

        g_adc_dma_sta = 0;  /* 清除DMA采集完成状态标志 */
        adc_nch_dma_enable(ADC_DMA_BUF_SIZE);   /* 启动下一次ADC DMA多通道采集 */
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
            // 处理发送失败的情况
            printf("fail to send \r\n");
        }
}

void send_CAN_array() {
				
    for (int i = 0; i < 12; i++) {
				uint32_t can_id = MASTER_SLAVE_ID + i; // 构造唯一的CAN ID
        uint8_t data_to_send[4]; // float占用4字节
        // 从CAN_sending_para数组中获取float值
        float value = CAN_sending_para[i];

        // 大端序系统中，需要将字节顺序反转
        for (int j = 0; j < sizeof(float); j++) {
            data_to_send[j] = *(((uint8_t *) &value) + (sizeof(float) - 1 - j));
        }

        // 调用can_send_msg发送数据
        if (can_send_msg(can_id, data_to_send, sizeof(data_to_send)) != 0) {
            // 发送失败的处理逻辑
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
    // 因为每个float值需要2个字节来存储，所以总共需要24个字节
    for (int i = 0; i < 12; ++i) {
        // 四舍五入到最近的整数
//				printf("\r\n");
        int rounded_value = (int)round(CAN_sending_para[i]);
//			printf("%d : %d  ", i, rounded_value);
				int rounded_value_abs = abs(rounded_value);
        // 将整数转换为两个字节
        // 将整数部分存储在第一个字节
        output[2 * i] = (uint8_t)(rounded_value_abs >> 8); // 存储高8位
        // 将整数部分的剩余部分存储在第二个字节
        output[2 * i + 1] = (uint8_t)(rounded_value_abs & 0xFF); // 存储低8位

        // 如果整数是负数，将最高位设置为1
        if (rounded_value < 0) {
            output[2 * i] |= 0x80; // 设置最高位
        }
    }
}

