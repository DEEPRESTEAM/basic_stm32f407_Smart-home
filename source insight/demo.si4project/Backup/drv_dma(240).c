

void drv_dma_init(uint32_t *src,uint32_t *drc,uint32_t size)
{
	DMA_InitTypeDef DMA_InitStruct;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	DMA_InitStruct.DMA_BufferSize = size;
	DMA_InitStruct.DMA_Channel =DMA_Channel_0;
	
	DMA_Init(DMA_Stream_TypeDef DMA2_Stream0, DMA_InitTypeDef * DMA_InitStruct)


}
