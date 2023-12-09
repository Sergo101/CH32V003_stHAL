/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2022/08/08
 * Description        : Main program body.
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/
/*
 *@Note
 *GPIO routine:
 *PD0 push-pull output.
 *
*/

#include "debug.h"
#include "systick_hal.h"
#include "i2c_hal.h"
#include <string.h>

#include "SSD1306.h"
#include "scd4x.h"

/* Global define */

/* Global Variable */

/*********************************************************************
 * @fn      GPIO_Toggle_INIT
 *
 * @brief   Initializes GPIOA.0
 *
 * @return  none
 */
void GPIO_Toggle_INIT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
}

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    SystemCoreClockUpdate();
    Delay_Init();
    USART_Printf_Init(115200);
    printf("SystemClk:%d\r\n", SystemCoreClock);
    printf( "ChipID:%08x\r\n", DBGMCU_GetCHIPID() );
    printf("GPIO Toggle TEST\r\n");
    
    GPIO_Toggle_INIT();

    uint8_t buff[32];
    Systick_Init ();
    HAL_I2C_Init(400000, 0xEE);
    SSD1306_Init();
    scd4x_Init();

    SSD1306_Fill(SSD1306_COLOR_BLACK);
           sprintf (buff,"Dushnometr");
           SSD1306_GotoXY(0, 0);
           SSD1306_Puts(buff, &Font_11x18, SSD1306_COLOR_WHITE);
           SSD1306_UpdateScreen();
           delay_1ms(1500);

uint16_t co2_conc = 0, rh = 0;
int16_t temp = 0;
uint32_t time = 0, prev_time = 0;
uint8_t sensor_disconnect = 0;
uint8_t err_code;
uint8_t data[32];

while(1)
    {
        err_code = scd4x_is_data_ready();
        if (err_code == 0) //data ready
            {
                 scd4x_read_measurement(&co2_conc, &temp, &rh);
                 time = (get_tick() - prev_time)/100;
                 prev_time = get_tick();

            }
        else if (err_code != SCD4x_DATA_NOT_READY) //i2c bus error
            {
                 sensor_disconnect = 1;
            }

        if (sensor_disconnect)//sensor reinit
            {
                if (scd4x_Init() == 0){
                    sensor_disconnect = 0;
                    }
            }

        SSD1306_Fill(SSD1306_COLOR_BLACK);

        sprintf (data, "CO2:%dppm", co2_conc);
        SSD1306_GotoXY(0, 0);
        SSD1306_Puts(data, &Font_11x18, SSD1306_COLOR_WHITE);

        sprintf (data, "RH:%d.%d  T:%d'C",rh/10, rh%10, temp);
        SSD1306_GotoXY(0, 25);
        SSD1306_Puts(data, &Font_7x10, SSD1306_COLOR_WHITE);

        sprintf (data, "time:%d.%d d/c:%d",time/10, time%10, sensor_disconnect);
        SSD1306_GotoXY(0, 40);
        SSD1306_Puts(data, &Font_7x10, SSD1306_COLOR_WHITE);

        SSD1306_UpdateScreen();
        delay_1ms(10);
        GPIO_WriteBit(GPIOD, GPIO_Pin_3,Bit_RESET);
        delay_1ms(1);
        GPIO_WriteBit(GPIOD, GPIO_Pin_3,Bit_SET);
    }
}
