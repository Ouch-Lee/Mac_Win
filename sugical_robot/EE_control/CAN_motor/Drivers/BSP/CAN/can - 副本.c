/**
 ****************************************************************************************************
 * @file        can.c
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

#include "./BSP/CAN/can.h"
#include "./BSP/LED/led.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"

/* USER CODE BEGIN 0 */
uint8_t canTxData[8];
uint8_t canRxData[8];
uint8_t start_motor[8];
uint8_t close_motor[8];
uint8_t stop_motor[8];
uint8_t close_motor[8];
uint8_t torque_control[8];
uint8_t torque_control_1[8];
uint8_t torque_control_2[8];
uint16_t encoderValue = 0;

/* USER CODE END 0 */


CAN_HandleTypeDef   g_canx_handler;     /* CANx��� */
CAN_TxHeaderTypeDef g_canx_txheader;    /* ���Ͳ������ */
CAN_RxHeaderTypeDef g_canx_rxheader;    /* ���ղ������ */

/**
 * @brief       CAN��ʼ��
 * @param       tsjw    : ����ͬ����Ծʱ�䵥Ԫ.��Χ: 1~3;
 * @param       tbs2    : ʱ���2��ʱ�䵥Ԫ.��Χ: 1~8;
 * @param       tbs1    : ʱ���1��ʱ�䵥Ԫ.��Χ: 1~16;
 * @param       brp     : �����ʷ�Ƶ��.��Χ: 1~1024;
 *   @note      ����4������, �ں����ڲ����1, ����, �κ�һ�����������ܵ���0
 *              CAN����APB1����, ������ʱ��Ƶ��Ϊ Fpclk1 = PCLK1 = 42Mhz
 *              tq     = brp * tpclk1;
 *              ������ = Fpclk1 / ((tbs1 + tbs2 + 1) * brp);
 *              �������� can_init(1, 6, 7, 6, 1), ��CAN������Ϊ:
 *              42M / ((6 + 7 + 1) * 6) = 500Kbps
 *
 * @param       mode    : CAN_MODE_NORMAL,  ��ͨģʽ;
                          CAN_MODE_LOOPBACK,�ػ�ģʽ;
 * @retval      0,  ��ʼ���ɹ�; ����, ��ʼ��ʧ��;
 */
uint8_t can_init(uint32_t tsjw, uint32_t tbs2, uint32_t tbs1, uint16_t brp, uint32_t mode)
{
    g_canx_handler.Instance = CAN1;
    g_canx_handler.Init.Prescaler = brp;                /* ��Ƶϵ��(Fdiv)Ϊbrp+1 */
    g_canx_handler.Init.Mode = mode;                    /* ģʽ���� */
    g_canx_handler.Init.SyncJumpWidth = tsjw;           /* ����ͬ����Ծ���(Tsjw)Ϊtsjw+1��ʱ�䵥λ CAN_SJW_1TQ~CAN_SJW_4TQ */
    g_canx_handler.Init.TimeSeg1 = tbs1;                /* tbs1��ΧCAN_BS1_1TQ~CAN_BS1_16TQ */
    g_canx_handler.Init.TimeSeg2 = tbs2;                /* tbs2��ΧCAN_BS2_1TQ~CAN_BS2_8TQ */
    g_canx_handler.Init.TimeTriggeredMode = DISABLE;    /* ��ʱ�䴥��ͨ��ģʽ */
    g_canx_handler.Init.AutoBusOff = DISABLE;           /* ����Զ����߹��� */
    g_canx_handler.Init.AutoWakeUp = DISABLE;           /* ˯��ģʽͨ���������(���CAN->MCR��SLEEPλ) */
    g_canx_handler.Init.AutoRetransmission = ENABLE;    /* ��ֹ�����Զ����� */
    g_canx_handler.Init.ReceiveFifoLocked = DISABLE;    /* ���Ĳ�����,�µĸ��Ǿɵ� */
    g_canx_handler.Init.TransmitFifoPriority = DISABLE; /* ���ȼ��ɱ��ı�ʶ������ */
    if (HAL_CAN_Init(&g_canx_handler) != HAL_OK)
    {
        return 1;
    }

#if CAN_RX0_INT_ENABLE

    /* ʹ���жϽ��� */
    __HAL_CAN_ENABLE_IT(&g_canx_handler, CAN_IT_RX_FIFO0_MSG_PENDING); /* FIFO0��Ϣ�Һ��ж����� */
    HAL_NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);                          /* ʹ��CAN�ж� */
    HAL_NVIC_SetPriority(USB_LP_CAN1_RX0_IRQn, 1, 0);                  /* ��ռ���ȼ�1�������ȼ�0 */
