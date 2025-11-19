#ifndef SYSTICK_H
#define SYSTICK_H

#include "stm32f1xx.h"

/*
 * SysTick Control and Status Register Bits
 */
#define SYSTICK_CTRL_ENABLE_Pos     0U
#define SYSTICK_CTRL_ENABLE_Msk     (1UL << SYSTICK_CTRL_ENABLE_Pos)

#define SYSTICK_CTRL_TICKINT_Pos    1U
#define SYSTICK_CTRL_TICKINT_Msk    (1UL << SYSTICK_CTRL_TICKINT_Pos)

#define SYSTICK_CTRL_CLKSOURCE_Pos  2U
#define SYSTICK_CTRL_CLKSOURCE_Msk  (1UL << SYSTICK_CTRL_CLKSOURCE_Pos)

#define SYSTICK_CTRL_COUNTFLAG_Pos  16U
#define SYSTICK_CTRL_COUNTFLAG_Msk  (1UL << SYSTICK_CTRL_COUNTFLAG_Pos)

/*
 * Function Prototypes
 */
void SysTick_Init(uint32_t system_clock_freq);
void delay_ms(uint32_t ms);
void delay_us(uint32_t us);

#endif // SYSTICK_H
