#include "drv_dma.h"
#include "stdio.h"
/******************************************
��������drv_dma_init

�������ܣ�DMA��ʼ��

���������src������Դ��drc��Ŀ�ĵ�                  size���������ݵ�����

�����������

����˵����

*********************************************/
void drv_dma_init(uint32_t *src,uint32_t *drc,uint32_t size)
{
	DMA_InitTypeDef DMA_InitStruct;//����ṹ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);//��ʱ��
	DMA_InitStruct.DMA_BufferSize = size;//��Ҫ�������ݵ�����
	DMA_InitStruct.DMA_Channel =DMA_Channel_0;//ͨ����
	DMA_InitStruct.DMA_DIR = DMA_DIR_MemoryToMemory;//�������ڴ浽�ڴ�
	DMA_InitStruct.DMA_FIFOMode = DMA_FIFOMode_Disable;//��ʹ��FIFO
	DMA_InitStruct.DMA_Memory0BaseAddr = (uint32_t)drc;//Ŀ�ĵ�ַ
	DMA_InitStruct.DMA_MemoryBurst = DMA_MemoryBurst_Single;//����ͻ��
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;//ȫ�ִ���
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;//��ַ����
	DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;//��ͨ����ģʽ������ģʽ��

	DMA_InitStruct.DMA_PeripheralBaseAddr =  (uint32_t)src;//����Դ
	DMA_InitStruct.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//����ͻ������
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;//ȫ�ִ���
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Enable;//��ַ����
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;//���ȼ�Ϊ��
	DMA_Init(DMA2_Stream0, &DMA_InitStruct);//��ʼ��
	DMA_Cmd(DMA2_Stream0, ENABLE);
}
extern uint32_t dma_src[10];
extern uint32_t dma_drc[10];
/******************************************
��������drv_dma_datacompare

�������ܣ���DMA���˵����ݽ���У��

�����������

�����������

����˵����

*********************************************/

void drv_dma_datacompare(void)
{
	uint8_t i=0;
	for(i=0;i<10;i++)	
	{
		if(dma_src[i]!=dma_drc[i])
		{
			printf("dma_datacompare err i=%d\r\n",i);
			return;
		}
	}
	printf("dma_datacompare ok:dma_drc[0]=0x%x,dma_drc[4]=0x%x,dma_drc[9]=0x%x\r\n",dma_drc[0],dma_drc[4],dma_drc[9]);

}
