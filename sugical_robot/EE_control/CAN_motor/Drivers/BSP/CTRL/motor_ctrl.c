#include "./SYSTEM/sys/sys.h"
//#include "./SYSTEM/usart/usart.h"
//#include "./SYSTEM/delay/delay.h"
//#include "./USMART/usmart.h"
#include "./BSP/CAN/can.h"
#include "./BSP/CAN/can.h"
#include "./BSP/CTRL/motor_ctrl.h"

//#include "./BSP/TIMER/btim.h"
//#include "demo.h"
//#include "./BSP/ATK_MS901M/atk_ms901m.h"
# include <stdio.h>
# include <stdlib.h>
# include "./BSP/CAN/can.h"

void motor_close(uint8_t motor_address)
{
		uint8_t msg_v[8] = {0};
		msg_v[0] = 0x80;	
//		msg_v[1] = 0x00;
//		msg_v[2] = 0x00;	
//		msg_v[3] = 0x00;	
//		msg_v[4] = 0x00;
//		msg_v[5] = 0x00;
//		msg_v[6] = 0x00;
//		msg_v[7] = 0x00;
		can_send_msg(motor_address + DEVICE_STD_ID, msg_v,8);
}

void motor_start(uint8_t motor_address)
{
		uint8_t msg_v[8] = {0};
		msg_v[0] = 0x88;	
		can_send_msg(motor_address + DEVICE_STD_ID, msg_v,8);
}	


void motor_torque_control(uint8_t motor_address, double iqValue)
{
/**********************************************************
	µç»úÁ¦¾Ø¿ØÖÆº¯Êý
	²ÎÊý·Ö±ðÎª£ºµç»úµØÖ· ¡¢ Å¤¾ØµçÁ÷Öµ
	ÆäÖÐ£º
	Å¤¾ØµçÁ÷Öµ·¶Î§Îª£¨65536-2048 ~ 2048£© Ô­ÒòÈçÏÂ£º
	µç»ú×ª¾ØµçÁ÷Öµiq £¨int16_tÀàÐÍ£¬·¶Î§-2048~2048£¬¶ÔÓ¦Êµ¼Ê×ª¾ØµçÁ÷·¶Î§-33A~33A£©
**********************************************************/	
		//½«iqvalueÖµ×ª»¯Îªuint16_tµÄÖµ
		uint16_t IQ = 0;	//·¢ËÍ¸øµç»úµÄ²ÎÊý
		if (iqValue < 0) {
				IQ = 65536 - (uint16_t)(-iqValue);
		} else {
				IQ = (uint16_t)iqValue;
		}
	
		uint8_t msg_v[8] = {0};
		msg_v[0] = 0xA1;	/* ¹¦ÄÜÂë */
		msg_v[1] = 0x00;
		msg_v[2] = 0x00;	
		msg_v[3] = 0x00;	
		msg_v[4] = *(uint8_t *)(&IQ) ;	/* µÍ×Ö½Ú */
		msg_v[5] = *((uint8_t *)&IQ + 1);	/*¸ß×Ö½Ú*/
		msg_v[6] = 0x00;
		msg_v[7] = 0x00;
		
    can_send_msg(motor_address + DEVICE_STD_ID, msg_v,8);
}


void motor_speed_control(uint8_t motor_address, double speedValue)
{
	uint16_t speed = 0;
	if (speedValue < 0) {
				speed = 65536 - (uint16_t)(-speedValue);
		} else {
				speed = (uint16_t)speedValue;
		}
		
		uint8_t msg_v[8] = {0};
		msg_v[0] = 0xA2;	/* ¹¦ÄÜÂë */
		msg_v[1] = 0x00;
		msg_v[2] = 0x00;	
		msg_v[3] = 0x00;	
		msg_v[4] = *( uint8_t *)&(speed );	/* µÍ×Ö½Ú */
		msg_v[5] = *((uint8_t *)(&speed) + 1);	/*¸ß×Ö½Ú*/
		msg_v[6] = *((uint8_t *)(&speed) + 2);
		msg_v[7] = *((uint8_t *)(&speed) + 3);
		
    can_send_msg(motor_address,msg_v,8);
}

/**********************************************************
主机发送该命令以控制电机的位置（多圈角度）
1. 控制值 angleControl 为 int32_t 类型，对应实际位置为 0.01degree/LSB，即 36000 代表 360°，
电机转动方向由目标位置和当前位置的差值决定。
2. 控制值 maxSpeed 限制了电机转动的最大速度，为 uint16_t 类型，对应实际转速 1dps/LSB，
即 360 代表 360dps。
**********************************************************/	
void motor_multi_angl_control(uint8_t motor_address, int32_t angleControl, uint16_t maxSpeed)
{
		
		uint8_t command[8];
    
    // 命令字节
    command[0] = 0xA4;
    // NULL 字节
    command[1] = 0x00;
    // 速度限制低字节和高字节
    command[2] = *(uint8_t *)&maxSpeed;
    command[3] = *(uint8_t *)((uint8_t *)&maxSpeed + 1);
    // 位置控制的低字节到高字节
    command[4] = *(uint8_t *)&angleControl;
    command[5] = *(uint8_t *)((uint8_t *)&angleControl + 1);
    command[6] = *(uint8_t *)((uint8_t *)&angleControl + 2);
    command[7] = *(uint8_t *)((uint8_t *)&angleControl + 3);
    can_send_msg(motor_address + DEVICE_STD_ID,command,8);
}

