#ifndef STM32F1XX_H
#define STM32F1XX_H

#include <stdint.h>

/*
 * =================================================================================
 * Base addresses for memories
 * =================================================================================
 */
#define FLASH_BASE            0x08000000U
#define SRAM_BASE             0x20000000U
#define ROM_BASE              0x1FFFF000U

/*
 * =================================================================================
 * Base addresses for peripherals
 * =================================================================================
 */
#define PERIPH_BASE           0x40000000U
#define APB1PERIPH_BASE       PERIPH_BASE
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x10000U)
#define AHBPERIPH_BASE        (PERIPH_BASE + 0x20000U)

/*
 * AHB Peripherals
 */
#define RCC_BASE              (AHBPERIPH_BASE + 0x1000U)
#define FLASH_R_BASE          (AHBPERIPH_BASE + 0x2000U) /*!< Flash registers base address */

/*
 * APB2 Peripherals
 */
#define AFIO_BASE             (APB2PERIPH_BASE + 0x0000U)
#define EXTI_BASE             (APB2PERIPH_BASE + 0x0400U)
#define GPIOA_BASE            (APB2PERIPH_BASE + 0x0800U)
#define GPIOB_BASE            (APB2PERIPH_BASE + 0x0C00U)
#define GPIOC_BASE            (APB2PERIPH_BASE + 0x1000U)
#define GPIOD_BASE            (APB2PERIPH_BASE + 0x1400U)
#define GPIOE_BASE            (APB2PERIPH_BASE + 0x1800U)
#define ADC1_BASE             (APB2PERIPH_BASE + 0x2400U)
#define ADC2_BASE             (APB2PERIPH_BASE + 0x2800U)
#define TIM1_BASE             (APB2PERIPH_BASE + 0x2C00U)
#define SPI1_BASE             (APB2PERIPH_BASE + 0x3000U)
#define USART1_BASE           (APB2PERIPH_BASE + 0x3800U)

/*
 * APB1 Peripherals
 */
#define TIM2_BASE             (APB1PERIPH_BASE + 0x0000U)
#define TIM3_BASE             (APB1PERIPH_BASE + 0x0400U)
#define TIM4_BASE             (APB1PERIPH_BASE + 0x0800U)
#define USART2_BASE           (APB1PERIPH_BASE + 0x4400U)
#define USART3_BASE           (APB1PERIPH_BASE + 0x4800U)
#define I2C1_BASE             (APB1PERIPH_BASE + 0x5400U)
#define I2C2_BASE             (APB1PERIPH_BASE + 0x5800U)
#define SPI2_BASE             (APB1PERIPH_BASE + 0x3800U)

/*
 * =================================================================================
 * Peripheral register definition structures
 * =================================================================================
 */

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

typedef struct {
    volatile uint32_t CRL;
    volatile uint32_t CRH;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t BRR;
    volatile uint32_t LCKR;
} GPIO_RegDef_t;

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

typedef struct
{
  volatile uint32_t CR1;
  volatile uint32_t CR2;
  volatile uint32_t SMCR;
  volatile uint32_t DIER;
  volatile uint32_t SR;
  volatile uint32_t EGR;
  volatile uint32_t CCMR1;
  volatile uint32_t CCMR2;
  volatile uint32_t CCER;
  volatile uint32_t CNT;
  volatile uint32_t PSC;
  volatile uint32_t ARR;
  volatile uint32_t RCR;
  volatile uint32_t CCR1;
  volatile uint32_t CCR2;
  volatile uint32_t CCR3;
  volatile uint32_t CCR4;
  volatile uint32_t BDTR;
  volatile uint32_t DCR;
  volatile uint32_t DMAR;
} TIM_TypeDef;

typedef struct
{
  volatile uint32_t SR;
  volatile uint32_t DR;
  volatile uint32_t BRR;
  volatile uint32_t CR1;
  volatile uint32_t CR2;
  volatile uint32_t CR3;
  volatile uint32_t GTPR;
} USART_TypeDef;

/* NVIC Structure */
#define SCS_BASE            (0xE000E000UL)
#define NVIC_BASE           (SCS_BASE +  0x0100UL)

typedef struct
{
  volatile uint32_t ISER[8U];               /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register */
       uint32_t RESERVED0[24U];
  volatile uint32_t ICER[8U];               /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
       uint32_t RESERVED1[24U];
  volatile uint32_t ISPR[8U];               /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register */
       uint32_t RESERVED2[24U];
  volatile uint32_t ICPR[8U];               /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register */
       uint32_t RESERVED3[24U];
  volatile uint32_t IABR[8U];               /*!< Offset: 0x200 (R/W)  Interrupt Active bit Register */
       uint32_t RESERVED4[56U];
  volatile uint8_t  IP[240U];               /*!< Offset: 0x300 (R/W)  Interrupt Priority Register (8Bit wide) */
       uint32_t RESERVED5[644U];
  volatile uint32_t STIR;                   /*!< Offset: 0xE00 ( /W)  Software Trigger Interrupt Register */
}  NVIC_Type;

/*
 * =================================================================================
 * Peripheral definitions
 * =================================================================================
 */

