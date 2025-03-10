#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif
	
/* Includes ------------------------------------------------------------------*/

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/CAN/can.h"




/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

//vicon同步相关参数设定
#define vicon_GPIO_PORT						GPIOC
#define vicon_GPIO_PIN						GPIO_PIN_10		//对应开发板上的 TX4 引脚
#define vicon_GPIO_CLK_ENABLE()		do{__HAL_RCC_GPIOC_CLK_ENABLE();}while(0)
#define vicon											HAL_GPIO_ReadPin(vicon_GPIO_PORT,vicon_GPIO_PIN);
extern float CAN_sending_para[12];
extern float received_data[8];
extern uint8_t output[24];  	
	
#define WristPosReport 0
#define betax   76.314 
#define betay   80.473
#define R_CL    16.0
#define CountsPerTurn   500.0
#define Harmonic   4.0
#define GearRatio  100.0
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */


void Error_Handler(void);
int get_encoder_angle(uint16_t cnt, uint16_t last_cnt, int opt_cnt);









#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
