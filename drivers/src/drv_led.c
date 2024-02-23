#include "drv_led.h"
/*****************************************************
�������ƣ�drv_led_init

�������ܣ���ʼ��led

�����������

�����������

����˵����PE8-LED1 �͵�ƽ��
*******************************************************/
void drv_led_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	//��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;//���ģʽ
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;//����
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;//����
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;//����
	
	GPIO_Init(GPIOE, &GPIO_InitStruct);//�����������������ʼ��GPIOE
	GPIO_SetBits(GPIOE, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10);//��ʼ��Ĭ�Ϲر�led
}
/*****************************************************
�������ƣ�drv_led_open

�������ܣ���led

�����������

�����������

����˵����PE8-LED1 �͵�ƽ��
*******************************************************/
void drv_led_open(uint16_t GPIO_Pin)
{
	GPIO_ResetBits(GPIOE , GPIO_Pin);
}
/*****************************************************
�������ƣ�drv_led_close

�������ܣ��ر�led

�����������

�����������

����˵����PE8-LED1 �ߵ�ƽ�ر�
*******************************************************/
void drv_led_close(uint16_t GPIO_Pin)
{
	GPIO_SetBits(GPIOE, GPIO_Pin);
}

