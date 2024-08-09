/**
 ****************************************************************************************************
 * @file        can.c
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

#include "./BSP/CAN/can.h"
#include "./BSP/LED/led.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"

/* USER CODE BEGIN 0 */
uint8_t canTxData[8];
uint8_t canRxData[8];
uint16_t encoderValue = 0;
int32_t IQ;
/* USER CODE END 0 */


CAN_HandleTypeDef   g_canx_handler;     /* CANx句柄 */
CAN_TxHeaderTypeDef g_canx_txheader;    /* 发送参数句柄 */
CAN_RxHeaderTypeDef g_canx_rxheader;    /* 接收参数句柄 */

/**
 * @brief       CAN初始化
 * @param       tsjw    : 重新同步跳跃时间单元.范围: 1~3;
 * @param       tbs2    : 时间段2的时间单元.范围: 1~8;
 * @param       tbs1    : 时间段1的时间单元.范围: 1~16;
 * @param       brp     : 波特率分频器.范围: 1~1024;
 *   @note      以上4个参数, 在函数内部会减1, 所以, 任何一个参数都不能等于0
 *              CAN挂在APB1上面, 其输入时钟频率为 Fpclk1 = PCLK1 = 42Mhz
 *              tq     = brp * tpclk1;
 *              波特率 = Fpclk1 / ((tbs1 + tbs2 + 1) * brp);
 *              我们设置 can_init(1, 6, 7, 6, 1), 则CAN波特率为:
 *              42M / ((6 + 7 + 1) * 6) = 500Kbps
 *
 * @param       mode    : CAN_MODE_NORMAL,  普通模式;
                          CAN_MODE_LOOPBACK,回环模式;
 * @retval      0,  初始化成功; 其他, 初始化失败;
 */
 
 void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */
	CAN_InitTypeDef		CAN1_InitConf;
  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  g_canx_handler.Instance = CAN1;
	g_canx_handler.Init = CAN1_InitConf;
  g_canx_handler.Init.Prescaler = 3;
  g_canx_handler.Init.Mode = CAN_MODE_NORMAL;
  g_canx_handler.Init.SyncJumpWidth = CAN_SJW_1TQ;
  g_canx_handler.Init.TimeSeg1 = CAN_BS1_7TQ;
  g_canx_handler.Init.TimeSeg2 = CAN_BS2_6TQ;
  g_canx_handler.Init.TimeTriggeredMode = DISABLE;
  g_canx_handler.Init.AutoBusOff = DISABLE;
  g_canx_handler.Init.AutoWakeUp = DISABLE;
  g_canx_handler.Init.AutoRetransmission = ENABLE;	
  g_canx_handler.Init.ReceiveFifoLocked = DISABLE;
  g_canx_handler.Init.TransmitFifoPriority = DISABLE;
	HAL_CAN_Init(&g_canx_handler);
	
	
  /* USER CODE BEGIN CAN1_Init 2 */
  /* USER CODE END CAN1_Init 2 */

}

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspInit 0 */
//    CAN_RX_GPIO_CLK_ENABLE();       /* CAN_RX脚时钟使能 */
//    CAN_TX_GPIO_CLK_ENABLE();       /* CAN_TX脚时钟使能 */
  /* USER CODE END CAN1_MspInit 0 */
    /* CAN1 clock enable */
    __HAL_RCC_CAN1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**CAN1 GPIO Configuration
    PA11     ------> CAN1_RX
    PA12     ------> CAN1_TX
    */
    GPIO_InitStruct.Pin =CAN_RX_GPIO_PIN|CAN_TX_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;              //上拉
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;         //快速
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  }
}

/* USER CODE BEGIN 1 */

/*
 * 函数名：CAN_Filter_Config
 * 描述  ：CAN的过滤器 配置
 * 调用  ：内部调用
 */
void CAN_Filter_Config()
{	
	/*config later*/
	CAN_FilterTypeDef sFilterConfig;
	
//  /*配置CAN过滤器*/
//  sFilterConfig.FilterBank = 0;                         /* 过滤器0 */
//  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;     /* 标识符屏蔽位模式 */
//  sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;    /* 长度32位位宽*/
//  sFilterConfig.FilterIdHigh = (DEVICE_STD_ID) << 5;                  /* 32位ID */
//  sFilterConfig.FilterIdLow = 0x0000;
//  sFilterConfig.FilterMaskIdHigh = 0xFC00;              /* 32位MASK */
//  sFilterConfig.FilterMaskIdLow = 0x0006;
//  sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;    /* 过滤器0关联到FIFO0 */
//  sFilterConfig.FilterActivation = CAN_FILTER_ENABLE;       /* 激活滤波器0 */
//  sFilterConfig.SlaveStartFilterBank = 0;
//	
//	if(HAL_CAN_ConfigFilter(&g_canx_handler,&sFilterConfig)!=HAL_OK)
//		println_str(&UART1_Handler,"The CAN filter config has not finished!");	
	
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;	// Identifier mask mode
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	sFilterConfig.FilterIdHigh = (DEVICE_STD_ID) << 5;	// id
	sFilterConfig.FilterIdLow = 0x0000;
	sFilterConfig.FilterMaskIdHigh = 0xFC00;	// id mask	// 0xFC00
	sFilterConfig.FilterMaskIdLow = 0x0006;
	sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
	sFilterConfig.FilterActivation = ENABLE;
	sFilterConfig.FilterBank = 0;
	if(HAL_CAN_ConfigFilter(&g_canx_handler, &sFilterConfig) != HAL_OK)
	{

	}	

	/* config can filter2 */
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;	// Identifier mask mode
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	sFilterConfig.FilterIdHigh = (DEVICE_STD_BOARDCAST_ID) << 5;	// id
	sFilterConfig.FilterIdLow = 0x0000;
	sFilterConfig.FilterMaskIdHigh = 0xFFE0;	// id mask	// 0xFFE0
	sFilterConfig.FilterMaskIdLow = 0x0006;
	sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
	sFilterConfig.FilterActivation = ENABLE;
	sFilterConfig.FilterBank = 14;
	if(HAL_CAN_ConfigFilter(&g_canx_handler, &sFilterConfig) != HAL_OK)
	{


	}	
	

}


