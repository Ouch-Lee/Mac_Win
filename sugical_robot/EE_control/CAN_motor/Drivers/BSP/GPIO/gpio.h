
#ifndef __GPIO_H
#define __GPIO_H

#include "./SYSTEM/sys/sys.h"
/******************************************************************************************/
/* 引脚 定义 */

#define ENCODER_A_GPIO_PORT                  GPIOE
#define ENCODER_A_GPIO_PIN                   GPIO_PIN_2
#define ENCODER_A_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOF_CLK_ENABLE(); }while(0)             /* PF口时钟使能 */

#define ENCODER_B_GPIO_PORT                  GPIOE
#define ENCODER_B_GPIO_PIN                   GPIO_PIN_3
#define ENCODER_B_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOF_CLK_ENABLE(); }while(0)             /* PF口时钟使能 */

/******************************************************************************************/

/* LED端口定义 */
//#define LED0(x)   do{ x ? \
//                      HAL_GPIO_WritePin(LED0_GPIO_PORT, LED0_GPIO_PIN, GPIO_PIN_SET) : \
//                      HAL_GPIO_WritePin(LED0_GPIO_PORT, LED0_GPIO_PIN, GPIO_PIN_RESET); \
//                  }while(0)       /* LED0 = RED */

//#define LED1(x)   do{ x ? \
//                      HAL_GPIO_WritePin(LED1_GPIO_PORT, LED1_GPIO_PIN, GPIO_PIN_SET) : \
//                      HAL_GPIO_WritePin(LED1_GPIO_PORT, LED1_GPIO_PIN, GPIO_PIN_RESET); \
//                  }while(0)       /* LED1 = GREEN */

///* LED取反定义 */
//#define LED0_TOGGLE()    do{ HAL_GPIO_TogglePin(LED0_GPIO_PORT, LED0_GPIO_PIN); }while(0)       /* LED0 = !LED0 */
//#define LED1_TOGGLE()    do{ HAL_GPIO_TogglePin(LED1_GPIO_PORT, LED1_GPIO_PIN); }while(0)       /* LED1 = !LED1 */

/******************************************************************************************/
/* 外部接口函数*/
void encoder_init(void);                                                                            /* 初始化 */

#endif
