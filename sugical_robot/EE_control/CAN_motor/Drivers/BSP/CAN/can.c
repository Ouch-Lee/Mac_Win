/**
 ****************************************************************************************************
 * @file        can.c
 * @author      ÕýµãÔ­×ÓÍÅ¶Ó(ALIENTEK)
 * @version     V1.0
 * @date        2021-10-25
 * @brief       CAN Çý¶¯´úÂë
 * @license     Copyright (c) 2020-2032, ¹ãÖÝÊÐÐÇÒíµç×Ó¿Æ¼¼ÓÐÏÞ¹«Ë¾
 ****************************************************************************************************
 * @attention
 *
 * ÊµÑéÆ½Ì¨:ÕýµãÔ­×Ó Ì½Ë÷Õß F407¿ª·¢°å
 * ÔÚÏßÊÓÆµ:www.yuanzige.com
 * ¼¼ÊõÂÛÌ³:www.openedv.com
 * ¹«Ë¾ÍøÖ·:www.alientek.com
 * ¹ºÂòµØÖ·:openedv.taobao.com
 *
 * ÐÞ¸ÄËµÃ÷
 * V1.0 20211025
 * µÚÒ»´Î·¢²¼
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


CAN_HandleTypeDef   g_canx_handler;     /* CANx¾ä±ú */
CAN_TxHeaderTypeDef g_canx_txheader;    /* ·¢ËÍ²ÎÊý¾ä±ú */
CAN_RxHeaderTypeDef g_canx_rxheader;    /* ½ÓÊÕ²ÎÊý¾ä±ú */

/**
 * @brief       CAN³õÊ¼»¯
 * @param       tsjw    : ÖØÐÂÍ¬²½ÌøÔ¾Ê±¼äµ¥Ôª.·¶Î§: 1~3;
 * @param       tbs2    : Ê±¼ä¶Î2µÄÊ±¼äµ¥Ôª.·¶Î§: 1~8;
 * @param       tbs1    : Ê±¼ä¶Î1µÄÊ±¼äµ¥Ôª.·¶Î§: 1~16;
 * @param       brp     : ²¨ÌØÂÊ·ÖÆµÆ÷.·¶Î§: 1~1024;
 *   @note      ÒÔÉÏ4¸ö²ÎÊý, ÔÚº¯ÊýÄÚ²¿»á¼õ1, ËùÒÔ, ÈÎºÎÒ»¸ö²ÎÊý¶¼²»ÄÜµÈÓÚ0
 *              CAN¹ÒÔÚAPB1ÉÏÃæ, ÆäÊäÈëÊ±ÖÓÆµÂÊÎª Fpclk1 = PCLK1 = 42Mhz
 *              tq     = brp * tpclk1;
 *              ²¨ÌØÂÊ = Fpclk1 / ((tbs1 + tbs2 + 1) * brp);
 *              ÎÒÃÇÉèÖÃ can_init(1, 6, 7, 6, 1), ÔòCAN²¨ÌØÂÊÎª:
 *              42M / ((6 + 7 + 1) * 6) = 500Kbps
 * 							now, (1,7,6,3,1)
 *
 * @param       mode    : CAN_MODE_NORMAL,  ÆÕÍ¨Ä£Ê½;
                          CAN_MODE_LOOPBACK,»Ø»·Ä£Ê½;
 * @retval      0,  ³õÊ¼»¯³É¹¦; ÆäËû, ³õÊ¼»¯Ê§°Ü;
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
    CAN_RX_GPIO_CLK_ENABLE();       /* CAN_RX½ÅÊ±ÖÓÊ¹ÄÜ */
    CAN_TX_GPIO_CLK_ENABLE();       /* CAN_TX½ÅÊ±ÖÓÊ¹ÄÜ */
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
    GPIO_InitStruct.Pull = GPIO_PULLUP;              //ÉÏÀ­
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;         //¿ìËÙ
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  }
}

/* USER CODE BEGIN 1 */

