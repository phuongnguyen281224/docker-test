#ifndef I2C_H
#define I2C_H

#include "stm32f1xx.h"

/*
 * I2C Configuration Structure
 */
typedef struct
{
    uint32_t I2C_ClockSpeed;          /*!< Specifies the clock frequency.
                                           This parameter must be set to a value lower than 400kHz */
    uint16_t I2C_Mode;                /*!< Specifies the I2C mode.
                                           This parameter can be a value of @ref I2C_mode */
    uint16_t I2C_DutyCycle;           /*!< Specifies the I2C fast mode duty cycle.
                                           This parameter can be a value of @ref I2C_duty_cycle_in_fast_mode */
    uint16_t I2C_OwnAddress1;         /*!< Specifies the first device own address.
                                           This parameter can be a 7-bit or 10-bit address. */
    uint16_t I2C_Ack;                 /*!< Enables or disables the acknowledgement.
                                           This parameter can be a value of @ref I2C_acknowledgement */
    uint16_t I2C_AcknowledgedAddress; /*!< Specifies if 7-bit or 10-bit address is acknowledged.
                                           This parameter can be a value of @ref I2C_acknowledged_address */
} I2C_Config_t;

/*
 * @ref I2C_mode
 */
#define I2C_Mode_I2C                ((uint16_t)0x0000)
#define I2C_Mode_SMBusDevice        ((uint16_t)0x0002)
#define I2C_Mode_SMBusHost          ((uint16_t)0x000A)

/*
 * @ref I2C_duty_cycle_in_fast_mode
 */
#define I2C_DutyCycle_2             ((uint16_t)0x0000)
#define I2C_DutyCycle_16_9          ((uint16_t)0x4000)

/*
 * @ref I2C_acknowledgement
 */
#define I2C_Ack_Enable              ((uint16_t)0x0400)
#define I2C_Ack_Disable             ((uint16_t)0x0000)

/*
 * @ref I2C_acknowledged_address
 */
#define I2C_AcknowledgedAddress_7bit    ((uint16_t)0x4000)
#define I2C_AcknowledgedAddress_10bit   ((uint16_t)0xC000)

/*
 * I2C Status Register 1 Flags
 */
#define I2C_SR1_SB                  ((uint16_t)0x0001)
#define I2C_SR1_ADDR                ((uint16_t)0x0002)
#define I2C_SR1_BTF                 ((uint16_t)0x0004)
#define I2C_SR1_ADD10               ((uint16_t)0x0008)
#define I2C_SR1_STOPF               ((uint16_t)0x0010)
#define I2C_SR1_RXNE                ((uint16_t)0x0040)
#define I2C_SR1_TXE                 ((uint16_t)0x0080)
#define I2C_SR1_BERR                ((uint16_t)0x0100)
#define I2C_SR1_ARLO                ((uint16_t)0x0200)
#define I2C_SR1_AF                  ((uint16_t)0x0400)
#define I2C_SR1_OVR                 ((uint16_t)0x0800)
#define I2C_SR1_PECERR              ((uint16_t)0x1000)
#define I2C_SR1_TIMEOUT             ((uint16_t)0x4000)
#define I2C_SR1_SMBALERT            ((uint16_t)0x8000)

/*
 * Function Prototypes
 */
void I2C_Init(I2C_TypeDef* I2Cx, I2C_Config_t* I2C_InitStruct);
void I2C_Cmd(I2C_TypeDef* I2Cx, uint8_t NewState);
void I2C_GenerateSTART(I2C_TypeDef* I2Cx, uint8_t NewState);
void I2C_GenerateSTOP(I2C_TypeDef* I2Cx, uint8_t NewState);
void I2C_SendData(I2C_TypeDef* I2Cx, uint8_t Data);
uint8_t I2C_ReceiveData(I2C_TypeDef* I2Cx);
uint8_t I2C_CheckEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT);

#endif // I2C_H
