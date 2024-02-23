
/*****************************************************
�������ƣ�drv_spi_init

�������ܣ���ʼ��spi1

�����������

�����������

����˵����		mosi-pb5   
			miso-pb4
			mclk-pb3
			nss -pb2
*******************************************************/
void drv_spi_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;//�ṹ�嶨��
	SPI_InitTypeDef SPI_InitStruct;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOE, ENABLE);//��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;//gpio��ʼ��
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;//W25Q128Ƭѡ���ų�ʼ��
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;//loraƬѡ���ų�ʼ��
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOE, &GPIO_InitStruct);

	GPIO_SetBits(GPIOB, GPIO_Pin_2);//Ĭ�ϲ�ѡ��ͨ���豸
	GPIO_SetBits(GPIOE, GPIO_Pin_1);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_SPI1);//ָ�����ù���
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_SPI1);

	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;//�����ʷ�Ƶ
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;//���ز���
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;//ʱ�ӿ���ʱΪ��
	SPI_InitStruct.SPI_CRCPolynomial = 7;//����CRC���㷽ʽУ��
	SPI_InitStruct.SPI_DataSize =SPI_DataSize_8b;//8λ���ݴ���
	SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;//˫��ȫ˫��
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;//��λ����
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;//����ģʽ
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;//Ƭѡ�������
	SPI_Init(SPI1, &SPI_InitStruct);//���������ò�����ʼ��SPI1
	SPI_Cmd(SPI1, ENABLE);//ʹ��SPI1
}
/*****************************************************
�������ƣ�drv_spi_wdata

�������ܣ�SPI��ȡ����

���������wdata ��Ҫд������

���������rdata ��ȡ��������

����˵����		mosi-pb5   
			miso-pb4
			mclk-pb3
			nss -pb2
*******************************************************/

uint8_t drv_spi_wdata(uint8_t wdata)
{
	uint8_t rdata=0;
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE)==RESET);//�ȴ��������
	SPI_I2S_SendData(SPI1, wdata);//Ҫ�������ȷ�����
	
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE)==RESET);//�ȴ��������
	rdata = SPI_I2S_ReceiveData(SPI1);//��ȡ����

	return rdata;//���������ݷ���
}
