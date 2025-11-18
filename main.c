#include <stdint.h>

// Register addresses
#define RCC_BASE      0x40021000
#define GPIOC_BASE    0x40011000

#define RCC_APB2ENR   (*(volatile uint32_t *)(RCC_BASE + 0x18))
#define GPIOC_CRH     (*(volatile uint32_t *)(GPIOC_BASE + 0x04))
#define GPIOC_ODR     (*(volatile uint32_t *)(GPIOC_BASE + 0x0C))

// Simple delay function
void delay(volatile uint32_t count) {
    while (count--) {}
}

int main(void) {
    // Enable clock for GPIOC
    // Bit 4 I/O port C clock enable
    RCC_APB2ENR |= (1 << 4);

    // Configure PC13 as output push-pull
    // Clear CNF13 and MODE13 bits (bits 20-23)
    GPIOC_CRH &= ~(0x0F << 20);
    // Set MODE13 to 01 (Output mode, max speed 10 MHz)
    // Set CNF13 to 00 (General purpose output push-pull)
    GPIOC_CRH |= (0x01 << 20);

    while(1) {
        // Turn LED on (drive pin low)
        GPIOC_ODR &= ~(1 << 13);
        delay(500000);

        // Turn LED off (drive pin high)
        GPIOC_ODR |= (1 << 13);
        delay(500000);
    }
}
