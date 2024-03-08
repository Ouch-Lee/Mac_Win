#include "./SYSTEM/sys/sys.h"
//#include "./SYSTEM/usart/usart.h"
//#include "./SYSTEM/delay/delay.h"
//#include "./USMART/usmart.h"
#include "./BSP/CAN/can.h"
//#include "./BSP/TIMER/btim.h"
//#include "demo.h"
//#include "./BSP/ATK_MS901M/atk_ms901m.h"
# include <stdio.h>
# include <stdlib.h>



void motor_torque_control(uint8_t motor_address,double iqValue)
{
/**********************************************************
	电机力矩控制函数
	参数分别为：电机地址 、 扭矩电流值
	其中：
	扭矩电流值范围为（65536-2048 ~ 2048） 原因如下：
	电机转矩电流值iq （int16_t类型，范围-2048~2048，对应实际转矩电流范围-33A~33A）
**********************************************************/	
		//将iqvalue值转化为uint16_t的值
		uint16_t IQ = 0;	//发送给电机的参数
		if (iqValue < 0) {
				IQ = 65536 - (uint16_t)(-iqValue);
		} else {
				IQ = (uint16_t)iqValue;
		}
	
		uint8_t msg_v[8] = {0};
		msg_v[0] = 0xA1;	/* 功能码 */
		msg_v[1] = 0x00;
		msg_v[2] = 0x00;	
		msg_v[3] = 0x00;	
		msg_v[4] = *((uint8_t *)&IQ );	/* 低字节 */
		msg_v[5] = *((uint8_t *)&IQ + 1);	/*高字节*/
		msg_v[6] = 0x00;
		msg_v[7] = 0x00;
		
    can_send_msg(motor_address,msg_v,8);
}



void motor_close(uint8_t motor_address)
{
		uint8_t msg_v[8] = {0};
		msg_v[0] = 0x80;	/* 功能码 */
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
		msg_v[0] = 0x81;	/* 功能码 */
		msg_v[1] = 0x00;
		msg_v[2] = 0x00;	
		msg_v[3] = 0x00;	
		msg_v[4] = 0x00;	
		msg_v[5] = 0x00;	
		msg_v[6] = 0x00;	
		msg_v[7] = 0x00;	
		
    can_send_msg(motor_address,msg_v,8);
}


void start_motor(uint8_t motor_address)
{
		uint8_t msg_v[8] = {0};
		msg_v[0] = 0x88;	/* 功能码 */
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
获取加速度：
	驱动回复(1 帧)：
	加速度数据Accelerate为int32_t类型，单位1dps/s ：

		DATA[0] 命令字节 0x33 
		DATA[1] NULL 0x00 
		DATA[2] NULL 0x00 
		DATA[3] NULL 0x00 
		DATA[4] 加速度字节 1 DATA[4] = *(uint8_t *)(&Accel) 
		DATA[5] 加速度字节 2 DATA[5] = *((uint8_t *)(&Accel)+1) 
		DATA[6] 加速度字节 3 DATA[6] = *((uint8_t *)(&Accel)+2) 
		DATA[7] 加速度字节 4 DATA[7] = *((uint8_t *)(&Accel)+3)
**********************************************************/	
		
	
		uint8_t msg_v[8] = {0}; 
		msg_v[0] = 0x33;	/* 命令字节 */
		msg_v[1] = 0x00;
		msg_v[2] = 0x00;	
		msg_v[3] = 0x00;	
		msg_v[4] = 0x00;	
		msg_v[5] = 0x00;	
		msg_v[6] = 0x00;	
		msg_v[7] = 0x00;	
    can_send_msg(motor_address,msg_v,8);	
}
void read_motor_State2(uint8_t motor_address)
{
/**********************************************************
获取加速度：
	驱动回复(1 帧)：
	电机受到命令回复主机，该帧数据包含以下参数：	
		1.电机温度 temperature （int8_t类型）
		2.电机转矩电流值iq （int16_t类型，范围-2048~2048，对应实际转矩电流范围-33A~33A）
	  3.电机转速speed （int16_t类型 ， 1dps/LSB） 如需要真实转速，还需要考虑1：10的减速器带来的影响
		4.编码器位置值

		DATA[0] 命令字节 0x9C 
		DATA[1] = *(uint8_t *)(&temperature) 
		DATA[2] = *(uint8_t *)(&iq) 
		DATA[3] = *((uint8_t *)(&iq)+1)  
		DATA[4] = *(uint8_t *)(&speed) 
		DATA[5] = *((uint8_t *)(&speed)+1)
		DATA[6] = *(uint8_t *)(&encoder) 
		DATA[7] = *((uint8_t *)(&encoder)+1) 
**********************************************************/	

		uint8_t msg_v[8] = {0}; 
		msg_v[0] = 0x9C;	/* 命令字节 */
		msg_v[1] = 0x00;
		msg_v[2] = 0x00;	
		msg_v[3] = 0x00;	
		msg_v[4] = 0x00;	
		msg_v[5] = 0x00;	
		msg_v[6] = 0x00;	
		msg_v[7] = 0x00;	
    can_send_msg(motor_address,msg_v,8);	
}
