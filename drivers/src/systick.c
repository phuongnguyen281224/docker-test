#include "systick.h"


static uint32_t g_system_clock = 8000000; // Default 8MHz

/**
 * @brief  Initialize SysTick driver
 * @param  system_clock_freq: System clock frequency in Hz
 */
void SysTick_Init(uint32_t system_clock_freq) {
    g_system_clock = system_clock_freq;
    
    // Disable SysTick during setup
    SysTick->CTRL = 0;
    
    // We will use SysTick for simple polling delays mostly, 
    // but if we wanted interrupts we would configure it here.
    // For now, let's just ensure it's reset.
    SysTick->VAL = 0;
}

/**
 * @brief  Delay for a specified number of milliseconds
 * @param  ms: Number of milliseconds to delay
 */
void delay_ms(uint32_t ms) {
    // Calculate the number of ticks for 1ms
    // SysTick clock source is AHB (HCLK) or AHB/8. 
    // We'll use AHB clock (CLKSOURCE = 1).
    
    uint32_t ticks_per_ms = g_system_clock / 1000;
    
    // Load the value
    SysTick->LOAD = ticks_per_ms - 1;
    SysTick->VAL = 0;
    
    // Enable SysTick with core clock source
    SysTick->CTRL = SYSTICK_CTRL_ENABLE_Msk | SYSTICK_CTRL_CLKSOURCE_Msk;
    
    for (uint32_t i = 0; i < ms; i++) {
        // Wait until the COUNTFLAG is set
        while (!((SysTick->CTRL) & SYSTICK_CTRL_COUNTFLAG_Msk));
    }
    
    // Disable SysTick
    SysTick->CTRL = 0;
}

/**
 * @brief  Delay for a specified number of microseconds
 * @param  us: Number of microseconds to delay
 */
void delay_us(uint32_t us) {
    uint32_t ticks_per_us = g_system_clock / 1000000;
    
    // Load the value
    SysTick->LOAD = ticks_per_us - 1;
    SysTick->VAL = 0;
    
    // Enable SysTick with core clock source
    SysTick->CTRL = SYSTICK_CTRL_ENABLE_Msk | SYSTICK_CTRL_CLKSOURCE_Msk;
    
    for (uint32_t i = 0; i < us; i++) {
        // Wait until the COUNTFLAG is set
        while (!((SysTick->CTRL) & SYSTICK_CTRL_COUNTFLAG_Msk));
    }
    
    // Disable SysTick
    SysTick->CTRL = 0;
}
