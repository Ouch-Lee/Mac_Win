/**
 ****************************************************************************************************
 * @file        main.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2021-10-25
 * @brief       CAN通信 实验
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 探索者 F407开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
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
//int Direction;//编码器方向
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
//        // 计算每个元素的CAN ID，这里只是简单地在基础ID上加上索引
////        uint32_t can_id = base_id + i;
//        
//        // 获取当前double值的指针
//        uint8_t *ptr_to_data = (uint8_t *)&CAN_sending_para[i];
//        
//        // 发送数据，len设置为8，因为double是8字节
//        uint8_t send_status = can_send_msg(base_id, ptr_to_data, 8);
//        
//        if (send_status != 0) {
//            // 处理发送失败的情况
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
            // 处理发送失败的情况
            printf("fail to send \r\n");
        }
}

void send_CAN_array() {
    for (int i = 0; i < 5; i++) {
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


