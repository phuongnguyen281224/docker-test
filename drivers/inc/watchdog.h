#ifndef WATCHDOG_H
#define WATCHDOG_H

#include "stm32f1xx.h"

/*
 * IWDG Key Values
 */
#define IWDG_KR_KEY_RELOAD      ((uint16_t)0xAAAA)
#define IWDG_KR_KEY_ENABLE      ((uint16_t)0xCCCC)
#define IWDG_KR_KEY_ACCESS      ((uint16_t)0x5555)

/*
 * IWDG Prescaler
 */
#define IWDG_Prescaler_4        ((uint8_t)0x00)
#define IWDG_Prescaler_8        ((uint8_t)0x01)
#define IWDG_Prescaler_16       ((uint8_t)0x02)
#define IWDG_Prescaler_32       ((uint8_t)0x03)
#define IWDG_Prescaler_64       ((uint8_t)0x04)
#define IWDG_Prescaler_128      ((uint8_t)0x05)
#define IWDG_Prescaler_256      ((uint8_t)0x06)

/*
 * IWDG Flag
 */
#define IWDG_FLAG_PVU           ((uint16_t)0x0001)
#define IWDG_FLAG_RVU           ((uint16_t)0x0002)

/*
 * WWDG Prescaler
 */
#define WWDG_Prescaler_1        ((uint32_t)0x00000000)
#define WWDG_Prescaler_2        ((uint32_t)0x00000080)
#define WWDG_Prescaler_4        ((uint32_t)0x00000100)
#define WWDG_Prescaler_8        ((uint32_t)0x00000180)

/*
 * Function Prototypes
 */

/* IWDG Functions */
void IWDG_WriteAccessCmd(uint16_t IWDG_WriteAccess);
void IWDG_SetPrescaler(uint8_t IWDG_Prescaler);
void IWDG_SetReload(uint16_t Reload);
void IWDG_ReloadCounter(void);
void IWDG_Enable(void);
uint8_t IWDG_GetFlagStatus(uint16_t IWDG_FLAG);

/* WWDG Functions */
void WWDG_DeInit(void);
void WWDG_SetPrescaler(uint32_t WWDG_Prescaler);
void WWDG_SetWindowValue(uint8_t WindowValue);
void WWDG_EnableIT(void);
void WWDG_SetCounter(uint8_t Counter);
void WWDG_Enable(uint8_t Counter);
uint8_t WWDG_GetFlagStatus(void);
void WWDG_ClearFlag(void);

#endif // WATCHDOG_H
