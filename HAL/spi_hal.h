/*
 * spi_hal.h
 *
 *  Created on: Oct 14, 2023
 *      Author: Sergo
 */

#ifndef HAL_SPI_HAL_H_
#define HAL_SPI_HAL_H_

#include "systick_hal.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


#include "ch32v00x_conf.h"
typedef enum {
    SPI_OK = 0,
    SPI_BUSY,
    SPI_TIMEOUT
} spi_process_enum;

void HAL_SPI_Init ();
//extern uint32_t get_tick();
uint8_t HAL_SPI_Write (SPI_TypeDef *spi_periph, uint8_t *pData, uint16_t Size, uint32_t spi_timeout);

uint8_t HAL_SPI_Read  (SPI_TypeDef *spi_periph, uint8_t *pData, uint16_t Size, uint32_t spi_timeout);



#endif /* HAL_SPI_HAL_H_ */
