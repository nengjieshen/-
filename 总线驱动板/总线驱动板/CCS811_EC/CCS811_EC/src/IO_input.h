#ifndef __IOINPUT_H__
#define __IOINPUT_H__

#include "Global.h"

#define Key1_PIN          GPIO_Pin_10
#define Key1_GPIO         GPIOA

#define Key2_PIN          GPIO_Pin_15
#define Key2_GPIO         GPIOB

#define INT_PIN           GPIO_PiN_12
#define INT_GPIO          GPIOB

void InputIOInit(void);

#endif
