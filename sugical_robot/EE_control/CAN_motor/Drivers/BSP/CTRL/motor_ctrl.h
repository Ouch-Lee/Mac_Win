/**
 ****************************************************************************************************
 * @file        motor_ctrl.c
 * @author      Recklesss
 * @version     V1.0
 * @date        2023-07-31
 * @brief       MG10015E-i10µç»úÇý¶¯
 * @team    Balance team
 ****************************************************************************************************
 * @attention
 *
 * ÊµÑéÆ½Ì¨:ÕýµãÔ­×Ó STM32F103¿ª·¢°å
 *
 * ÐÞ¸ÄËµÃ÷
 * V1.0 20230731
 * µÚÒ»´Î·¢²¼
 *
 ****************************************************************************************************
 */

#ifndef _MOTOR_H
#define _MOTOR_H
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./USMART/usmart.h"
#include "./BSP/CAN/can.h"
//#include "./BSP/TIMER/btim.h"
//#include "demo.h"
//#include "./BSP/ATK_MS901M/atk_ms901m.h"
# include <stdio.h>
# include <stdlib.h>

/******************************************************************************************/
/* Íâ²¿½Ó¿Úº¯Êý*/

/*µç»ú¿ØÖÆÃüÁî*/
//Á¦¾Ø¿ØÖÆ
void motor_torque_control(uint8_t motor_address,double iqValue);
void motor_speed_control(uint8_t motor_address,double speedValue);
void motor_pause(uint8_t motor_address);

/*µç»ú·´À¡Êý¾Ý»ñÈ¡ÃüÁî*/
void read_motor_position(uint8_t motor_address);
//µç»ú¼ÓËÙ¶È
void read_motor_Accelerate(uint8_t motor_address);
//µç»ú×´Ì¬2
void read_motor_State2(uint8_t motor_address, double state[3]);
void test_param_tran(uint8_t num,uint8_t *state);
uint8_t simu_spring_damping(uint8_t K, uint8_t C, uint8_t p, uint8_t v);
#endif
