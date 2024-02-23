
/*****************************************************
函数名称：drv_spi_init

函数功能：初始化spi1

输入参数：无

输出参数：无

其它说明：		mosi-pb5   
			miso-pb4
			mclk-pb3
			nss -pb2
*******************************************************/
void drv_spi_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;//结构体定义
	SPI_InitTypeDef SPI_InitStruct;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOE, ENABLE);//开时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;//gpio初始化
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;//W25Q128片选引脚初始化
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;//lora片选引脚初始化
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOE, &GPIO_InitStruct);

	GPIO_SetBits(GPIOB, GPIO_Pin_2);//默认不选中通信设备
	GPIO_SetBits(GPIOE, GPIO_Pin_1);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_SPI1);//指定复用功能
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_SPI1);

	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;//波特率分频
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;//后沿采样
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;//时钟空闲时为高
	SPI_InitStruct.SPI_CRCPolynomial = 7;//采用CRC计算方式校验
	SPI_InitStruct.SPI_DataSize =SPI_DataSize_8b;//8位数据传输
	SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;//双线全双工
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;//高位先行
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;//主机模式
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;//片选软件控制
	SPI_Init(SPI1, &SPI_InitStruct);//按上面配置参数初始化SPI1
	SPI_Cmd(SPI1, ENABLE);//使能SPI1
}
/*****************************************************
函数名称：drv_spi_wdata

函数功能：SPI读取数据

输入参数：wdata 需要写的数据

输出参数：rdata 读取到的数据

其它说明：		mosi-pb5   
			miso-pb4
			mclk-pb3
			nss -pb2
*******************************************************/

uint8_t drv_spi_wdata(uint8_t wdata)
{
	uint8_t rdata=0;
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE)==RESET);//等待发送完成
	SPI_I2S_SendData(SPI1, wdata);//要读数据先发数据
	
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE)==RESET);//等待发送完成
	rdata = SPI_I2S_ReceiveData(SPI1);//读取数据

	return rdata;//将读到数据返回
}