/**
 * @brief       CAN底层驱动，引脚配置，时钟配置，中断配置
                此函数会被HAL_CAN_Init()调用
 * @param       hcan:CAN句柄
 * @retval      无
 */
void CAN_Config(void)
{
//  can_init(CAN_SJW_1TQ, CAN_BS2_6TQ, CAN_BS1_7TQ, 3, CAN_MODE_LOOPBACK);  /* CAN初始化, 环回模式, 波特率500Kbps */
	  MX_CAN1_Init();
	
	__HAL_CAN_ENABLE_IT(&g_canx_handler, CAN_IT_RX_FIFO0_MSG_PENDING); /* FIFO0消息挂号中断允许 */
	HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
	
  CAN_Filter_Config();
//	__HAL_CAN_ENABLE_IT(&g_canx_handler, CAN_IT_RX_FIFO0_MSG_PENDING); /* FIFO0消息挂号中断允许 */
//	HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 0, 0);
//	HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
//	
	/*##-3- Start the CAN peripheral ###########################################*/
	if(HAL_CAN_Start(&g_canx_handler)!=HAL_OK)//！！！一定要打开can外设，不打开can收发就处于关闭状态
	{	
	printf("\r\n The CAN peripheral has not started! \r\n");
	}
//		println_str(&UART1_Handler,"The CAN peripheral has not started!");	

  /*##-4- Activate CAN RX notification 开中断#######################################*/
	if(HAL_CAN_ActivateNotification(&g_canx_handler, CAN_IT_RX_FIFO0_MSG_PENDING)!=HAL_OK)
	{
		printf("\r\n CAN RX0 notification has not opened! \r\n");
//		println_str(&UART1_Handler,"CAN RX0 notification has not opened!");	
	}
//	if(HAL_CAN_ActivateNotification(&g_canx_handler, CAN_IT_RX_FIFO1_MSG_PENDING)!=HAL_OK)
//		println_str(&UART1_Handler,"CAN RX1 notification has not opened!");	
}

#if CAN_RX0_INT_ENABLE /* 使能RX0中断 */

/**
 * @brief       CAN RX0 中断服务函数
 *   @note      处理CAN FIFO0的接收中断
 * @param       无
 * @retval      无
 */
void USB_LP_CAN1_RX0_IRQHandler(void)
{
    uint8_t rxbuf[8];
    uint32_t id;
    can_receive_msg(id, rxbuf);
    printf("id:%d\r\n", g_canx_rxheader.StdId);
    printf("ide:%d\r\n", g_canx_rxheader.IDE);
    printf("rtr:%d\r\n", g_canx_rxheader.RTR);
    printf("len:%d\r\n", g_canx_rxheader.DLC);

    printf("rxbuf[0]:%d\r\n", rxbuf[0]);
    printf("rxbuf[1]:%d\r\n", rxbuf[1]);
    printf("rxbuf[2]:%d\r\n", rxbuf[2]);
    printf("rxbuf[3]:%d\r\n", rxbuf[3]);
    printf("rxbuf[4]:%d\r\n", rxbuf[4]);
    printf("rxbuf[5]:%d\r\n", rxbuf[5]);
    printf("rxbuf[6]:%d\r\n", rxbuf[6]);
    printf("rxbuf[7]:%d\r\n", rxbuf[7]);
}

#endif

void CAN1_RX0_IRQHandler()
{
	uint8_t rxbuf[8];
  uint32_t id;
	uint16_t TH = 65535; //反转阈值用来将获取到的参数修正为负数
  uint16_t iq;		//力矩电流
  uint16_t speed; //速度
	int32_t Speed;
	
  uint8_t ide, rtr, len;
	
//  
	
  can_receive_msg(id, rxbuf);
  
	
	if(rxbuf[0] == 0x9C){
		iq =(uint16_t)(((uint8_t)rxbuf[3]<<8)
									|((uint8_t)rxbuf[2]<<0));
		if(iq > 60000) {
			IQ = -(TH-iq);
			printf("{motorTnfo}%d",IQ);
			printf(",");
		}else{
			IQ = iq;
			printf("{motorTnfo}%d",iq);
			printf(",");
		}

	//	printf("%d",iq);
	//	printf(",");
		
		speed =(uint16_t)(((uint8_t)rxbuf[5]<<8)
										 |((uint8_t)rxbuf[4]<<0));
		if(speed > 60000) {
			Speed = -(TH-speed);
			printf("%d",Speed);
			printf("\n");
		}else{
			printf("%d",speed);
			printf("\n");
		}
	}
}


