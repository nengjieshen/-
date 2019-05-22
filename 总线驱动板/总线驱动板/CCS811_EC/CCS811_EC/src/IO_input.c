#include "IO_input.h"

void InputIOInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

u8 GetKeyState(u8 keynum)
{
	u8 Temp = 0;
	if(keynum == 1) Temp = GPIO_ReadInputDataBit(Key1_GPIO, Key1_PIN);
	else Temp = GPIO_ReadInputDataBit(Key2_GPIO, Key2_PIN);
	return Temp;
}

u8 ButtomPush(void)
{
	u8 Key_state =0;
	Key_state = GetKeyState(1);
	if(Key_state==0)
	{
		while(1)
		{
			if(GetKeyState(1)==1) break;
		}
		return 1;
	}
	else return 0;

}

