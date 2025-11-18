#include "gpio.h"

// Simple delay function
void delay(volatile uint32_t count) {
    while (count--) {}
}

int main(void) {
    GPIO_Handle_t GpioLed;

    // Configure the LED pin (PC13)
    GpioLed.pGPIOx = GPIOC;
    GpioLed.PinConfig.GPIO_PinNumber = GPIO_PIN_13;
    GpioLed.PinConfig.GPIO_PinMode = GPIO_MODE_OUT_PP;
    GpioLed.PinConfig.GPIO_PinSpeed = GPIO_SPEED_2MHZ;

    // Initialize the GPIO pin
    GPIO_Init(&GpioLed);

    while(1) {
        // Turn LED on (Blue Pill LED is active low)
        GPIO_WriteToOutputPin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
        delay(500000);

        // Turn LED off
        GPIO_WriteToOutputPin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
        delay(500000);

        /*
        // Example of using the toggle function
        GPIO_ToggleOutputPin(GPIOC, GPIO_PIN_13);
        delay(500000);
        */
    }
}
