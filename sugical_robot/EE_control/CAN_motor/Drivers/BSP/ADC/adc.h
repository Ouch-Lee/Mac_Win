/**
 ****************************************************************************************************
 * @file        adc.h
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.2
 * @date        2021-10-18
 * @brief       ADC ��������
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
 * V1.0 20211018
 * ��һ�η���
 * V1.1 20211018
 * 1,֧��ADC��ͨ��DMA�ɼ� 
 * 2,����adc_dma_init��adc_dma_enable����
 * V1.2 20211018
 * 1,֧��ADC��ͨ��DMA�ɼ�
 * 2,����adc_nch_dma_init��adc_nch_dma_gpio_init����
 * 
 ****************************************************************************************************
 */

#ifndef __ADC_H
#define __ADC_H

#include "./SYSTEM/sys/sys.h"


/******************************************************************************************/
/* ADC������ ���� */

#define ADC_ADCX_CHY_GPIO_PORT              GPIOA
#define ADC_ADCX_CHY_GPIO_PIN               GPIO_PIN_5
#define ADC_ADCX_CHY_GPIO_CLK_ENABLE()      do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)     /* PA��ʱ��ʹ�� */

#define ADC_ADCX                            ADC1 
#define ADC_ADCX_CHY                        ADC_CHANNEL_5                                   /* ͨ��Y,  0 <= Y <= 17 */ 
#define ADC_ADCX_CHY_CLK_ENABLE()           do{ __HAL_RCC_ADC1_CLK_ENABLE(); }while(0)      /* ADC1 ʱ��ʹ�� */


#define ADC_CH_NUM                          6                                               /* ��Ҫת����ͨ����Ŀ */

/* ADC��ͨ��/��ͨ�� DMA�ɼ� DMA��������� ����
 * ע��: �������ǵ�ͨ������ʹ������Ķ���.
 */
#define ADC_ADCX_DMASx                      DMA2_Stream4
#define ADC_ADCX_DMASx_Chanel               DMA_CHANNEL_0                                   /* ADC1_DMA����Դ */
#define ADC_ADCX_DMASx_IRQn                 DMA2_Stream4_IRQn
#define ADC_ADCX_DMASx_IRQHandler           DMA2_Stream4_IRQHandler

#define ADC_ADCX_DMASx_IS_TC()              ( DMA2->HISR & (1 << 5) )                       /* �ж� DMA2_Stream4 ������ɱ�־, ����һ���ٺ�����ʽ,
                                                                                             * ���ܵ�����ʹ��, ֻ������if���������
                                                                                             */
#define ADC_ADCX_DMASx_CLR_TC()             do{ DMA2->HIFCR |= 1 << 5; }while(0)            /* ��� DMA2_Stream4 ������ɱ�־ */

/******************************************************************************************/

void adc_init(void);    /* ADC��ʼ�� */
void adc_channel_set(ADC_HandleTypeDef *adc_handle, uint32_t ch, uint32_t rank, uint32_t stime);    /* ADCͨ������ */
uint32_t adc_get_result(uint32_t ch);       /* ���ĳ��ͨ��ֵ */
uint32_t adc_get_result_average(uint32_t ch, uint8_t times);    /* �õ�ĳ��ͨ����������������ƽ��ֵ */

void adc_dma_init(uint32_t mar);            /* ADC DMA�ɼ���ʼ�� */
void adc_dma_enable( uint16_t ndtr);        /* ʹ��һ��ADC DMA�ɼ����� */

void adc_nch_dma_init(uint32_t tmr);        /* ADC��ͨ�� DMA�ɼ���ʼ�� */
void adc_nch_dma_gpio_init(void);           /* ADC��ͨ�� GPIO��ʼ�� */
void adc_nch_dma_enable(uint16_t ndtr);     /* ʹ��һ��ADC DMA��ͨ���ɼ����� */

#endif 





