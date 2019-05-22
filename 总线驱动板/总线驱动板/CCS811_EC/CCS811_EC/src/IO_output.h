#ifndef __IOOUTPUT_H__
#define __IOOUTPUT_H__

#include "Global.h"

#define WAKE_PIN          GPIO_Pin_1
#define WAKE_GPIO         GPIOB
#define WAKE_ON           GPIO_SetBits(WAKE_GPIO,WAKE_PIN)
#define WAKE_OFF          GPIO_ResetBits(WAKE_GPIO,WAKE_PIN)

#define LED_PIN           GPIO_Pin_9
#define LED_GPIO          GPIOB
#define LED_ON            GPIO_SetBits(LED_GPIO,LED_PIN)
#define LED_OFF           GPIO_ResetBits(LED_GPIO,LED_PIN)
/*   开发板自带LED   PC13*/
#define LED2_PIN           GPIO_Pin_13
#define LED2_GPIO          GPIOC
#define LED2_ON            GPIO_SetBits(LED2_GPIO,LED2_PIN)
#define LED2_OFF           GPIO_ResetBits(LED2_GPIO,LED2_PIN)

#define BUZZ_PIN           GPIO_Pin_8
#define BUZZ_GPIO          GPIOB
#define BUZZ_ON            GPIO_SetBits(BUZZ_GPIO,BUZZ_PIN)
#define BUZZ_OFF           GPIO_ResetBits(BUZZ_GPIO,BUZZ_PIN)

//#define RST_PIN           GPIO_Pin_13
//#define RST_GPIO          GPIOB
//#define RST_ON            GPIO_SetBits(RST_GPIO,RST_PIN)
//#define RST_OFF           GPIO_ResetBits(RST_GPIO,RST_PIN)

void OutputIOInit(void);

#endif
