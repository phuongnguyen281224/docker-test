#ifndef UART_H
#define UART_H

#include "stm32f10x.h"

/*
 * Configuration structure for UART
 */
typedef struct {
    uint32_t BaudRate;        /*!< This member configures the UART communication baud rate */
    uint32_t WordLength;      /*!< Specifies the number of data bits transmitted or received in a frame.
                                   This parameter can be a value of @ref UART_Word_Length */
    uint32_t StopBits;        /*!< Specifies the number of stop bits transmitted.
                                   This parameter can be a value of @ref UART_Stop_Bits */
    uint32_t Parity;          /*!< Specifies the parity mode.
                                   This parameter can be a value of @ref UART_Parity */
    uint32_t Mode;            /*!< Specifies whether the Receive or Transmit mode is enabled or disabled.
                                   This parameter can be a value of @ref UART_Mode */
    uint32_t HwFlowCtl;       /*!< Specifies whether the hardware flow control mode is enabled or disabled.
                                   This parameter can be a value of @ref UART_Hardware_Flow_Control */
} UART_Config_t;

/*
 * Handle structure for UART
 */
typedef struct {
    USART_TypeDef *pUSARTx;
    UART_Config_t UART_Config;
} UART_Handle_t;

/*
 * @ref UART_Word_Length
 */
#define UART_WORDLENGTH_8B                  0x0000
#define UART_WORDLENGTH_9B                  USART_CR1_M

/*
 * @ref UART_Stop_Bits
 */
#define UART_STOPBITS_1                     0x0000
#define UART_STOPBITS_0_5                   0x1000
#define UART_STOPBITS_2                     0x2000
#define UART_STOPBITS_1_5                   0x3000

/*
 * @ref UART_Parity
 */
#define UART_PARITY_NONE                    0x0000
#define UART_PARITY_EVEN                    USART_CR1_PCE
#define UART_PARITY_ODD                     (USART_CR1_PCE | USART_CR1_PS)

/*
 * @ref UART_Mode
 */
#define UART_MODE_RX                        USART_CR1_RE
#define UART_MODE_TX                        USART_CR1_TE
#define UART_MODE_TXRX                      (USART_CR1_TE | USART_CR1_RE)

/*
 * @ref UART_Hardware_Flow_Control
 */
#define UART_HW_FLOW_CTRL_NONE              0x0000
#define UART_HW_FLOW_CTRL_CTS               USART_CR3_CTSE
#define UART_HW_FLOW_CTRL_RTS               USART_CR3_RTSE
#define UART_HW_FLOW_CTRL_CTS_RTS           (USART_CR3_CTSE | USART_CR3_RTSE)

/*
 * APIs
 */

// Init
void UART_Init(UART_Handle_t *pUARTHandle);
void UART_DeInit(USART_TypeDef *pUSARTx);

// Data Transfer
void UART_Transmit(UART_Handle_t *pUARTHandle, uint8_t *pTxBuffer, uint32_t Len);
void UART_Receive(UART_Handle_t *pUARTHandle, uint8_t *pRxBuffer, uint32_t Len);
uint8_t UART_ReceiveByte(UART_Handle_t *pUARTHandle);

// Interrupts
void UART_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void UART_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void UART_IRQHandler(UART_Handle_t *pUARTHandle);

// Application Callbacks
void UART_ApplicationEventCallback(UART_Handle_t *pUARTHandle, uint8_t AppEv);

#endif // UART_H
