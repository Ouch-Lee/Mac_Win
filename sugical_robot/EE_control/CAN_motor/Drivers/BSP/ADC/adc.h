
#ifndef __ADC_H
#define __ADC_H

#include "./SYSTEM/sys/sys.h"

/******************************************************************************************/
/* ADC������ ���� */

#define ADC_ADCX_CHY_GPIO_PORT              GPIOA
#define ADC_ADCX_CHY_GPIO_PIN               GPIO_PIN_5
#define ADC_ADCX_CHY_GPIO_CLK_ENABLE()      do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)         /* PA��ʱ��ʹ�� */

#define ADC_ADCX                            ADC1 
#define ADC_ADCX_CHY                        ADC_CHANNEL_5                                       /* ͨ��Y,  0 <= Y <= 17 */ 
#define ADC_ADCX_CHY_CLK_ENABLE()           do{ __HAL_RCC_ADC1_CLK_ENABLE(); }while(0)          /* ADC1 ʱ��ʹ�� */

/******************************************************************************************/


/* �ⲿ�ӿں���*/
void adc_init(void);                                            /* ADC��ʼ�� */
void adc_channel_set(ADC_HandleTypeDef *adc_handle, uint32_t ch, uint32_t rank, uint32_t stime); /* ADCͨ������ */
uint32_t adc_get_result(uint32_t ch);                           /* ���ĳ��ͨ��ֵ */
uint32_t adc_get_result_average(uint32_t ch, uint8_t times);    /* �õ�ĳ��ͨ����������������ƽ��ֵ */                                                                         /* ��ʼ�� */

#endif
