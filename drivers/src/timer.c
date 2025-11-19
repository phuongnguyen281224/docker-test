#include "timer.h"
#include "rcc.h"
#include "gpio.h"

// Helper function to enable clock for a given timer
static void TIM_EnableClock(TIM_TypeDef *TIMx) {
    if (TIMx == TIM1) RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    else if (TIMx == TIM2) RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    else if (TIMx == TIM3) RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
    else if (TIMx == TIM4) RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
}

void TIM_Base_Init(TIM_Handle_t *pTIMHandle) {
    TIM_EnableClock(pTIMHandle->pTIMx);

    // 1. Set Prescaler
    pTIMHandle->pTIMx->PSC = pTIMHandle->BaseConfig.Prescaler;

    // 2. Set Auto-Reload Register
    pTIMHandle->pTIMx->ARR = pTIMHandle->BaseConfig.Period;

    // 3. Set Counter Mode (Direction)
    if (pTIMHandle->BaseConfig.CounterMode == TIM_COUNTERMODE_UP) {
        pTIMHandle->pTIMx->CR1 &= ~TIM_CR1_DIR;
    } else {
        pTIMHandle->pTIMx->CR1 |= TIM_CR1_DIR;
    }
}

void TIM_Base_Start(TIM_TypeDef *TIMx) {
    TIMx->CR1 |= TIM_CR1_CEN;
}

void TIM_Base_Stop(TIM_TypeDef *TIMx) {
    TIMx->CR1 &= ~TIM_CR1_CEN;
}

void TIM_Base_Start_IT(TIM_TypeDef *TIMx) {
    TIMx->DIER |= TIM_DIER_UIE;
    TIMx->CR1 |= TIM_CR1_CEN;
}

void TIM_Base_Stop_IT(TIM_TypeDef *TIMx) {
    TIMx->DIER &= ~TIM_DIER_UIE;
    TIMx->CR1 &= ~TIM_CR1_CEN;
}

void TIM_PWM_Init(TIM_Handle_t *pTIMHandle, uint8_t Channel) {
    uint16_t ccmr_offset = 0;
    uint16_t ccer_offset = 0;
    uint32_t ccmr_val = 0;

    // Configure CCMR register
    if (Channel == 1 || Channel == 2) {
        ccmr_offset = 0; // CCMR1
    } else {
        ccmr_offset = 0x04; // CCMR2
    }

    // Read current CCMR value
    if (Channel == 1 || Channel == 3) {
        // Channel 1 or 3 (Low byte of CCMR)
        ccmr_val = pTIMHandle->pTIMx->CCMR1; // Read from CCMR1 or CCMR2 based on offset logic below
        if (ccmr_offset == 0x04) ccmr_val = pTIMHandle->pTIMx->CCMR2;

        ccmr_val &= ~(0xFF); // Clear first 8 bits
        ccmr_val |= (pTIMHandle->PWMConfig.OCMode << 4);
        ccmr_val |= TIM_CCMR1_OC1PE; // Enable Preload
    } else {
        // Channel 2 or 4 (High byte of CCMR)
        ccmr_val = pTIMHandle->pTIMx->CCMR1;
        if (ccmr_offset == 0x04) ccmr_val = pTIMHandle->pTIMx->CCMR2;

        ccmr_val &= ~(0xFF00); // Clear high 8 bits
        ccmr_val |= (pTIMHandle->PWMConfig.OCMode << 12);
        ccmr_val |= TIM_CCMR1_OC2PE; // Enable Preload
    }

    // Write back to CCMR
    if (ccmr_offset == 0) pTIMHandle->pTIMx->CCMR1 = ccmr_val;
    else pTIMHandle->pTIMx->CCMR2 = ccmr_val;

    // Configure CCER register (Polarity)
    // CCER has 4 bits per channel: CCxE, CCxP, ...
    // Channel 1: bit 0, 1
    // Channel 2: bit 4, 5
    // Channel 3: bit 8, 9
    // Channel 4: bit 12, 13
    ccer_offset = (Channel - 1) * 4;
    pTIMHandle->pTIMx->CCER &= ~(0x3 << ccer_offset); // Clear CCxE and CCxP
    pTIMHandle->pTIMx->CCER |= (pTIMHandle->PWMConfig.OCPolarity << (ccer_offset + 1));

    // Set initial Pulse (Duty Cycle)
    switch (Channel) {
        case 1: pTIMHandle->pTIMx->CCR1 = pTIMHandle->PWMConfig.Pulse; break;
        case 2: pTIMHandle->pTIMx->CCR2 = pTIMHandle->PWMConfig.Pulse; break;
        case 3: pTIMHandle->pTIMx->CCR3 = pTIMHandle->PWMConfig.Pulse; break;
        case 4: pTIMHandle->pTIMx->CCR4 = pTIMHandle->PWMConfig.Pulse; break;
    }
    
    // Enable Main Output for Advanced Timers (TIM1)
    if (pTIMHandle->pTIMx == TIM1) {
        TIM1->BDTR |= TIM_BDTR_MOE;
    }
}

void TIM_PWM_Start(TIM_TypeDef *TIMx, uint8_t Channel) {
    uint16_t ccer_offset = (Channel - 1) * 4;
    TIMx->CCER |= (1 << ccer_offset); // Enable CCxE
    TIMx->CR1 |= TIM_CR1_CEN; // Enable Counter
}

void TIM_PWM_Stop(TIM_TypeDef *TIMx, uint8_t Channel) {
    uint16_t ccer_offset = (Channel - 1) * 4;
    TIMx->CCER &= ~(1 << ccer_offset); // Disable CCxE
}

