#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

/*
 * =================================================================================
 * Base addresses for peripherals
 * =================================================================================
 */
#define PERIPH_BASE           0x40000000U
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x10000U)

#define GPIOA_BASE            (APB2PERIPH_BASE + 0x0800U)
#define GPIOB_BASE            (APB2PERIPH_BASE + 0x0C00U)
#define GPIOC_BASE            (APB2PERIPH_BASE + 0x1000U)
#define GPIOD_BASE            (APB2PERIPH_BASE + 0x1400U)

#define RCC_BASE              0x40021000U

/*
 * =================================================================================
 * Peripheral register definition structures
 * =================================================================================
 */

// GPIO register map
typedef struct {
    volatile uint32_t CRL;  // Port configuration register low
    volatile uint32_t CRH;  // Port configuration register high
    volatile uint32_t IDR;  // Port input data register
    volatile uint32_t ODR;  // Port output data register
    volatile uint32_t BSRR; // Port bit set/reset register
    volatile uint32_t BRR;  // Port bit reset register
    volatile uint32_t LCKR; // Port configuration lock register
} GPIO_RegDef_t;

// RCC register map
typedef struct {
    volatile uint32_t CR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t APB2RSTR;
    volatile uint32_t APB1RSTR;
    volatile uint32_t AHBENR;
    volatile uint32_t APB2ENR;
    volatile uint32_t APB1ENR;
    volatile uint32_t BDCR;
    volatile uint32_t CSR;
} RCC_RegDef_t;


/*
 * =================================================================================
 * Peripheral definitions (Peripheral base addresses typecasted to xxx_RegDef_t)
 * =================================================================================
 */

#define GPIOA  ((GPIO_RegDef_t*)GPIOA_BASE)
#define GPIOB  ((GPIO_RegDef_t*)GPIOB_BASE)
#define GPIOC  ((GPIO_RegDef_t*)GPIOC_BASE)
#define GPIOD  ((GPIO_RegDef_t*)GPIOD_BASE)

#define RCC    ((RCC_RegDef_t*)RCC_BASE)


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


// Generic Macros
#define ENABLE 1
#define DISABLE 0
#define SET ENABLE
#define RESET DISABLE
#define GPIO_PIN_SET   SET
#define GPIO_PIN_RESET RESET

/*
 * =================================================================================
 * Function Prototypes for GPIO Driver
 * =================================================================================
 */

// Peripheral Clock Setup
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnOrDi);

// Initialization and De-initialization
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx); // Note: STM32F1 doesn't have peripheral reset registers for GPIO, this will be a conceptual reset.

// Data Read and Write
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

#endif // GPIO_H
