#include "ADC.h"

void ADCIOInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = ADC1_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(ADC1_GPIO, &GPIO_InitStructure);
}

void ADCInit(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 16;
	ADC_Init(ADC1_ADC, &ADC_InitStructure);

	 ADC_Cmd(ADC1_ADC, ENABLE);
	 ADC_ResetCalibration(ADC1_ADC);
	 while(ADC_GetResetCalibrationStatus(ADC1_ADC));

	 ADC_StartCalibration(ADC1_ADC);
	 while(ADC_GetCalibrationStatus(ADC1_ADC));
	 ADC_SoftwareStartConvCmd(ADC1_ADC, ENABLE);
}

u16 GetADCValue(void)
{
	u16  ADC_data = 0;
	ADC_SoftwareStartConvCmd(ADC1_ADC, DISABLE);
	ADC_RegularChannelConfig(ADC1_ADC,ADC1_CH, 1, ADC_SampleTime_7Cycles5);
	ADC_SoftwareStartConvCmd(ADC1_ADC, ENABLE);
	while(!ADC_GetFlagStatus(ADC1_ADC,ADC_FLAG_EOC));
	ADC_data = ADC_GetConversionValue(ADC1_ADC);
	ADC_SoftwareStartConvCmd(ADC1_ADC, DISABLE);
	return ADC_data;
}
