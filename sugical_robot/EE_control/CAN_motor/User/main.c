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
#include <stdio.h>
#include <string.h>

/* USER CODE BEGIN PV */


static uint8_t motorId_yaw = 1;
static uint8_t motorId_pitch = 2;
//static uint16_t iqControl[2] = {15,20};
static uint16_t iqControl = 0;
static uint32_t speedControl = 150;
static uint32_t txMailBox;
static double motor_yaw_para[3] = {0.0, 0.0, 0.0};
static double motor_pitch_para[3]  = {0.0, 0.0, 0.0};

// about encoder
//uint16_t cnt = 0;
//uint16_t last_cnt = 0;
//int diff_cnt =0;
//int opt_cnt = 0; 
//int encoder_angle = 0;
//static double encoder_angle_KF = 0;
//int Direction;//编码器方向
/* USER CODE END PV */

//KalmanFilter KF_1;


//void processEncoder();
void updateEncoderAngle(uint16_t *last_cnt, int *opt_cnt, int *encoder_angle);

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
    int encoder_angle = 0;
	
		char buffer[20];
    printf("\r\n start test \r\n");
		delay_ms(1000);
		
		while (1)
    {	
			
//			// test encoder:
			
//			encoder_angle = get_encoder_angle(cnt, last_cnt, opt_cnt);
			
//			encoder_angle_KF = KalmanFilter_update(&KF_1, encoder_angle);
				updateEncoderAngle(&last_cnt, &opt_cnt, &encoder_angle);
				printf("\r\n %d ", encoder_angle);
//			printf("\r\n init angle is %d and KF is %f \r\n", encoder_angle, encoder_angle_KF);
//			

				// test CAN and motor
				motor_torque_control(motorId_yaw, iqControl);
				read_motor_State2(motorId_yaw, motor_yaw_para); 
//			printf("\r\n the angle for motor %d is: %f, \r\n",motorId_yaw, motor_yaw_para[2]);
//				
//				HAL_Delay(50);
				motor_torque_control(motorId_pitch, 10); // drive motor
 				read_motor_State2(motorId_pitch, motor_pitch_para); 
//				printf("\r\n %f", motor_yaw_para[2]);
//				sprintf(buffer, "%.6f",motor_yaw_para[2]);
//				uint16_t size = strlen(buffer);
//				HAL_UART_Transmit(&g_uart1_handle, (uint8_t *)buffer, size, HAL_MAX_DELAY);
			
//			printf("\r\n the angle for motor %d is: %f, \r\n",motorId_pitch, motor_pitch_para[2]);
//				printf("State array for motor %d in motor_ctrl: [tau: %f, v: %f, P; %f]\n", motorId_pitch,
//           motor_pitch_para[0], motor_pitch_para[1], motor_pitch_para[2]);

//			printf("-----------------------------------------");
//			printf("State array: [t: %u, tau: %u, v: %u, P; %u]\n", 
//           motor_para[0], motor_para[1], motor_para[2], motor_para[3]);
//			F_simu = simu_spring_damping()
			
		

//			motor_torque_control(motorId, -iqControl);
			
			/*this part try to get the prrcise angle informaion  */
//			motor_speed_control(motorId, speedControl);
//			printf("\r\n the position is: %u, \r\n", motor_para[3]);
			
			

    }
}

void updateEncoderAngle(uint16_t *last_cnt, int *opt_cnt, int *encoder_angle) {
    uint16_t cnt = __HAL_TIM_GET_COUNTER(&htim5);
    int diff_cnt = cnt - *last_cnt;
    if (abs(diff_cnt) > 10) {
        diff_cnt = (cnt - *last_cnt) / 1024;
    }

    *opt_cnt += diff_cnt;
    *encoder_angle = *opt_cnt * 360 / 1024;
    *last_cnt = cnt;
}




