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


/* USER CODE BEGIN PV */


static uint8_t motorId = 1;
static uint16_t iqControl = 10;
static uint32_t speedControl = 150;
static uint32_t txMailBox;
static double motor_para[3];
static int16_t speed;
/* USER CODE END PV */


void show_res(uint8_t res)
{
	            if (res)
            {
              /* 提示发送失败 */
							 usart_show_string("Faild");
							
            }
            else
            {
							/* 提示发送成功 */
							usart_show_string("OK");
            }
}

int main(void)
{
    uint8_t key;
    uint8_t i = 0, t = 0;
    uint8_t cnt = 0;
    uint8_t rx_buffer[8];
    uint8_t rxlen = 0;
    uint8_t res;
		uint8_t F_simu;

	
	/* commond  */

    
    HAL_Init();                             /* 初始化HAL库 */
    sys_stm32_clock_init(336, 8, 2, 7);     /* 设置时钟,168Mhz */
    delay_init(168);                        /* 延时初始化 */
    usart_init(115200);                     /* 串口初始化为115200 */
    usmart_dev.init(84);                    /* 初始化USMART */
    encoder_init();                             /* 初始化LED */
////    key_init();                             /* 初始化按键 */
    CAN_Config();
    printf("\r\n start test \r\n");
		while (1)
    {	
			delay_ms(20);
//			motor_torque_control(motorId, iqControl); // drive motor
////			rxlen = can_receive_msg(DEVICE_STD_ID + 1, rx_buffer);  /* CAN ID = 0x12, 接收数据查询 */
//			read_motor_State2(1, motor_para); 
			
			GPIO_PinState pinState0 = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_2);
			GPIO_PinState pinState1 = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_3);
			
			if (pinState0 == GPIO_PIN_SET) {
            printf("\r\n PIN2 is high \r\n");
        } else {
            printf("\r\n PIN2 is low \r\n");
        }

        if (pinState1 == GPIO_PIN_SET) {
            printf("\r\n PIN3 is high \r\n");
        } else {
            printf("\r\n PIN3 is low \r\n");
        }

//			printf("State array: [t: %u, tau: %u, v: %u, P; %u]\n", 
//           motor_para[0], motor_para[1], motor_para[2], motor_para[3]);
//			F_simu = simu_spring_damping()
			
		
//			delay_ms(2000);
//			motor_torque_control(motorId, -iqControl);
			
			/*this part try to get the prrcise angle informaion  */
//			motor_speed_control(motorId, speedControl);
//			printf("\r\n the position is: %u, \r\n", motor_para[3]);
			
			
			

    }
}

