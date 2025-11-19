#ifndef TIMER_H
#define TIMER_H

#include "stm32f10x.h"

/*
 * Configuration structure for Timer
 */
typedef struct {
    uint16_t Prescaler;       /*!< Specifies the prescaler value used to divide the TIM clock. */
    uint16_t Period;          /*!< Specifies the period value to be loaded into the active Auto-Reload Register at the next update event. */
    uint16_t CounterMode;     /*!< Specifies the counter mode. This parameter can be a value of @ref TIM_Counter_Mode */
} TIM_Base_Config_t;

/*
 * Configuration structure for PWM
 */
typedef struct {
    uint16_t OCMode;          /*!< Specifies the TIM mode. This parameter can be a value of @ref TIM_Output_Compare_and_PWM_modes */
    uint16_t Pulse;           /*!< Specifies the pulse value to be loaded into the Capture Compare Register. */
    uint16_t OCPolarity;      /*!< Specifies the output polarity. This parameter can be a value of @ref TIM_Output_Compare_Polarity */
} TIM_PWM_Config_t;

/*
 * Configuration structure for Input Capture
 */
typedef struct {
    uint16_t ICPolarity;      /*!< Specifies the active edge of the input signal. This parameter can be a value of @ref TIM_Input_Capture_Polarity */
    uint16_t ICSelection;     /*!< Specifies the input. This parameter can be a value of @ref TIM_Input_Capture_Selection */
    uint16_t ICPrescaler;     /*!< Specifies the Input Capture Prescaler. This parameter can be a value of @ref TIM_Input_Capture_Prescaler */
    uint16_t ICFilter;        /*!< Specifies the input capture filter. This parameter can be a number between 0x0 and 0xF */
} TIM_IC_Config_t;

/*
 * Handle structure for Timer
 */
typedef struct {
    TIM_TypeDef *pTIMx;       /*!< Pointer to the TIMx peripheral register base address */
    TIM_Base_Config_t BaseConfig;
    TIM_PWM_Config_t PWMConfig;
    TIM_IC_Config_t ICConfig;
} TIM_Handle_t;

/*
 * TIM_Counter_Mode
 */
#define TIM_COUNTERMODE_UP                0x0000
#define TIM_COUNTERMODE_DOWN              TIM_CR1_DIR

/*
 * TIM_Output_Compare_and_PWM_modes
 */
#define TIM_OCMODE_TIMING                 0x0000
#define TIM_OCMODE_ACTIVE                 0x0010
#define TIM_OCMODE_INACTIVE               0x0020
#define TIM_OCMODE_TOGGLE                 0x0030
#define TIM_OCMODE_PWM1                   0x0060
#define TIM_OCMODE_PWM2                   0x0070

/*
 * TIM_Output_Compare_Polarity
 */
#define TIM_OCPOLARITY_HIGH               0x0000
#define TIM_OCPOLARITY_LOW                TIM_CCER_CC1P

/*
 * TIM_Input_Capture_Polarity
 */
#define TIM_ICPOLARITY_RISING             0x0000
#define TIM_ICPOLARITY_FALLING            TIM_CCER_CC1P
#define TIM_ICPOLARITY_BOTHEDGE           (TIM_CCER_CC1P | TIM_CCER_CC1NP) // Note: CC1NP is only available on TIM1/TIM8 in some devices, check datasheet. For F103 basic timers, usually only Rising/Falling.

/*
 * TIM_Input_Capture_Selection
 */
#define TIM_ICSELECTION_DIRECTTI          0x01 /*!< TIM Input 1, 2, 3 or 4 is selected to be connected to IC1, IC2, IC3 or IC4, respectively */
#define TIM_ICSELECTION_INDIRECTTI        0x02 /*!< TIM Input 1, 2, 3 or 4 is selected to be connected to IC2, IC1, IC4 or IC3, respectively */
#define TIM_ICSELECTION_TRC               0x03 /*!< TIM Input 1, 2, 3 or 4 is selected to be connected to TRC */

/*
 * TIM_Input_Capture_Prescaler
 */
#define TIM_ICPSC_DIV1                    0x0000 /*!< Capture performed each time an edge is detected on the capture input */
#define TIM_ICPSC_DIV2                    0x0004 /*!< Capture performed once every 2 events */
#define TIM_ICPSC_DIV4                    0x0008 /*!< Capture performed once every 4 events */
#define TIM_ICPSC_DIV8                    0x000C /*!< Capture performed once every 8 events */


/*
 * APIs
 */

// Base
void TIM_Base_Init(TIM_Handle_t *pTIMHandle);
void TIM_Base_Start(TIM_TypeDef *TIMx);
void TIM_Base_Stop(TIM_TypeDef *TIMx);
void TIM_Base_Start_IT(TIM_TypeDef *TIMx);
void TIM_Base_Stop_IT(TIM_TypeDef *TIMx);

// PWM
void TIM_PWM_Init(TIM_Handle_t *pTIMHandle, uint8_t Channel);
void TIM_PWM_Start(TIM_TypeDef *TIMx, uint8_t Channel);
void TIM_PWM_Stop(TIM_TypeDef *TIMx, uint8_t Channel);
void TIM_PWM_SetDutyCycle(TIM_TypeDef *TIMx, uint8_t Channel, uint16_t Pulse);

// Input Capture
void TIM_IC_Init(TIM_Handle_t *pTIMHandle, uint8_t Channel);
void TIM_IC_Start_IT(TIM_TypeDef *TIMx, uint8_t Channel);
void TIM_IC_Stop_IT(TIM_TypeDef *TIMx, uint8_t Channel);
uint32_t TIM_IC_ReadCaptureValue(TIM_TypeDef *TIMx, uint8_t Channel);

// Interrupts
void TIM_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void TIM_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void TIM_IRQHandler(TIM_Handle_t *pTIMHandle);

// Application Callbacks
void TIM_PeriodElapsedCallback(TIM_Handle_t *pTIMHandle);
void TIM_IC_CaptureCallback(TIM_Handle_t *pTIMHandle);

#endif // TIMER_H
