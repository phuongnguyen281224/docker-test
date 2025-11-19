#include "flash.h"

/**
 * @brief  Unlocks the FLASH Program Erase Controller.
 */
void FLASH_Unlock(void) {
    /* Authorize the FPEC Access */
    FLASH->KEYR = FLASH_KEY1;
    FLASH->KEYR = FLASH_KEY2;
}

/**
 * @brief  Locks the FLASH Program Erase Controller.
 */
void FLASH_Lock(void) {
    /* Set the LOCK Bit to lock the FPEC and the CR of  */
    FLASH->CR |= (1 << 7); // LOCK bit
}

/**
 * @brief  Erases a specified FLASH page.
 * @param  Page_Address: The page address to be erased.
 * @return FLASH Status: The returned value can be: FLASH_BUSY, FLASH_ERROR_PG,
 *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
 */
FLASH_Status FLASH_ErasePage(uint32_t Page_Address) {
    FLASH_Status status = FLASH_COMPLETE;
    
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(0x000B0000);
    
    if (status == FLASH_COMPLETE) {
        /* if the previous operation is completed, proceed to erase the page */
        FLASH->CR |= (1 << 1); // PER bit
        FLASH->AR = Page_Address;
        FLASH->CR |= (1 << 6); // STRT bit
        
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(0x000B0000);
        
        /* Disable the PER Bit */
        FLASH->CR &= ~(1 << 1);
    }
    
    return status;
}

/**
 * @brief  Erases all FLASH pages.
 * @return FLASH Status: The returned value can be: FLASH_BUSY, FLASH_ERROR_PG,
 *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
 */
FLASH_Status FLASH_EraseAllPages(void) {
    FLASH_Status status = FLASH_COMPLETE;
    
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(0x000B0000);
    
    if (status == FLASH_COMPLETE) {
        /* if the previous operation is completed, proceed to erase all pages */
        FLASH->CR |= (1 << 2); // MER bit
        FLASH->CR |= (1 << 6); // STRT bit
        
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(0x000B0000);
        
        /* Disable the MER Bit */
        FLASH->CR &= ~(1 << 2);
    }
    
    return status;
}

/**
 * @brief  Programs a word at a specified address.
 * @param  Address: specifies the address to be programmed.
 * @param  Data: specifies the data to be programmed.
 * @return FLASH Status: The returned value can be: FLASH_BUSY, FLASH_ERROR_PG,
 *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
 */
FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data) {
    FLASH_Status status = FLASH_COMPLETE;
    
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(0x000B0000);
    
    if (status == FLASH_COMPLETE) {
        /* if the previous operation is completed, proceed to program the new data */
        FLASH->CR |= (1 << 0); // PG bit
        
        *(volatile uint32_t*)Address = Data;
        
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(0x000B0000);
        
        /* Disable the PG Bit */
        FLASH->CR &= ~(1 << 0);
    }
    
    return status;
}

/**
 * @brief  Returns the FLASH Status.
 * @return FLASH Status: The returned value can be: FLASH_BUSY, FLASH_ERROR_PG,
 *         FLASH_ERROR_WRP or FLASH_COMPLETE.
 */
FLASH_Status FLASH_GetStatus(void) {
    FLASH_Status status = FLASH_COMPLETE;
    
    if ((FLASH->SR & FLASH_FLAG_BSY) == FLASH_FLAG_BSY) {
        status = FLASH_BUSY;
    } else if ((FLASH->SR & FLASH_FLAG_PGERR) != 0) {
        status = FLASH_ERROR_PG;
    } else if ((FLASH->SR & FLASH_FLAG_WRPRTERR) != 0) {
        status = FLASH_ERROR_WRP;
    } else {
        status = FLASH_COMPLETE;
    }
    
    return status;
}

/**
 * @brief  Waits for a FLASH operation to complete or a TIMEOUT to occur.
 * @param  Timeout: FLASH programming Timeout
 * @return FLASH Status: The returned value can be: FLASH_BUSY, FLASH_ERROR_PG,
 *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
 */
FLASH_Status FLASH_WaitForLastOperation(uint32_t Timeout) {
    FLASH_Status status = FLASH_COMPLETE;
    
    /* Check for the Flash Status */
    status = FLASH_GetStatus();
    
    /* Wait for a Flash operation to complete or a TIMEOUT to occur */
    while ((status == FLASH_BUSY) && (Timeout != 0x00)) {
        status = FLASH_GetStatus();
        Timeout--;
    }
    
    if (Timeout == 0x00) {
        status = FLASH_TIMEOUT;
    }
    
    return status;
}
