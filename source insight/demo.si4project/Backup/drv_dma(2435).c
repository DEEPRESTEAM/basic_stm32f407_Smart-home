

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
	
	
	DMA_Init(DMA_Stream_TypeDef DMA2_Stream0, DMA_InitTypeDef * DMA_InitStruct)


}
