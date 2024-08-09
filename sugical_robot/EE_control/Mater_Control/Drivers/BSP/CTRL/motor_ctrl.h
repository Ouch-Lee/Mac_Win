
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
 ****************************************************************************************************
 */

#ifndef _MOTOR_H
#define _MOTOR_H
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./USMART/usmart.h"
#include "./BSP/CAN/can.h"
# include <stdio.h>
# include <stdlib.h>


#define TRUE 1
#define FALSE 0


/***	TYPE DEFINE	***/
typedef enum {
    AT_THETA_0,
    MOVING_TO_THETA_1,
    AT_THETA_1,
    MOVING_TO_THETA_0 // 从THETA_1向THETA_0移动
} EncoderState;

/***	EXTERNAL VARIABLES	***/
extern float encoder_angle[6];
extern uint8_t motor_IDs[8];
extern float offset_angle[8];
/******************************************************************************************/

void motor_close(uint8_t motor_address);
void motor_stop(uint8_t motor_address);
void motor_start(uint8_t motor_address);
void motor_torque_control(uint8_t motor_address,double iqValue);
void motor_speed_control(uint8_t motor_address,double speedValue);
void motor_multi_angl_control(uint8_t motor_address, int32_t angleControl, uint16_t maxSpeed);
void motor_pause(uint8_t motor_address);

/*读取电机相关数据 */
void read_multi_angle(uint8_t motor_address);
void read_motor_position(uint8_t motor_address);

//µç»ú¼ÓËÙ¶È
void read_motor_Accelerate(uint8_t motor_address);
//µç»ú×´Ì¬2
void read_motor_State2(uint8_t motor_address, double *state);
void prepare_working(float *init_angle); 
void display_encoder_angle(void);
void update_encoder_angle(void);
void ready_work(void);
uint8_t is_at_theta(float current, float target, float error_range);

uint8_t simu_spring_damping(uint8_t K, uint8_t C, uint8_t p, uint8_t v);

#endif
