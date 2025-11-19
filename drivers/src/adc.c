#include "adc.h"

/**
 * @brief  Initializes the ADCx peripheral according to the specified parameters
 *         in the ADC_InitStruct.
 * @param  ADCx: where x can be 1 or 2 to select the ADC peripheral.
 * @param  ADC_InitStruct: pointer to an ADC_Config_t structure that contains
 *         the configuration information for the specified ADC peripheral.
 */
void ADC_Init(ADC_TypeDef* ADCx, ADC_Config_t* ADC_InitStruct) {
    uint32_t tmpreg1 = 0;
    uint8_t tmpreg2 = 0;

    /*---------------------------- ADCx CR1 Configuration -----------------*/
    /* Get the ADCx CR1 value */
    tmpreg1 = ADCx->CR1;
    /* Clear DUALMOD and SCAN bits */
    tmpreg1 &= 0xFFF0FEFF;
    /* Configure ADCx: Dual mode and Scan conversion mode */
    tmpreg1 |= (uint32_t)(ADC_InitStruct->ADC_Mode | ((uint32_t)ADC_InitStruct->ADC_ScanConvMode << 8));
    /* Write to ADCx CR1 */
    ADCx->CR1 = tmpreg1;

    /*---------------------------- ADCx CR2 Configuration -----------------*/
    /* Get the ADCx CR2 value */
    tmpreg1 = ADCx->CR2;
    /* Clear CONT, ALIGN and EXTSEL bits */
    tmpreg1 &= 0xFFF1F7FD;
    /* Configure ADCx: external trigger, right/left data alignment and continuous conversion mode */
    tmpreg1 |= (uint32_t)(ADC_InitStruct->ADC_DataAlign | ADC_InitStruct->ADC_ExternalTrigConv |
            ((uint32_t)ADC_InitStruct->ADC_ContinuousConvMode << 1));
    /* Write to ADCx CR2 */
    ADCx->CR2 = tmpreg1;

    /*---------------------------- ADCx SQR1 Configuration -----------------*/
    /* Get the ADCx SQR1 value */
    tmpreg1 = ADCx->SQR1;
    /* Clear L bits */
    tmpreg1 &= 0xFF0FFFFF;
    /* Configure ADCx: regular channel sequence length */
    tmpreg2 |= (uint8_t)(ADC_InitStruct->ADC_NbrOfChannel - (uint8_t)1);
    tmpreg1 |= (uint32_t)((uint32_t)tmpreg2 << 20);
    /* Write to ADCx SQR1 */
    ADCx->SQR1 = tmpreg1;
}

/**
 * @brief  Enables or disables the specified ADC peripheral.
 * @param  ADCx: where x can be 1 or 2 to select the ADC peripheral.
 * @param  NewState: new state of the ADCx peripheral. 
 *         This parameter can be: ENABLE or DISABLE.
 */
void ADC_Cmd(ADC_TypeDef* ADCx, uint8_t NewState) {
    if (NewState != DISABLE) {
        /* Enable the selected ADC peripheral */
        ADCx->CR2 |= (1 << 0); // ADON bit
    } else {
        /* Disable the selected ADC peripheral */
        ADCx->CR2 &= ~(1 << 0);
    }
}

/**
 * @brief  Configures for the selected ADC regular channel its corresponding
 *         rank in the sequencer and its sample time.
 * @param  ADCx: where x can be 1 or 2 to select the ADC peripheral.
 * @param  ADC_Channel: the ADC channel to configure. 
 * @param  Rank: The rank in the regular group sequencer.
 *         This parameter must be between 1 to 16.
 * @param  ADC_SampleTime: The sample time value to be set for the selected channel.
 */
