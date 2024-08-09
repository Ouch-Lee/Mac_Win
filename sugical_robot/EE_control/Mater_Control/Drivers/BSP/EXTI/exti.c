/**
 ****************************************************************************************************
 * @file        exti.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2021-10-14
 * @brief       �ⲿ�ж� ��������
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
 * V1.0 20211014
 * ��һ�η���
 *
 ****************************************************************************************************
 */

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/EXTI/exti.h"
#include "./SYSTEM/usart/usart.h"

volatile int encoder_count = 0;

/**
 * @brief       KEY0 �ⲿ�жϷ������
 * @param       ��
 * @retval      ��
 */
void ENCODER_A_INT_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(ENCODER_A_GPIO_PIN);         /* �����жϴ����ú��� ���KEY0�����ж��� ���жϱ�־λ */
    __HAL_GPIO_EXTI_CLEAR_IT(ENCODER_A_GPIO_PIN);         /* HAL��Ĭ�������ж��ٴ���ص����˳�ʱ����һ���жϣ����ⰴ�������󴥷� */
}

/**
 * @brief       KEY1 �ⲿ�жϷ������
 * @param       ��
 * @retval      ��
 */
void ENCODER_B_INT_IRQHandler(void)
{ 
    HAL_GPIO_EXTI_IRQHandler(ENCODER_B_GPIO_PIN);         /* �����жϴ����ú��� ���KEY1�����ж��� ���жϱ�־λ���ж��°벿��HAL_GPIO_EXTI_Callbackִ�� */
    __HAL_GPIO_EXTI_CLEAR_IT(ENCODER_B_GPIO_PIN);         /* HAL��Ĭ�������ж��ٴ���ص����˳�ʱ����һ���жϣ����ⰴ�������󴥷� */
}

/**
 * @brief       KEY2 �ⲿ�жϷ������
 * @param       ��
 * @retval      ��
 */
//void KEY2_INT_IRQHandler(void)
//{ 
//    HAL_GPIO_EXTI_IRQHandler(KEY2_INT_GPIO_PIN);        /* �����жϴ����ú��� ���KEY2�����ж��� ���жϱ�־λ���ж��°벿��HAL_GPIO_EXTI_Callbackִ�� */
//    __HAL_GPIO_EXTI_CLEAR_IT(KEY2_INT_GPIO_PIN);        /* HAL��Ĭ�������ж��ٴ���ص����˳�ʱ����һ���жϣ����ⰴ�������󴥷� */
//}

///**
// * @brief       WK_UP �ⲿ�жϷ������
// * @param       ��
// * @retval      ��
// */
//void WKUP_INT_IRQHandler(void)
//{ 
//    HAL_GPIO_EXTI_IRQHandler(WKUP_INT_GPIO_PIN);        /* �����жϴ����ú��� ���KEY_UP�����ж��� ���жϱ�־λ���ж��°벿��HAL_GPIO_EXTI_Callbackִ�� */
//    __HAL_GPIO_EXTI_CLEAR_IT(WKUP_INT_GPIO_PIN);        /* HAL��Ĭ�������ж��ٴ���ص����˳�ʱ����һ���жϣ����ⰴ�������󴥷� */
//}

/**
 * @brief       �жϷ����������Ҫ��������
 *              ��HAL�������е��ⲿ�жϷ�����������ô˺���
 * @param       GPIO_Pin:�ж����ź�
 * @retval      ��
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	
    if (GPIO_Pin == ENCODER_A_GPIO_PIN) {

//			// ��ȡA���B��ĵ�ǰ״̬
//			uint8_t A = HAL_GPIO_ReadPin(ENCODER_GPIO_PORT, ENCODER_A_GPIO_PIN);
//			uint8_t B = HAL_GPIO_ReadPin(ENCODER_GPIO_PORT, ENCODER_B_GPIO_PIN);

//			// �ж�A���������
//			if (A == 1) {
//					// ����B���״̬�жϷ���
//					if (B == 0) {
//							encoder_count--;
//					} else {
//							encoder_count++;
//					}
//			}
				
				if (HAL_GPIO_ReadPin(ENCODER_GPIO_PORT, ENCODER_B_GPIO_PIN) == 0) {
					encoder_count++;
					printf("\r\n detect high pin \r\n");
				} else {
					encoder_count--;
				
				}
			}
		
			printf("\r\n count: %d \r\n", encoder_count);

			// ����ǰһ��A��״̬

		
}

/**
 * @brief       �ⲿ�жϳ�ʼ������
 * @param       ��
 * @retval      ��
 */
void extix_init(void)
{
	
		// ��ʼ��A���Ӧ��PE2
    GPIO_InitTypeDef GPIO_InitStruct;
		__HAL_RCC_GPIOA_CLK_ENABLE();
		GPIO_InitStruct.Pin = ENCODER_A_GPIO_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(ENCODER_GPIO_PORT, &GPIO_InitStruct);
	
		// ��ʼ��B���Ӧ��PE3
		
		GPIO_InitStruct.Pin = ENCODER_B_GPIO_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(ENCODER_GPIO_PORT, &GPIO_InitStruct);
	
	
    HAL_NVIC_SetPriority(ENCODER_A_INT_IRQn, 0, 0);               /* ��ռ0�������ȼ�2 */
    HAL_NVIC_EnableIRQ(ENCODER_A_INT_IRQn);                       /* ʹ���ж���4 */


}












