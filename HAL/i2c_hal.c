/*
 * i2c_hal.c
 *
 *  Created on: Sep 27, 2023
 *      Author: Sergo
 */
#include "i2c_hal.h"

/*********************************************************************
 * @fn      IIC_Init
 *
 * @brief   Initializes the IIC peripheral.
 *
 * @return  none
 */

void HAL_I2C_Init(u32 bound, u16 address)
{
    GPIO_InitTypeDef GPIO_InitStructure={0};
    I2C_InitTypeDef I2C_InitTSturcture={0};

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE );
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_I2C1, ENABLE );

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( GPIOC, &GPIO_InitStructure );

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( GPIOC, &GPIO_InitStructure );

    I2C_InitTSturcture.I2C_ClockSpeed = bound;
    I2C_InitTSturcture.I2C_Mode = I2C_Mode_I2C;
    I2C_InitTSturcture.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitTSturcture.I2C_OwnAddress1 = address;
    I2C_InitTSturcture.I2C_Ack = I2C_Ack_Enable;
    I2C_InitTSturcture.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_Init( I2C1, &I2C_InitTSturcture );

    I2C_Cmd( I2C1, ENABLE );

    I2C_AcknowledgeConfig( I2C1, ENABLE );
}

/**
  * @brief  Transmit an amount of data in blocking mode to slave
  * @param  i2c_periph variable for i2c peripherial
  * @param  DevAddress Target device address: The device 7 bits address value
  *         in datasheet must be shifted to the left before calling the interface
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be sent
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
uint8_t HAL_I2C_Transmit (I2C_TypeDef *i2c_periph, uint8_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t i2c_timeout)
{
    uint32_t tickstart = get_tick();
            uint16_t count = Size;

              /* i2c master sends start signal only when the bus is idle */
              while((I2C_GetFlagStatus( i2c_periph, I2C_FLAG_BUSY ) != RESET) && (get_tick() - tickstart < i2c_timeout)) ;

                    if(get_tick() - tickstart < i2c_timeout) {
                        /* whether to send ACK or not for the next byte */
                    } else {
                        I2C_GenerateSTOP( i2c_periph, ENABLE );
                        return I2C_BUSY;
                    }
                /* send the start signal */
                I2C_GenerateSTART( i2c_periph, ENABLE );
                while(!I2C_CheckEvent( I2C1, I2C_EVENT_MASTER_MODE_SELECT )  && (get_tick() - tickstart < i2c_timeout)) ;

                               if(get_tick() - tickstart < i2c_timeout) {
                                                       /* whether to send ACK or not for the next byte */
                               } else {
                                   I2C_GenerateSTOP( i2c_periph, ENABLE );
                                       return I2C_BUSY;
                                       }
                    I2C_Send7bitAddress( i2c_periph, DevAddress, I2C_Direction_Transmitter );


                /* address flag set means i2c slave sends ACK */
              while((!I2C_CheckEvent( i2c_periph, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED )) && (get_tick() - tickstart < i2c_timeout));

                if(get_tick() - tickstart < i2c_timeout) {
                } else {
                    I2C_GenerateSTOP( i2c_periph, ENABLE );
                    return I2C_ADDR_NACK;
                }

                for(count = 0; count < Size; count ++) {

                    I2C_SendData( i2c_periph, *pData );
                    /* point to the next byte to be written */
                    pData++;
                    /* wait until transmission complete */
                while((!I2C_CheckEvent( i2c_periph, I2C_EVENT_MASTER_BYTE_TRANSMITTED )) && (get_tick() - tickstart < i2c_timeout));

                   if(get_tick() - tickstart < i2c_timeout) {
                   } else {
                       I2C_GenerateSTOP( i2c_periph, ENABLE );
                        return I2C_TIMEOUT;
                   }
                }

                I2C_GenerateSTOP( i2c_periph, ENABLE );

        return I2C_OK;
}