void ADC_RegularChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime) {
    uint32_t tmpreg1 = 0, tmpreg2 = 0;

    /* if ADC_Channel_10 ... ADC_Channel_17 is selected */
    if (ADC_Channel > ADC_Channel_9) {
        /* Get the old register value */
        tmpreg1 = ADCx->SMPR1;
        /* Calculate the mask to clear */
        tmpreg2 = (uint32_t)0x07 << (3 * (ADC_Channel - 10));
        /* Clear the old channel sample time */
        tmpreg1 &= ~tmpreg2;
        /* Calculate the mask to set */
        tmpreg2 = (uint32_t)ADC_SampleTime << (3 * (ADC_Channel - 10));
        /* Set the new channel sample time */
        tmpreg1 |= tmpreg2;
        /* Store the new register value */
        ADCx->SMPR1 = tmpreg1;
    } else { /* ADC_Channel include in ADC_Channel_[0..9] */
        /* Get the old register value */
        tmpreg1 = ADCx->SMPR2;
        /* Calculate the mask to clear */
        tmpreg2 = (uint32_t)0x07 << (3 * ADC_Channel);
        /* Clear the old channel sample time */
        tmpreg1 &= ~tmpreg2;
        /* Calculate the mask to set */
        tmpreg2 = (uint32_t)ADC_SampleTime << (3 * ADC_Channel);
        /* Set the new channel sample time */
        tmpreg1 |= tmpreg2;
        /* Store the new register value */
        ADCx->SMPR2 = tmpreg1;
    }

    /* For Rank 1 to 6 */
    if (Rank < 7) {
        /* Get the old register value */
        tmpreg1 = ADCx->SQR3;
        /* Calculate the mask to clear */
        tmpreg2 = (uint32_t)0x1F << (5 * (Rank - 1));
        /* Clear the old SQx bits for the selected rank */
        tmpreg1 &= ~tmpreg2;
        /* Calculate the mask to set */
        tmpreg2 = (uint32_t)ADC_Channel << (5 * (Rank - 1));
        /* Set the SQx bits for the selected rank */
        tmpreg1 |= tmpreg2;
        /* Store the new register value */
        ADCx->SQR3 = tmpreg1;
    }
    /* For Rank 7 to 12 */
    else if (Rank < 13) {
        /* Get the old register value */
        tmpreg1 = ADCx->SQR2;
        /* Calculate the mask to clear */
        tmpreg2 = (uint32_t)0x1F << (5 * (Rank - 7));
        /* Clear the old SQx bits for the selected rank */
        tmpreg1 &= ~tmpreg2;
        /* Calculate the mask to set */
        tmpreg2 = (uint32_t)ADC_Channel << (5 * (Rank - 7));
        /* Set the SQx bits for the selected rank */
        tmpreg1 |= tmpreg2;
        /* Store the new register value */
        ADCx->SQR2 = tmpreg1;
    }
    /* For Rank 13 to 16 */
    else {
        /* Get the old register value */
        tmpreg1 = ADCx->SQR1;
        /* Calculate the mask to clear */
        tmpreg2 = (uint32_t)0x1F << (5 * (Rank - 13));
        /* Clear the old SQx bits for the selected rank */
        tmpreg1 &= ~tmpreg2;
        /* Calculate the mask to set */
        tmpreg2 = (uint32_t)ADC_Channel << (5 * (Rank - 13));
        /* Set the SQx bits for the selected rank */
        tmpreg1 |= tmpreg2;
        /* Store the new register value */
        ADCx->SQR1 = tmpreg1;
    }
}

/**
 * @brief  Enables or disables the selected ADC software start conversion.
 * @param  ADCx: where x can be 1 or 2 to select the ADC peripheral.
 * @param  NewState: new state of the selected ADC software start conversion.
 *         This parameter can be: ENABLE or DISABLE.
 */
void ADC_SoftwareStartConvCmd(ADC_TypeDef* ADCx, uint8_t NewState) {
    if (NewState != DISABLE) {
        /* Enable the selected ADC conversion on external event and start the selected
           ADC conversion on external event */
        ADCx->CR2 |= (1 << 22); // SWSTART bit
    } else {
        /* Disable the selected ADC conversion on external event */
        ADCx->CR2 &= ~(1 << 22);
    }
}

/**
 * @brief  Checks whether the specified ADC flag is set or not.
 * @param  ADCx: where x can be 1 or 2 to select the ADC peripheral.
 * @param  ADC_FLAG: specifies the flag to check. 
 *         This parameter can be one of the following values:
 *            @arg ADC_FLAG_EOC: End of conversion flag
 * @return The new state of ADC_FLAG (SET or RESET).
 */
uint8_t ADC_GetFlagStatus(ADC_TypeDef* ADCx, uint8_t ADC_FLAG) {
    if ((ADCx->SR & ADC_FLAG) != (uint8_t)RESET) {
        return SET;
    } else {
        return RESET;
    }
}

/**
 * @brief  Returns the last ADCx conversion result data for regular channel.
 * @param  ADCx: where x can be 1 or 2 to select the ADC peripheral.
 * @return The Data conversion value.
 */
uint16_t ADC_GetConversionValue(ADC_TypeDef* ADCx) {
    /* Return the selected ADC conversion value */
    return (uint16_t) ADCx->DR;
}
