#include "stm32f10x.h"                  // Device header
//#include "delay.h" 

void LED_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5);
}
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}
u8 keyscan(void)
{
	u8 flag = 0;
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0) == 0)
	{
		//delay_ms(10);
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0) == 0) flag = 1;
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0) == 0); 
	}
	return flag;
}
main(void)
{
	int i;
	LED_Init();
	KEY_Init();
	while(1)
	{
		if(keyscan()==1)
		{
			i=(i+1)%2;
			if(i==0)
			{
				GPIO_ResetBits(GPIOB,GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_5);
			}
			else if(i==1)
			{
				GPIO_SetBits(GPIOB,GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_5);
			}
		}
	}
}
