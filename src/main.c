#include "stm32f1xx.h"
#include "gpio.h"
#include "rcc.h"
#include "timer.h"
#include "uart.h"
#include "systick.h"
#include <string.h>

// Global Handles
UART_Handle_t huart1;

void SystemClock_Config(void); // Defined in rcc.c (assumed) or we rely on default

int main(void) {
    // 1. System Clock Config
    // SystemClock_Config(); // Assuming already configured or default 72MHz setup if available
    // For now, we assume 72MHz or default HSI. If default HSI (8MHz), prescalers need adjustment.
    // Let's assume the user has a startup file that calls SystemInit.
    
    // Initialize SysTick for delay_ms (assuming 72MHz clock)
    SysTick_Init(72000000);

    // 2. GPIO Init
    GPIO_Handle_t GpioLed, GpioUartTx, GpioUartRx;

    // LED (PC13)
    GpioLed.pGPIOx = GPIOC;
    GpioLed.PinConfig.GPIO_PinNumber = GPIO_PIN_13;
    GpioLed.PinConfig.GPIO_PinMode = GPIO_MODE_OUT_PP;
    GpioLed.PinConfig.GPIO_PinSpeed = GPIO_SPEED_2MHZ;
    GPIO_Init(&GpioLed);

    // UART1 TX (PA9)
    GpioUartTx.pGPIOx = GPIOA;
    GpioUartTx.PinConfig.GPIO_PinNumber = GPIO_PIN_9;
    GpioUartTx.PinConfig.GPIO_PinMode = GPIO_MODE_AF_PP;
    GpioUartTx.PinConfig.GPIO_PinSpeed = GPIO_SPEED_50MHZ;
    GPIO_Init(&GpioUartTx);

    // UART1 RX (PA10)
    GpioUartRx.pGPIOx = GPIOA;
    GpioUartRx.PinConfig.GPIO_PinNumber = GPIO_PIN_10;
    GpioUartRx.PinConfig.GPIO_PinMode = GPIO_MODE_IN_FLOATING;
    GPIO_Init(&GpioUartRx);

    // 3. Timer Init (TIM2) for Delay - REMOVED (Using SysTick)

    // 4. UART Init (UART1)
    huart1.pUSARTx = USART1;
    huart1.UART_Config.BaudRate = 9600;
    huart1.UART_Config.WordLength = UART_WORDLENGTH_8B;
    huart1.UART_Config.StopBits = UART_STOPBITS_1;
    huart1.UART_Config.Parity = UART_PARITY_NONE;
    huart1.UART_Config.Mode = UART_MODE_TXRX;
    huart1.UART_Config.HwFlowCtl = UART_HW_FLOW_CTRL_NONE;
    UART_Init(&huart1);

    char msg[] = "Hello from STM32 UART Driver!\r\n";
    UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg));

    while(1) {
        // Blink LED
        GPIO_ToggleOutputPin(GPIOC, GPIO_PIN_13);
        
        // Send Heartbeat
        // UART_Transmit(&huart1, (uint8_t*)"Tick\r\n", 6);

        // Echo Check
        // Note: This is blocking receive for 1 byte, might stall the loop if no data.
        // For testing, we can check RXNE flag manually or just rely on blink.
        if (USART1->SR & USART_SR_RXNE) {
            uint8_t data = UART_ReceiveByte(&huart1);
            UART_Transmit(&huart1, &data, 1); // Echo back
        }

        delay_ms(500);
    }
}

