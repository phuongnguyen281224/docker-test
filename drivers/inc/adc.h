#ifndef ADC_H
#define ADC_H

#include "stm32f1xx.h"

/*
 * ADC Configuration Structure
 */
typedef struct
{
    uint32_t ADC_Mode;                      /*!< Configures the ADC to operate in independent or
                                                 dual mode. 
                                                 This parameter can be a value of @ref ADC_mode */
    uint32_t ADC_ScanConvMode;              /*!< Specifies whether the conversion is performed in
                                                 Scan (multichannels) or Single (one channel) mode.
                                                 This parameter can be set to ENABLE or DISABLE */
    uint32_t ADC_ContinuousConvMode;        /*!< Specifies whether the conversion is performed in
                                                 Continuous or Single mode.
                                                 This parameter can be set to ENABLE or DISABLE */
    uint32_t ADC_ExternalTrigConv;          /*!< Defines the external trigger used to start the analog
                                                 to digital conversion of regular channels. 
                                                 This parameter can be a value of @ref ADC_external_trigger_sources_for_regular_channels_conversion */
    uint32_t ADC_DataAlign;                 /*!< Specifies whether the ADC data alignment is left or right.
                                                 This parameter can be a value of @ref ADC_data_align */
    uint8_t ADC_NbrOfChannel;               /*!< Specifies the number of ADC channels that will be converted
                                                 using the sequencer for regular channel group.
                                                 This parameter must range from 1 to 16. */
} ADC_Config_t;

/*
 * @ref ADC_mode
 */
#define ADC_Mode_Independent                ((uint32_t)0x00000000)

/*
 * @ref ADC_external_trigger_sources_for_regular_channels_conversion
 */
#define ADC_ExternalTrigConv_None           ((uint32_t)0x000E0000)

/*
 * @ref ADC_data_align
 */
#define ADC_DataAlign_Right                 ((uint32_t)0x00000000)
#define ADC_DataAlign_Left                  ((uint32_t)0x00000800)

/*
 * ADC Channels
 */
#define ADC_Channel_0                       ((uint8_t)0x00)
#define ADC_Channel_1                       ((uint8_t)0x01)
#define ADC_Channel_2                       ((uint8_t)0x02)
#define ADC_Channel_3                       ((uint8_t)0x03)
#define ADC_Channel_4                       ((uint8_t)0x04)
#define ADC_Channel_5                       ((uint8_t)0x05)
#define ADC_Channel_6                       ((uint8_t)0x06)
#define ADC_Channel_7                       ((uint8_t)0x07)
#define ADC_Channel_8                       ((uint8_t)0x08)
#define ADC_Channel_9                       ((uint8_t)0x09)
#define ADC_Channel_10                      ((uint8_t)0x0A)
#define ADC_Channel_11                      ((uint8_t)0x0B)
#define ADC_Channel_12                      ((uint8_t)0x0C)
#define ADC_Channel_13                      ((uint8_t)0x0D)
#define ADC_Channel_14                      ((uint8_t)0x0E)
#define ADC_Channel_15                      ((uint8_t)0x0F)
#define ADC_Channel_16                      ((uint8_t)0x10)
#define ADC_Channel_17                      ((uint8_t)0x11)

/*
 * ADC Sampling Times
 */
#define ADC_SampleTime_1Cycles5             ((uint8_t)0x00)
#define ADC_SampleTime_7Cycles5             ((uint8_t)0x01)
#define ADC_SampleTime_13Cycles5            ((uint8_t)0x02)
#define ADC_SampleTime_28Cycles5            ((uint8_t)0x03)
#define ADC_SampleTime_41Cycles5            ((uint8_t)0x04)
#define ADC_SampleTime_55Cycles5            ((uint8_t)0x05)
#define ADC_SampleTime_71Cycles5            ((uint8_t)0x06)
#define ADC_SampleTime_239Cycles5           ((uint8_t)0x07)

/*
 * Function Prototypes
 */
void ADC_Init(ADC_TypeDef* ADCx, ADC_Config_t* ADC_InitStruct);
void ADC_Cmd(ADC_TypeDef* ADCx, uint8_t NewState);
void ADC_RegularChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime);
void ADC_SoftwareStartConvCmd(ADC_TypeDef* ADCx, uint8_t NewState);
uint8_t ADC_GetFlagStatus(ADC_TypeDef* ADCx, uint8_t ADC_FLAG);
uint16_t ADC_GetConversionValue(ADC_TypeDef* ADCx);

#endif // ADC_H
