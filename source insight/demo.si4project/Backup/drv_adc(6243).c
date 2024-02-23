#include "drv_adc.h"
#define adc_data_size 100
uint16_t adc_data[adc_data_size];
void drv_adc_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	ADC_CommonInitTypeDef ADC_CommonInitStruct;
	ADC_InitTypeDef ADC_InitStruct;
	DMA_InitTypeDef DMA_InitStruct;//定义结构体
	
	//开时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_DMA2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	ADC_CommonInitStruct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;//直接模式
	ADC_CommonInitStruct.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStruct.ADC_Prescaler = ADC_Prescaler_Div4; //168/2/4 = 21M
	ADC_CommonInitStruct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//延时5个时钟周期
	ADC_CommonInit(&ADC_CommonInitStruct);
	
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;//连续转换
	ADC_InitStruct.ADC_DataAlign =ADC_DataAlign_Right;
	ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStruct.ADC_NbrOfConversion = 1;
	ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;
	ADC_Init(ADC1, &ADC_InitStruct);

	DMA_InitStruct.DMA_BufferSize = adc_data_size;//需要搬运数据的数量
	DMA_InitStruct.DMA_Channel =DMA_Channel_0;//通道号
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralToMemory;//方向是外设到内存
	DMA_InitStruct.DMA_FIFOMode = DMA_FIFOMode_Disable;//不使用FIFO
	DMA_InitStruct.DMA_Memory0BaseAddr = (uint32_t)adc_data;//目的地址
	DMA_InitStruct.DMA_MemoryBurst = DMA_MemoryBurst_Single;//单次突发
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//半字传输
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;//地址自增
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;//循环模式

	DMA_InitStruct.DMA_PeripheralBaseAddr =  (uint32_t)&ADC1->DR;//数据源
	DMA_InitStruct.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//单次突发传输
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//半字传输
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//地址不自增
	DMA_InitStruct.DMA_Priority = DMA_Priority_VeryHigh;//优先级为非常高
	DMA_Init(DMA2_Stream0, &DMA_InitStruct);//初始化
	DMA_Cmd(DMA2_Stream0, ENABLE);//使能DMA
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_480Cycles);
	ADC_DMARequestAfterLastTransferCmd( ADC1, ENABLE);//设置DMA的触发条件
	ADC_Cmd(ADC1, ENABLE);
	ADC_DMACmd(ADC1, ENABLE);
	ADC_SoftwareStartConv(ADC1);//软件触发ADC转换
}
uint16_t drv_adcdata_sum(void)
{
	uint32_t temp=0;
	uint8_t i=0;
	for(i=0;i<adc_data_size;i++)
	{
		temp= temp + adc_data[i];
	}
	return (uint16_t)(temp/adc_data_size);
}

