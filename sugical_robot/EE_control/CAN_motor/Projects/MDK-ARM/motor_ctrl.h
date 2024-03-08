/**
 ****************************************************************************************************
 * @file        motor_ctrl.c
 * @author      Recklesss
 * @version     V1.0
 * @date        2023-07-31
 * @brief       MG10015E-i10电机驱动
 * @team    Balance team
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 STM32F103开发板
 *
 * 修改说明
 * V1.0 20230731
 * 第一次发布
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
/* 外部接口函数*/

/*电机控制命令*/
//力矩控制
void motor_torque_control(uint8_t motor_address,double iqValue);
//电机暂停
void motor_pause(uint8_t motor_address);

/*电机反馈数据获取命令*/
void read_motor_position(uint8_t motor_address);
//电机加速度
void read_motor_Accelerate(uint8_t motor_address);
//电机状态2
void read_motor_State2(uint8_t motor_address);                                                                          /* 初始化 */

#endif
