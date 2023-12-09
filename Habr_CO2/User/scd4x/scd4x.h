#pragma once


/*lint ++flb "Enter library region" */
#include "systick_hal.h"
#include "i2c_hal.h"

#include <stdint.h>
#include <stdio.h>

//#include "math.h"

#define I2C_SCD4x I2C1
#define I2C_Timeout 50

#define SCD4x_SLAVE_ADDR 0x62<<1

//BASIC COMMAND
#define SCD4x_START_PERIODIC_MEASUREMENT 0x21B1
#define SCD4x_READ_MEASUREMENT 0xEC05
#define SCD4x_STOP_PERIODIC_MEASUREMENT 0x3F86
//On-Chip putput signal compensation
#define SCD4x_SET_TEMPERATURE_OFFSET 0x241D
#define SCD4x_GET_TEMPERATURE_OFFSET 0x2318
#define SCD4x_SET_SENSOR_ALTITUDE 0x2427
#define SCD4x_GET_SENSOR_ALTITUDE 0x2322
#define SCD4x_SET_AMBIENT_PRESSURE 0xE000
#define SCD4x_GET_AMBIENT_PRESSURE 0xE000
//Field calibration
#define SCD4x_PERFORM_FORSED_RECALIBRATION 0x362F
#define SCD4x_SET_AUTOMATIC_SELF_CALIBRATION_EN 0x2416
#define SCD4x_GET_AUTOMATIC_SELF_CALIBRATION_EN 0x2313
//Low power periodic measurement mode
#define SCD4x_START_LOW_POWER_PERIODIC_MEASUREMENT 0x21AC
#define SCD4x_GET_DATA_READY_STATUS 0xE4B8
//Advanced features
#define SCD4x_PERSIST_SETTINGS 0x3615
#define SCD4x_GET_SERIAL_NUMBER 0x3682
#define SCD4x_PERFORM_SELF_TEST 0x3639
#define SCD4x_PERFORM_FACTORY_RESET 0x3632
#define SCD4x_REINIT 0x3646
//Single shot measurement mode
//(SCD41 only)
#define SCD4x_MEASURE_SINGLE_SHOT 0x219D
#define SCD4x_MEASURE_SINGLE_SHOT_RHT_ONLY 0x2196
#define SCD4x_POWER_DOWN 0x36E0
#define SCD4x_WAKE_UP 0x36F6
#define SCD4x_SET_AUTOMATIC_SELF_CALIBRATION_INIT_PERIOD 0x2445
#define SCD4x_GET_AUTOMATIC_SELF_CALIBRATION_INIT_PERIOD 0x2340
#define SCD4x_SET_AUTOMATIC_SELF_CALIBRATION_STANDART_PERIOD 0x244E
#define SCD4x_GET_AUTOMATIC_SELF_CALIBRATION_STANDART_PERIOD 0x234B

#define CRC8_POLYNOMIAL 0x31
#define CRC8_INIT 0xFF

#define SCD4x_DATA_NOT_READY 0xF0
/*
 * transmit command to scd4x thru i2c
 */
uint8_t scd4x_send_command (uint16_t command);

uint8_t scd4x_Init(void);			//reset sensor and start operation

/*
 * transmit amount of bytes from scd4x
 * uint8_t *pData <-> pointer to data buffer
 * uint16_t Size  <-> number of bytes that would be transmitted
 */
uint8_t scd4x_transmit_data (uint8_t *pData, uint16_t Size);
/*
 * receive amount of bytes from scd4x
 * uint8_t *pData <-> pointer to data buffer
 * uint16_t Size  <-> number of bytes that would be received
 */
uint8_t scd4x_receive_data (uint8_t *pData, uint16_t Size);

/*
 * receive measurement from scd4x
 * uint16_t *co2_conc <-> pointer to co2 concentration received data in ppm
 * int16_t *temp <-> pointer to temperature received data in deg celcium
 * uint16_t *humidity <-> pointer to humidity received data in %*10
 */
uint8_t scd4x_read_measurement(uint16_t* co2_conc, int16_t* temp, uint16_t* humidity);

/*
 * retuns 1 if data ready
 */
uint8_t scd4x_is_data_ready(void);

uint16_t scd4x_read_self_calibration (void);

uint8_t scd4x_set_self_calibration (uint8_t on);

int16_t scd4x_force_recalibration (uint16_t co2_ppm);

uint8_t sensirion_common_generate_crc(const uint8_t* data, uint16_t count);

