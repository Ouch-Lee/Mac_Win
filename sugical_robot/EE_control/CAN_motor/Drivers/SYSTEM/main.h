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

//viconÍ¬²½Ïà¹Ø²ÎÊýÉè¶¨
#define vicon_GPIO_PORT						GPIOC
#define vicon_GPIO_PIN						GPIO_PIN_10		//¶ÔÓ¦¿ª·¢°åÉÏµÄ TX4 Òý½Å
#define vicon_GPIO_CLK_ENABLE()		do{__HAL_RCC_GPIOC_CLK_ENABLE();}while(0)
#define vicon											HAL_GPIO_ReadPin(vicon_GPIO_PORT,vicon_GPIO_PIN);
	
	
	
#define WristPosReport 0
#define betax   76.314 
#define betay   80.473
#define R_CL    16.0
#define CountsPerTurn   500.0
#define Harmonic   4.0
#define GearRatio  100.0
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */













#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
