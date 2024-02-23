#include "drv_led.h"
#include "drv_systick.h"
/*****************************************************
函数名称：delay

函数功能：延时函数

输入参数：无

输出参数：无

其它说明：仅测试用，后面可以删除
*******************************************************/
void delay(uint32_t   tim)
{
	uint32_t i,j;
	for(i=0;i<tim;i++)
	{
		for(j=0;j<10000;j++);
	}
}

int main()
{	
	drv_led_init();
	while(1)
	{
		drv_led_open();
		delay(1000);
		drv_led_close();
		delay(1000);
	}
}


