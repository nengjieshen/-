/////////////////////////////////////////////////////////////////
//
// 本程序只供学习使用，未经作者许可，不得用于其它任何用途
// STM32F103C8T6核心板	   
// by Pang
// 修改日期:2019/01/02
// 版本：V1.0
// 版权所有，盗版必究。
// All rights reserved
// 模块接线方式：PB10-I2C_SCL、PB11-I2C_SDA、PA4-nWAK
//
////////////////////////////////////////////////////////////////
#include "CCS811.h"
u8 BUF[12];
u8 Information[10];
u8 MeasureMode, Status, Error_ID;
u8 FlagGetId = 1;
u8 n         = 4;                                        // 3次读取ID都对则说明没问题
u8 temp      = 0x5a;
ccs811_measurement_t CCS;

#define STEP_DELAY 100

void CCS811_GPIO_Config()
{

	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //开端口时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;					 		 // CCS811-CS
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	     //推挽输出
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //开端口时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;					 		 // CCS811-CS
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	     //推挽输出
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	CCS811_CS_OFF();

	CCS811_I2C_GPIO_Config(); 													   //IIC GPIO Configure
}

void CCS811Init()
{
	u8 idCount = 0;               // count the correct times of id.
	CCS811_CS_ON(); 					   	//nWAKE pin is asserted at least 50μs before the transaction and kept asserted throughout,nWAKE pin is active low
	delay_ms(STEP_DELAY);
	// get CCS811 device id,when addr pin connect to GND and the id is 0x81(129)
	while( FlagGetId)
	{
		CCS811_ReadI2C(CCS811_Add, 0x20, Information, 1); //Read CCS's information  ,ID
		if(Information[0] == 0x81)
		{
			if(++idCount == n)
			{
				FlagGetId = 0;
			}
			else
			{
				//printf("id=%d,correct %d!\r\n", Information[0], idCount);
			}
		}
		else
		{
			//printf("id=%d,incorrect,continuing...\r\n", Information[0]);
		}
		delay_ms(STEP_DELAY);
	}
	//printf("id correct,initing...\r\n");
	delay_ms(STEP_DELAY);
	CCS811_ReadI2C(CCS811_Add, 0x23, &Information[1], 2);	  //FW_Boot_Version
	delay_ms(STEP_DELAY);
	CCS811_ReadI2C(CCS811_Add, 0x24, &Information[3], 2); 	//FW_App_Version
	delay_ms(STEP_DELAY);
	CCS811_ReadI2C(CCS811_Add, 0x00, &Status, 1);	          //Firstly the status register is read and the APP_VALID flag is checked.
	delay_ms(STEP_DELAY);
	// if there is valid application firmware loaded
	if(Status & 0x10)
	{

		while(!(Status & 0x80)) // if firmware not in application mode but boot mode.
		{
			CCS811_WriteI2C_byte(CCS811_Add, 0xF3, 0xF0);	      // Application Verify
			//printf("trying to transition the CCS811 state from boot to application mode...\r\n");
			CCS811_MWriteI2C_byte(CCS811_Add, 0xF4, &temp, 0);	//Used to transition the CCS811 state from boot to application mode, a write with no data is required.
			delay_ms(STEP_DELAY);
			CCS811_ReadI2C(CCS811_Add, 0x00, &Status, 1);
			delay_ms(STEP_DELAY);

		}
		//printf("CCS811 is already in application mode!\r\n");
	}
	delay_ms(STEP_DELAY);
	CCS811_ReadI2C(CCS811_Add, 0x01, &MeasureMode, 1);
	delay_ms(STEP_DELAY);
	MeasureMode &= 0x70;                                       // get measure mode
	//if measure mode incorrect,and reset the measure mode.
	while(MeasureMode != DRIVE_MODE_1SEC)
	{
		CCS811_WriteI2C_byte(CCS811_Add, 0x01, DRIVE_MODE_1SEC); // Write Measure Mode Register,sensor measurement every second,no interrupt
		delay_ms(STEP_DELAY);
		CCS811_ReadI2C(CCS811_Add, 0x01, &MeasureMode, 1);
		MeasureMode &= 0x70;
		//printf("trying to enter measure mode...\r\n");
		delay_ms(STEP_DELAY);
	}
	delay_ms(STEP_DELAY);
	CCS811_ReadI2C(CCS811_Add, 0x00, &Status, 1);
	delay_ms(STEP_DELAY);
	CCS811_ReadI2C(CCS811_Add, 0x01, &MeasureMode, 1);
	delay_ms(STEP_DELAY);
	CCS811_CS_OFF();
	delay_ms(STEP_DELAY);
	CCS811_ReadI2C(CCS811_Add, 0xE0, &Error_ID, 1);
	//printf("status=%d error_id=%d measureMode=%d \r\n", Status, Error_ID, MeasureMode);

}

void CCS811GetData()
{
	CCS811_CS_ON(); 	// nWAKE pin is asserted at least 50μs before the transaction and kept asserted throughout,nWAKE pin is active low
	delay_ms(10);
	CCS811_ReadI2C(CCS811_Add, 0x02, BUF, 8);
	delay_ms(10);
	CCS811_ReadI2C(CCS811_Add, 0x20, Information, 1); // Read CCS's information  ,ID
	delay_ms(10);
	CCS811_ReadI2C(CCS811_Add, 0xE0, &Error_ID, 1);
	CCS811_CS_OFF();
	CCS.eco2 = (u16)BUF[0] * 256 + BUF[1];
	CCS.tvoc = (u16)BUF[2] * 256 + BUF[3];
	CCS.device_id  = Information[0];
	CCS.error_id   = Error_ID;
	Error_ID       = 0;
	Information[0] = 0;
}

void CCS811ClearData()
{
	CCS.device_id = 0;
	CCS.eco2      = 0;
	CCS.status    = 0;
	CCS.tvoc      = 0;
	CCS.error_id  = 0;

}
