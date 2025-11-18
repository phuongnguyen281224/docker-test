#ifndef RCC_H
#define RCC_H

#include <stdint.h>

/*
 * =================================================================================
 * Base addresses for peripherals
 * =================================================================================
 */
#define RCC_BASE              0x40021000U
#define FLASH_BASE            0x40022000U


/*
 * =================================================================================
 * Peripheral register definition structures
 * =================================================================================
 */

// RCC register map
typedef struct {
    volatile uint32_t CR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t APB2RSTR;
    volatile uint32_t APB1RSTR;
    volatile uint32_t AHBENR;
    volatile uint32_t APB2ENR;
    volatile uint32_t APB1ENR;
    volatile uint32_t BDCR;
    volatile uint32_t CSR;
} RCC_RegDef_t;

// Flash register map
typedef struct {
    volatile uint32_t ACR;
    volatile uint32_t KEYR;
    volatile uint32_t OPTKEYR;
    volatile uint32_t SR;
    volatile uint32_t CR;
    volatile uint32_t AR;
    volatile uint32_t OBR;
    volatile uint32_t WRPR;
} FLASH_RegDef_t;


/*
 * =================================================================================
 * Peripheral definitions
 * =================================================================================
 */

#define RCC    ((RCC_RegDef_t*)RCC_BASE)
#define FLASH  ((FLASH_RegDef_t*)FLASH_BASE)


/*
 * =================================================================================
 * Function Prototypes for RCC Driver
 * =================================================================================
 */

void SystemClock_Config(void);


#endif // RCC_H
