
#include "./BSP/GPIO/gpio.h"
#include "./SYSTEM/sys/sys.h"


/**
 * @brief       初始化GPIO相关IO口, 并使能时钟
 * @param       无
 * @retval      无
 */
void encoder_init(void)
{
//    GPIO_InitTypeDef gpio_init_struct;
//    
//    ENCODER_A_GPIO_CLK_ENABLE();                                 /* LED0时钟使能 */
//    ENCODER_B_GPIO_CLK_ENABLE();                                 /* LED1时钟使能 */

//    gpio_init_struct.Pin = LED0_GPIO_PIN;                   /* LED0引脚 */
//    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;            /* 推挽输出 */
//    gpio_init_struct.Pull = GPIO_PULLUP;                    /* 上拉 */
//    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* 高速 */
//    HAL_GPIO_Init(LED0_GPIO_PORT, &gpio_init_struct);       /* 初始化LED0引脚 */

//    gpio_init_struct.Pin = LED1_GPIO_PIN;                   /* LED1引脚 */
//    HAL_GPIO_Init(LED1_GPIO_PORT, &gpio_init_struct);       /* 初始化LED1引脚 */
//    
//    LED0(1);                                                /* 关闭 LED0 */
//    LED1(1);                                                /* 关闭 LED1 */
		// 初始化A相对应的PE2
	
	
//    GPIO_InitTypeDef GPIO_InitStruct;
//		ENCODER_A_GPIO_CLK_ENABLE();  
//		GPIO_InitStruct.Pin = ENCODER_A_GPIO_PIN;
//		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//		GPIO_InitStruct.Pull = GPIO_PULLUP;
//		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
//		HAL_GPIO_Init(ENCODER_GPIO_PORT, &GPIO_InitStruct);
//	
//		// 初始化B相对应的PE3
//		ENCODER_B_GPIO_CLK_ENABLE();
//		GPIO_InitStruct.Pin = ENCODER_B_GPIO_PIN;
//		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//		GPIO_InitStruct.Pull = GPIO_PULLUP;
//		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
//		HAL_GPIO_Init(ENCODER_GPIO_PORT, &GPIO_InitStruct);
		
		// TEST GPIO
		 __HAL_RCC_GPIOH_CLK_ENABLE();
		__HAL_RCC_GPIOA_CLK_ENABLE();
		
		
}