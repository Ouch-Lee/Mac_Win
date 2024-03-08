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
	������ؿ��ƺ���
	�����ֱ�Ϊ�������ַ �� Ť�ص���ֵ
	���У�
	Ť�ص���ֵ��ΧΪ��65536-2048 ~ 2048�� ԭ�����£�
	���ת�ص���ֵiq ��int16_t���ͣ���Χ-2048~2048����Ӧʵ��ת�ص�����Χ-33A~33A��
**********************************************************/	
		//��iqvalueֵת��Ϊuint16_t��ֵ
		uint16_t IQ = 0;	//���͸�����Ĳ���
		if (iqValue < 0) {
				IQ = 65536 - (uint16_t)(-iqValue);
		} else {
				IQ = (uint16_t)iqValue;
		}
	
		uint8_t msg_v[8] = {0};
		msg_v[0] = 0xA1;	/* ������ */
		msg_v[1] = 0x00;
		msg_v[2] = 0x00;	
		msg_v[3] = 0x00;	
		msg_v[4] = *((uint8_t *)&IQ );	/* ���ֽ� */
		msg_v[5] = *((uint8_t *)&IQ + 1);	/*���ֽ�*/
		msg_v[6] = 0x00;
		msg_v[7] = 0x00;
		
    can_send_msg(motor_address,msg_v,8);
}



void motor_close(uint8_t motor_address)
{
		uint8_t msg_v[8] = {0};
		msg_v[0] = 0x80;	/* ������ */
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
		msg_v[0] = 0x81;	/* ������ */
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
		msg_v[0] = 0x88;	/* ������ */
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
��ȡ���ٶȣ�
	�����ظ�(1 ֡)��
	���ٶ�����AccelerateΪint32_t���ͣ���λ1dps/s ��

		DATA[0] �����ֽ� 0x33 
		DATA[1] NULL 0x00 
		DATA[2] NULL 0x00 
		DATA[3] NULL 0x00 
		DATA[4] ���ٶ��ֽ� 1 DATA[4] = *(uint8_t *)(&Accel) 
		DATA[5] ���ٶ��ֽ� 2 DATA[5] = *((uint8_t *)(&Accel)+1) 
		DATA[6] ���ٶ��ֽ� 3 DATA[6] = *((uint8_t *)(&Accel)+2) 
		DATA[7] ���ٶ��ֽ� 4 DATA[7] = *((uint8_t *)(&Accel)+3)
**********************************************************/	
		
	
		uint8_t msg_v[8] = {0}; 
		msg_v[0] = 0x33;	/* �����ֽ� */
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
��ȡ���ٶȣ�
	�����ظ�(1 ֡)��
	����ܵ�����ظ���������֡���ݰ������²�����	
		1.����¶� temperature ��int8_t���ͣ�
		2.���ת�ص���ֵiq ��int16_t���ͣ���Χ-2048~2048����Ӧʵ��ת�ص�����Χ-33A~33A��
	  3.���ת��speed ��int16_t���� �� 1dps/LSB�� ����Ҫ��ʵת�٣�����Ҫ����1��10�ļ�����������Ӱ��
		4.������λ��ֵ

		DATA[0] �����ֽ� 0x9C 
		DATA[1] = *(uint8_t *)(&temperature) 
		DATA[2] = *(uint8_t *)(&iq) 
		DATA[3] = *((uint8_t *)(&iq)+1)  
		DATA[4] = *(uint8_t *)(&speed) 
		DATA[5] = *((uint8_t *)(&speed)+1)
		DATA[6] = *(uint8_t *)(&encoder) 
		DATA[7] = *((uint8_t *)(&encoder)+1) 
**********************************************************/	

		uint8_t msg_v[8] = {0}; 
		msg_v[0] = 0x9C;	/* �����ֽ� */
		msg_v[1] = 0x00;
		msg_v[2] = 0x00;	
		msg_v[3] = 0x00;	
		msg_v[4] = 0x00;	
		msg_v[5] = 0x00;	
		msg_v[6] = 0x00;	
		msg_v[7] = 0x00;	
    can_send_msg(motor_address,msg_v,8);	
}