/*
 * º¯ÊýÃû£ºCAN_Filter_Config
 * ÃèÊö  £ºCANµÄ¹ýÂËÆ÷ ÅäÖÃ
 * µ÷ÓÃ  £ºÄÚ²¿µ÷ÓÃ
 */
void CAN_Filter_Config()
{	
	/*config later*/
	CAN_FilterTypeDef sFilterConfig;
	
//  /*ÅäÖÃCAN¹ýÂËÆ÷*/
  sFilterConfig.FilterBank = 0;                         /* ¹ýÂËÆ÷0 */
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;     /* ±êÊ¶·ûÆÁ±ÎÎ»Ä£Ê½ */
  sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;    /* ³¤¶È32Î»Î»¿í*/
//  sFilterConfig.FilterIdHigh = 0x0000;                  /* 32Î»ID */
//  sFilterConfig.FilterIdLow = 0x0000;
  sFilterConfig.FilterMaskIdHigh = 0x0000;              /* 32Î»MASK */
  sFilterConfig.FilterMaskIdLow = 0x0000;
  sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;    /* ¹ýÂËÆ÷0¹ØÁªµ½FIFO0 */
  sFilterConfig.FilterActivation = CAN_FILTER_ENABLE;       /* ¼¤»îÂË²¨Æ÷0 */
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
 * @brief       CANµ×²ãÇý¶¯£¬Òý½ÅÅäÖÃ£¬Ê±ÖÓÅäÖÃ£¬ÖÐ¶ÏÅäÖÃ
                ´Ëº¯Êý»á±»HAL_CAN_Init()µ÷ÓÃ
 * @param       hcan:CAN¾ä±ú
 * @retval      ÎÞ
 */
void CAN_Config(void)
{
	  MX_CAN1_Init();

	__HAL_CAN_ENABLE_IT(&g_canx_handler, CAN_IT_RX_FIFO0_MSG_PENDING); /* FIFO0ÏûÏ¢¹ÒºÅÖÐ¶ÏÔÊÐí */
	HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 0, 0); // USB_LP_CAN1_RX0_IRQn
	HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
	
  CAN_Filter_Config();
//	
	/*##-3- Start the CAN peripheral ###########################################*/
	if(HAL_CAN_Start(&g_canx_handler)!=HAL_OK)//£¡£¡£¡Ò»¶¨Òª´ò¿ªcanÍâÉè£¬²»´ò¿ªcanÊÕ·¢¾Í´¦ÓÚ¹Ø±Õ×´Ì¬
	{	
	printf("\r\n The CAN peripheral has not started! \r\n");
	}
//		println_str(&UART1_Handler,"The CAN peripheral has not started!");	

  /*##-4- Activate CAN RX notification ¿ªÖÐ¶Ï#######################################*/
	if(HAL_CAN_ActivateNotification(&g_canx_handler, CAN_IT_RX_FIFO0_MSG_PENDING)!=HAL_OK)
	{
		printf("\r\n CAN RX0 notification has not opened! \r\n");
//		println_str(&UART1_Handler,"CAN RX0 notification has not opened!");	
	}
//	if(HAL_CAN_ActivateNotification(&g_canx_handler, CAN_IT_RX_FIFO1_MSG_PENDING)!=HAL_OK)
//		println_str(&UART1_Handler,"CAN RX1 notification has not opened!");	
}

#if CAN_RX0_INT_ENABLE /* Ê¹ÄÜRX0ÖÐ¶Ï */

/**
 * @brief       CAN RX0 ÖÐ¶Ï·þÎñº¯Êý
 *   @note      ´¦ÀíCAN FIFO0µÄ½ÓÊÕÖÐ¶Ï
 * @param       ÎÞ
 * @retval      ÎÞ
 */
