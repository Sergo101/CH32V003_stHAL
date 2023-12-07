/*
 * systick_hal.h
 *
 *  Created on: Sep 27, 2023
 *      Author: Sergo
 */

#ifndef SYSTICK_HAL_H_
#define SYSTICK_HAL_H_
#include "ch32v00x.h"

void Systick_Init (void);

void Systick_Increment (void);

void delay_1ms(uint32_t count);

void delay_decrement(void);

uint32_t get_tick (void);

void SysTick_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
#endif /* SYSTICK_HAL_H_ */
