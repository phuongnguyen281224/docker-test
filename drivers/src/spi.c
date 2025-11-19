#include "spi.h"

/**
 * @brief  Initializes the SPIx peripheral according to the specified 
 *         parameters in the SPI_InitStruct.
 * @param  SPIx: where x can be 1 or 2 to select the SPI peripheral.
 * @param  SPI_InitStruct: pointer to a SPI_Config_t structure that
 *         contains the configuration information for the specified SPI peripheral.
 */
void SPI_Init(SPI_TypeDef* SPIx, SPI_Config_t* SPI_InitStruct) {
    uint16_t tmpreg = 0;

    /*---------------------------- SPIx CR1 Configuration ------------------------*/
    /* Get the SPIx CR1 value */
    tmpreg = SPIx->CR1;
    
    /* Clear BIDIMode, BIDIOE, RxONLY, SSM, SSI, LSBFirst, BR, MSTR, CPOL and CPHA bits */
    tmpreg &= 0x3040;
    
    /* Configure SPIx: direction, NSS management, first transmitted bit, BaudRate prescaler
       master/slave mode, CPOL and CPHA */
    tmpreg |= (uint16_t)((uint32_t)SPI_InitStruct->SPI_Direction | SPI_InitStruct->SPI_Mode |
                  SPI_InitStruct->SPI_DataSize | SPI_InitStruct->SPI_CPOL |  
                  SPI_InitStruct->SPI_CPHA | SPI_InitStruct->SPI_NSS |  
                  SPI_InitStruct->SPI_BaudRatePrescaler | SPI_InitStruct->SPI_FirstBit);
    
    /* Write to SPIx CR1 */
    SPIx->CR1 = tmpreg;
}

/**
 * @brief  Enables or disables the specified SPI peripheral.
 * @param  SPIx: where x can be 1 or 2 to select the SPI peripheral.
 * @param  NewState: new state of the SPIx peripheral. 
 *         This parameter can be: ENABLE or DISABLE.
 */
void SPI_Cmd(SPI_TypeDef* SPIx, uint8_t NewState) {
    if (NewState != DISABLE) {
        /* Enable the selected SPI peripheral */
        SPIx->CR1 |= (1 << 6); // SPE bit
    } else {
        /* Disable the selected SPI peripheral */
        SPIx->CR1 &= (uint16_t)~((uint16_t)(1 << 6));
    }
}

/**
 * @brief  Transmits a Data through the SPIx peripheral.
 * @param  SPIx: where x can be 1 or 2 to select the SPI peripheral.
 * @param  Data: Data to be transmitted.
 */
void SPI_SendData(SPI_TypeDef* SPIx, uint16_t Data) {
    /* Write in the DR register the data to be sent */
    SPIx->DR = Data;
}

/**
 * @brief  Returns the most recent received data by the SPIx peripheral.
 * @param  SPIx: where x can be 1 or 2 to select the SPI peripheral.
 * @return The value of the received data.
 */
uint16_t SPI_ReceiveData(SPI_TypeDef* SPIx) {
    /* Return the data in the DR register */
    return SPIx->DR;
}

/**
 * @brief  Checks whether the specified SPI flag is set or not.
 * @param  SPIx: where x can be 1 or 2 to select the SPI peripheral.
 * @param  SPI_FLAG: specifies the SPI flag to check.
 * @return The new state of SPI_FLAG (SET or RESET).
 */
uint8_t SPI_GetFlagStatus(SPI_TypeDef* SPIx, uint16_t SPI_FLAG) {
    /* Check the status of the specified SPI flag */
    if ((SPIx->SR & SPI_FLAG) != (uint16_t)RESET) {
        /* SPI_FLAG is set */
        return SET;
    } else {
        /* SPI_FLAG is reset */
        return RESET;
    }
}
