/*
 * i2c_hal.h
 *
 *  Created on: Sep 27, 2023
 *      Author: Sergo
 */

#ifndef HAL_I2C_HAL_H_
#define HAL_I2C_HAL_H_

#include "ch32v00x_conf.h"
#include "systick_hal.h"

typedef enum {
    I2C_OK = 0,
    I2C_ADDR_NACK,
    I2C_TIMEOUT,
    I2C_BUSY,
} i2c_process_enum;
void HAL_I2C_Init(u32 bound, u16 address);

uint8_t HAL_I2C_Transmit (I2C_TypeDef *i2c_periph, uint8_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t i2c_timeout);

uint8_t HAL_I2C_Receive (I2C_TypeDef *i2c_periph, uint8_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t i2c_timeout);

uint8_t HAL_I2C_Mem_Write (I2C_TypeDef *i2c_periph, uint8_t DevAddress, uint8_t MemAddress, uint8_t *pData, uint16_t Size, uint32_t i2c_timeout);

uint8_t HAL_I2C_Mem_Read (I2C_TypeDef *i2c_periph, uint8_t DevAddress, uint8_t MemAddress, uint8_t *pData, uint16_t Size, uint32_t i2c_timeout);

#endif /* HAL_I2C_HAL_H_ */
