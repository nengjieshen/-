
#include "Global.h"


void TIM3_IRQHandler(void) 											//TIME3中断服务函数  需要设定中断优先级  即NVIC配置
{
    if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET)					//判断是否发生了更新(溢出)中断
    {
        TIM_ClearITPendingBit(TIM3,TIM_IT_Update);					//清除溢出中断标志位
    }
}


int main(void)
{
	SystemInit();
	delay_init();
	ServoInit();

	while(1)
	{
		SetServo1PWM(200);
		SetServo2PWM(200);
	}
}
