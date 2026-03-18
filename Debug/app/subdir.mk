################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../app/demo_temperature.c \
../app/main_temp_snippet.c \
../app/temp_app.c \
../app/uart_printf_retarget.c 

OBJS += \
./app/demo_temperature.o \
./app/main_temp_snippet.o \
./app/temp_app.o \
./app/uart_printf_retarget.o 

C_DEPS += \
./app/demo_temperature.d \
./app/main_temp_snippet.d \
./app/temp_app.d \
./app/uart_printf_retarget.d 


# Each subdirectory must supply rules for building sources it contributes
app/%.o app/%.su app/%.cyclo: ../app/%.c app/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U585xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../app -I../sht4x -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-app

clean-app:
	-$(RM) ./app/demo_temperature.cyclo ./app/demo_temperature.d ./app/demo_temperature.o ./app/demo_temperature.su ./app/main_temp_snippet.cyclo ./app/main_temp_snippet.d ./app/main_temp_snippet.o ./app/main_temp_snippet.su ./app/temp_app.cyclo ./app/temp_app.d ./app/temp_app.o ./app/temp_app.su ./app/uart_printf_retarget.cyclo ./app/uart_printf_retarget.d ./app/uart_printf_retarget.o ./app/uart_printf_retarget.su

.PHONY: clean-app

