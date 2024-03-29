#include "drv_dma.h"
#include "stdio.h"
/******************************************
函数名：drv_dma_init

函数功能：DMA初始化

输入参数：src：数据源，drc：目的地                  size：搬运数据的数量

输出参数：无

其它说明：

*********************************************/
void drv_dma_init(uint32_t *src,uint32_t *drc,uint32_t size)
{
	DMA_InitTypeDef DMA_InitStruct;//定义结构体
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);//开时钟
	DMA_InitStruct.DMA_BufferSize = size;//需要搬运数据的数量
	DMA_InitStruct.DMA_Channel =DMA_Channel_0;//通道号
	DMA_InitStruct.DMA_DIR = DMA_DIR_MemoryToMemory;//方向是内存到内存
	DMA_InitStruct.DMA_FIFOMode = DMA_FIFOMode_Disable;//不使用FIFO
	DMA_InitStruct.DMA_Memory0BaseAddr = (uint32_t)drc;//目的地址
	DMA_InitStruct.DMA_MemoryBurst = DMA_MemoryBurst_Single;//单次突发
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;//全字传输
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;//地址自增
	DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;

	DMA_InitStruct.DMA_PeripheralBaseAddr =  (uint32_t)src;
	DMA_InitStruct.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;
	DMA_Init(DMA2_Stream0, &DMA_InitStruct);
	DMA_Cmd(DMA2_Stream0, ENABLE);
}
extern uint32_t dma_src[10];
extern uint32_t dma_drc[10];
/******************************************
函数名：drv_dma_datacompare

函数功能：对DMA搬运的数据进行校验

输入参数：无

输出参数：无

其它说明：

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

