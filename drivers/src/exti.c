#include "exti.h"

/**
 * @brief  Initialize the EXTI according to the specified parameters in the EXTI_Config_t
 * @param  pEXTIConfig: pointer to a EXTI_Config_t structure
 */
void EXTI_Init(EXTI_Config_t *pEXTIConfig) {
    if (pEXTIConfig->EXTI_LineCmd == ENABLE) {
        // 1. Configure the Mode (Interrupt or Event)
        if (pEXTIConfig->EXTI_Mode == EXTI_MODE_INTERRUPT) {
            EXTI->IMR |= (1 << pEXTIConfig->EXTI_Line);
            EXTI->EMR &= ~(1 << pEXTIConfig->EXTI_Line);
        } else {
            EXTI->EMR |= (1 << pEXTIConfig->EXTI_Line);
            EXTI->IMR &= ~(1 << pEXTIConfig->EXTI_Line);
        }

        // 2. Configure the Trigger
        if (pEXTIConfig->EXTI_Trigger == EXTI_TRIGGER_RISING) {
            EXTI->RTSR |= (1 << pEXTIConfig->EXTI_Line);
            EXTI->FTSR &= ~(1 << pEXTIConfig->EXTI_Line);
        } else if (pEXTIConfig->EXTI_Trigger == EXTI_TRIGGER_FALLING) {
            EXTI->FTSR |= (1 << pEXTIConfig->EXTI_Line);
            EXTI->RTSR &= ~(1 << pEXTIConfig->EXTI_Line);
        } else if (pEXTIConfig->EXTI_Trigger == EXTI_TRIGGER_RISING_FALLING) {
            EXTI->RTSR |= (1 << pEXTIConfig->EXTI_Line);
            EXTI->FTSR |= (1 << pEXTIConfig->EXTI_Line);
        }
    } else {
        // Disable the line
        EXTI->IMR &= ~(1 << pEXTIConfig->EXTI_Line);
        EXTI->EMR &= ~(1 << pEXTIConfig->EXTI_Line);
    }
}

/**
 * @brief  Deinitializes the EXTI peripheral registers to their default reset values.
 */
void EXTI_DeInit(void) {
    EXTI->IMR = 0x00000000;
    EXTI->EMR = 0x00000000;
    EXTI->RTSR = 0x00000000;
    EXTI->FTSR = 0x00000000;
    EXTI->PR = 0x000FFFFF; // Write 1 to clear
}

/**
 * @brief  Checks whether the specified EXTI line is asserted or not.
 * @param  EXTI_Line: specifies the EXTI line to check.
 * @return The new state of EXTI_Line (SET or RESET).
 */
uint8_t EXTI_GetPendingStatus(uint32_t EXTI_Line) {
    if (EXTI->PR & (1 << EXTI_Line)) {
        return SET;
    } else {
        return RESET;
    }
}

/**
 * @brief  Clears the EXTI's line pending bits.
 * @param  EXTI_Line: specifies the EXTI lines to clear.
 */
void EXTI_ClearPendingBit(uint32_t EXTI_Line) {
    EXTI->PR = (1 << EXTI_Line);
}

/**
 * @brief  Selects the GPIO pin used as EXTI Line.
 * @param  GPIO_PortSource: selects the GPIO port to be used as source for EXTI lines.
 * @param  GPIO_PinSource: specifies the EXTI line to be configured.
 */
void AFIO_EXTIConfig(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource) {
    // 1. Enable AFIO clock
    RCC->APB2ENR |= (1 << 0); // AFIOEN bit

    uint32_t temp, temp1, temp2;
    
    temp1 = GPIO_PinSource >> 2;
    temp2 = GPIO_PinSource & 0x03;
    
    temp = (0x0F) << (4 * temp2);
    AFIO->EXTICR[temp1] &= ~temp;
    AFIO->EXTICR[temp1] |= (((uint32_t)GPIO_PortSource) << (4 * temp2));
}
