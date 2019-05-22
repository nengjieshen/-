################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ADC.c \
../src/CCS811.c \
../src/CCS811_IIC.c \
../src/Delay.c \
../src/IO_input.c \
../src/IO_output.c \
../src/PWM.c \
../src/Timer.c \
../src/Usart.c \
../src/main.c \
../src/oled.c \
../src/sys.c \
../src/syscalls.c \
../src/system_stm32f10x.c 

OBJS += \
./src/ADC.o \
./src/CCS811.o \
./src/CCS811_IIC.o \
./src/Delay.o \
./src/IO_input.o \
./src/IO_output.o \
./src/PWM.o \
./src/Timer.o \
./src/Usart.o \
./src/main.o \
./src/oled.o \
./src/sys.o \
./src/syscalls.o \
./src/system_stm32f10x.o 

C_DEPS += \
./src/ADC.d \
./src/CCS811.d \
./src/CCS811_IIC.d \
./src/Delay.d \
./src/IO_input.d \
./src/IO_output.d \
./src/PWM.d \
./src/Timer.d \
./src/Usart.d \
./src/main.d \
./src/oled.d \
./src/sys.d \
./src/syscalls.d \
./src/system_stm32f10x.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -I"E:/毕设/总线驱动板/总线驱动板/CCS811_EC/CCS811_EC/StdPeriph_Driver/inc" -I"E:/毕设/总线驱动板/总线驱动板/CCS811_EC/CCS811_EC/Drivers" -I"E:/毕设/总线驱动板/总线驱动板/CCS811_EC/CCS811_EC/inc" -I"E:/毕设/总线驱动板/总线驱动板/CCS811_EC/CCS811_EC/CMSIS/device" -I"E:/毕设/总线驱动板/总线驱动板/CCS811_EC/CCS811_EC/CMSIS/core" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


