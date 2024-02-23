#include "drv_key.h"
#include "drv_systick.h"
/******************************************
��������drv_key_init

�������ܣ�������ʼ��

�����������

�����������

����˵����PE4 - KEY1

*********************************************/
void drv_key_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOE, &GPIO_InitStruct);
}
/******************************************
��������drv_keydata

�������ܣ���������

�����������

����������������·���1

����˵����PE4 - KEY1

*********************************************/
uint8_t drv_key_scan(void)
{
	uint8_t ret=0;
	if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4) == 0)//���GPIOE4��ƽ�Ƿ�Ϊ�͵�ƽ
	{
		drv_systick_delayms(20);//��ʱ20ms
		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4) == 0)//���GPIOE4��ƽ�Ƿ�Ϊ�͵�ƽ
		{
			while(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4) == 0);//�ȴ�����̧�𣨼��GPIOE4��ƽ�Ƿ�Ϊ�ߵ�ƽ��
			ret=1;
			
		}

	}
	return ret;
}
