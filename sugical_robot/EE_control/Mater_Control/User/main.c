
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/GPIO/gpio.h"
#include "./BSP/LED/led.h"
#include "./USMART/usmart.h"
#include "./BSP/KEY/key.h"
#include "./BSP/CAN/can.h"
#include "./BSP/CTRL/motor_ctrl.h"
#include "./Inc/DataTransmission.h"
#include "./BSP/EXTI/exti.h"
#include "./SYSTEM/tim/tim.h"
#include "./BSP/KF/kf.h"
#include "./BSP/ADC/adc.h"
#include "./BSP/DMA/dma.h"
#include "./BSP/MAPPING/mapping.h"
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/* USER CODE BEGIN PV */
volatile uint8_t KEY0_Press = 0;
volatile uint8_t ControlMode = 0;

/***	EXTERNAL VARIABLES	***/
extern uint8_t motor_IDs[8];
extern float init_angle[8];
extern float CAN_sending_para[12]; 
extern uint8_t output[24]; 
extern float slave_unit_joint_angles[10];
extern float motor_encoder_angles[10];
extern float joint_angles[10];

/* USER CODE END PV */

//KalmanFilter KF_1;
// encoder + adc 相关参数


extern uint8_t g_adc_dma_sta;               /* DMA传输状态标志, 0, 未完成; 1, 已完成 */
extern uint16_t g_adc_dma_buf[ADC_DMA_BUF_SIZE];   /* ADC DMA BUF */

int main(void)
{
    HAL_Init();                             /* 初始化HAL库 */
    sys_stm32_clock_init(336, 8, 2, 7);     /* 设置时钟,168Mhz */
    delay_init(168);                        /* 延时初始化 */
    usart_init(115200);                     /* 串口初始化为115200 */
    usmart_dev.init(84);                    /* 初始化USMART */
		encoder_init(); 
		MX_TIM5_Init();
//		key_init();                             /* 初始化按键 */
//		led_init();                             /* 初始化LED */
		HAL_TIM_Encoder_Start(&htim5, TIM_CHANNEL_ALL);
//		KalmanFilter_init(&KF_1, 0.1, 16);
    CAN_Config(); // init can
		// params for encoder
		adc_nch_dma_init((uint32_t)&g_adc_dma_buf);
		adc_nch_dma_enable(ADC_DMA_BUF_SIZE);   /* 启动ADC DMA多通道采集 */
		printf("start! \r\n");
		delay_ms(1000);


	
		// prepare to start work
//		prepare_working(init_angle);
		// tigger to torque mode
//		ready_work();
		HAL_Delay(1000);
		for(int i=0; i<8;i++){
								motor_torque_control(motor_IDs[i], 0);
								HAL_Delay(20);
							}
		
							
							
		while(1)
		{
				update_encoder_angle();
				get_all_motor_angles();
				send_CAN_array_0(motor_encoder_angles);
				print_sent_data(motor_encoder_angles, 10);
				HAL_Delay(10);
		}
		
		
		while (1)
    {	
				
				update_encoder_angle();
//				display_encoder_angle();
				/*将所有读取的编码器角度存于motor_encoder_angles中，角度
				经过偏置处理，符合[这里需要补充一张图]中角度的规定*/
				get_all_motor_angles();
//				Mapping_ABS(motor_encoder_angles);
//				send_CAN_array_0();
//				send_CAN_array(CAN_sending_para, slave_unit_joint_angles);
				/* 通过按键选择控制模式，进入不同处理  */
				KEY0_Press = ModeSwitch();                  /* 得到键值 */
				if(KEY0_Press) ControlMode = !ControlMode;  // 状态翻转
				switch (ControlMode)
				{
					case ABS_MODE:
						// 绿灯亮
						LED1(1);
						LED0(0);
						/* 从检测角度到【绝对控制模式】需要发送的角度*/
						Mapping_ABS(motor_encoder_angles);
						send_CAN_array(CAN_sending_para, slave_unit_joint_angles);
						break;
					case INCREMENT_MODE:
						// 红灯亮
						LED1(0);
						LED0(1);
						// 增量控制模式
						Mapping_INCREMENT(motor_encoder_angles);
						send_CAN_array(CAN_sending_para, joint_angles);
						break;
					default : break;
				
				}	
				print_sent_data(CAN_sending_para, 5);
				HAL_Delay(10);
    }
}





