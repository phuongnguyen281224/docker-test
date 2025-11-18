#include "gpio.h"

/*********************************************************************
 * @fn      		  - GPIO_PeriClockControl
 *
 * @brief             - This function enables or disables peripheral clock for the given GPIO port
 *
 * @param[in]         - pGPIOx: base address of the GPIO peripheral
 * @param[in]         - EnOrDi: ENABLE or DISABLE macros
 *
 * @return            - none
 *
 * @Note              - none
 */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnOrDi) {
    if (EnOrDi == ENABLE) {
        if (pGPIOx == GPIOA) {
            GPIOA_PCLK_EN();
        } else if (pGPIOx == GPIOB) {
            GPIOB_PCLK_EN();
        } else if (pGPIOx == GPIOC) {
            GPIOC_PCLK_EN();
        } else if (pGPIOx == GPIOD) {
            GPIOD_PCLK_EN();
        }
    } else {
        if (pGPIOx == GPIOA) {
            GPIOA_PCLK_DI();
        } else if (pGPIOx == GPIOB) {
            GPIOB_PCLK_DI();
        } else if (pGPIOx == GPIOC) {
            GPIOC_PCLK_DI();
        } else if (pGPIOx == GPIOD) {
            GPIOD_PCLK_DI();
        }
    }
}

/*********************************************************************
 * @fn      		  - GPIO_Init
 *
 * @brief             - This function initializes the given GPIO pin
 *
 * @param[in]         - pGPIOHandle: pointer to a GPIO_Handle_t structure that contains
 *                                   the configuration information for the specified GPIO peripheral.
 *
 * @return            - none
 *
 * @Note              - none
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle) {
    uint32_t temp = 0;
    GPIO_RegDef_t *pGPIOx = pGPIOHandle->pGPIOx;
    uint8_t pinNumber = pGPIOHandle->PinConfig.GPIO_PinNumber;
    uint8_t mode = pGPIOHandle->PinConfig.GPIO_PinMode;
    uint8_t speed = pGPIOHandle->PinConfig.GPIO_PinSpeed;

    // 1. Enable peripheral clock
    GPIO_PeriClockControl(pGPIOx, ENABLE);

    // 2. Configure the mode and speed
    volatile uint32_t *configReg;
    uint8_t shift;

    if (pinNumber < 8) {
        configReg = &pGPIOx->CRL;
        shift = pinNumber * 4;
    } else {
        configReg = &pGPIOx->CRH;
        shift = (pinNumber - 8) * 4;
    }

    // Clear the 4 bits for the pin
    *configReg &= ~(0x0F << shift);

    if (mode <= GPIO_MODE_IN_PU_PD) { // Input Modes
        if (mode == GPIO_MODE_IN_ANALOG) {
            // CNF = 00, MODE = 00 (Analog)
            temp = 0x00;
        } else if (mode == GPIO_MODE_IN_FLOATING) {
            // CNF = 01, MODE = 00 (Floating)
            temp = 0x04;
        } else { // GPIO_MODE_IN_PU_PD
            // CNF = 10, MODE = 00 (Pull-up/Pull-down)
            temp = 0x08;
            // Note: The actual pull-up/pull-down is set via ODR register
            // For simplicity, we assume user will set ODR separately if needed.
            // For pull-up: Set ODR bit to 1. For pull-down: Set ODR bit to 0.
        }
    } else { // Output Modes
        temp = speed; // Set speed (MODE bits)
        if (mode == GPIO_MODE_OUT_PP) {
            // CNF = 00 (Push-pull)
            temp |= 0x00;
        } else if (mode == GPIO_MODE_OUT_OD) {
            // CNF = 01 (Open-drain)
            temp |= 0x04;
        } else if (mode == GPIO_MODE_AF_PP) {
            // CNF = 10 (Alternate function push-pull)
            temp |= 0x08;
        } else { // GPIO_MODE_AF_OD
            // CNF = 11 (Alternate function open-drain)
            temp |= 0x0C;
        }
    }

    *configReg |= (temp << shift);
}

/*********************************************************************
 * @fn      		  - GPIO_DeInit
 *
 * @brief             - This function de-initializes the given GPIO port
 *
 * @param[in]         - pGPIOx: base address of the GPIO peripheral
 *
 * @return            - none
 *
 * @Note              - In STM32F1, there is no single register to reset a GPIO peripheral.
 *                      We will reset the configuration registers to their default state.
 */
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx) {
    pGPIOx->CRL = 0x44444444;
    pGPIOx->CRH = 0x44444444;
    pGPIOx->ODR = 0x00000000;
    pGPIOx->BSRR = 0x00000000;
    pGPIOx->BRR = 0x00000000;
}

/*********************************************************************
 * @fn      		  - GPIO_ReadFromInputPin
 *
 * @brief             - This function reads the value from a specified input pin
 *
 * @param[in]         - pGPIOx: base address of the GPIO peripheral
 * @param[in]         - PinNumber: The pin number to be read
 *
 * @return            - 0 or 1
 *
 * @Note              - none
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber) {
    uint8_t value;
    value = (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x00000001);
    return value;
}

/*********************************************************************
 * @fn      		  - GPIO_ReadFromInputPort
 *
 * @brief             - This function reads the value from the entire port
 *
 * @param[in]         - pGPIOx: base address of the GPIO peripheral
 *
 * @return            - The 16-bit value of the port's input data register
 *
 * @Note              - none
 */
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx) {
    uint16_t value;
    value = (uint16_t)pGPIOx->IDR;
    return value;
}

/*********************************************************************
 * @fn      		  - GPIO_WriteToOutputPin
 *
 * @brief             - This function writes a value to a specified output pin
 *
 * @param[in]         - pGPIOx: base address of the GPIO peripheral
 * @param[in]         - PinNumber: The pin number to be written to
 * @param[in]         - Value: The value to be written (GPIO_PIN_SET or GPIO_PIN_RESET)
 *
 * @return            - none
 *
 * @Note              - none
 */
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value) {
    if (Value == GPIO_PIN_SET) {
        // Use BSRR register to set the pin
        pGPIOx->BSRR = (1 << PinNumber);
    } else {
        // Use BRR register to reset the pin
        pGPIOx->BRR = (1 << PinNumber);
    }
}

/*********************************************************************
 * @fn      		  - GPIO_WriteToOutputPort
 *
 * @brief             - This function writes a value to the entire output port
 *
 * @param[in]         - pGPIOx: base address of the GPIO peripheral
 * @param[in]         - Value: The 16-bit value to be written to the port
 *
 * @return            - none
 *
 * @Note              - none
 */
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value) {
    pGPIOx->ODR = Value;
}

/*********************************************************************
 * @fn      		  - GPIO_ToggleOutputPin
 *
 * @brief             - This function toggles the specified output pin
 *
 * @param[in]         - pGPIOx: base address of the GPIO peripheral
 * @param[in]         - PinNumber: The pin number to be toggled
 *
 * @return            - none
 *
 * @Note              - none
 */
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber) {
    pGPIOx->ODR ^= (1 << PinNumber);
}
