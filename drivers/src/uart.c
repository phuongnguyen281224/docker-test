#include "uart.h"
#include "rcc.h"
#include "gpio.h"

// Helper to enable clock
static void UART_EnableClock(USART_TypeDef *USARTx) {
    if (USARTx == USART1) RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    else if (USARTx == USART2) RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    else if (USARTx == USART3) RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
}

// Helper to get PCLK frequency
static uint32_t UART_GetPCLKFrequency(USART_TypeDef *USARTx) {
    if (USARTx == USART1) return 72000000; // APB2 (Assuming 72MHz)
    else return 36000000; // APB1 (Assuming 36MHz)
}

void UART_Init(UART_Handle_t *pUARTHandle) {
    UART_EnableClock(pUARTHandle->pUSARTx);

    // 1. Configure Mode (TX/RX)
    uint32_t tempreg = 0;
    tempreg = pUARTHandle->UART_Config.Mode;
    
    // 2. Configure Parity
    tempreg |= pUARTHandle->UART_Config.Parity;

    // 3. Configure Word Length
    tempreg |= pUARTHandle->UART_Config.WordLength;

    // 4. Configure Stop Bits (in CR2)
    pUARTHandle->pUSARTx->CR2 &= ~(0x3000); // Clear STOP bits
    pUARTHandle->pUSARTx->CR2 |= pUARTHandle->UART_Config.StopBits;

    // 5. Configure Hardware Flow Control (in CR3)
    pUARTHandle->pUSARTx->CR3 &= ~(0x300); // Clear CTSE/RTSE
    pUARTHandle->pUSARTx->CR3 |= pUARTHandle->UART_Config.HwFlowCtl;

    // 6. Configure Baud Rate
    uint32_t pclk = UART_GetPCLKFrequency(pUARTHandle->pUSARTx);
    uint32_t usartdiv = (pclk * 100) / (16 * pUARTHandle->UART_Config.BaudRate); // *100 to keep 2 decimal places
    uint32_t mantissa = usartdiv / 100;
    uint32_t fraction = (usartdiv - (mantissa * 100));
    fraction = (fraction * 16 + 50) / 100; // Rounding

    pUARTHandle->pUSARTx->BRR = (mantissa << 4) | (fraction & 0xF);

    // 7. Enable UART
    tempreg |= USART_CR1_UE;
    pUARTHandle->pUSARTx->CR1 = tempreg;
}

void UART_Transmit(UART_Handle_t *pUARTHandle, uint8_t *pTxBuffer, uint32_t Len) {
    for (uint32_t i = 0; i < Len; i++) {
        // Wait until TXE flag is set
        while (!(pUARTHandle->pUSARTx->SR & USART_SR_TXE));
        // Write data to DR
        pUARTHandle->pUSARTx->DR = (pTxBuffer[i] & 0xFF);
    }
    // Wait for TC flag
    while (!(pUARTHandle->pUSARTx->SR & USART_SR_TC));
}

void UART_Receive(UART_Handle_t *pUARTHandle, uint8_t *pRxBuffer, uint32_t Len) {
    for (uint32_t i = 0; i < Len; i++) {
        // Wait until RXNE flag is set
        while (!(pUARTHandle->pUSARTx->SR & USART_SR_RXNE));
        // Read data from DR
        pRxBuffer[i] = (uint8_t)(pUARTHandle->pUSARTx->DR & 0xFF);
    }
}

uint8_t UART_ReceiveByte(UART_Handle_t *pUARTHandle) {
    // Wait until RXNE flag is set
    while (!(pUARTHandle->pUSARTx->SR & USART_SR_RXNE));
    // Read data from DR
    return (uint8_t)(pUARTHandle->pUSARTx->DR & 0xFF);
}

void UART_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi) {
    if (EnorDi == 1) {
        if (IRQNumber <= 31) NVIC->ISER[0] |= (1 << IRQNumber);
        else if (IRQNumber < 64) NVIC->ISER[1] |= (1 << (IRQNumber % 32));
        else if (IRQNumber < 96) NVIC->ISER[2] |= (1 << (IRQNumber % 64));
    } else {
        if (IRQNumber <= 31) NVIC->ICER[0] |= (1 << IRQNumber);
        else if (IRQNumber < 64) NVIC->ICER[1] |= (1 << (IRQNumber % 32));
        else if (IRQNumber < 96) NVIC->ICER[2] |= (1 << (IRQNumber % 64));
    }
}

void UART_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority) {
    uint8_t iprx = IRQNumber / 4;
    uint8_t iprx_section = IRQNumber % 4;
    uint8_t shift_amount = (8 * iprx_section) + (8 - 4);
    NVIC->IP[iprx] |= (IRQPriority << shift_amount);
}

void UART_IRQHandler(UART_Handle_t *pUARTHandle) {
    // Implement generic IRQ handling if needed (e.g. ring buffer)
    // For now, just a placeholder or basic callback
}
