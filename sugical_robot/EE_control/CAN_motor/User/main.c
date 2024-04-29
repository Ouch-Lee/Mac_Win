/**
 ****************************************************************************************************
 * @file        main.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2021-10-25
 * @brief       CANͨ�� ʵ��
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� ̽���� F407������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 ****************************************************************************************************
 */

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
#include "main.h"
#include <stdio.h>
#include <string.h>

/* USER CODE BEGIN PV */


static uint8_t motorId_yaw = 1;
static uint8_t motorId_pitch = 2;
//static uint16_t iqControl[2] = {15,20};
static uint16_t iqControl = 15;
static uint32_t speedControl = 150;
//static uint32_t txMailBox;
static double motor_yaw_para[3] = {0.0, 0.0, 200.0};
static double motor_pitch_para[3]  = {0.0, 0.0, 100.0}; 
float CAN_sending_para[5]; 
float received_data[5]; // store message from motor

// about encoder
//uint16_t cnt = 0;
//uint16_t last_cnt = 0;
//int diff_cnt =0;
//int opt_cnt = 0; 
static double encoder_angle = 0.00;
//static double encoder_angle_KF = 0;
//int Direction;//����������
/* USER CODE END PV */

//KalmanFilter KF_1;


//void processEncoder();
void updateEncoderAngle(uint16_t *last_cnt, int *opt_cnt, double *encoder_angle);
void send_CAN_array(); 
void send_CAN_num(uint32_t can_id);
void print_sent_data(float *data, int size);
void send_double_data_via_can(double data[], uint32_t id);

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
		uint16_t cnt = 0;
    uint16_t last_cnt = 0;
    int opt_cnt = 0;

		uint32_t can_id = 0x1;
//    printf("\r\n start test \r\n");
		delay_ms(1000);
		while (1)
    {	
//			// test encoder:
//			encoder_angle_KF = KalmanFilter_update(&KF_1, encoder_angle);
//				updateEncoderAngle(&last_cnt, &opt_cnt, &encoder_angle);
				CAN_sending_para[0] = 0.00; // encoder_angle; ///360 * 3.14159 * 20
			
//				printf("\r\n%.2f %.2f ", encoder_angle, 0.00);
//			printf("\r\n init angle is %d and KF is %f \r\n", encoder_angle, encoder_angle_KF);
//			

				// test CAN and motor
				motor_torque_control(motorId_yaw, 0);
				CAN_sending_para[2] = received_data[0];
				HAL_Delay(10);
//			printf("\r\n the angle for motor %d is: %f, \r\n",motorId_yaw, motor_yaw_para[2]);
//				

				motor_torque_control(motorId_pitch, 0); // drive motor
				CAN_sending_para[3] = received_data[1];
			
//  this is testing if CAN_sending_para work

				send_CAN_array();
				print_sent_data(CAN_sending_para, 5);
				
				HAL_Delay(500);
				
		
//			motor_torque_control(motorId, -iqControl);
			
			
			

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

//void send_CAN_array(uint32_t base_id) {
//    for (int i = 0; i < 5; i++) {
//        // ����ÿ��Ԫ�ص�CAN ID������ֻ�Ǽ򵥵��ڻ���ID�ϼ�������
////        uint32_t can_id = base_id + i;
//        
//        // ��ȡ��ǰdoubleֵ��ָ��
//        uint8_t *ptr_to_data = (uint8_t *)&CAN_sending_para[i];
//        
//        // �������ݣ�len����Ϊ8����Ϊdouble��8�ֽ�
//        uint8_t send_status = can_send_msg(base_id, ptr_to_data, 8);
//        
//        if (send_status != 0) {
//            // ������ʧ�ܵ����
//            break;
//        }
//    }
//}
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
    for (int i = 0; i < 5; i++) {
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
				HAL_Delay(50);
    }
}

void print_sent_data(float *data, int size) {
		printf("Data: ");
    for (int i = 0; i < size; ++i) {
        printf("%f ", data[i]);
    }
		printf(" . \n");
		
}


