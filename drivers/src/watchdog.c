#include "watchdog.h"

/*
 * =================================================================================
 * IWDG Functions
 * =================================================================================
 */

/**
 * @brief  Enables or disables write access to IWDG_PR and IWDG_RLR registers.
 * @param  IWDG_WriteAccess: new state of write access to IWDG_PR and IWDG_RLR registers.
 *         This parameter can be one of the following values:
 *            @arg IWDG_KR_KEY_ACCESS: Enable write access
 *            @arg IWDG_KR_KEY_RELOAD: Disable write access
 */
void IWDG_WriteAccessCmd(uint16_t IWDG_WriteAccess) {
    IWDG->KR = IWDG_WriteAccess;
}

/**
 * @brief  Sets IWDG Prescaler value.
 * @param  IWDG_Prescaler: specifies the IWDG Prescaler value.
 *         This parameter can be one of the following values:
 *            @arg IWDG_Prescaler_4: IWDG prescaler set to 4
 *            @arg IWDG_Prescaler_8: IWDG prescaler set to 8
 *            @arg IWDG_Prescaler_16: IWDG prescaler set to 16
 *            @arg IWDG_Prescaler_32: IWDG prescaler set to 32
 *            @arg IWDG_Prescaler_64: IWDG prescaler set to 64
 *            @arg IWDG_Prescaler_128: IWDG prescaler set to 128
 *            @arg IWDG_Prescaler_256: IWDG prescaler set to 256
 */
void IWDG_SetPrescaler(uint8_t IWDG_Prescaler) {
    IWDG->PR = IWDG_Prescaler;
}

/**
 * @brief  Sets IWDG Reload value.
 * @param  Reload: specifies the IWDG Reload value.
 *         This parameter must be a number between 0 and 0x0FFF.
 */
void IWDG_SetReload(uint16_t Reload) {
    IWDG->RLR = Reload;
}

/**
 * @brief  Reloads IWDG counter with value defined in the reload register
 *         (write access to IWDG_PR and IWDG_RLR registers disabled).
 */
void IWDG_ReloadCounter(void) {
    IWDG->KR = IWDG_KR_KEY_RELOAD;
}

/**
 * @brief  Enables IWDG (write access to IWDG_PR and IWDG_RLR registers disabled).
 */
void IWDG_Enable(void) {
    IWDG->KR = IWDG_KR_KEY_ENABLE;
}

/**
 * @brief  Checks whether the specified IWDG flag is set or not.
 * @param  IWDG_FLAG: specifies the flag to check.
 *         This parameter can be one of the following values:
 *            @arg IWDG_FLAG_PVU: Prescaler Value Update on going
 *            @arg IWDG_FLAG_RVU: Reload Value Update on going
 * @return The new state of IWDG_FLAG (SET or RESET).
 */
uint8_t IWDG_GetFlagStatus(uint16_t IWDG_FLAG) {
    if ((IWDG->SR & IWDG_FLAG) != (uint32_t)RESET) {
        return SET;
    } else {
        return RESET;
    }
}

/*
 * =================================================================================
 * WWDG Functions
 * =================================================================================
 */

/**
 * @brief  Deinitializes the WWDG peripheral registers to their default reset values.
 */
void WWDG_DeInit(void) {
    RCC->APB1RSTR |= (1 << 11); // WWDGRST
    RCC->APB1RSTR &= ~(1 << 11);
}

/**
 * @brief  Sets the WWDG Prescaler.
 * @param  WWDG_Prescaler: specifies the WWDG Prescaler.
 *         This parameter can be one of the following values:
 *            @arg WWDG_Prescaler_1: WWDG counter clock = (PCLK1/4096)/1
 *            @arg WWDG_Prescaler_2: WWDG counter clock = (PCLK1/4096)/2
 *            @arg WWDG_Prescaler_4: WWDG counter clock = (PCLK1/4096)/4
 *            @arg WWDG_Prescaler_8: WWDG counter clock = (PCLK1/4096)/8
 */
void WWDG_SetPrescaler(uint32_t WWDG_Prescaler) {
    uint32_t tmpreg = 0;
    /* Clear WDGTB[1:0] bits */
    tmpreg = WWDG->CFR & 0xFFFFFE7F;
    /* Set WDGTB[1:0] bits according to WWDG_Prescaler value */
    tmpreg |= WWDG_Prescaler;
    /* Store the new value */
    WWDG->CFR = tmpreg;
}

/**
 * @brief  Sets the WWDG window value.
 * @param  WindowValue: specifies the window value to be compared to the downcounter.
 *         This parameter value must be lower than 0x80.
 */
void WWDG_SetWindowValue(uint8_t WindowValue) {
    uint32_t tmpreg = 0;
    /* Clear W[6:0] bits */
    tmpreg = WWDG->CFR & 0xFFFFFF80;
    /* Set W[6:0] bits according to WindowValue value */
    tmpreg |= WindowValue & (uint8_t)0x7F;
    /* Store the new value */
    WWDG->CFR = tmpreg;
}

/**
 * @brief  Enables the WWDG Early Wakeup interrupt(EWI).
 */
void WWDG_EnableIT(void) {
    WWDG->CFR |= (1 << 9); // EWI bit
}

/**
 * @brief  Sets the WWDG counter value.
 * @param  Counter: specifies the watchdog counter value.
 *         This parameter must be a number between 0x40 and 0x7F.
 */
void WWDG_SetCounter(uint8_t Counter) {
    /* Write to T[6:0] bits to configure the counter value, no need to do
       a read-modify-write; writing a 0 to WDGA bit does nothing */
    WWDG->CR = Counter & (uint8_t)0x7F;
}

/**
 * @brief  Enables WWDG and load the counter value.                  
 * @param  Counter: specifies the watchdog counter value.
 *         This parameter must be a number between 0x40 and 0x7F.
 */
void WWDG_Enable(uint8_t Counter) {
    WWDG->CR = (1 << 7) | Counter; // WDGA | Counter
}

/**
 * @brief  Checks whether the Early Wakeup interrupt flag is set or not.
 * @return The new state of the Early Wakeup interrupt flag (SET or RESET).
 */
uint8_t WWDG_GetFlagStatus(void) {
    if ((WWDG->SR & 0x01) != (uint32_t)RESET) {
        return SET;
    } else {
        return RESET;
    }
}

/**
 * @brief  Clears Early Wakeup interrupt flag.
 */
void WWDG_ClearFlag(void) {
    WWDG->SR = (uint32_t)0x00;
}
