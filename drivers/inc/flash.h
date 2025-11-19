#ifndef FLASH_H
#define FLASH_H

#include "stm32f1xx.h"

/*
 * FLASH Status
 */
typedef enum
{ 
  FLASH_BUSY = 1,
  FLASH_ERROR_PG,
  FLASH_ERROR_WRP,
  FLASH_COMPLETE,
  FLASH_TIMEOUT
} FLASH_Status;

/*
 * FLASH Flags
 */
#define FLASH_FLAG_BSY         ((uint32_t)0x00000001)  /*!< FLASH Busy flag */
#define FLASH_FLAG_PGERR       ((uint32_t)0x00000004)  /*!< FLASH Programming error flag */
#define FLASH_FLAG_WRPRTERR    ((uint32_t)0x00000010)  /*!< FLASH Write protected error flag */
#define FLASH_FLAG_EOP         ((uint32_t)0x00000020)  /*!< FLASH End of Operation flag */

/*
 * FLASH Keys
 */
#define FLASH_KEY1             ((uint32_t)0x45670123)
#define FLASH_KEY2             ((uint32_t)0xCDEF89AB)

/*
 * Function Prototypes
 */
void FLASH_Unlock(void);
void FLASH_Lock(void);
FLASH_Status FLASH_ErasePage(uint32_t Page_Address);
FLASH_Status FLASH_EraseAllPages(void);
FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data);
FLASH_Status FLASH_GetStatus(void);
FLASH_Status FLASH_WaitForLastOperation(uint32_t Timeout);

#endif // FLASH_H