/**
  * @brief  Receive i2c data in blocking mode from slave
  * @param  i2c_periph variable for i2c peripherial
  * @param  DevAddress Target device address: The device 7 bits address value
  *         in datasheet must be shifted to the left before calling the interface
  * @param  MemAddSize Size of internal memory address
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be sent
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
uint8_t HAL_I2C_Receive (I2C_TypeDef *i2c_periph, uint8_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t i2c_timeout)
{
        uint32_t tickstart = get_tick();
        uint16_t count = Size;
        /* i2c master sends start signal only when the bus is idle */
        while((I2C_GetFlagStatus( i2c_periph, I2C_FLAG_BUSY ) != RESET) && (get_tick() - tickstart < i2c_timeout)) ;

        if(get_tick() - tickstart < i2c_timeout) {
        } else {
                return I2C_BUSY;
                }
        /* send the start signal */
        I2C_GenerateSTART( I2C1, ENABLE );
        while(!I2C_CheckEvent( I2C1, I2C_EVENT_MASTER_MODE_SELECT )  && (get_tick() - tickstart < i2c_timeout)) ;

                        if(get_tick() - tickstart < i2c_timeout) {
                                                /* whether to send ACK or not for the next byte */
                        } else {
                            I2C_GenerateSTOP( i2c_periph, ENABLE );
                                return I2C_BUSY;
                                }

        I2C_Send7bitAddress( i2c_periph, DevAddress, I2C_Direction_Receiver );
        /* address flag set means i2c slave sends ACK */
        while((!I2C_CheckEvent( i2c_periph, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED )) && (get_tick() - tickstart < i2c_timeout));

        if(get_tick() - tickstart < i2c_timeout)
        {
        } else {
                I2C_GenerateSTOP( i2c_periph, ENABLE );
                return I2C_ADDR_NACK;
               }
         I2C_AcknowledgeConfig( i2c_periph, ENABLE );

         for(count = 0; count < Size; count ++)
         {
             /* wait until data not received */
             while((I2C_GetFlagStatus( i2c_periph, I2C_FLAG_RXNE ) ==  RESET) && (get_tick() - tickstart < i2c_timeout));

             if( count == (Size-2) )
              {
               /*before receiving last byte and after receiving byte-1 disable ACK for last byte */
              I2C_AcknowledgeConfig( i2c_periph, DISABLE );
              }

              /* receive data and store in buffer */
          *pData = I2C_ReceiveData( i2c_periph );
          pData++;
          }
         /* check timeout while receiving data */
          if(get_tick() - tickstart > i2c_timeout)
          {
           I2C_GenerateSTOP( i2c_periph, ENABLE );
           return I2C_TIMEOUT;
          }

          I2C_GenerateSTOP( i2c_periph, ENABLE );

    return I2C_OK;
}

/**
  * @brief  Write an amount of data in blocking mode to a specific memory address
  * @param  i2c_periph variable for i2c peripherial
  * @param  DevAddress Target device address: The device 7 bits address value
  *         in datasheet must be shifted to the left before calling the interface
  * @param  MemAddress Internal memory address
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be sent
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
uint8_t HAL_I2C_Mem_Write (I2C_TypeDef *i2c_periph, uint8_t DevAddress, uint8_t MemAddress, uint8_t *pData, uint16_t Size, uint32_t i2c_timeout)
{
    uint32_t tickstart = get_tick();
            uint16_t count = Size;

              /* i2c master sends start signal only when the bus is idle */
              while((I2C_GetFlagStatus( i2c_periph, I2C_FLAG_BUSY ) != RESET) && (get_tick() - tickstart < i2c_timeout)) ;

                    if(get_tick() - tickstart < i2c_timeout) {
                        /* whether to send ACK or not for the next byte */
                    } else {
                        I2C_GenerateSTOP( i2c_periph, ENABLE );
                        return I2C_BUSY;
                    }
                /* send the start signal */
                I2C_GenerateSTART( i2c_periph, ENABLE );
                while(!I2C_CheckEvent( I2C1, I2C_EVENT_MASTER_MODE_SELECT )  && (get_tick() - tickstart < i2c_timeout)) ;

                               if(get_tick() - tickstart < i2c_timeout) {
                                                       /* whether to send ACK or not for the next byte */
                               } else {
                                   I2C_GenerateSTOP( i2c_periph, ENABLE );
                                       return I2C_BUSY;
                                       }
                    I2C_Send7bitAddress( i2c_periph, DevAddress, I2C_Direction_Transmitter );


                /* address flag set means i2c slave sends ACK */
              while((!I2C_CheckEvent( i2c_periph, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED )) && (get_tick() - tickstart < i2c_timeout));

                if(get_tick() - tickstart < i2c_timeout) {
                } else {
                    I2C_GenerateSTOP( i2c_periph, ENABLE );
                    return I2C_ADDR_NACK;
                }
                /*Transmitt internal address byte*/
                 I2C_SendData( i2c_periph, MemAddress );

                 /* wait until transmission complete */
               while((!I2C_CheckEvent( i2c_periph, I2C_EVENT_MASTER_BYTE_TRANSMITTED )) && (get_tick() - tickstart < i2c_timeout));

                 if(get_tick() - tickstart < i2c_timeout) {
                 } else {
                     I2C_GenerateSTOP( i2c_periph, ENABLE );
                        return I2C_TIMEOUT;
                 }

                for(count = 0; count < Size; count ++) {

                    I2C_SendData( i2c_periph, *pData );
                    /* point to the next byte to be written */
                    pData++;
                    /* wait until transmission complete */
                while((!I2C_CheckEvent( i2c_periph, I2C_EVENT_MASTER_BYTE_TRANSMITTED )) && (get_tick() - tickstart < i2c_timeout));

                   if(get_tick() - tickstart < i2c_timeout) {
                   } else {
                       I2C_GenerateSTOP( i2c_periph, ENABLE );
                        return I2C_TIMEOUT;
                   }
                }

                I2C_GenerateSTOP( i2c_periph, ENABLE );

        return I2C_OK;
}

