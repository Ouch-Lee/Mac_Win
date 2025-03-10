/**
 ****************************************************************************************************
 * @file        can.h
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2021-10-25
 * @brief       CAN 驱动代码
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 探索者 F407开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 * 修改说明
 * V1.0 20211025
 * 第一次发布
 *
 ****************************************************************************************************
 */

#ifndef __CAN_H
#define __CAN_H

#include "./SYSTEM/sys/sys.h"


/******************************************************************************************/
/* CAN 引脚 定义 */

#define CAN_RX_GPIO_PORT                GPIOA
#define CAN_RX_GPIO_PIN                 GPIO_PIN_11
#define CAN_RX_GPIO_CLK_ENABLE()        do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)     /* PA口时钟使能 */

#define CAN_TX_GPIO_PORT                GPIOA
#define CAN_TX_GPIO_PIN                 GPIO_PIN_12
#define CAN_TX_GPIO_CLK_ENABLE()        do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)     /* PA口时钟使能 */

#define DEVICE_STD_ID						(0x140)
#define DEVICE_STD_BOARDCAST_ID	(0x280)

/******************************************************************************************/

/* USER CODE BEGIN Private defines */
extern uint8_t canTxData[];
extern uint8_t canRxData[];
extern uint8_t start_motor[];
extern uint8_t close_motor[];
extern uint8_t stop_motor[];
extern uint8_t close_motor[];
extern uint8_t torque_control[];
extern uint8_t torque_control_1[];
extern uint8_t torque_control_2[];
extern uint16_t encoderValue;
/* USER CODE END Private defines */


/* CAN接收RX0中断使能 */
#define CAN_RX0_INT_ENABLE              0                                              /* 0,不使能; 1,使能; */

/* 对外接口函数 */
uint8_t can_receive_msg(uint32_t id, uint8_t *buf);                                     /* CAN接收数据, 查询 */
uint8_t can_send_msg(uint32_t id, uint8_t *msg, uint8_t len);                           /* CAN发送数据 */
uint8_t can_init(uint32_t tsjw,uint32_t tbs2,uint32_t tbs1,uint16_t brp,uint32_t mode); /* CAN初始化 */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan);
void Error_Handler(void);
#endif








