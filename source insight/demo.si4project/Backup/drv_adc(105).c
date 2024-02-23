#define adc_data_size 100
uint16_t adc_data[adc_data_size];
void drv_adc_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	ADC_InitTypeDef ADC_InitStruct;
	DMA_InitTypeDef DMA_InitStruct;//����ṹ��
	//��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_DMA2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStruct.ADC_DataAlign =ADC_DataAlign_Right;
	ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStruct.ADC_NbrOfConversion = 1;
	ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;
	ADC_Init(ADC1, &ADC_InitStruct);

	DMA_InitStruct.DMA_BufferSize = adc_data_size;//��Ҫ�������ݵ�����
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
	DMA_Cmd(DMA2_Stream0, ENABLE);//ʹ��DMA

	
}