void CAN1_RX0_IRQHandler()
{
	uint8_t msg_v[8];
  uint32_t id;

  uint8_t ide, rtr, len;
	
//  
	
      // ¶ÁÈ¡FIFO 0ÖÐµÄÏûÏ¢
  if (HAL_CAN_GetRxMessage(&g_canx_handler, CAN_RX_FIFO0, &g_canx_rxheader, msg_v) == HAL_OK) {
        // ´æ´¢IDºÍ³¤¶Èµ½¾Ö²¿±äÁ¿
        id = g_canx_rxheader.StdId;
        len = g_canx_rxheader.DLC;

        // µ÷ÓÃÏûÏ¢´¦Àíº¯Êý£¬´«µÝ¾Ö²¿±äÁ¿
        ProcessMotorCANMessage(id, msg_v, len);

        // Çå³ýÖÐ¶Ï±êÖ¾
        __HAL_CAN_CLEAR_FLAG(&g_canx_handler, CAN_IT_RX_FIFO0_MSG_PENDING);
	}
}

void ProcessMotorCANMessage(uint32_t id, uint8_t *rxbuf, uint8_t len) {
    // ¼ì²éÊý¾Ý³¤¶ÈÊÇ·ñÎª8×Ö½Ú
    if (len != 8) {
        printf("Received message with incorrect length: %d bytes, ID: 0x%03X\n", len, id);
        return;
    }

    // ´òÓ¡½ÓÊÕµ½µÄ8×Ö½ÚÊý¾Ý
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

/* ÏÂÃæ¼¸¸öº¯Êý¶¼ÊÇCAN½ÓÊÕµ½²»Í¬µÄ·µ»ØÖ¡ºóµÄ´¦Àíº¯Êý */

void handle_multi_angle(uint32_t id, uint8_t *rxbuf) {
    // ´ÓrxbufÖÐ½âÎö³ömotorAngle
    uint64_t tempMotorAngle = 0;
    for (int i = 1; i <= 7; ++i) {  // ÕýÈ·µÄ·¶Î§Ó¦¸ÃÊÇ1µ½7
        tempMotorAngle |= (uint64_t)(rxbuf[i]) << (8 * (i - 1));
    }

    // ´¦Àí·ûºÅÀ©Õ¹
    int64_t motorAngle;
    if (tempMotorAngle & (1ULL << 55)) { // Èç¹ûµÚ55Î»£¨×î¸ßÓÐÐ§Êý¾ÝÎ»£©Îª1£¬±íÊ¾¸ºÊý
        motorAngle = tempMotorAngle | 0xFF00000000000000ULL; // ·ûºÅÀ©Õ¹
    } else {
        motorAngle = tempMotorAngle;
    }

    // ÓÉÓÚ½Ç¶ÈÊý¾ÝÊÇint64_tÀàÐÍ£¬ÎÒÃÇÐèÒª½«Æä×ª»»ÎªÊµ¼ÊµÄ½Ç¶ÈÖµ£¨µ¥Î»Îª¶È£©
    // ÓÉÓÚµ¥Î»ÊÇ0.01¡ã/LSB£¬ËùÒÔÐèÒª³ËÒÔ0.01À´×ª»»Îª¶È
    float angle_in_degrees = motorAngle * 0.01;

    // ´æ´¢µ½received_dataÊý×éÖÐ
    // ¼ì²éidÊÇ·ñÔÚÓÐÐ§·¶Î§ÄÚ£¬±ÜÃâÊý×éÔ½½ç
    if (id >= DEVICE_STD_ID + 1 && id < DEVICE_STD_ID + 1 + MAX_DEVICES) {
        received_data[id - DEVICE_STD_ID - 1] = angle_in_degrees;
    } else {
        printf("Error: Invalid ID received.\n");
    }

    // ´òÓ¡½Ç¶ÈÖµÒÔ¹©¼ì²é£¨¿ÉÑ¡£©
//    printf("Motor angle for ID 0x%03X: %f degrees\n", id, angle_in_degrees);
}



/* ÉÏÃæ¼¸¸öº¯Êý¶¼ÊÇCAN½ÓÊÕµ½²»Í¬µÄ·µ»ØÖ¡ºóµÄ´¦Àíº¯Êý */


#endif



/**
 * @brief       CAN ·¢ËÍÒ»×éÊý¾Ý
 *   @note      ·¢ËÍ¸ñÊ½¹Ì¶¨Îª: ±ê×¼ID, Êý¾ÝÖ¡
 * @param       id      : ±ê×¼ID(11Î»)
 * @retval      ·¢ËÍ×´Ì¬ 0, ³É¹¦; 1, Ê§°Ü;
 */
uint8_t can_send_msg(uint32_t id, uint8_t *msg, uint8_t len)
{
    uint32_t TxMailbox = CAN_TX_MAILBOX0;
    g_canx_txheader.StdId = id;         /* ±ê×¼±êÊ¶·û */ //
    g_canx_txheader.ExtId = 0x00;         /* À©Õ¹±êÊ¶·û(29Î») */
    g_canx_txheader.IDE = CAN_ID_STD;   /* Ê¹ÓÃ±ê×¼Ö¡ */
    g_canx_txheader.RTR = CAN_RTR_DATA; /* Êý¾ÝÖ¡ */
    g_canx_txheader.DLC = len;

    if (HAL_CAN_AddTxMessage(&g_canx_handler, &g_canx_txheader, msg, &TxMailbox) != HAL_OK) /* ·¢ËÍÏûÏ¢ */
    {
        return 1;
    }
    while (HAL_CAN_GetTxMailboxesFreeLevel(&g_canx_handler) != 3); /* µÈ´ý·¢ËÍÍê³É,ËùÓÐÓÊÏäÎª¿Õ */
    return 0;
}

/**
 * @brief       CAN ½ÓÊÕÊý¾Ý²éÑ¯
 *   @note      ½ÓÊÕÊý¾Ý¸ñÊ½¹Ì¶¨Îª: ±ê×¼ID, Êý¾ÝÖ¡
 * @param       id      : Òª²éÑ¯µÄ ±ê×¼ID(11Î»)
 * @param       buf     : Êý¾Ý»º´æÇø
 * @retval      ½ÓÊÕ½á¹û
 *   @arg       0   , ÎÞÊý¾Ý±»½ÓÊÕµ½;
 *   @arg       ÆäËû, ½ÓÊÕµÄÊý¾Ý³¤¶È
 */
uint8_t can_receive_msg(uint32_t id, uint8_t *buf)
{
	g_canx_rxheader.StdId = id;         /* ±ê×¼±êÊ¶·DEVICE_STD_ID +û */
  g_canx_rxheader.ExtId = 0x00;         /* À©Õ¹±êÊ¶·û(29Î») ±ê×¼±êÊ¶·ûÇé¿öÏÂ£¬¸Ã³ÉÔ±ÎÞÐ§*/
  g_canx_rxheader.IDE = CAN_ID_STD;   /* Ê¹ÓÃ±ê×¼±êÊ¶·û */
  g_canx_rxheader.RTR = CAN_RTR_DATA; /* Êý¾ÝÖ¡ */
  g_canx_rxheader.DLC = 8;
	
  if (HAL_CAN_GetRxFifoFillLevel(&g_canx_handler, CAN_RX_FIFO0) == 0)     /* Ã»ÓÐ½ÓÊÕµ½Êý¾Ý */
  {
//		printf("%i", 6657);
//		printf("\n");
    return 0;
  }

  if (HAL_CAN_GetRxMessage(&g_canx_handler, CAN_RX_FIFO0, &g_canx_rxheader, buf) != HAL_OK)  /* ¶ÁÈ¡Êý¾Ý */
  {

		return 0;
  }
  
  if (g_canx_rxheader.StdId!= id || g_canx_rxheader.IDE != CAN_ID_STD || g_canx_rxheader.RTR != CAN_RTR_DATA)       /* ½ÓÊÕµ½µÄID²»¶Ô / ²»ÊÇ±ê×¼Ö¡ / ²»ÊÇÊý¾ÝÖ¡ */
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
