################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32.s 

OBJS += \
./startup/startup_stm32.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-as -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -I"E:/毕设/总线驱动板/总线驱动板/CCS811_EC/CCS811_EC/StdPeriph_Driver/inc" -I"E:/毕设/总线驱动板/总线驱动板/CCS811_EC/CCS811_EC/inc" -I"E:/毕设/总线驱动板/总线驱动板/CCS811_EC/CCS811_EC/CMSIS/device" -I"E:/毕设/总线驱动板/总线驱动板/CCS811_EC/CCS811_EC/CMSIS/core" -I"E:/毕设/总线驱动板/总线驱动板/CCS811_EC/CCS811_EC/Drivers" -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


