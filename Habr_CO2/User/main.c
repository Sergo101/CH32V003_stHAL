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
    u8 i = 0;

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


    while(1)
    {
        SSD1306_Fill(SSD1306_COLOR_BLACK);
        sprintf (buff,"Blink OFF");
        SSD1306_GotoXY(0, 0);
        SSD1306_Puts(buff, &Font_11x18, SSD1306_COLOR_WHITE);
        SSD1306_UpdateScreen();
        delay_1ms(500);

        SSD1306_Fill(SSD1306_COLOR_WHITE);
        sprintf (buff,"Blink ON");
        SSD1306_GotoXY(0, 0);
        SSD1306_Puts(buff, &Font_11x18, SSD1306_COLOR_BLACK);
        SSD1306_UpdateScreen();
        delay_1ms(500);

        GPIO_WriteBit(GPIOD, GPIO_Pin_3, (i == 0) ? (i = Bit_SET) : (i = Bit_RESET));
    }
}
