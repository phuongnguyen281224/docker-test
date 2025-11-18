#include "rcc.h"

/*********************************************************************
 * @fn      		  - SystemClock_Config
 *
 * @brief             - Configures the system clock to 72MHz using HSE and PLL.
 *
 * @details           - This function performs the following steps:
 *                      1. Enables the High-Speed External (HSE) oscillator.
 *                      2. Waits for the HSE to become stable.
 *                      3. Configures the Flash prefetch buffer and latency for high-speed operation.
 *                      4. Configures the AHB, APB1, and APB2 bus prescalers.
 *                      5. Configures the PLL (Phase-Locked Loop) to multiply the HSE frequency (8MHz * 9 = 72MHz).
 *                      6. Enables the PLL.
 *                      7. Waits for the PLL to lock.
 *                      8. Selects the PLL as the system clock source.
 *                      9. Waits for the system clock to switch to the PLL.
 *
 * @param[in]         - None
 *
 * @return            - None
 *
 * @Note              - This configuration assumes an 8MHz crystal is used for the HSE.
 *                    - This is a common setup for "Blue Pill" STM32F103C8T6 boards.
 */
void SystemClock_Config(void) {
    // 1. Enable HSE and wait for it to be ready
    RCC->CR |= (1 << 16); // HSEON = 1
    while (!(RCC->CR & (1 << 17))); // Wait for HSERDY

    // 2. Configure Flash prefetch and latency
    FLASH->ACR |= (1 << 4); // PRFTBE = 1 (Prefetch buffer enable)
    FLASH->ACR &= ~((1 << 0) | (1 << 1) | (1 << 2)); // Clear LATENCY bits
    FLASH->ACR |= (2 << 0); // LATENCY = 2 (Two wait states, as SYSCLK > 48MHz)

    // 3. Configure bus prescalers
    // AHB prescaler = 1
    RCC->CFGR &= ~((1 << 4) | (1 << 5) | (1 << 6) | (1 << 7)); // HPRE = 0xxx
    // APB1 prescaler = 2
    RCC->CFGR &= ~((1 << 8) | (1 << 9) | (1 << 10)); // PPRE1 = 100
    RCC->CFGR |= (4 << 8);
    // APB2 prescaler = 1
    RCC->CFGR &= ~((1 << 11) | (1 << 12) | (1 << 13)); // PPRE2 = 0xxx

    // 4. Configure PLL
    // PLL source = HSE, PLL multiplication factor = 9
    RCC->CFGR |= (1 << 16); // PLLSRC = 1 (HSE oscillator clock selected as PLL input clock)
    RCC->CFGR &= ~((1 << 18) | (1 << 19) | (1 << 20) | (1 << 21)); // Clear PLLMUL bits
    RCC->CFGR |= (7 << 18); // PLLMUL = 0111 (PLL input clock x 9)

    // 5. Enable PLL and wait for it to be ready
    RCC->CR |= (1 << 24); // PLLON = 1
    while (!(RCC->CR & (1 << 25))); // Wait for PLLRDY

    // 6. Select PLL as system clock source and wait for it to be set
    RCC->CFGR &= ~((1 << 0) | (1 << 1)); // Clear SW bits
    RCC->CFGR |= (2 << 0); // SW = 10 (PLL selected as system clock)
    while (!((RCC->CFGR & (0b11 << 2)) == (0b10 << 2))); // Wait for SWS to indicate PLL is used
}
