
#include "./BSP/GPIO/gpio.h"
#include "./SYSTEM/sys/sys.h"


/**
 * @brief       ��ʼ��GPIO���IO��, ��ʹ��ʱ��
 * @param       ��
 * @retval      ��
 */
void encoder_init(void)
{
//    GPIO_InitTypeDef gpio_init_struct;
//    
//    ENCODER_A_GPIO_CLK_ENABLE();                                 /* LED0ʱ��ʹ�� */
//    ENCODER_B_GPIO_CLK_ENABLE();                                 /* LED1ʱ��ʹ�� */

//    gpio_init_struct.Pin = LED0_GPIO_PIN;                   /* LED0���� */
//    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;            /* ������� */
//    gpio_init_struct.Pull = GPIO_PULLUP;                    /* ���� */
//    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* ���� */
//    HAL_GPIO_Init(LED0_GPIO_PORT, &gpio_init_struct);       /* ��ʼ��LED0���� */

//    gpio_init_struct.Pin = LED1_GPIO_PIN;                   /* LED1���� */
//    HAL_GPIO_Init(LED1_GPIO_PORT, &gpio_init_struct);       /* ��ʼ��LED1���� */
//    
//    LED0(1);                                                /* �ر� LED0 */
//    LED1(1);                                                /* �ر� LED1 */
		GPIO_InitTypeDef GPIO_InitStruct;
		GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_PULLDOWN;
		HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
}