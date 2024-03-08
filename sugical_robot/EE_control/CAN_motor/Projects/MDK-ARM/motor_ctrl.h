/**
 ****************************************************************************************************
 * @file        motor_ctrl.c
 * @author      Recklesss
 * @version     V1.0
 * @date        2023-07-31
 * @brief       MG10015E-i10�������
 * @team    Balance team
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� STM32F103������
 *
 * �޸�˵��
 * V1.0 20230731
 * ��һ�η���
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
/* �ⲿ�ӿں���*/

/*�����������*/
//���ؿ���
void motor_torque_control(uint8_t motor_address,double iqValue);
//�����ͣ
void motor_pause(uint8_t motor_address);

/*����������ݻ�ȡ����*/
void read_motor_position(uint8_t motor_address);
//������ٶ�
void read_motor_Accelerate(uint8_t motor_address);
//���״̬2
void read_motor_State2(uint8_t motor_address);                                                                          /* ��ʼ�� */

#endif