void TIM_PWM_SetDutyCycle(TIM_TypeDef *TIMx, uint8_t Channel, uint16_t Pulse) {
    switch (Channel) {
        case 1: TIMx->CCR1 = Pulse; break;
        case 2: TIMx->CCR2 = Pulse; break;
        case 3: TIMx->CCR3 = Pulse; break;
        case 4: TIMx->CCR4 = Pulse; break;
    }
}

void TIM_IC_Init(TIM_Handle_t *pTIMHandle, uint8_t Channel) {
    // Simplified IC Init for basic capture
     uint16_t ccmr_offset = 0;
    uint32_t ccmr_val = 0;

    if (Channel == 1 || Channel == 2) ccmr_offset = 0; // CCMR1
    else ccmr_offset = 0x04; // CCMR2

    // Read current CCMR
    if (ccmr_offset == 0) ccmr_val = pTIMHandle->pTIMx->CCMR1;
    else ccmr_val = pTIMHandle->pTIMx->CCMR2;

    if (Channel == 1 || Channel == 3) {
        ccmr_val &= ~(0xFF);
        ccmr_val |= (pTIMHandle->ICConfig.ICSelection & 0x03); // CCxS
        ccmr_val |= (pTIMHandle->ICConfig.ICFilter << 4);      // ICxF
    } else {
        ccmr_val &= ~(0xFF00);
        ccmr_val |= ((pTIMHandle->ICConfig.ICSelection & 0x03) << 8);
        ccmr_val |= (pTIMHandle->ICConfig.ICFilter << 12);
    }

    if (ccmr_offset == 0) pTIMHandle->pTIMx->CCMR1 = ccmr_val;
    else pTIMHandle->pTIMx->CCMR2 = ccmr_val;

    // Configure CCER (Polarity and Enable)
    uint16_t ccer_offset = (Channel - 1) * 4;
    pTIMHandle->pTIMx->CCER &= ~(0x3 << ccer_offset); // Clear
    pTIMHandle->pTIMx->CCER |= (pTIMHandle->ICConfig.ICPolarity << (ccer_offset + 1)); // Set Polarity
    pTIMHandle->pTIMx->CCER |= (1 << ccer_offset); // Enable Capture
}

void TIM_IC_Start_IT(TIM_TypeDef *TIMx, uint8_t Channel) {
    uint16_t dier_bit = 0;
    switch (Channel) {
        case 1: dier_bit = TIM_DIER_CC1IE; break;
        case 2: dier_bit = TIM_DIER_CC2IE; break;
        case 3: dier_bit = TIM_DIER_CC3IE; break;
        case 4: dier_bit = TIM_DIER_CC4IE; break;
    }
    TIMx->DIER |= dier_bit;
    TIMx->CR1 |= TIM_CR1_CEN;
}

void TIM_IC_Stop_IT(TIM_TypeDef *TIMx, uint8_t Channel) {
    uint16_t dier_bit = 0;
    switch (Channel) {
        case 1: dier_bit = TIM_DIER_CC1IE; break;
        case 2: dier_bit = TIM_DIER_CC2IE; break;
        case 3: dier_bit = TIM_DIER_CC3IE; break;
        case 4: dier_bit = TIM_DIER_CC4IE; break;
    }
    TIMx->DIER &= ~dier_bit;
}

uint32_t TIM_IC_ReadCaptureValue(TIM_TypeDef *TIMx, uint8_t Channel) {
    switch (Channel) {
        case 1: return TIMx->CCR1;
        case 2: return TIMx->CCR2;
        case 3: return TIMx->CCR3;
        case 4: return TIMx->CCR4;
    }
    return 0;
}

void TIM_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi) {
    if (EnorDi == 1) { // Enable
        if (IRQNumber <= 31) {
            NVIC->ISER[0] |= (1 << IRQNumber);
        } else if (IRQNumber > 31 && IRQNumber < 64) {
            NVIC->ISER[1] |= (1 << (IRQNumber % 32));
        } else if (IRQNumber >= 64 && IRQNumber < 96) {
            NVIC->ISER[2] |= (1 << (IRQNumber % 64));
        }
    } else { // Disable
        if (IRQNumber <= 31) {
            NVIC->ICER[0] |= (1 << IRQNumber);
        } else if (IRQNumber > 31 && IRQNumber < 64) {
            NVIC->ICER[1] |= (1 << (IRQNumber % 32));
        } else if (IRQNumber >= 64 && IRQNumber < 96) {
            NVIC->ICER[2] |= (1 << (IRQNumber % 64));
        }
    }
}

void TIM_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority) {
    uint8_t iprx = IRQNumber / 4;
    uint8_t iprx_section = IRQNumber % 4;
    uint8_t shift_amount = (8 * iprx_section) + (8 - 4); // 4 bits implemented
    NVIC->IP[iprx] |= (IRQPriority << shift_amount);
}

void TIM_IRQHandler(TIM_Handle_t *pTIMHandle) {
    // Check for Update Event
    if (pTIMHandle->pTIMx->SR & TIM_SR_UIF) {
        pTIMHandle->pTIMx->SR &= ~TIM_SR_UIF; // Clear flag
        TIM_PeriodElapsedCallback(pTIMHandle);
    }
    // Check for Capture Events (Simplified)
    if (pTIMHandle->pTIMx->SR & (TIM_SR_CC1IF | TIM_SR_CC2IF | TIM_SR_CC3IF | TIM_SR_CC4IF)) {
        // Clear flags handled in callback or by reading CCR
        TIM_IC_CaptureCallback(pTIMHandle);
    }
}

__attribute__((weak)) void TIM_PeriodElapsedCallback(TIM_Handle_t *pTIMHandle) {
    (void)pTIMHandle;
    // Weak implementation
}

__attribute__((weak)) void TIM_IC_CaptureCallback(TIM_Handle_t *pTIMHandle) {
    (void)pTIMHandle;
    // Weak implementation
}



