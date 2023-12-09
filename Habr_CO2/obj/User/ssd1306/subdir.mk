################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/ssd1306/fonts.c \
../User/ssd1306/ssd1306.c 

OBJS += \
./User/ssd1306/fonts.o \
./User/ssd1306/ssd1306.o 

C_DEPS += \
./User/ssd1306/fonts.d \
./User/ssd1306/ssd1306.d 


# Each subdirectory must supply rules for building sources it contributes
User/ssd1306/%.o: ../User/ssd1306/%.c
	@	@	riscv-none-embed-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\MounRiver\ch32v003_EVT\EXAM\SRC\Debug" -I"D:\MounRiver\ch32v003_EVT\EXAM\SRC\Core" -I"D:\MounRiver\ch32v003_EVT\EXAM\CH32V003_stHAL\Habr_CO2\User" -I"D:\MounRiver\ch32v003_EVT\EXAM\SRC\Peripheral\inc" -I"D:\MounRiver\ch32v003_EVT\EXAM\CH32V003_stHAL\HAL" -I"D:\MounRiver\ch32v003_EVT\EXAM\CH32V003_stHAL\Habr_CO2\User\ssd1306" -I"D:\MounRiver\ch32v003_EVT\EXAM\CH32V003_stHAL\Habr_CO2\User\scd4x" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

