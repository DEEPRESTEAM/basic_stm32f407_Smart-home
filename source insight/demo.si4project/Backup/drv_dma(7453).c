#include "drv_dma.h"

void drv_dma_init(uint32_t *src,uint32_t *drc,uint32_t size)
{
	DMA_InitTypeDef DMA_InitStruct;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	DMA_InitStruct.DMA_BufferSize = size;
	DMA_InitStruct.DMA_Channel =DMA_Channel_0;
	DMA_InitStruct.DMA_DIR = DMA_DIR_MemoryToMemory;
	DMA_InitStruct.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStruct.DMA_Memory0BaseAddr = drc;//Ä¿µÄµØÖ·
	DMA_InitStruct.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;

	DMA_InitStruct.DMA_PeripheralBaseAddr = *src;
	DMA_InitStruct.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;
	DMA_Init(DMA2_Stream0, &DMA_InitStruct);
	DMA_Cmd(DMA2_Stream0, ENABLE);
}
extern uint32_t dma_src[10];
extern uint32_t dma_drc[10];
void drv_dma_datacompare(void)
{
	uint8_t i=0;
	for(i=0;i<10;i++)	
	{
		if(dma_src[i]!=dma_drc[i])
		{
			printf("dma_datacompare err i=%d\r\n"i);
			return;
		}
	}
	printf("dma_datacompare ok\r\n")

}