#define RCC      ((RCC_RegDef_t*)RCC_BASE)
#define GPIOA    ((GPIO_RegDef_t*)GPIOA_BASE)
#define GPIOB    ((GPIO_RegDef_t*)GPIOB_BASE)
#define GPIOC    ((GPIO_RegDef_t*)GPIOC_BASE)
#define GPIOD    ((GPIO_RegDef_t*)GPIOD_BASE)
#define GPIOE    ((GPIO_RegDef_t*)GPIOE_BASE)
#define FLASH    ((FLASH_RegDef_t*)FLASH_R_BASE)
#define TIM1     ((TIM_TypeDef *) TIM1_BASE)
#define TIM2     ((TIM_TypeDef *) TIM2_BASE)
#define TIM3     ((TIM_TypeDef *) TIM3_BASE)
#define TIM4     ((TIM_TypeDef *) TIM4_BASE)
#define USART1   ((USART_TypeDef *) USART1_BASE)
#define USART2   ((USART_TypeDef *) USART2_BASE)
#define USART3   ((USART_TypeDef *) USART3_BASE)
#define NVIC     ((NVIC_Type      *)     NVIC_BASE     )

/*
 * =================================================================================
 * Bit Definitions
 * =================================================================================
 */

/* RCC_CR Bit Definitions */
#define RCC_CR_HSION        (1 << 0)
#define RCC_CR_HSIRDY       (1 << 1)
#define RCC_CR_HSEON        (1 << 16)
#define RCC_CR_HSERDY       (1 << 17)
#define RCC_CR_HSEBYP       (1 << 18)
#define RCC_CR_CSSON        (1 << 19)
#define RCC_CR_PLLON        (1 << 24)
#define RCC_CR_PLLRDY       (1 << 25)

/* RCC_CFGR Bit Definitions */
#define RCC_CFGR_SW_HSI     (0 << 0)
#define RCC_CFGR_SW_HSE     (1 << 0)
#define RCC_CFGR_SW_PLL     (2 << 0)
#define RCC_CFGR_SWS_HSI    (0 << 2)
#define RCC_CFGR_SWS_HSE    (1 << 2)
#define RCC_CFGR_SWS_PLL    (2 << 2)

#define RCC_CFGR_HPRE_DIV1  (0 << 4)
#define RCC_CFGR_PPRE1_DIV1 (0 << 8)
#define RCC_CFGR_PPRE1_DIV2 (4 << 8)
#define RCC_CFGR_PPRE2_DIV1 (0 << 11)

#define RCC_CFGR_PLLSRC     (1 << 16)
#define RCC_CFGR_PLLXTPRE   (1 << 17)
#define RCC_CFGR_PLLMULL9   (7 << 18)

/* FLASH_ACR Bit Definitions */
#define FLASH_ACR_LATENCY_0 (0 << 0)
#define FLASH_ACR_LATENCY_1 (1 << 0)
#define FLASH_ACR_LATENCY_2 (2 << 0)
#define FLASH_ACR_PRFTBE    (1 << 4)

/* RCC Bit Defs for TIM */
#define RCC_APB2ENR_TIM1EN  (1 << 11)
#define RCC_APB1ENR_TIM2EN  (1 << 0)
#define RCC_APB1ENR_TIM3EN  (1 << 1)
#define RCC_APB1ENR_TIM4EN  (1 << 2)
#define RCC_APB2ENR_USART1EN (1 << 14)
#define RCC_APB1ENR_USART2EN (1 << 17)
#define RCC_APB1ENR_USART3EN (1 << 18)

/* TIM Bit Defs */
#define TIM_CR1_CEN         (1 << 0)
#define TIM_CR1_DIR         (1 << 4)
#define TIM_DIER_UIE        (1 << 0)
#define TIM_DIER_CC1IE      (1 << 1)
#define TIM_DIER_CC2IE      (1 << 2)
#define TIM_DIER_CC3IE      (1 << 3)
#define TIM_DIER_CC4IE      (1 << 4)
#define TIM_SR_UIF          (1 << 0)
#define TIM_SR_CC1IF        (1 << 1)
#define TIM_SR_CC2IF        (1 << 2)
#define TIM_SR_CC3IF        (1 << 3)
#define TIM_SR_CC4IF        (1 << 4)
#define TIM_CCMR1_OC1PE     (1 << 3)
#define TIM_CCMR1_OC2PE     (1 << 11)
#define TIM_CCER_CC1P       (1 << 1)
#define TIM_CCER_CC1NP      (1 << 3)
#define TIM_BDTR_MOE        (1 << 15)

/* USART Bit Defs */
#define USART_SR_TXE        (1 << 7)
#define USART_SR_TC         (1 << 6)
#define USART_SR_RXNE       (1 << 5)
#define USART_CR1_UE        (1 << 13)
#define USART_CR1_M         (1 << 12)
#define USART_CR1_PCE       (1 << 10)
#define USART_CR1_PS        (1 << 9)
#define USART_CR1_TE        (1 << 3)
#define USART_CR1_RE        (1 << 2)
#define USART_CR3_CTSE      (1 << 9)
#define USART_CR3_RTSE      (1 << 8)

/* Generic Macros */
#define ENABLE              1
#define DISABLE             0
#define SET                 ENABLE
#define RESET               DISABLE
#define GPIO_PIN_SET        SET
#define GPIO_PIN_RESET      RESET

#endif // STM32F1XX_H
