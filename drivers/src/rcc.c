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
    volatile uint32_t timeout = 0;

    // 1. Enable HSE and wait for it to be ready
    RCC->CR |= RCC_CR_HSEON;
    
    timeout = 0;
    while (!(RCC->CR & RCC_CR_HSERDY)) {
        timeout++;
        if (timeout > 100000) {
            // Handle timeout (e.g., use HSI or error handler)
            // For now, we just break to avoid infinite loop
            break; 
        }
    }

    if (RCC->CR & RCC_CR_HSERDY) {
        // 2. Configure Flash prefetch and latency
        FLASH->ACR |= FLASH_ACR_PRFTBE;
        FLASH->ACR &= ~(FLASH_ACR_LATENCY_0 | FLASH_ACR_LATENCY_1 | FLASH_ACR_LATENCY_2); // Clear LATENCY bits
        FLASH->ACR |= FLASH_ACR_LATENCY_2; // Two wait states

        // 3. Configure bus prescalers
        // AHB prescaler = 1
        RCC->CFGR &= ~((1 << 4) | (1 << 5) | (1 << 6) | (1 << 7)); // HPRE = 0xxx (DIV1)
        
        // APB1 prescaler = 2
        RCC->CFGR &= ~((1 << 8) | (1 << 9) | (1 << 10)); // Clear PPRE1
        RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;
        
        // APB2 prescaler = 1
        RCC->CFGR &= ~((1 << 11) | (1 << 12) | (1 << 13)); // Clear PPRE2 (DIV1)

        // 4. Configure PLL
        // PLL source = HSE, PLL multiplication factor = 9
        RCC->CFGR |= RCC_CFGR_PLLSRC; 
        RCC->CFGR &= ~((1 << 18) | (1 << 19) | (1 << 20) | (1 << 21)); // Clear PLLMUL bits
        RCC->CFGR |= RCC_CFGR_PLLMULL9;

        // 5. Enable PLL and wait for it to be ready
        RCC->CR |= RCC_CR_PLLON;
        
        timeout = 0;
        while (!(RCC->CR & RCC_CR_PLLRDY)) {
            timeout++;
            if (timeout > 100000) break;
        }

        if (RCC->CR & RCC_CR_PLLRDY) {
            // 6. Select PLL as system clock source and wait for it to be set
            RCC->CFGR &= ~((1 << 0) | (1 << 1)); // Clear SW bits
            RCC->CFGR |= RCC_CFGR_SW_PLL;
            
            timeout = 0;
            while ((RCC->CFGR & (0x03 << 2)) != RCC_CFGR_SWS_PLL) {
                timeout++;
                if (timeout > 100000) break;
            }
        }
    }
}

/*********************************************************************
 * @fn      		  - RCC_APB2PeriphClockCmd
 *
 * @brief             - Enable or disable peripheral clock for APB2 peripherals
 *
 * @param[in]         - RCC_APB2Periph: specifies the APB2 peripheral to gates its clock.
 * @param[in]         - NewState: new state of the specified peripheral clock.
 *                      This parameter can be: ENABLE or DISABLE.
 *
 * @return            - None
 */
void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, uint8_t NewState) {
    if (NewState != DISABLE) {
        RCC->APB2ENR |= RCC_APB2Periph;
    } else {
        RCC->APB2ENR &= ~RCC_APB2Periph;
    }
}

/*********************************************************************
 * @fn      		  - RCC_APB1PeriphClockCmd
 *
 * @brief             - Enable or disable peripheral clock for APB1 peripherals
 *
 * @param[in]         - RCC_APB1Periph: specifies the APB1 peripheral to gates its clock.
 * @param[in]         - NewState: new state of the specified peripheral clock.
 *                      This parameter can be: ENABLE or DISABLE.
 *
 * @return            - None
 */
void RCC_APB1PeriphClockCmd(uint32_t RCC_APB1Periph, uint8_t NewState) {
    if (NewState != DISABLE) {
        RCC->APB1ENR |= RCC_APB1Periph;
    } else {
        RCC->APB1ENR &= ~RCC_APB1Periph;
    }
}
