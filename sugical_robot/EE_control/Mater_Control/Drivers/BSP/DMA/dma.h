/**
 ****************************************************************************************************
 * @file        dma.h
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2021-10-18
 * @brief       DMA ��������
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
 *
 ****************************************************************************************************
 */

#ifndef __DMA_H
#define	__DMA_H

#include "./SYSTEM/sys/sys.h"

void dma_map_config(DMA_Stream_TypeDef* DMAx_CHx,uint32_t src,uint32_t dest);                 /* �ڴ�ӳ�������ʼ������ */
void dma_usart1_tx_config(uint32_t mar);                        /* ����1 TX DMA��ʼ�� */
void dma_enable(DMA_Stream_TypeDef *dmax_chy, uint16_t ndtr); /* ʹ��һ��DMA���� */
void dma_basic_config(DMA_Stream_TypeDef *dmax_chy,  uint32_t par, uint32_t mar);  /* DMA�������� */
#endif






























