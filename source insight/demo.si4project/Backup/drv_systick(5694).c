#include "drv_systick.h"
static uint8_t fs_us=0;
static uint16_t fs_ms=0;
/******************************************
函数名：drv_systick_init

函数功能：滴答定时器初始化

输入参数：systick  系统时钟频率

输出参数：无

其它说明：

*********************************************/ 
void drv_systick_init(uint32_t systick)
{
	SysTick->CTRL &= ~0x05;
	fs_us = systick/8;  //计时1us需要计的次数
	fs_ms = 1000*fs_us;//计时1ms需要计的次数
}
/******************************************
函数名：drv_systick_delayms

函数功能：systick  ms定时

输入参数：ms 需要延时的MS数

输出参数：无

其它说明： 

*********************************************/
void drv_systick_delayms(uint16_t ms)//798问题
{
	uint32_t temp=0;
	uint8_t systick_flg=0;
	while(systick_flg == 0)
	{
		if(ms > 798)
		{
			SysTick->LOAD = fs_ms*798;//重装置寄存器赋值	
		}
		else
		{


		}




	}


	
	SysTick->LOAD = fs_ms*ms;//重装置寄存器赋值
	SysTick->VAL = 0;//清空当前计数寄存器值
	SysTick->CTRL |= 0x01;//打开滴答定时器
	do
	{
		temp = SysTick->CTRL;
	}
	while (!(temp & (0x01 << 16)));//等待计时完成
	SysTick->CTRL &= ~0x01;//关闭滴答定时器
	SysTick->VAL = 0;//清空当前计数寄存器值
}

