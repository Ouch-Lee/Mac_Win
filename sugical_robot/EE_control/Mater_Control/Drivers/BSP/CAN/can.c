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
#include "./SYSTEM/usart/usart.h"
#include "main.h"

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
 * 							now, (1,7,6,3,1)
 *
 * @param       mode    : CAN_MODE_NORMAL,  普通模式;
                          CAN_MODE_LOOPBACK,回环模式;
 * @retval      0,  初始化成功; 其他, 初始化失败;
 */
 
 void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */
	CAN_InitTypeDef		CAN1_InitConf;   // 111
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
    CAN_RX_GPIO_CLK_ENABLE();       /* CAN_RX脚时钟使能 */
    CAN_TX_GPIO_CLK_ENABLE();       /* CAN_TX脚时钟使能 */
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
  sFilterConfig.FilterBank = 0;                         /* 过滤器0 */
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;     /* 标识符屏蔽位模式 */
  sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;    /* 长度32位位宽*/
//  sFilterConfig.FilterIdHigh = 0x0000;                  /* 32位ID */
//  sFilterConfig.FilterIdLow = 0x0000;
  sFilterConfig.FilterMaskIdHigh = 0x0000;              /* 32位MASK */
  sFilterConfig.FilterMaskIdLow = 0x0000;
  sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;    /* 过滤器0关联到FIFO0 */
  sFilterConfig.FilterActivation = CAN_FILTER_ENABLE;       /* 激活滤波器0 */
  sFilterConfig.SlaveStartFilterBank = 14;
	
	if(HAL_CAN_ConfigFilter(&g_canx_handler,&sFilterConfig)!=HAL_OK)
		printf("\r\n The CAN filter config has not finished! \r\n");

	
//	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;	// Identifier mask mode
//	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
//	sFilterConfig.FilterIdHigh = (DEVICE_STD_ID) << 5;	// id
//	sFilterConfig.FilterIdLow = 0x0000;
//	sFilterConfig.FilterMaskIdHigh = 0xFC00;	// id mask	// 0xFC00
//	sFilterConfig.FilterMaskIdLow = 0x0006;
//	sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
//	sFilterConfig.FilterActivation = ENABLE;
//	sFilterConfig.FilterBank = 0;
//	if(HAL_CAN_ConfigFilter(&g_canx_handler, &sFilterConfig) != HAL_OK)
//	{

//	}	

//	/* config can filter2 */
//	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;	// Identifier mask mode
//	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
//	sFilterConfig.FilterIdHigh = (DEVICE_STD_BOARDCAST_ID) << 5;	// id
//	sFilterConfig.FilterIdLow = 0x0000;
//	sFilterConfig.FilterMaskIdHigh = 0xFFE0;	// id mask	// 0xFFE0
//	sFilterConfig.FilterMaskIdLow = 0x0006;
//	sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
//	sFilterConfig.FilterActivation = ENABLE;
//	sFilterConfig.FilterBank = 14;
//	if(HAL_CAN_ConfigFilter(&g_canx_handler, &sFilterConfig) != HAL_OK)
//	{


//	}	
//	

}


/**
 * @brief       CAN底层驱动，引脚配置，时钟配置，中断配置
                此函数会被HAL_CAN_Init()调用
 * @param       hcan:CAN句柄
 * @retval      无
 */
void CAN_Config(void)
{
	  MX_CAN1_Init();

	__HAL_CAN_ENABLE_IT(&g_canx_handler, CAN_IT_RX_FIFO0_MSG_PENDING); /* FIFO0消息挂号中断允许 */
	HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 0, 0); // USB_LP_CAN1_RX0_IRQn
	HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
	
  CAN_Filter_Config();
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
void CAN1_RX0_IRQHandler()
{
	uint8_t msg_v[8];
  uint32_t id;

  uint8_t ide, rtr, len;
	
//  
	
      // 读取FIFO 0中的消息
  if (HAL_CAN_GetRxMessage(&g_canx_handler, CAN_RX_FIFO0, &g_canx_rxheader, msg_v) == HAL_OK) {
        // 存储ID和长度到局部变量
        id = g_canx_rxheader.StdId;
        len = g_canx_rxheader.DLC;

        // 调用消息处理函数，传递局部变量
        ProcessMotorCANMessage(id, msg_v, len);

        // 清除中断标志
        __HAL_CAN_CLEAR_FLAG(&g_canx_handler, CAN_IT_RX_FIFO0_MSG_PENDING);
	}
}

