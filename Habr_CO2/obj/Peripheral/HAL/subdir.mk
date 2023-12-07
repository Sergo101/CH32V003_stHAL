################################################################################
# MRS Version: 1.9.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/MounRiver/ch32v003_EVT/EXAM/SRC/Peripheral/HAL/i2c_hal.c \
D:/MounRiver/ch32v003_EVT/EXAM/SRC/Peripheral/HAL/systick_hal.c 

OBJS += \
./Peripheral/HAL/i2c_hal.o \
./Peripheral/HAL/systick_hal.o 

C_DEPS += \
./Peripheral/HAL/i2c_hal.d \
./Peripheral/HAL/systick_hal.d 


# Each subdirectory must supply rules for building sources it contributes
Peripheral/HAL/i2c_hal.o: D:/MounRiver/ch32v003_EVT/EXAM/SRC/Peripheral/HAL/i2c_hal.c
	@	@	riscv-none-embed-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\MounRiver\ch32v003_EVT\EXAM\SRC\Debug" -I"D:\MounRiver\ch32v003_EVT\EXAM\SRC\Core" -I"D:\MounRiver\ch32v003_EVT\EXAM\GPIO\GPIO_Toggle\User" -I"D:\MounRiver\ch32v003_EVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/HAL/systick_hal.o: D:/MounRiver/ch32v003_EVT/EXAM/SRC/Peripheral/HAL/systick_hal.c
	@	@	riscv-none-embed-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\MounRiver\ch32v003_EVT\EXAM\SRC\Debug" -I"D:\MounRiver\ch32v003_EVT\EXAM\SRC\Core" -I"D:\MounRiver\ch32v003_EVT\EXAM\GPIO\GPIO_Toggle\User" -I"D:\MounRiver\ch32v003_EVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

