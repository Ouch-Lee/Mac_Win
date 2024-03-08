/**
 ****************************************************************************************************
 * @file        can.h
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2021-10-25
 * @brief       CAN ��������
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� ̽���� F407������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 * �޸�˵��
 * V1.0 20211025
 * ��һ�η���
 *
 ****************************************************************************************************
 */

#ifndef __CAN_H
#define __CAN_H

#include "./SYSTEM/sys/sys.h"


/******************************************************************************************/
/* CAN ���� ���� */
typedef struct {
  uint16_t COB_ID;	/**< message's ID */
  uint8_t RTR;		/**< remote transmission request��Զ�˴�������. (0 if not remote request message, 1 if remote request message) */
  uint8_t len;		/**< message's length (0 to 8) */
  uint8_t Data[8]; /**< message's datas */
} Message;

#define CAN_CLK_ENABLE()         		__HAL_RCC_CAN1_CLK_ENABLE();
#define CAN_RX_GPIO_PORT                GPIOA
#define CAN_RX_GPIO_PIN                 GPIO_PIN_11
#define CAN_RX_GPIO_CLK_ENABLE()        do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)     /* PA��ʱ��ʹ�� */

#define CAN_TX_GPIO_PORT                GPIOA
#define CAN_TX_GPIO_PIN                 GPIO_PIN_12
#define CAN_TX_GPIO_CLK_ENABLE()        do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)     /* PA��ʱ��ʹ�� */

#define DEVICE_STD_ID						(0x140)
#define DEVICE_STD_BOARDCAST_ID	(0x280)
typedef  CAN_TxHeaderTypeDef CANTxMsg;
typedef  CAN_RxHeaderTypeDef CANRxMsg;
/******************************************************************************************/

/* USER CODE BEGIN Private defines */
extern uint8_t canTxData[];
extern uint8_t canRxData[];


extern uint16_t encoderValue;
/* USER CODE END Private defines */


/* CAN����RX0�ж�ʹ�� */
#define CAN_RX0_INT_ENABLE              0                                              /* 0,��ʹ��; 1,ʹ��; */

/* ����ӿں��� */
void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle);
void CAN_Filter_Config();
uint8_t can_receive_msg(uint32_t id, uint8_t *buf);                                     /* CAN��������, ��ѯ */
uint8_t can_send_msg(uint32_t id, uint8_t *msg, uint8_t len);                           /* CAN�������� */
uint8_t can_init(uint32_t tsjw,uint32_t tbs2,uint32_t tbs1,uint16_t brp,uint32_t mode); /* CAN��ʼ�� */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan);
void HAL_CAN_MspInit(CAN_HandleTypeDef *hcan);
void Error_Handler(void);
void CAN_Config(void);
void CAN1_RX0_IRQHandler();
#endif








