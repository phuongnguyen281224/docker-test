#include "dma.h"

/**
 * @brief  Initializes the DMAy Channelx according to the specified parameters 
 *         in the DMA_InitStruct.
 * @param  DMAy_Channelx: where y can be 1 or 2 to select the DMA and 
 *         x can be 1 to 7 for DMA1 and 1 to 5 for DMA2 to select the DMA Channel.
 * @param  DMA_InitStruct: pointer to a DMA_Init_t structure that contains
 *         the configuration information for the specified DMA Channel.
 */
void DMA_Init(DMA_Channel_TypeDef* DMAy_Channelx, DMA_Init_t* DMA_InitStruct) {
    uint32_t tmpreg = 0;

    /*--------------------------- DMAy Channelx CCR Configuration -----------------*/
    /* Get the DMAy_Channelx CCR value */
    tmpreg = DMAy_Channelx->CCR;

    /* Clear MEM2MEM, PL, MSIZE, PSIZE, MINC, PINC, CIRC and DIR bits */
    tmpreg &= 0xFFFF800F;

    /* Configure DMAy Channelx: data transfer, data size, priority level and mode */
    tmpreg |= DMA_InitStruct->DMA_DIR | DMA_InitStruct->DMA_Mode |
              DMA_InitStruct->DMA_PeripheralInc | DMA_InitStruct->DMA_MemoryInc |
              DMA_InitStruct->DMA_PeripheralDataSize | DMA_InitStruct->DMA_MemoryDataSize |
              DMA_InitStruct->DMA_Priority | DMA_InitStruct->DMA_M2M;

    /* Write to DMAy Channelx CCR */
    DMAy_Channelx->CCR = tmpreg;

    /*--------------------------- DMAy Channelx CNDTR Configuration ---------------*/
    /* Write to DMAy Channelx CNDTR */
    DMAy_Channelx->CNDTR = DMA_InitStruct->DMA_BufferSize;

    /*--------------------------- DMAy Channelx CPAR Configuration ----------------*/
    /* Write to DMAy Channelx CPAR */
    DMAy_Channelx->CPAR = DMA_InitStruct->DMA_PeripheralBaseAddr;

    /*--------------------------- DMAy Channelx CMAR Configuration ----------------*/
    /* Write to DMAy Channelx CMAR */
    DMAy_Channelx->CMAR = DMA_InitStruct->DMA_MemoryBaseAddr;
}

/**
 * @brief  Deinitializes the DMAy Channelx registers to their default reset values.
 * @param  DMAy_Channelx: where y can be 1 or 2 to select the DMA and 
 *         x can be 1 to 7 for DMA1 and 1 to 5 for DMA2 to select the DMA Channel.
 */
void DMA_DeInit(DMA_Channel_TypeDef* DMAy_Channelx) {
    /* Disable the selected DMAy Channelx */
    DMAy_Channelx->CCR &= (uint16_t)(~1);

    /* Reset DMAy Channelx control register */
    DMAy_Channelx->CCR = 0;

    /* Reset DMAy Channelx remaining bytes register */
    DMAy_Channelx->CNDTR = 0;

    /* Reset DMAy Channelx peripheral address register */
    DMAy_Channelx->CPAR = 0;

    /* Reset DMAy Channelx memory address register */
    DMAy_Channelx->CMAR = 0;
}

/**
 * @brief  Enables or disables the specified DMAy Channelx.
 * @param  DMAy_Channelx: where y can be 1 or 2 to select the DMA and 
 *         x can be 1 to 7 for DMA1 and 1 to 5 for DMA2 to select the DMA Channel.
 * @param  NewState: new state of the DMAy Channelx. 
 *         This parameter can be: ENABLE or DISABLE.
 */
void DMA_Cmd(DMA_Channel_TypeDef* DMAy_Channelx, uint8_t NewState) {
    if (NewState != DISABLE) {
        /* Enable the selected DMAy Channelx */
        DMAy_Channelx->CCR |= 1;
    } else {
        /* Disable the selected DMAy Channelx */
        DMAy_Channelx->CCR &= (uint16_t)(~1);
    }
}