void ProcessMotorCANMessage(uint32_t id, uint8_t *rxbuf, uint8_t len) {
    // 检查数据长度是否为8字节
    if (len != 8) {
        printf("Received message with incorrect length: %d bytes, ID: 0x%03X\n", len, id);
        return;
    }

    // 打印接收到的8字节数据
//    printf("Received 8 bytes for ID 0x%03X: ", id);
//    for (int i = 0; i < len; ++i) {
//        printf("%02X ", rxbuf[i]);
//    }
//    printf("\n");
		
		
		switch(rxbuf[0]){
			case 0x92:
				handle_multi_angle(id, rxbuf);
				break;
//			case 0x92:
//				hanlde_single_angle();
//				break;
//			case 0xA1:
//				handle_state_2();
//				break;
				
		}
}

/* 下面几个函数都是CAN接收到不同的返回帧后的处理函数 */

void handle_multi_angle(uint32_t id, uint8_t *rxbuf) {
    // 从rxbuf中解析出motorAngle
    uint64_t tempMotorAngle = 0;
    for (int i = 1; i <= 7; ++i) {  // 正确的范围应该是1到7
        tempMotorAngle |= (uint64_t)(rxbuf[i]) << (8 * (i - 1));
    }

    // 处理符号扩展
    int64_t motorAngle;
    if (tempMotorAngle & (1ULL << 55)) { // 如果第55位（最高有效数据位）为1，表示负数
        motorAngle = tempMotorAngle | 0xFF00000000000000ULL; // 符号扩展
    } else {
        motorAngle = tempMotorAngle;
    }

    // 由于角度数据是int64_t类型，我们需要将其转换为实际的角度值（单位为度）
    // 由于单位是0.01°/LSB，所以需要乘以0.01来转换为度
    float angle_in_degrees = motorAngle * 0.01;

    // 存储到received_data数组中
    // 检查id是否在有效范围内，避免数组越界
    if (id >= DEVICE_STD_ID + 1 && id < DEVICE_STD_ID + 1 + MAX_DEVICES) {
        received_data[id - DEVICE_STD_ID - 1] = angle_in_degrees;
    } else {
        printf("Error: Invalid ID received.\n");
    }

    // 打印角度值以供检查（可选）
//    printf("Motor angle for ID 0x%03X: %f degrees\n", id, angle_in_degrees);
}



/* 上面几个函数都是CAN接收到不同的返回帧后的处理函数 */


#endif



/**
 * @brief       CAN 发送一组数据
 *   @note      发送格式固定为: 标准ID, 数据帧
 * @param       id      : 标准ID(11位)
 * @retval      发送状态 0, 成功; 1, 失败;
 */
uint8_t can_send_msg(uint32_t id, uint8_t *msg, uint8_t len)
{
    uint32_t TxMailbox = CAN_TX_MAILBOX0;
    g_canx_txheader.StdId = id;         /* 标准标识符 */ //
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
uint8_t can_receive_msg(uint32_t id, uint8_t *buf)
{
	g_canx_rxheader.StdId = id;         /* 标准标识稤EVICE_STD_ID +� */
  g_canx_rxheader.ExtId = 0x00;         /* 扩展标识符(29位) 标准标识符情况下，该成员无效*/
  g_canx_rxheader.IDE = CAN_ID_STD;   /* 使用标准标识符 */
  g_canx_rxheader.RTR = CAN_RTR_DATA; /* 数据帧 */
  g_canx_rxheader.DLC = 8;
	
  if (HAL_CAN_GetRxFifoFillLevel(&g_canx_handler, CAN_RX_FIFO0) == 0)     /* 没有接收到数据 */
  {
//		printf("%i", 6657);
//		printf("\n");
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
