################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/MounRiver/ch32v003_EVT/EXAM/My\ Way/HAL/i2c_hal.c \
D:/MounRiver/ch32v003_EVT/EXAM/My\ Way/HAL/spi_hal.c \
D:/MounRiver/ch32v003_EVT/EXAM/My\ Way/HAL/systick_hal.c 

OBJS += \
./HAL/i2c_hal.o \
./HAL/spi_hal.o \
./HAL/systick_hal.o 

C_DEPS += \
./HAL/i2c_hal.d \
./HAL/spi_hal.d \
./HAL/systick_hal.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/i2c_hal.o: D:/MounRiver/ch32v003_EVT/EXAM/My\ Way/HAL/i2c_hal.c
	@	@	riscv-none-embed-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\MounRiver\ch32v003_EVT\EXAM\SRC\Debug" -I"D:\MounRiver\ch32v003_EVT\EXAM\SRC\Core" -I"D:\MounRiver\ch32v003_EVT\EXAM\My Way\Habr_CO2\User" -I"D:\MounRiver\ch32v003_EVT\EXAM\SRC\Peripheral\inc" -I"D:\MounRiver\ch32v003_EVT\EXAM\My Way\HAL" -I"D:\MounRiver\ch32v003_EVT\EXAM\My Way\Habr_CO2\User\ssd1306" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
HAL/spi_hal.o: D:/MounRiver/ch32v003_EVT/EXAM/My\ Way/HAL/spi_hal.c
	@	@	riscv-none-embed-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\MounRiver\ch32v003_EVT\EXAM\SRC\Debug" -I"D:\MounRiver\ch32v003_EVT\EXAM\SRC\Core" -I"D:\MounRiver\ch32v003_EVT\EXAM\My Way\Habr_CO2\User" -I"D:\MounRiver\ch32v003_EVT\EXAM\SRC\Peripheral\inc" -I"D:\MounRiver\ch32v003_EVT\EXAM\My Way\HAL" -I"D:\MounRiver\ch32v003_EVT\EXAM\My Way\Habr_CO2\User\ssd1306" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
HAL/systick_hal.o: D:/MounRiver/ch32v003_EVT/EXAM/My\ Way/HAL/systick_hal.c
	@	@	riscv-none-embed-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\MounRiver\ch32v003_EVT\EXAM\SRC\Debug" -I"D:\MounRiver\ch32v003_EVT\EXAM\SRC\Core" -I"D:\MounRiver\ch32v003_EVT\EXAM\My Way\Habr_CO2\User" -I"D:\MounRiver\ch32v003_EVT\EXAM\SRC\Peripheral\inc" -I"D:\MounRiver\ch32v003_EVT\EXAM\My Way\HAL" -I"D:\MounRiver\ch32v003_EVT\EXAM\My Way\Habr_CO2\User\ssd1306" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

