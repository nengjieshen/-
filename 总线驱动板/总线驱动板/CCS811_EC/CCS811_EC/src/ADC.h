#ifndef __ADC_H__
#define __ADC_H__

#include "Global.h"

#define ADC1_PIN         GPIO_Pin_4
#define ADC1_GPIO        GPIOA
#define ADC1_CH          4
#define ADC1_ADC         ADC2

void ADCIOInit(void);
void ADCInit(void);
u16 GetADCValue(void);

#endif
