#ifndef __PWM_H__
#define __PWM_H__

#include "Global.h"

#define Servo_A_PIN       GPIO_Pin_8
#define Servo_B_PIN       GPIO_Pin_7
#define Servo_C_PIN       GPIO_Pin_6

#define Servo_GPIO        GPIOB

#define Servo_TIM         TIM4
#define Servo_Period      2000

void ServoIOInit(void);
void ServoTIMInit(void);
void ServoInit(void);
void SetServo1PWM(u16 xpwm);
void SetServo2PWM(u16 xpwm);

#endif
