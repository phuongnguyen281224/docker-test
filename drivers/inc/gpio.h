#ifndef GPIO_H
#define GPIO_H

#include "stm32f1xx.h"

/*
 * =================================================================================
 * Clock Enable/Disable Macros for GPIO Ports
 * =================================================================================
 */

#define GPIOA_PCLK_EN()    (RCC->APB2ENR |= (1 << 2))
#define GPIOB_PCLK_EN()    (RCC->APB2ENR |= (1 << 3))
#define GPIOC_PCLK_EN()    (RCC->APB2ENR |= (1 << 4))
#define GPIOD_PCLK_EN()    (RCC->APB2ENR |= (1 << 5))

#define GPIOA_PCLK_DI()    (RCC->APB2ENR &= ~(1 << 2))
#define GPIOB_PCLK_DI()    (RCC->APB2ENR &= ~(1 << 3))
#define GPIOC_PCLK_DI()    (RCC->APB2ENR &= ~(1 << 4))
#define GPIOD_PCLK_DI()    (RCC->APB2ENR &= ~(1 << 5))


/*
 * =================================================================================
 * Configuration and Handle Structures
 * =================================================================================
 */

// Pin configuration structure
typedef struct {
    uint8_t GPIO_PinNumber;      // Possible values from @GPIO_PIN_NUMBERS
    uint8_t GPIO_PinMode;        // Possible values from @GPIO_PIN_MODES
    uint8_t GPIO_PinSpeed;       // Possible values from @GPIO_PIN_SPEED
} GPIO_PinConfig_t;

// Handle structure for a GPIO pin
typedef struct {
    GPIO_RegDef_t *pGPIOx;       // Pointer to hold the base address of the GPIO port
    GPIO_PinConfig_t PinConfig;  // Holds GPIO pin configuration settings
} GPIO_Handle_t;


/*
 * =================================================================================
 * Macros and Enums for Configuration
 * =================================================================================
 */

// @GPIO_PIN_NUMBERS
#define GPIO_PIN_0     0
#define GPIO_PIN_1     1
#define GPIO_PIN_2     2
#define GPIO_PIN_3     3
#define GPIO_PIN_4     4
#define GPIO_PIN_5     5
#define GPIO_PIN_6     6
#define GPIO_PIN_7     7
#define GPIO_PIN_8     8
#define GPIO_PIN_9     9
#define GPIO_PIN_10    10
#define GPIO_PIN_11    11
#define GPIO_PIN_12    12
#define GPIO_PIN_13    13
#define GPIO_PIN_14    14
#define GPIO_PIN_15    15


// @GPIO_PIN_MODES
// Input modes
#define GPIO_MODE_IN_ANALOG       0x00 // Analog mode
#define GPIO_MODE_IN_FLOATING     0x01 // Floating input (reset state)
#define GPIO_MODE_IN_PU_PD        0x02 // Input with pull-up / pull-down

// Output modes
#define GPIO_MODE_OUT_PP          0x10 // General purpose output push-pull
#define GPIO_MODE_OUT_OD          0x11 // General purpose output open-drain
#define GPIO_MODE_AF_PP           0x12 // Alternate function output push-pull
#define GPIO_MODE_AF_OD           0x13 // Alternate function output open-drain


// @GPIO_PIN_SPEED
#define GPIO_SPEED_10MHZ          1 // Output mode, max speed 10 MHz
#define GPIO_SPEED_2MHZ           2 // Output mode, max speed 2 MHz
#define GPIO_SPEED_50MHZ          3 // Output mode, max speed 50 MHz


/*
 * =================================================================================
 * Function Prototypes for GPIO Driver
 * =================================================================================
 */

// Peripheral Clock Setup
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnOrDi);

// Initialization and De-initialization
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

// Data Read and Write
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

#endif // GPIO_H