/**
  * @brief  Read an amount of data in blocking mode from a specific memory address
  * @param  i2c_periph variable for i2c peripherial
  * @param  DevAddress Target device address: The device 7 bits address value
  *         in datasheet must be shifted to the left before calling the interface
  * @param  MemAddress Internal memory address
  * @param  MemAddSize Size of internal memory address
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be sent
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
uint8_t HAL_I2C_Mem_Read (I2C_TypeDef *i2c_periph, uint8_t DevAddress, uint8_t MemAddress, uint8_t *pData, uint16_t Size, uint32_t i2c_timeout)
{
        uint32_t tickstart = get_tick();
        uint16_t count = Size;
        /* i2c master sends start signal only when the bus is idle */
        while((I2C_GetFlagStatus( i2c_periph, I2C_FLAG_BUSY ) != RESET) && (get_tick() - tickstart < i2c_timeout)) ;

        if(get_tick() - tickstart < i2c_timeout) {
                                /* whether to send ACK or not for the next byte */
        } else {
            I2C_GenerateSTOP( i2c_periph, ENABLE );
                return I2C_BUSY;
                }
        /* send the start signal */
        I2C_GenerateSTART( i2c_periph, ENABLE );

        while(!I2C_CheckEvent( I2C1, I2C_EVENT_MASTER_MODE_SELECT )  && (get_tick() - tickstart < i2c_timeout)) ;

                if(get_tick() - tickstart < i2c_timeout) {
                                        /* whether to send ACK or not for the next byte */
                } else {
                    I2C_GenerateSTOP( i2c_periph, ENABLE );
                        return I2C_BUSY;
                        }
        I2C_Send7bitAddress( i2c_periph, DevAddress, I2C_Direction_Transmitter );


        /* address flag set means i2c slave sends ACK */
        while((!I2C_CheckEvent( i2c_periph, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED )) && (get_tick() - tickstart < i2c_timeout));

        if(get_tick() - tickstart < i2c_timeout)
        {
        } else {
            I2C_GenerateSTOP( i2c_periph, ENABLE );
                return I2C_ADDR_NACK;
               }

        /*Transmitt internal address byte*/
        I2C_SendData( i2c_periph, MemAddress );

        /* wait until transmission complete */
        while((!I2C_CheckEvent( i2c_periph, I2C_EVENT_MASTER_BYTE_TRANSMITTED )) && (get_tick() - tickstart < i2c_timeout));

        if(get_tick() - tickstart < i2c_timeout)
        {
        } else {
            I2C_GenerateSTOP( i2c_periph, ENABLE );
                return I2C_TIMEOUT;
                }

        /* send the restart signal */
        I2C_GenerateSTOP( i2c_periph, ENABLE );
        I2C_GenerateSTART( I2C1, ENABLE );
        while(!I2C_CheckEvent( I2C1, I2C_EVENT_MASTER_MODE_SELECT )  && (get_tick() - tickstart < i2c_timeout)) ;

                        if(get_tick() - tickstart < i2c_timeout) {
                                                /* whether to send ACK or not for the next byte */
                        } else {
                            I2C_GenerateSTOP( i2c_periph, ENABLE );
                                return I2C_BUSY;
                                }

        I2C_Send7bitAddress( i2c_periph, DevAddress, I2C_Direction_Receiver );
        /* address flag set means i2c slave sends ACK */
        while((!I2C_CheckEvent( i2c_periph, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED )) && (get_tick() - tickstart < i2c_timeout));

        if(get_tick() - tickstart < i2c_timeout)
        {
        } else {
                I2C_GenerateSTOP( i2c_periph, ENABLE );
                return I2C_ADDR_NACK;
               }
        I2C_AcknowledgeConfig( i2c_periph, ENABLE );

         for(count = 0; count < Size; count ++)
         {
             /* wait until data recieved */
             while((I2C_GetFlagStatus( i2c_periph, I2C_FLAG_RXNE ) ==  RESET) && (get_tick() - tickstart < i2c_timeout));

             if( count == (Size-2) )
             {
                 /*before receiving last byte and after receiving byte-1 disable ACK for last byte */
                 I2C_AcknowledgeConfig( i2c_periph, DISABLE );
             }

              /* receive data and store in buffer */
          *pData = I2C_ReceiveData( i2c_periph );
          pData++;
          }
         /* check timeout while receiving data */
          if(get_tick() - tickstart > i2c_timeout)
          {
           I2C_GenerateSTOP( i2c_periph, ENABLE );
           return I2C_TIMEOUT;
          }

                        /* send a stop condition to I2C bus */
          I2C_GenerateSTOP( i2c_periph, ENABLE );

    return I2C_OK;
}
