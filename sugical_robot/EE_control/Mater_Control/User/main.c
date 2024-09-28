
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
// encoder + adc ��ز���


extern uint8_t g_adc_dma_sta;               /* DMA����״̬��־, 0, δ���; 1, ����� */
extern uint16_t g_adc_dma_buf[ADC_DMA_BUF_SIZE];   /* ADC DMA BUF */

int main(void)
{
    HAL_Init();                             /* ��ʼ��HAL�� */
    sys_stm32_clock_init(336, 8, 2, 7);     /* ����ʱ��,168Mhz */
    delay_init(168);                        /* ��ʱ��ʼ�� */
    usart_init(115200);                     /* ���ڳ�ʼ��Ϊ115200 */
    usmart_dev.init(84);                    /* ��ʼ��USMART */
		encoder_init(); 
		MX_TIM5_Init();
//		key_init();                             /* ��ʼ������ */
//		led_init();                             /* ��ʼ��LED */
		HAL_TIM_Encoder_Start(&htim5, TIM_CHANNEL_ALL);
//		KalmanFilter_init(&KF_1, 0.1, 16);
    CAN_Config(); // init can
		// params for encoder
		adc_nch_dma_init((uint32_t)&g_adc_dma_buf);
		adc_nch_dma_enable(ADC_DMA_BUF_SIZE);   /* ����ADC DMA��ͨ���ɼ� */
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
				/*�����ж�ȡ�ı������Ƕȴ���motor_encoder_angles�У��Ƕ�
				����ƫ�ô�������[������Ҫ����һ��ͼ]�нǶȵĹ涨*/
				get_all_motor_angles();
//				Mapping_ABS(motor_encoder_angles);
//				send_CAN_array_0();
//				send_CAN_array(CAN_sending_para, slave_unit_joint_angles);
				/* ͨ������ѡ�����ģʽ�����벻ͬ����  */
				KEY0_Press = ModeSwitch();                  /* �õ���ֵ */
				if(KEY0_Press) ControlMode = !ControlMode;  // ״̬��ת
				switch (ControlMode)
				{
					case ABS_MODE:
						// �̵���
						LED1(1);
						LED0(0);
						/* �Ӽ��Ƕȵ������Կ���ģʽ����Ҫ���͵ĽǶ�*/
						Mapping_ABS(motor_encoder_angles);
						send_CAN_array(CAN_sending_para, slave_unit_joint_angles);
						break;
					case INCREMENT_MODE:
						// �����
						LED1(0);
						LED0(1);
						// ��������ģʽ
						Mapping_INCREMENT(motor_encoder_angles);
						send_CAN_array(CAN_sending_para, joint_angles);
						break;
					default : break;
				
				}	
				print_sent_data(CAN_sending_para, 5);
				HAL_Delay(10);
    }
}





