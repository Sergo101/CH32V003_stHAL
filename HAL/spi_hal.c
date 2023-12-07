/*
 * spi_hal.c
 *
 *  Created on: Oct 14, 2023
 *      Author: Sergo
 */
#include "spi_hal.h"

void HAL_SPI_Init (void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
        SPI_InitTypeDef  SPI_InitStructure = {0};

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_SPI1, ENABLE);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOC, &GPIO_InitStructure);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(GPIOC, &GPIO_InitStructure);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOC, &GPIO_InitStructure);


        SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;

        SPI_InitStructure.SPI_Mode = SPI_Mode_Master;


        SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
        SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
        SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
        SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
        SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
        SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
        SPI_InitStructure.SPI_CRCPolynomial = 7;
        SPI_Init(SPI1, &SPI_InitStructure);

        //SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx, ENABLE);
        //SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Rx, ENABLE);

        SPI_Init( SPI1, &SPI_InitStructure );

        SPI_Cmd(SPI1, ENABLE);
}
/**
  * @brief  Write an amount of data in blocking mode to a specific memory address
  * @param  spi_periph variable for spi peripherial

  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be sent
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
uint8_t HAL_SPI_Write (SPI_TypeDef *spi_periph, uint8_t *pData, uint16_t Size, uint32_t spi_timeout)
{
uint32_t tickstart = get_tick();
    uint16_t i;


    for (i = 0; i < Size ; i++)
    {
        while(RESET == SPI_I2S_GetFlagStatus( spi_periph, SPI_I2S_FLAG_TXE ) && (get_tick() - tickstart < spi_timeout)) ;

                    SPI_I2S_SendData( spi_periph, pData[i] );
    }
    while(SET == SPI_I2S_GetFlagStatus( spi_periph, SPI_I2S_FLAG_BSY ) && (get_tick() - tickstart < spi_timeout));

    if(get_tick() - tickstart < spi_timeout) {
                } else {
                    return SPI_TIMEOUT;
                }
 return SPI_OK;

}

/**
  * @brief  Read an amount of data in blocking mode from a specific memory address
  * @param  spi_periph variable for spi peripherial

  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be read
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
uint8_t HAL_SPI_Read  (SPI_TypeDef *spi_periph, uint8_t *pData, uint16_t Size, uint32_t spi_timeout)
{
        //uint32_t tickstart = get_tick();
        //uint16_t i;
/*
    while(SET == spi_i2s_flag_get(spi_periph, SPI_FLAG_RBNE) && (get_tick() - tickstart < spi_timeout)) {
        spi_i2s_data_receive (spi_periph);//î÷èñòêà áóôåðà ïðèåìà
        }

    for (i = 0; i < Size ; i++)
    {
        while(RESET == spi_i2s_flag_get(spi_periph, SPI_FLAG_TBE) && (get_tick() - tickstart < spi_timeout)) {
        }
                    spi_i2s_data_transmit(spi_periph, 0);//îòïðàâèòü ïóñòîé áàéò äëÿ ãåíåðàöèè òàêòîâîãî ñèãíàëà
        while(SET == spi_i2s_flag_get(spi_periph, SPI_STAT_TRANS) && (get_tick() - tickstart < spi_timeout));//æäàòü îêîí÷àíèÿ ïåðåäà÷è ïóñòîãî áàéòà


        while(RESET == spi_i2s_flag_get(spi_periph, SPI_FLAG_RBNE) && (get_tick() - tickstart < spi_timeout)) {
        }
        pData[i] = (uint8_t)spi_i2s_data_receive (spi_periph);//ïðî÷èòàòü áàéò èç áóôåðà
    }
    if(get_tick() - tickstart < spi_timeout) {
                } else {
                    return SPI_TIMEOUT;
                }
*/
 return SPI_OK;
}
