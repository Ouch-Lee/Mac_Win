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
		
    can_send_msg(motor_address,msg_v,8);
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


void motor_close(uint8_t motor_address)
{
		uint8_t msg_v[8] = {0};
		msg_v[0] = 0x80;	/* ¹¦ÄÜÂë */
		msg_v[1] = 0x00;
		msg_v[2] = 0x00;	
		msg_v[3] = 0x00;	
		msg_v[4] = 0x00;	
		msg_v[5] = 0x00;	
		msg_v[6] = 0x00;	
		msg_v[7] = 0x00;	
		
		can_send_msg(motor_address,msg_v,8);
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
 this function is used to read the params about motor

**********************************************************/	

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

 
// void read_motor_State3(uint8_t motor_address, double *state2)
//{
///**********************************************************
//		DATA[0] ÃüÁî×Ö½Ú 0x9C 
//		DATA[1] = *(uint8_t *)(&temperature) 
//		DATA[2] = *(uint8_t *)(&iq) 
//		DATA[3] = *((uint8_t *)(&iq)+1)  
//		DATA[4] = *(uint8_t *)(&speed) 
//		DATA[5] = *((uint8_t *)(&speed)+1)
//		DATA[6] = *(uint8_t *)(&encoder) 
//		DATA[7] = *((uint8_t *)(&encoder)+1) 
//**********************************************************/	
//		uint8_t msg_v[8]; 
//    uint8_t rxlen = can_receive_msg(motor_address + DEVICE_STD_ID, msg_v);
//        if (rxlen)
//        {
////						printf("\r\n already receive the msg \r\n");

//						int16_t tau = (int16_t)(msg_v[2] | (msg_v[3] << 8)); //iq
//						int16_t speed  = (int16_t)(msg_v[4] | (msg_v[5] << 8)); // speed
//						uint16_t position = (uint16_t)(msg_v[6] | (msg_v[7] << 8));  //encoder = position
//						state2[0] = (double) tau *16.5 / 2048;
//						state2[1] =  (double) speed * 360 / (1 << 16);
//						state2[2] = (double) position / 65535.0 * 360.0;
////									printf("State array for motor %d in motor_ctrl: [tau: %f, v: %f, P; %f]\n", motor_address,
////           state[0], state[1], state[2]);
//						printf("angle for motor %d is %f]\n", motor_address, state2[2]);
//				}
// }
//				
//            for (int i = 0; i < rxlen; i++)
//            {
//								usart_show_xnum(msg_v[i], rxlen);
//            }
					
//					printf("\r\n msg[0]: %x\n ,msg[1]: %x\n ,msg[2]: %x\n ,msg[3]: %x\n ,msg[4]: %x\n ,msg[5]: %x\n ,msg[6]: %x\n ,msg[7]: %x\n",
//						msg_v[0],msg_v[1],msg_v[2],msg_v[3],msg_v[4],msg_v[5],msg_v[6],msg_v[7]);
				
//		state[0]  = msg_v[1];  // temperature

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


