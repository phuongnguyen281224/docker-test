#ifndef DMA_H
#define DMA_H

#include "stm32f1xx.h"

/*
 * DMA Configuration Structure
 */
typedef struct
{
    uint32_t DMA_PeripheralBaseAddr; /*!< Specifies the peripheral base address for DMAy Channelx. */
    uint32_t DMA_MemoryBaseAddr;     /*!< Specifies the memory base address for DMAy Channelx. */
    uint32_t DMA_DIR;                /*!< Specifies if the peripheral is the source or destination.
                                          This parameter can be a value of @ref DMA_data_transfer_direction */
    uint32_t DMA_BufferSize;         /*!< Specifies the buffer size, in data unit, of the specified Channel. 
                                          The data unit is equal to the configuration set in DMA_PeripheralDataSize
                                          or DMA_MemoryDataSize members depending in the transfer direction. */
    uint32_t DMA_PeripheralInc;      /*!< Specifies whether the Peripheral address register is incremented or not.
                                          This parameter can be a value of @ref DMA_peripheral_incremented_mode */
    uint32_t DMA_MemoryInc;          /*!< Specifies whether the memory address register is incremented or not.
                                          This parameter can be a value of @ref DMA_memory_incremented_mode */
    uint32_t DMA_PeripheralDataSize; /*!< Specifies the Peripheral data width.
                                          This parameter can be a value of @ref DMA_peripheral_data_size */
    uint32_t DMA_MemoryDataSize;     /*!< Specifies the Memory data width.
                                          This parameter can be a value of @ref DMA_memory_data_size */
    uint32_t DMA_Mode;               /*!< Specifies the operation mode of the DMAy Channelx.
                                          This parameter can be a value of @ref DMA_circular_normal_mode */
    uint32_t DMA_Priority;           /*!< Specifies the software priority for the DMAy Channelx.
                                          This parameter can be a value of @ref DMA_priority_level */
    uint32_t DMA_M2M;                /*!< Specifies if the DMAy Channelx will be used in memory-to-memory transfer.
                                          This parameter can be a value of @ref DMA_memory_to_memory */
} DMA_Init_t;

/*
 * DMA_data_transfer_direction
 */
#define DMA_DIR_PeripheralDST       ((uint32_t)0x00000010)
#define DMA_DIR_PeripheralSRC       ((uint32_t)0x00000000)

/*
 * DMA_peripheral_incremented_mode
 */
#define DMA_PeripheralInc_Enable    ((uint32_t)0x00000040)
#define DMA_PeripheralInc_Disable   ((uint32_t)0x00000000)

/*
 * DMA_memory_incremented_mode
 */
#define DMA_MemoryInc_Enable        ((uint32_t)0x00000080)
#define DMA_MemoryInc_Disable       ((uint32_t)0x00000000)

/*
 * DMA_peripheral_data_size
 */
#define DMA_PeripheralDataSize_Byte      ((uint32_t)0x00000000)
#define DMA_PeripheralDataSize_HalfWord  ((uint32_t)0x00000100)
#define DMA_PeripheralDataSize_Word      ((uint32_t)0x00000200)

/*
 * DMA_memory_data_size
 */
#define DMA_MemoryDataSize_Byte          ((uint32_t)0x00000000)
#define DMA_MemoryDataSize_HalfWord      ((uint32_t)0x00000400)
#define DMA_MemoryDataSize_Word          ((uint32_t)0x00000800)

/*
 * DMA_circular_normal_mode
 */
#define DMA_Mode_Circular           ((uint32_t)0x00000020)
#define DMA_Mode_Normal             ((uint32_t)0x00000000)

/*
 * DMA_priority_level
 */
#define DMA_Priority_VeryHigh       ((uint32_t)0x00003000)
#define DMA_Priority_High           ((uint32_t)0x00002000)
#define DMA_Priority_Medium         ((uint32_t)0x00001000)
#define DMA_Priority_Low            ((uint32_t)0x00000000)

/*
 * DMA_memory_to_memory
 */
#define DMA_M2M_Enable              ((uint32_t)0x00004000)
#define DMA_M2M_Disable             ((uint32_t)0x00000000)

/*
 * Function Prototypes
 */
void DMA_Init(DMA_Channel_TypeDef* DMAy_Channelx, DMA_Init_t* DMA_InitStruct);
void DMA_DeInit(DMA_Channel_TypeDef* DMAy_Channelx);
void DMA_Cmd(DMA_Channel_TypeDef* DMAy_Channelx, uint8_t NewState);

#endif // DMA_H
