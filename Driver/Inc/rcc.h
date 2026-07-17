#ifndef RCC_H
#define RCC_H

#include <stdint.h>

typedef struct
{
    volatile uint32_t CR;       /*< RCC clock control register */
    volatile uint32_t PLLCFGR;  /*< RCC PLL configuration register */
    volatile uint32_t CFGR;     /*< RCC clock configuration register */
    volatile uint32_t CIR;      /*< RCC clock interrupt register */
    volatile uint32_t AHB1RSTR; /*< RCC AHB1 peripheral reset register */
    volatile uint32_t AHB2RSTR; /*< RCC AHB2 peripheral reset register */
    volatile uint32_t AHB3RSTR; /*< RCC AHB3 peripheral reset register */
    uint32_t RESERVED0;
    volatile uint32_t APB1RSTR; /*< RCC APB1 peripheral reset register */
    volatile uint32_t APB2RSTR; /*< RCC APB2 peripheral reset register */
    uint32_t RESERVED1[2];
    volatile uint32_t AHB1ENR;  /*< RCC AHB1 peripheral clock enable register */
    volatile uint32_t AHB2ENR;  /*< RCC AHB2 peripheral clock enable register */
    volatile uint32_t AHB3ENR;  /*< RCC AHB3 peripheral clock enable register */
    uint32_t RESERVED2;
    volatile uint32_t APB1ENR;  /*< RCC APB1 peripheral clock enable register */
    volatile uint32_t APB2ENR;  /*< RCC APB2 peripheral clock enable register */
} RCC_TypeDef;

#define RCC_BASE 0x40023800UL

#define RCC ((RCC_TypeDef *)RCC_BASE)

/* AHB1 peripheral clock enable register bits */
#define RCC_AHB1ENR_GPIOAEN (1U << 0) /* GPIOA clock enable */
#define RCC_AHB1ENR_GPIOBEN (1U << 1) /* GPIOB clock enable */
#define RCC_AHB1ENR_GPIOCEN (1U << 2) /* GPIOC clock enable */
#define RCC_AHB1ENR_GPIODEN (1U << 3) /* GPIOD clock enable */
#define RCC_AHB1ENR_GPIOEEN (1U << 4) /* GPIOE clock enable */
#define RCC_AHB1ENR_GPIOHEN (1U << 7) /* GPIOH clock enable */

/* APB1 peripheral clock enable register bits */
#define RCC_APB1ENR_TIM2EN (1U << 0) /* TIM2 clock enable */
#define RCC_APB1ENR_TIM3EN (1U << 1) /* TIM3 clock enable */
#define RCC_APB1ENR_TIM4EN (1U << 2) /* TIM4 clock enable */
#define RCC_APB1ENR_TIM5EN (1U << 3) /* TIM5 clock enable */
#define RCC_APB1ENR_SPI2EN (1U << 14) /* SPI2 clock enable */
#define RCC_APB1ENR_SPI3EN (1U << 15) /* SPI3 clock enable */
#define RCC_APB1ENR_USART2EN (1U << 17) /* USART2 clock enable */
#define RCC_APB1ENR_I2C1EN (1U << 21) /* I2C1 clock enable */
#define RCC_APB1ENR_I2C2EN (1U << 22) /* I2C2 clock enable */
#define RCC_APB1ENR_I2C3EN (1U << 23) /* I2C3 clock enable */

/* APB2 peripheral clock enable register bits */
#define RCC_APB2ENR_TIM1EN (1U << 0) /* TIM1 clock enable */
#define RCC_APB2ENR_USART1EN (1U << 4) /* USART1 clock enable */
#define RCC_APB2ENR_USART6EN (1U << 5) /* USART6 clock enable */
#define RCC_APB2ENR_ADC1EN (1U << 8) /* ADC1 clock enable */
#define RCC_APB2ENR_SPI1EN (1U << 12) /* SPI1 clock enable */
#define RCC_APB2ENR_SYSCFGEN (1U << 14) /* SYSCFG clock enable */
#define RCC_APB2ENR_TIM9EN (1U << 16) /* TIM9 clock enable */
#define RCC_APB2ENR_TIM10EN (1U << 17) /* TIM10 clock enable */
#define RCC_APB2ENR_TIM11EN (1U << 18) /* TIM11 clock enable */

/* GPIO Clock*/
void RCC_EnableGPIOA(void);
void RCC_EnableGPIOB(void);
void RCC_EnableGPIOC(void);
void RCC_EnableGPIOD(void);
void RCC_EnableGPIOE(void);
void RCC_EnableGPIOH(void);

/* USART Clock*/
void RCC_EnableUSART1(void);
void RCC_EnableUSART2(void);
void RCC_EnableUSART6(void);

/* I2C Clock*/
void RCC_EnableI2C1(void);
void RCC_EnableI2C2(void);
void RCC_EnableI2C3(void);

/* SPI Clock*/
void RCC_EnableSPI1(void);
void RCC_EnableSPI2(void);
void RCC_EnableSPI3(void);

/*TIM Clock*/
void RCC_EnableTIM1(void);
void RCC_EnableTIM2(void);
void RCC_EnableTIM3(void);
void RCC_EnableTIM4(void);
void RCC_EnableTIM5(void);
void RCC_EnableTIM9(void);
void RCC_EnableTIM10(void);
void RCC_EnableTIM11(void);

/* Clock Frequency */
uint32_t RCC_GetSystemClockFreq(void);
uint32_t RCC_GetHCLKFreq(void);
uint32_t RCC_GetPCLK1Freq(void);
uint32_t RCC_GetPCLK2Freq(void);

#endif /* RCC_H */


