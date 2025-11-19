#ifndef EXTI_H
#define EXTI_H

#include "stm32f1xx.h"
#include "gpio.h"

/*
 * EXTI Mode
 */
#define EXTI_MODE_INTERRUPT     0
#define EXTI_MODE_EVENT         1

/*
 * EXTI Trigger
 */
#define EXTI_TRIGGER_RISING     0
#define EXTI_TRIGGER_FALLING    1
#define EXTI_TRIGGER_RISING_FALLING 2

/*
 * EXTI Configuration Structure
 */
typedef struct
{
    uint8_t EXTI_Line;      /*!< Specifies the EXTI lines to be enabled or disabled.
                                 This parameter can be any combination of @ref EXTI_Lines */
    uint8_t EXTI_Mode;      /*!< Specifies the mode for the EXTI lines.
                                 This parameter can be a value of @ref EXTI_Mode */
    uint8_t EXTI_Trigger;   /*!< Specifies the trigger signal active edge for the EXTI lines.
                                 This parameter can be a value of @ref EXTI_Trigger */
    uint8_t EXTI_LineCmd;   /*!< Specifies the new state of the selected EXTI lines.
                                 This parameter can be set either to ENABLE or DISABLE */
} EXTI_Config_t;

/*
 * EXTI Lines
 */
#define EXTI_LINE0      0
#define EXTI_LINE1      1
#define EXTI_LINE2      2
#define EXTI_LINE3      3
#define EXTI_LINE4      4
#define EXTI_LINE5      5
#define EXTI_LINE6      6
#define EXTI_LINE7      7
#define EXTI_LINE8      8
#define EXTI_LINE9      9
#define EXTI_LINE10     10
#define EXTI_LINE11     11
#define EXTI_LINE12     12
#define EXTI_LINE13     13
#define EXTI_LINE14     14
#define EXTI_LINE15     15

/*
 * Function Prototypes
 */
void EXTI_Init(EXTI_Config_t *pEXTIConfig);
void EXTI_DeInit(void);
uint8_t EXTI_GetPendingStatus(uint32_t EXTI_Line);
void EXTI_ClearPendingBit(uint32_t EXTI_Line);

/*
 * AFIO Configuration for EXTI
 */
void AFIO_EXTIConfig(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource);

#define GPIO_PORT_SOURCE_GPIOA      0
#define GPIO_PORT_SOURCE_GPIOB      1
#define GPIO_PORT_SOURCE_GPIOC      2
#define GPIO_PORT_SOURCE_GPIOD      3
#define GPIO_PORT_SOURCE_GPIOE      4

#endif // EXTI_H
