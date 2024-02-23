#include "drv_systick.h"
static uint8_t fs_us=0;
static uint16_t fs_ms=0;
/******************************************
��������drv_systick_init

�������ܣ��δ�ʱ����ʼ��

���������systick  ϵͳʱ��Ƶ��

�����������

����˵����

*********************************************/ 
void drv_systick_init(uint32_t systick)
{
	SysTick->CTRL &= ~0x05;
	fs_us = systick/8;  //��ʱ1us��Ҫ�ƵĴ���
	fs_ms = 1000*fs_us;//��ʱ1ms��Ҫ�ƵĴ���
}
/******************************************
��������drv_systick_delayms

�������ܣ�systick  ms��ʱ

���������ms ��Ҫ��ʱ��MS��

�����������

����˵���� 

*********************************************/
void drv_systick_delayms(uint16_t ms)//798����
{
	uint32_t temp=0;
	uint8_t systick_flg=0;
	while(systick_flg == 0)
	{
		if(ms > 798)
		{
			SysTick->LOAD = fs_ms*798;//��װ�üĴ�����ֵ	
		}
		else
		{


		}




	}


	
	SysTick->LOAD = fs_ms*ms;//��װ�üĴ�����ֵ
	SysTick->VAL = 0;//��յ�ǰ�����Ĵ���ֵ
	SysTick->CTRL |= 0x01;//�򿪵δ�ʱ��
	do
	{
		temp = SysTick->CTRL;
	}
	while (!(temp & (0x01 << 16)));//�ȴ���ʱ���
	SysTick->CTRL &= ~0x01;//�رյδ�ʱ��
	SysTick->VAL = 0;//��յ�ǰ�����Ĵ���ֵ
}