#endif

    CAN_FilterTypeDef sFilterConfig;

    /*����CAN������*/
    sFilterConfig.FilterBank = 0;                             /* ������0 */
    sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
    sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
    sFilterConfig.FilterIdHigh = 0x0000;                      /* 32λID */
    sFilterConfig.FilterIdLow = 0x0000;
    sFilterConfig.FilterMaskIdHigh = 0x0000;                  /* 32λMASK */
    sFilterConfig.FilterMaskIdLow = 0x0000;
    sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;    /* ������0������FIFO0 */
    sFilterConfig.FilterActivation = CAN_FILTER_ENABLE;       /* �����˲���0 */
    sFilterConfig.SlaveStartFilterBank = 14;

    /* ���������� */
    if (HAL_CAN_ConfigFilter(&g_canx_handler, &sFilterConfig) != HAL_OK)
    {
    return 2;
    }

    /* ����CAN��Χ�豸 */
    if (HAL_CAN_Start(&g_canx_handler) != HAL_OK)
    {
    return 3;
    }


    return 0;
}

/**
 * @brief       CAN�ײ��������������ã�ʱ�����ã��ж�����
                �˺����ᱻHAL_CAN_Init()����
 * @param       hcan:CAN���
 * @retval      ��
 */
void HAL_CAN_MspInit(CAN_HandleTypeDef *hcan)
{
    if (CAN1 == hcan->Instance)
    {
        CAN_RX_GPIO_CLK_ENABLE();       /* CAN_RX��ʱ��ʹ�� */
        CAN_TX_GPIO_CLK_ENABLE();       /* CAN_TX��ʱ��ʹ�� */
        __HAL_RCC_CAN1_CLK_ENABLE();    /* ʹ��CAN1ʱ�� */

        GPIO_InitTypeDef gpio_init_struct;

        gpio_init_struct.Pin = CAN_TX_GPIO_PIN;
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;
        gpio_init_struct.Pull = GPIO_PULLUP;
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
        gpio_init_struct.Alternate = GPIO_AF9_CAN1;
        HAL_GPIO_Init(CAN_TX_GPIO_PORT, &gpio_init_struct); /* CAN_TX�� ģʽ���� */

        gpio_init_struct.Pin = CAN_RX_GPIO_PIN;
        HAL_GPIO_Init(CAN_RX_GPIO_PORT, &gpio_init_struct); /* CAN_RX�� �������ó�����ģʽ */
    }
}

#if CAN_RX0_INT_ENABLE /* ʹ��RX0�ж� */

/**
 * @brief       CAN RX0 �жϷ�����
 *   @note      ����CAN FIFO0�Ľ����ж�
 * @param       ��
 * @retval      ��
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

/**
 * @brief       CAN ����һ������
 *   @note      ���͸�ʽ�̶�Ϊ: ��׼ID, ����֡
 * @param       id      : ��׼ID(11λ)
 * @retval      ����״̬ 0, �ɹ�; 1, ʧ��;
 */
uint8_t can_send_msg(uint32_t id, uint8_t *msg, uint8_t len)
{
    uint32_t TxMailbox = CAN_TX_MAILBOX0;
    g_canx_txheader.StdId = DEVICE_STD_ID + id;         /* ��׼��ʶ�� */ //
    g_canx_txheader.ExtId = 0x00;         /* ��չ��ʶ��(29λ) */
    g_canx_txheader.IDE = CAN_ID_STD;   /* ʹ�ñ�׼֡ */
    g_canx_txheader.RTR = CAN_RTR_DATA; /* ����֡ */
    g_canx_txheader.DLC = len;

    if (HAL_CAN_AddTxMessage(&g_canx_handler, &g_canx_txheader, msg, &TxMailbox) != HAL_OK) /* ������Ϣ */
    {
        return 1;
    }
    while (HAL_CAN_GetTxMailboxesFreeLevel(&g_canx_handler) != 3); /* �ȴ��������,��������Ϊ�� */
    return 0;
}

/**
 * @brief       CAN �������ݲ�ѯ
 *   @note      �������ݸ�ʽ�̶�Ϊ: ��׼ID, ����֡
 * @param       id      : Ҫ��ѯ�� ��׼ID(11λ)
 * @param       buf     : ���ݻ�����
 * @retval      ���ս��
 *   @arg       0   , �����ݱ����յ�;
 *   @arg       ����, ���յ����ݳ���
 */
uint8_t can_receive_msg(uint32_t id, uint8_t *buf)
{
    if (HAL_CAN_GetRxFifoFillLevel(&g_canx_handler, CAN_RX_FIFO0) == 0)     /* û�н��յ����� */
    {
        return 0;
    }

    if (HAL_CAN_GetRxMessage(&g_canx_handler, CAN_RX_FIFO0, &g_canx_rxheader, buf) != HAL_OK)  /* ��ȡ���� */
    {
        return 0;
    }

    if (g_canx_rxheader.StdId!=DEVICE_STD_ID + id || g_canx_rxheader.IDE != CAN_ID_STD || g_canx_rxheader.RTR != CAN_RTR_DATA)       /* ���յ���ID���� / ���Ǳ�׼֡ / ��������֡ */
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
