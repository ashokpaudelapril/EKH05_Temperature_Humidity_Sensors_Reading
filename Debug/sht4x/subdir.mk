################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../sht4x/sensirion_common.c \
../sht4x/sensirion_i2c.c \
../sht4x/sensirion_i2c_hal.c \
../sht4x/sht4x_i2c.c 

OBJS += \
./sht4x/sensirion_common.o \
./sht4x/sensirion_i2c.o \
./sht4x/sensirion_i2c_hal.o \
./sht4x/sht4x_i2c.o 

C_DEPS += \
./sht4x/sensirion_common.d \
./sht4x/sensirion_i2c.d \
./sht4x/sensirion_i2c_hal.d \
./sht4x/sht4x_i2c.d 


# Each subdirectory must supply rules for building sources it contributes
sht4x/%.o sht4x/%.su sht4x/%.cyclo: ../sht4x/%.c sht4x/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U585xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../app -I../sht4x -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-sht4x

clean-sht4x:
	-$(RM) ./sht4x/sensirion_common.cyclo ./sht4x/sensirion_common.d ./sht4x/sensirion_common.o ./sht4x/sensirion_common.su ./sht4x/sensirion_i2c.cyclo ./sht4x/sensirion_i2c.d ./sht4x/sensirion_i2c.o ./sht4x/sensirion_i2c.su ./sht4x/sensirion_i2c_hal.cyclo ./sht4x/sensirion_i2c_hal.d ./sht4x/sensirion_i2c_hal.o ./sht4x/sensirion_i2c_hal.su ./sht4x/sht4x_i2c.cyclo ./sht4x/sht4x_i2c.d ./sht4x/sht4x_i2c.o ./sht4x/sht4x_i2c.su

.PHONY: clean-sht4x