void motor_pause(uint8_t motor_address)
{
		uint8_t msg_v[8] = {0};
		msg_v[0] = 0x81;	/* ¹¦ÄÜÂë */
		msg_v[1] = 0x00;
		msg_v[2] = 0x00;	
		msg_v[3] = 0x00;	
		msg_v[4] = 0x00;	
		msg_v[5] = 0x00;	
		msg_v[6] = 0x00;	
		msg_v[7] = 0x00;	
		
    can_send_msg(motor_address,msg_v,8);
}

//void read_motor_position(uint8_t motor_address)
//{
///**********************************************************


//**********************************************************/	
//	uint8_t msg_v[2]={0x36,0x6B};
//	uint8_t rxbuf[6]={0};

//	int32_t position;
//  uint8_t re;
//	
//  can_send_msg(motor_address,msg_v,2);


//}
void read_motor_Accelerate(uint8_t motor_address)
{
/**********************************************************
»ñÈ¡¼ÓËÙ¶È£º
	Çý¶¯»Ø¸´(1 Ö¡)£º
	¼ÓËÙ¶ÈÊý¾ÝAccelerateÎªint32_tÀàÐÍ£¬µ¥Î»1dps/s £º

		DATA[0] ÃüÁî×Ö½Ú 0x33 
		DATA[1] NULL 0x00 
		DATA[2] NULL 0x00 
		DATA[3] NULL 0x00 
		DATA[4] ¼ÓËÙ¶È×Ö½Ú 1 DATA[4] = *(uint8_t *)(&Accel) 
		DATA[5] ¼ÓËÙ¶È×Ö½Ú 2 DATA[5] = *((uint8_t *)(&Accel)+1) 
		DATA[6] ¼ÓËÙ¶È×Ö½Ú 3 DATA[6] = *((uint8_t *)(&Accel)+2) 
		DATA[7] ¼ÓËÙ¶È×Ö½Ú 4 DATA[7] = *((uint8_t *)(&Accel)+3)
**********************************************************/	
		
	
		uint8_t msg_v[8] = {0}; 
		msg_v[0] = 0x33;	/* ÃüÁî×Ö½Ú */
		msg_v[1] = 0x00;
		msg_v[2] = 0x00;	
		msg_v[3] = 0x00;	
		msg_v[4] = 0x00;	
		msg_v[5] = 0x00;	
		msg_v[6] = 0x00;	
		msg_v[7] = 0x00;	
    can_send_msg(motor_address,msg_v,8);	
}

/**********************************************************
 these functions are used to read the params about motor

**********************************************************/	
void read_multi_angle(uint8_t motor_address)
{
		uint8_t msg_v[8] = {0}; 
		msg_v[0] = 0x92;
		can_send_msg(motor_address + DEVICE_STD_ID, msg_v, 8);	
}

void read_motor_State2(uint8_t motor_address, double *state)
{
/**********************************************************
		DATA[0] ÃüÁî×Ö½Ú 0x9C 
		DATA[1] = *(uint8_t *)(&temperature) 
		DATA[2] = *(uint8_t *)(&iq) 
		DATA[3] = *((uint8_t *)(&iq)+1)  
		DATA[4] = *(uint8_t *)(&speed) 
		DATA[5] = *((uint8_t *)(&speed)+1)
		DATA[6] = *(uint8_t *)(&encoder) 
		DATA[7] = *((uint8_t *)(&encoder)+1) 
**********************************************************/	
		uint8_t msg_v[8]; 
    uint8_t rxlen = can_receive_msg(motor_address + DEVICE_STD_ID, msg_v);
        if (rxlen)
        {
//						printf("\r\n already receive the msg \r\n");

						int16_t tau = (int16_t)(msg_v[2] | (msg_v[3] << 8)); //iq
						int16_t speed  = (int16_t)(msg_v[4] | (msg_v[5] << 8)); // speed
						uint16_t position = (uint16_t)(msg_v[6] | (msg_v[7] << 8));  //encoder = position
						state[0] = (double) tau *16.5 / 2048;
						state[1] =  (double) speed * 360 / (1 << 16);
						state[2] = (double) position / 65535.0 * 360.0;
//									printf("State array for motor %d in motor_ctrl: [tau: %f, v: %f, P; %f]\n", motor_address,
//           state[0], state[1], state[2]);
						printf("%.2f ", state[2]);
				}
			
 }

 
void test_param_tran(uint8_t num, uint8_t *state)
{
	for(int i=0; i<4; i++)
	{
		state[i] = num;
	}

}
uint8_t simu_spring_damping(uint8_t K, uint8_t C, uint8_t p, uint8_t v)
{
	uint8_t F_out = -(K * p + C * v);
	return F_out;
}


