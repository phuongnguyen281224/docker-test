#include "rtc.h"

/**
 * @brief  Enables or disables the specified RTC interrupts.
 * @param  RTC_IT: specifies the RTC interrupts sources to be enabled or disabled.
 * @param  NewState: new state of the specified RTC interrupts.
 *         This parameter can be: ENABLE or DISABLE.
 */
void RTC_ITConfig(uint16_t RTC_IT, uint8_t NewState) {
    if (NewState != DISABLE) {
        RTC->CRH |= RTC_IT;
    } else {
        RTC->CRH &= (uint16_t)~RTC_IT;
    }
}

/**
 * @brief  Enters the RTC configuration mode.
 */
void RTC_EnterConfigMode(void) {
    /* Set the CNF flag to enter in the Configuration Mode */
    RTC->CRL |= (1 << 4);
}

/**
 * @brief  Exits from the RTC configuration mode.
 */
void RTC_ExitConfigMode(void) {
    /* Reset the CNF flag to exit from the Configuration Mode */
    RTC->CRL &= ~(1 << 4);
}

/**
 * @brief  Gets the RTC counter value.
 * @return RTC counter value.
 */
uint32_t RTC_GetCounter(void) {
    uint16_t high1 = 0, high2 = 0, low = 0;
    high1 = RTC->CNTH;
    low = RTC->CNTL;
    high2 = RTC->CNTH;

    if (high1 != high2) { /* In case of counter roll over during reading of CNTH and CNTL */
        return (((uint32_t)high2 << 16) | RTC->CNTL);
    } else {
        return (((uint32_t)high1 << 16) | low);
    }
}

/**
 * @brief  Sets the RTC counter value.
 * @param  CounterValue: RTC counter new value.
 */
void RTC_SetCounter(uint32_t CounterValue) {
    RTC_EnterConfigMode();
    /* Set RTC COUNTER MSB word */
    RTC->CNTH = (CounterValue >> 16);
    /* Set RTC COUNTER LSB word */
    RTC->CNTL = (CounterValue & 0xFFFF);
    RTC_ExitConfigMode();
}

/**
 * @brief  Sets the RTC prescaler value.
 * @param  PrescalerValue: RTC prescaler new value.
 */
void RTC_SetPrescaler(uint32_t PrescalerValue) {
    RTC_EnterConfigMode();
    /* Set RTC PRESCALER MSB word */
    RTC->PRLH = (PrescalerValue >> 16);
    /* Set RTC PRESCALER LSB word */
    RTC->PRLL = (PrescalerValue & 0xFFFF);
    RTC_ExitConfigMode();
}

/**
 * @brief  Sets the RTC alarm value.
 * @param  AlarmValue: RTC alarm new value.
 */
void RTC_SetAlarm(uint32_t AlarmValue) {
    RTC_EnterConfigMode();
    /* Set the ALARM MSB word */
    RTC->ALRH = (AlarmValue >> 16);
    /* Set the ALARM LSB word */
    RTC->ALRL = (AlarmValue & 0xFFFF);
    RTC_ExitConfigMode();
}

/**
 * @brief  Gets the RTC divider value.
 * @return RTC Divider value.
 */
uint32_t RTC_GetDivider(void) {
    uint32_t tmpreg = 0;
    tmpreg = ((uint32_t)RTC->DIVH & (uint32_t)0x000F) << 16;
    tmpreg |= RTC->DIVL;
    return tmpreg;
}

/**
 * @brief  Waits until last write operation on RTC registers has finished.
 */
void RTC_WaitForLastTask(void) {
    /* Loop until RTOFF flag is set */
    while ((RTC->CRL & RTC_FLAG_RTOFF) == (uint16_t)RESET) {
    }
}

/**
 * @brief  Waits until the RTC registers (RTC_CNT, RTC_ALR and RTC_PRL)
 *         are synchronized with RTC APB clock.
 */
void RTC_WaitForSynchro(void) {
    /* Clear RSF flag */
    RTC->CRL &= (uint16_t)~RTC_FLAG_RSF;
    /* Loop until RSF flag is set */
    while ((RTC->CRL & RTC_FLAG_RSF) == (uint16_t)RESET) {
    }
}

/**
 * @brief  Checks whether the specified RTC flag is set or not.
 * @param  RTC_FLAG: specifies the flag to check.
 * @return The new state of RTC_FLAG (SET or RESET).
 */
uint8_t RTC_GetFlagStatus(uint16_t RTC_FLAG) {
    if ((RTC->CRL & RTC_FLAG) != (uint16_t)RESET) {
        return SET;
    } else {
        return RESET;
    }
}

/**
 * @brief  Clears the RTC's pending flags.
 * @param  RTC_FLAG: specifies the flag to clear.
 */
void RTC_ClearFlag(uint16_t RTC_FLAG) {
    /* Clear the corresponding RTC flag */
    RTC->CRL &= (uint16_t)~RTC_FLAG;
}

/**
 * @brief  Enables or disables access to the Backup Domain registers.
 * @param  NewState: new state of the access to the Backup Domain registers.
 *         This parameter can be: ENABLE or DISABLE.
 */
void PWR_BackupAccessCmd(uint8_t NewState) {
    if (NewState != DISABLE) {
        /* Enable the Backup Access */
        PWR->CR |= (1 << 8); // DBP bit
    } else {
        /* Disable the Backup Access */
        PWR->CR &= ~(1 << 8);
    }
}

/**
 * @brief  Deinitializes the BKP peripheral registers to their default reset values.
 */
void BKP_DeInit(void) {
    /* Reset the Backup Domain */
    RCC->BDCR |= (1 << 16); // BDRST
    RCC->BDCR &= ~(1 << 16);
}
