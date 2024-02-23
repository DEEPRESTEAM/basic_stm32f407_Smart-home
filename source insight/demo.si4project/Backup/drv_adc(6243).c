#include "drv_adc.h"
#define adc_data_size 100
uint16_t adc_data[adc_data_size];
void drv_adc_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	ADC_CommonInitTypeDef ADC_CommonInitStruct;
	ADC_InitTypeDef ADC_InitStruct;
	DMA_InitTypeDef DMA_InitStruct;//����ṹ��
	
	//��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_DMA2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	ADC_CommonInitStruct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;//ֱ��ģʽ
	ADC_CommonInitStruct.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStruct.ADC_Prescaler = ADC_Prescaler_Div4; //168/2/4 = 21M
	ADC_CommonInitStruct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//��ʱ5��ʱ������
	ADC_CommonInit(&ADC_CommonInitStruct);
	
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;//����ת��
	ADC_InitStruct.ADC_DataAlign =ADC_DataAlign_Right;
	ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStruct.ADC_NbrOfConversion = 1;
	ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;
	ADC_Init(ADC1, &ADC_InitStruct);

	DMA_InitStruct.DMA_BufferSize = adc_data_size;//��Ҫ�������ݵ�����
	DMA_InitStruct.DMA_Channel =DMA_Channel_0;//ͨ����
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralToMemory;//���������赽�ڴ�
	DMA_InitStruct.DMA_FIFOMode = DMA_FIFOMode_Disable;//��ʹ��FIFO
	DMA_InitStruct.DMA_Memory0BaseAddr = (uint32_t)adc_data;//Ŀ�ĵ�ַ
	DMA_InitStruct.DMA_MemoryBurst = DMA_MemoryBurst_Single;//����ͻ��
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//���ִ���
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;//��ַ����
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;//ѭ��ģʽ

	DMA_InitStruct.DMA_PeripheralBaseAddr =  (uint32_t)&ADC1->DR;//����Դ
	DMA_InitStruct.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//����ͻ������
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//���ִ���
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//��ַ������
	DMA_InitStruct.DMA_Priority = DMA_Priority_VeryHigh;//���ȼ�Ϊ�ǳ���
	DMA_Init(DMA2_Stream0, &DMA_InitStruct);//��ʼ��
	DMA_Cmd(DMA2_Stream0, ENABLE);//ʹ��DMA
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_480Cycles);
	ADC_DMARequestAfterLastTransferCmd( ADC1, ENABLE);//����DMA�Ĵ�������
	ADC_Cmd(ADC1, ENABLE);
	ADC_DMACmd(ADC1, ENABLE);
	ADC_SoftwareStartConv(ADC1);//�������ADCת��
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

