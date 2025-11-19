#ifndef SPI_H
#define SPI_H

#include "stm32f1xx.h"

/*
 * SPI Configuration Structure
 */
typedef struct
{
    uint16_t SPI_Direction;          /*!< Specifies the SPI unidirectional or bidirectional data mode.
                                          This parameter can be a value of @ref SPI_data_direction */
    uint16_t SPI_Mode;               /*!< Specifies the SPI operating mode.
                                          This parameter can be a value of @ref SPI_mode */
    uint16_t SPI_DataSize;           /*!< Specifies the SPI data size.
                                          This parameter can be a value of @ref SPI_data_size */
    uint16_t SPI_CPOL;               /*!< Specifies the serial clock steady state.
                                          This parameter can be a value of @ref SPI_Clock_Polarity */
    uint16_t SPI_CPHA;               /*!< Specifies the clock active edge for the bit capture.
                                          This parameter can be a value of @ref SPI_Clock_Phase */
    uint16_t SPI_NSS;                /*!< Specifies whether the NSS signal is managed by
                                          hardware (NSS pin) or by software using the SSI bit.
                                          This parameter can be a value of @ref SPI_Slave_Select_management */
    uint16_t SPI_BaudRatePrescaler;  /*!< Specifies the Baud Rate prescaler value which will be
                                          used to configure the transmit and receive SCK clock.
                                          This parameter can be a value of @ref SPI_BaudRate_Prescaler */
    uint16_t SPI_FirstBit;           /*!< Specifies whether data transfers start from MSB or LSB bit.
                                          This parameter can be a value of @ref SPI_MSB_LSB_transmission */
} SPI_Config_t;

/*
 * @ref SPI_data_direction
 */
#define SPI_Direction_2Lines_FullDuplex     ((uint16_t)0x0000)
#define SPI_Direction_2Lines_RxOnly         ((uint16_t)0x0400)
#define SPI_Direction_1Line_Rx              ((uint16_t)0x8000)
#define SPI_Direction_1Line_Tx              ((uint16_t)0xC000)

/*
 * @ref SPI_mode
 */
#define SPI_Mode_Master                     ((uint16_t)0x0104)
#define SPI_Mode_Slave                      ((uint16_t)0x0000)

/*
 * @ref SPI_data_size
 */
#define SPI_DataSize_16b                    ((uint16_t)0x0800)
#define SPI_DataSize_8b                     ((uint16_t)0x0000)

/*
 * @ref SPI_Clock_Polarity
 */
#define SPI_CPOL_Low                        ((uint16_t)0x0000)
#define SPI_CPOL_High                       ((uint16_t)0x0002)

/*
 * @ref SPI_Clock_Phase
 */
#define SPI_CPHA_1Edge                      ((uint16_t)0x0000)
#define SPI_CPHA_2Edge                      ((uint16_t)0x0001)

/*
 * @ref SPI_Slave_Select_management
 */
#define SPI_NSS_Soft                        ((uint16_t)0x0200)
#define SPI_NSS_Hard                        ((uint16_t)0x0000)

/*
 * @ref SPI_BaudRate_Prescaler
 */
#define SPI_BaudRatePrescaler_2             ((uint16_t)0x0000)
#define SPI_BaudRatePrescaler_4             ((uint16_t)0x0008)
#define SPI_BaudRatePrescaler_8             ((uint16_t)0x0010)
#define SPI_BaudRatePrescaler_16            ((uint16_t)0x0018)
#define SPI_BaudRatePrescaler_32            ((uint16_t)0x0020)
#define SPI_BaudRatePrescaler_64            ((uint16_t)0x0028)
#define SPI_BaudRatePrescaler_128           ((uint16_t)0x0030)
#define SPI_BaudRatePrescaler_256           ((uint16_t)0x0038)

/*
 * @ref SPI_MSB_LSB_transmission
 */
#define SPI_FirstBit_MSB                    ((uint16_t)0x0000)
#define SPI_FirstBit_LSB                    ((uint16_t)0x0080)

/*
 * SPI Status Register Flags
 */
#define SPI_SR_RXNE                         ((uint16_t)0x0001)
#define SPI_SR_TXE                          ((uint16_t)0x0002)
#define SPI_SR_BSY                          ((uint16_t)0x0080)

/*
 * Function Prototypes
 */
void SPI_Init(SPI_TypeDef* SPIx, SPI_Config_t* SPI_InitStruct);
void SPI_Cmd(SPI_TypeDef* SPIx, uint8_t NewState);
void SPI_SendData(SPI_TypeDef* SPIx, uint16_t Data);
uint16_t SPI_ReceiveData(SPI_TypeDef* SPIx);

#endif // SPI_H
