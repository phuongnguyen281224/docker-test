#ifndef RCC_H
#define RCC_H

#include "stm32f1xx.h"

/*
 * =================================================================================
 * Function Prototypes for RCC Driver
 * =================================================================================
 */

void SystemClock_Config(void);

// Peripheral Clock Control
void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, uint8_t NewState);
void RCC_APB1PeriphClockCmd(uint32_t RCC_APB1Periph, uint8_t NewState);

// Macros for APB2 Peripherals
#define RCC_APB2Periph_AFIO      (1 << 0)
#define RCC_APB2Periph_GPIOA     (1 << 2)
#define RCC_APB2Periph_GPIOB     (1 << 3)
#define RCC_APB2Periph_GPIOC     (1 << 4)
#define RCC_APB2Periph_GPIOD     (1 << 5)
#define RCC_APB2Periph_GPIOE     (1 << 6)
#define RCC_APB2Periph_ADC1      (1 << 9)
#define RCC_APB2Periph_ADC2      (1 << 10)
#define RCC_APB2Periph_TIM1      (1 << 11)
#define RCC_APB2Periph_SPI1      (1 << 12)
#define RCC_APB2Periph_USART1    (1 << 14)

// Macros for APB1 Peripherals
#define RCC_APB1Periph_TIM2      (1 << 0)
#define RCC_APB1Periph_TIM3      (1 << 1)
#define RCC_APB1Periph_TIM4      (1 << 2)
#define RCC_APB1Periph_USART2    (1 << 17)
#define RCC_APB1Periph_USART3    (1 << 18)
#define RCC_APB1Periph_I2C1      (1 << 21)
#define RCC_APB1Periph_I2C2      (1 << 22)
#define RCC_APB1Periph_SPI2      (1 << 14)

#endif // RCC_H
