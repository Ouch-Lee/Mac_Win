/**
 ****************************************************************************************************
 * @file        exti.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2021-10-14
 * @brief       外部中断 驱动代码
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
 * V1.0 20211014
 * 第一次发布
 *
 ****************************************************************************************************
 */

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/EXTI/exti.h"
#include "./SYSTEM/usart/usart.h"

volatile int encoder_count = 0;

/**
 * @brief       KEY0 外部中断服务程序
 * @param       无
 * @retval      无
 */
void ENCODER_A_INT_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(ENCODER_A_GPIO_PIN);         /* 调用中断处理公用函数 清除KEY0所在中断线 的中断标志位 */
    __HAL_GPIO_EXTI_CLEAR_IT(ENCODER_A_GPIO_PIN);         /* HAL库默认先清中断再处理回调，退出时再清一次中断，避免按键抖动误触发 */
}

/**
 * @brief       KEY1 外部中断服务程序
 * @param       无
 * @retval      无
 */
void ENCODER_B_INT_IRQHandler(void)
{ 
    HAL_GPIO_EXTI_IRQHandler(ENCODER_B_GPIO_PIN);         /* 调用中断处理公用函数 清除KEY1所在中断线 的中断标志位，中断下半部在HAL_GPIO_EXTI_Callback执行 */
    __HAL_GPIO_EXTI_CLEAR_IT(ENCODER_B_GPIO_PIN);         /* HAL库默认先清中断再处理回调，退出时再清一次中断，避免按键抖动误触发 */
}

/**
 * @brief       KEY2 外部中断服务程序
 * @param       无
 * @retval      无
 */
//void KEY2_INT_IRQHandler(void)
//{ 
//    HAL_GPIO_EXTI_IRQHandler(KEY2_INT_GPIO_PIN);        /* 调用中断处理公用函数 清除KEY2所在中断线 的中断标志位，中断下半部在HAL_GPIO_EXTI_Callback执行 */
//    __HAL_GPIO_EXTI_CLEAR_IT(KEY2_INT_GPIO_PIN);        /* HAL库默认先清中断再处理回调，退出时再清一次中断，避免按键抖动误触发 */
//}

///**
// * @brief       WK_UP 外部中断服务程序
// * @param       无
// * @retval      无
// */
//void WKUP_INT_IRQHandler(void)
//{ 
//    HAL_GPIO_EXTI_IRQHandler(WKUP_INT_GPIO_PIN);        /* 调用中断处理公用函数 清除KEY_UP所在中断线 的中断标志位，中断下半部在HAL_GPIO_EXTI_Callback执行 */
//    __HAL_GPIO_EXTI_CLEAR_IT(WKUP_INT_GPIO_PIN);        /* HAL库默认先清中断再处理回调，退出时再清一次中断，避免按键抖动误触发 */
//}

/**
 * @brief       中断服务程序中需要做的事情
 *              在HAL库中所有的外部中断服务函数都会调用此函数
 * @param       GPIO_Pin:中断引脚号
 * @retval      无
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	
    if (GPIO_Pin == ENCODER_A_GPIO_PIN) {

//			// 读取A相和B相的当前状态
//			uint8_t A = HAL_GPIO_ReadPin(ENCODER_GPIO_PORT, ENCODER_A_GPIO_PIN);
//			uint8_t B = HAL_GPIO_ReadPin(ENCODER_GPIO_PORT, ENCODER_B_GPIO_PIN);

//			// 判断A相的上升沿
//			if (A == 1) {
//					// 根据B相的状态判断方向
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

			// 更新前一个A相状态

		
}

/**
 * @brief       外部中断初始化程序
 * @param       无
 * @retval      无
 */
void extix_init(void)
{
	
		// 初始化A相对应的PE2
    GPIO_InitTypeDef GPIO_InitStruct;
		__HAL_RCC_GPIOA_CLK_ENABLE();
		GPIO_InitStruct.Pin = ENCODER_A_GPIO_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(ENCODER_GPIO_PORT, &GPIO_InitStruct);
	
		// 初始化B相对应的PE3
		
		GPIO_InitStruct.Pin = ENCODER_B_GPIO_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(ENCODER_GPIO_PORT, &GPIO_InitStruct);
	
	
    HAL_NVIC_SetPriority(ENCODER_A_INT_IRQn, 0, 0);               /* 抢占0，子优先级2 */
    HAL_NVIC_EnableIRQ(ENCODER_A_INT_IRQn);                       /* 使能中断线4 */


}