/**
 * @brief       CAN 发送一组数据
 *   @note      发送格式固定为: 标准ID, 数据帧
 * @param       id      : 标准ID(11位)
 * @retval      发送状态 0, 成功; 1, 失败;
 */
uint8_t can_send_msg(uint32_t id, uint8_t *msg, uint8_t len)
{
    uint32_t TxMailbox = CAN_TX_MAILBOX0;
    g_canx_txheader.StdId = DEVICE_STD_ID + id;         /* 标准标识符 */ //
    g_canx_txheader.ExtId = 0x00;         /* 扩展标识符(29位) */
    g_canx_txheader.IDE = CAN_ID_STD;   /* 使用标准帧 */
    g_canx_txheader.RTR = CAN_RTR_DATA; /* 数据帧 */
    g_canx_txheader.DLC = len;

    if (HAL_CAN_AddTxMessage(&g_canx_handler, &g_canx_txheader, msg, &TxMailbox) != HAL_OK) /* 发送消息 */
    {
        return 1;
    }
    while (HAL_CAN_GetTxMailboxesFreeLevel(&g_canx_handler) != 3); /* 等待发送完成,所有邮箱为空 */
    return 0;
}

/**
 * @brief       CAN 接收数据查询
 *   @note      接收数据格式固定为: 标准ID, 数据帧
 * @param       id      : 要查询的 标准ID(11位)
 * @param       buf     : 数据缓存区
 * @retval      接收结果
 *   @arg       0   , 无数据被接收到;
 *   @arg       其他, 接收的数据长度
 */
//uint8_t can_receive_msg(uint32_t id, uint8_t *buf)
//{
//	g_canx_rxheader.StdId = DEVICE_STD_ID + id;         /* 标准标识符 */
//  g_canx_rxheader.ExtId = 0x00;         /* 扩展标识符(29位) 标准标识符情况下，该成员无效*/
//  g_canx_rxheader.IDE = CAN_ID_STD;   /* 使用标准标识符 */
//  g_canx_rxheader.RTR = CAN_RTR_DATA; /* 数据帧 */
//  g_canx_rxheader.DLC = 8;
//	
//  if (HAL_CAN_GetRxFifoFillLevel(&g_canx_handler, CAN_RX_FIFO0) == 0)     /* 没有接收到数据 */
//  {
////		printf("%i", 6657);
////		printf("\n");
//    return 0;
//  }

//  if (HAL_CAN_GetRxMessage(&g_canx_handler, CAN_RX_FIFO0, &g_canx_rxheader, buf) != HAL_OK)  /* 读取数据 */
//  {

//		return 0;
//  }
//  
//  if (g_canx_rxheader.StdId!= id + DEVICE_STD_ID || g_canx_rxheader.IDE != CAN_ID_STD || g_canx_rxheader.RTR != CAN_RTR_DATA)       /* 接收到的ID不对 / 不是标准帧 / 不是数据帧 */
//  {
//    return 0;    
//  }

//  return g_canx_rxheader.DLC;
//}

uint8_t can_receive_msg(uint32_t id, uint8_t *buf)
{
    if (HAL_CAN_GetRxFifoFillLevel(&g_canx_handler, CAN_RX_FIFO0) == 0)     /* 没有接收到数据 */
    {
        return 0;
    }

    if (HAL_CAN_GetRxMessage(&g_canx_handler, CAN_RX_FIFO0, &g_canx_rxheader, buf) != HAL_OK)  /* 读取数据 */
    {
        return 0;
    }

    if (g_canx_rxheader.StdId!= id || g_canx_rxheader.IDE != CAN_ID_STD || g_canx_rxheader.RTR != CAN_RTR_DATA)       /* 接收到的ID不对 / 不是标准帧 / 不是数据帧 */
    {
        return 0;    
    }

    return g_canx_rxheader.DLC;

}
/*********************************************************************************
* @brief	HAL_CAN_RxFifo0MsgPendingCallback, called in can interrupt
* @param	None
* @retval	None
*********************************************************************************/
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
  /* Get RX message */
  if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &g_canx_rxheader, canRxData) != HAL_OK)
  {
    /* Reception Error */
    Error_Handler();
  }


  if ((g_canx_rxheader.StdId == (DEVICE_STD_ID + 1)) && (g_canx_rxheader.DLC == 8))
  {
		/* get encoder value */
		encoderValue = (canRxData[7] << 8) + canRxData[6];
		printf("\r\n the value: %d  \r\n", encoderValue);
//		LED1_TOGGLE();
  }
}

void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
