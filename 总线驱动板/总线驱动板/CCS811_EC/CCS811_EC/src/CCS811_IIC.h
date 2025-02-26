#ifndef _IIC_H
#define _IIC_H
#include "Global.h"
#define SCL_H         GPIOB->BSRR = GPIO_Pin_10
#define SCL_L         GPIOB->BRR  = GPIO_Pin_10
   
#define SDA_H         GPIOB->BSRR = GPIO_Pin_11
#define SDA_L         GPIOB->BRR  = GPIO_Pin_11

#define SCL_read      GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)
#define SDA_read      GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)
void CCS811_I2C_GPIO_Config(void);
void CCS811_I2C_Stop(void);
u8 CCS811_WriteI2C_byte(u8 Slave_Address,u8 REG_Address,u8 data);
u8 CCS811_MWriteI2C_byte(u8 Slave_Address,u8 REG_Address,u8 const *data,u8 length);
u8 CCS811_ReadI2C(u8 Slave_Address,u8 REG_Address,u8 *REG_data,u8 length);
#endif
