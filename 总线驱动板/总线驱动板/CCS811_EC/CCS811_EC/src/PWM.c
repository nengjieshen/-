#include "PWM.h"

void ServoIOInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = Servo_A_PIN|Servo_B_PIN|Servo_C_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(Servo_GPIO, &GPIO_InitStructure);
}

void ServoTIMInit(void)
{
    TIM_TimeBaseInitTypeDef TIM4_TimeBaseStructure;
    TIM_OCInitTypeDef TIM4_OCInitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

    TIM4_TimeBaseStructure.TIM_Prescaler = 700;
    TIM4_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM4_TimeBaseStructure.TIM_Period = Servo_Period;
    TIM4_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM4_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(Servo_TIM, &TIM4_TimeBaseStructure);

    TIM4_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
    TIM4_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM4_OCInitStructure.TIM_OutputNState=TIM_OutputState_Disable;
    TIM4_OCInitStructure.TIM_Pulse =140; //SERVO_Period >> 1;
    TIM4_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM4_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
    TIM4_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;

    TIM_OC1Init(Servo_TIM, &TIM4_OCInitStructure);
    TIM_OC1PreloadConfig(Servo_TIM, TIM_OCPreload_Enable);

    TIM_OC2Init(Servo_TIM, &TIM4_OCInitStructure);
    TIM_OC2PreloadConfig(Servo_TIM, TIM_OCPreload_Enable);

    TIM_Cmd(Servo_TIM, ENABLE);
    TIM_CtrlPWMOutputs(Servo_TIM,ENABLE);
}

void ServoInit(void)
{
    ServoIOInit();
    ServoTIMInit();
}

void SetServo1PWM(u16 xpwm)
{
    TIM_SetCompare1(Servo_TIM,xpwm);
}

void SetServo2PWM(u16 xpwm)
{
    TIM_SetCompare2(Servo_TIM,xpwm);
}
