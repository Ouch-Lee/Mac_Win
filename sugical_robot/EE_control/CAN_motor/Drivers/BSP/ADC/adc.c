
#include "./BSP/ADC/adc.h"
#include "./SYSTEM/sys/sys.h"

ADC_HandleTypeDef g_adc_handle;

/**
 * @brief       ��ʼ��ADC
 * @param       ��
 * @retval      ��
 */

void adc_init(void)
{
		g_adc_handle.Instance = ADC_ADCX;
		g_adc_handle.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV4;
		g_adc_handle.Init.Resolution = ADC_RESOLUTION_12B;  
		g_adc_handle.Init.DataAlign = ADC_DATAALIGN_RIGHT;                      /* �Ҷ��� */
    g_adc_handle.Init.ScanConvMode = DISABLE;                               /* ��ɨ��ģʽ */
    g_adc_handle.Init.ContinuousConvMode = DISABLE;                         /* �ر�����ת�� */
    g_adc_handle.Init.NbrOfConversion = 1;                                  /* 1��ת���ڹ��������� Ҳ����ֻת����������1 */
    g_adc_handle.Init.DiscontinuousConvMode = DISABLE;                      /* ��ֹ����������ģʽ */
    g_adc_handle.Init.NbrOfDiscConversion = 0;                              /* ����������ͨ����Ϊ0 */
    g_adc_handle.Init.ExternalTrigConv = ADC_SOFTWARE_START;                /* ������� */
    g_adc_handle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE; /* ʹ��������� */
    g_adc_handle.Init.DMAContinuousRequests = DISABLE;                      /* �ر�DMA���� */
    HAL_ADC_Init(&g_adc_handle);                                            /* ��ʼ�� */
}

/**
 * @brief       ADC�ײ��������������ã�ʱ��ʹ��
                �˺����ᱻHAL_ADC_Init()����
 * @param       hadc:ADC���
 * @retval      ��
 */
void HAL_ADC_MspInit(ADC_HandleTypeDef *hadc)
{
	if(hadc->Instance == ADC_ADCX)
	{
		GPIO_InitTypeDef gpio_init_struct;
		ADC_ADCX_CHY_GPIO_CLK_ENABLE();
		ADC_ADCX_CHY_CLK_ENABLE();
		
		/* AD�ɼ�����ģʽ����,ģ������ */
        gpio_init_struct.Pin = ADC_ADCX_CHY_GPIO_PIN;
        gpio_init_struct.Mode = GPIO_MODE_ANALOG;
        gpio_init_struct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(ADC_ADCX_CHY_GPIO_PORT, &gpio_init_struct);
	}
	
}


/**
 * @brief       ����ADCͨ������ʱ��
 * @param       adcx : adc���ָ��,ADC_HandleTypeDef
 * @param       ch   : ͨ����, ADC_CHANNEL_0~ADC_CHANNEL_17
 * @param       stime: ����ʱ��  0~7, ��Ӧ��ϵΪ:
 *   @arg       ADC_SAMPLETIME_3CYCLES,  3��ADCʱ������        ADC_SAMPLETIME_15CYCLES, 15��ADCʱ������
 *   @arg       ADC_SAMPLETIME_28CYCLES, 28��ADCʱ������       ADC_SAMPLETIME_56CYCLES, 56��ADCʱ������
 *   @arg       ADC_SAMPLETIME_84CYCLES, 84��ADCʱ������       ADC_SAMPLETIME_112CYCLES,112��ADCʱ������
 *   @arg       ADC_SAMPLETIME_144CYCLES,144��ADCʱ������      ADC_SAMPLETIME_480CYCLES,480��ADCʱ������
 * @param       rank: ��ͨ���ɼ�ʱ��Ҫ���õĲɼ����,
                �����㶨��channel1��rank=1��channel2��rank=2��
                ��ô��Ӧ����DMA����ռ�ı�������AdcDMA[0] ��i��channel1��ת�������AdcDMA[1]����ͨ��2��ת������� 
                ��ͨ��DMA����Ϊ ADC_REGULAR_RANK_1
 *   @arg       ���1~16��ADC_REGULAR_RANK_1~ADC_REGULAR_RANK_16
 * @retval      ��
 */

void adc_channel_set(ADC_HandleTypeDef *adc_handle, uint32_t ch, uint32_t rank, uint32_t stime)
{
    /* ���ö�ӦADCͨ�� */
    ADC_ChannelConfTypeDef adc_channel;
    adc_channel.Channel = ch;               /* ����ADCX��ͨ��ch */
    adc_channel.Rank = rank;                /* ���ò������� */
    adc_channel.SamplingTime = stime;       /* ���ò���ʱ�� */
    HAL_ADC_ConfigChannel( adc_handle, &adc_channel);   
}

