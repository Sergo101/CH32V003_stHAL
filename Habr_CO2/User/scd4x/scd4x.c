
#include "scd4x.h"

/**
 * @brief Transmit command to scd41 sensor
 *
 * @param command - internal command
 * @return i2c_err_code
 */
uint8_t scd4x_send_command (uint16_t command)
{
    uint8_t buff[2];
    buff [0] = (uint8_t)(command>>8);
    buff [1] = (uint8_t)command;
    return scd4x_transmit_data(buff, 2);
}

/**
 * @brief Transmit an amount of data thru I2C to scd41 sensor
 * @param *pData - pointer to data buffer
 * @param Size - Amount of data to be sent
 * @return i2c_err_code
 */
uint8_t scd4x_transmit_data (uint8_t *pData, uint16_t Size)
{
    return HAL_I2C_Transmit(I2C_SCD4x, SCD4x_SLAVE_ADDR, pData, Size, I2C_Timeout);
}

/**
 * @brief Receive an amount of data thru I2C from scd41 sensor
 * @param *pData - pointer to data buffer
 * @param Size - Amount of data to be receive
 * @return i2c_err_code
 */
uint8_t scd4x_receive_data (uint8_t *pData, uint16_t Size)
{
    return HAL_I2C_Receive(I2C_SCD4x, SCD4x_SLAVE_ADDR, pData, Size, I2C_Timeout);
}
/**
 * @brief Init function for scd41 sensor
 * @return i2c_err_code
 */
uint8_t scd4x_Init(void)
{
    uint8_t err_code;
    err_code = scd4x_send_command (SCD4x_START_PERIODIC_MEASUREMENT);
    return err_code;
}

/**
 * @brief Read measured data
 * @*co2_conc - pointer to variable, where function return concentration of CO2 in ppm
 * @*temp - pointer to variable, where function return temperature in Celcium degree
 * @*humidity - pointer to variable, where function return humidity in %*10
 * @return i2c_err_code
 */
uint8_t scd4x_read_measurement(uint16_t* co2_conc, int16_t* temp, uint16_t* humidity)
{
    uint8_t buff [10];
    uint8_t err_code = 0;
    scd4x_send_command (SCD4x_READ_MEASUREMENT);
    err_code = scd4x_receive_data (buff, 9);
    if (err_code != 0)
    {
        return err_code; //return i2c err code in case of i2c troubles
    }
    if (buff[2] != sensirion_common_generate_crc(buff,2)
       ||buff[5] != sensirion_common_generate_crc(&buff[3],2)
       ||buff[8] != sensirion_common_generate_crc(&buff[6],2))
    {
        return 0xFF;//crc error
    }
    *co2_conc = ((uint16_t)buff[0]<<8) + buff[1];
    *temp = (int32_t)(((uint16_t)buff[3]<<8) + buff[4])*175/65535 - 45;
    *humidity = (int32_t)(((uint16_t)buff[3]<<8) + buff[4])*1000/65535;
    return 0;
}

/**
 * @brief Check is measured data ready to be read from sensor
 * @return 0 if data is ready
 *         SCD4x_DATA_NOT_READY if data not ready
 *         i2c_err_code if i2c troubles occurred
 */
uint8_t scd4x_is_data_ready(void)
{
    uint8_t buff [3];
    uint16_t status = 0;
    uint8_t err_code = 0;
    scd4x_send_command (SCD4x_GET_DATA_READY_STATUS);
    err_code = scd4x_receive_data (buff, 3);
    if (err_code != 0)
    {
        return err_code; //return i2c err code in case of i2c troubles
    }
    status = ((uint16_t)buff[0]<<8) + buff[1];
    status = status & 0x07FF; //set first 5 bits to zero
    if (status)return 0; //return 0 if data is ready
    else return SCD4x_DATA_NOT_READY;
}

/**
 * @brief Read self calibration status.
 *          This function should be called only when continuous measure stopped
 * @ return 0 if self calibration disable
 *          1 if self calibration enable
 *          0xFF if crc_error
 */
uint16_t scd4x_read_self_calibration (void)
{
    uint8_t buff [3];
    uint16_t status = 0;
        scd4x_send_command (SCD4x_GET_AUTOMATIC_SELF_CALIBRATION_EN);
        //delay_1ms(5);
        scd4x_receive_data (buff, 3);
        status = ((uint16_t)buff[0]<<8) + buff[1];
        if (buff[2] != sensirion_common_generate_crc(buff,2))
        {
            return 0xFF;
        }
        else return status;
}

/**
 * @brief Enable or disable self calibration.
 *          This function should be called only when continuous measure stopped
 * @param on - set 0 for disable self calibration
 *             set 1 for enable self calibration
 * @ return i2c_err_code
 */
uint8_t scd4x_set_self_calibration (uint8_t on)
{
    uint8_t buff [5];
    buff [0] = (uint8_t)(SCD4x_SET_AUTOMATIC_SELF_CALIBRATION_EN>>8);
    buff [1] = (uint8_t)SCD4x_SET_AUTOMATIC_SELF_CALIBRATION_EN;
    buff [2] = 0x00;
    buff [3] = on;
    buff [4] = sensirion_common_generate_crc (&buff [2],2);
    return scd4x_transmit_data (buff, 5);
}

/**
 * @brief Force calibrate sensor with actual conc
 * @param co2_ppm - actual co2 concentration in ppm
 * @return
 */
int16_t scd4x_force_recalibration (uint16_t co2_ppm)
{
    uint8_t buff [5];
    buff [0] = (uint8_t)(SCD4x_PERFORM_FORSED_RECALIBRATION>>8);
    buff [1] = (uint8_t)SCD4x_PERFORM_FORSED_RECALIBRATION;
    buff [2] = (uint8_t)co2_ppm>>8;
    buff [3] = (uint8_t)co2_ppm;
    buff [4] = sensirion_common_generate_crc (&buff [2],2);
    scd4x_transmit_data (buff, 5);

    delay_1ms(400);
    scd4x_receive_data (buff, 3);
    return (int16_t)(((uint16_t)buff[0]<<8) + buff[1]-0x8000);
}

uint8_t sensirion_common_generate_crc(const uint8_t* data, uint16_t count) {
    uint16_t current_byte;
    uint8_t crc = CRC8_INIT;
    uint8_t crc_bit;
    /* calculates 8-Bit checksum with given polynomial */
    for (current_byte = 0; current_byte < count; ++current_byte) {
           crc ^= (data[current_byte]);
           for (crc_bit = 8; crc_bit > 0; --crc_bit) {
               if (crc & 0x80)
                   crc = (crc << 1) ^ CRC8_POLYNOMIAL;
               else
                   crc = (crc << 1);
           }
    }
 return crc;
}
/*lint --flb "Leave library region" */
