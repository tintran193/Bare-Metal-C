#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

typedef struct
{
    volatile uint32_t MODER;   /*< GPIO port mode register */ 
    volatile uint32_t OTYPER;  /*< GPIO port output type register */
    volatile uint32_t OSPEEDR; /*< GPIO port output speed register */ 
    volatile uint32_t PUPDR;   /*< GPIO port pull-up/pull-down register */
    volatile uint32_t IDR;     /*< GPIO port input data register */
    volatile uint32_t ODR;     /*< GPIO port output data register */
    volatile uint32_t BSRR;    /*< GPIO port bit set/reset register */
    volatile uint32_t LCKR;    /*< GPIO port configuration lock register */
    volatile uint32_t AFR[2];  /*< GPIO alternate function registers */
} GPIO_TypeDef;

#define GPIO_BASE 0x40020000UL

#define GPIOA_BASE (GPIO_BASE + 0x0000UL)
#define GPIOB_BASE (GPIO_BASE + 0x0400UL)
#define GPIOC_BASE (GPIO_BASE + 0x0800UL)
#define GPIOD_BASE (GPIO_BASE + 0x0C00UL)
#define GPIOE_BASE (GPIO_BASE + 0x1000UL)
#define GPIOH_BASE (GPIO_BASE + 0x1C00UL)

#define GPIOA ((GPIO_TypeDef *)GPIOA_BASE)
#define GPIOB ((GPIO_TypeDef *)GPIOB_BASE)
#define GPIOC ((GPIO_TypeDef *)GPIOC_BASE)
#define GPIOD ((GPIO_TypeDef *)GPIOD_BASE)
#define GPIOE ((GPIO_TypeDef *)GPIOE_BASE)
#define GPIOH ((GPIO_TypeDef *)GPIOH_BASE)

typedef enum
{
    gpio_pin_reset = 0,
    gpio_pin_set
} GPIO_State_t;

typedef enum
{
    gpio_mode_input = 0b00,
    gpio_mode_output = 0b01,
    gpio_mode_alfunc = 0b10,
    gpio_mode_analog = 0b11
} GPIO_Mode_t;

typedef enum
{
    gpio_otype_pushpull = 0,
    gpio_otype_opendrain
} GPIO_Otype_t;

typedef enum
{
    gpio_speed_low = 0b00,
    gpio_speed_med = 0b01,
    gpio_speed_high = 0b10,
    gpio_speed_vhigh = 0b11
} GPIO_Speed_t;

typedef enum
{
    gpio_nopull = 0b00,
    gpio_pullup = 0b01,
    gpio_pulldown = 0b10
} GPIO_Pull_t;

typedef enum
{
    gpio_af0 = 0b0000, /*< System */
    gpio_af1 = 0b0001, /*< TIM1, TIM2 */
    gpio_af2 = 0b0010, /*< TIM3..5 */    
    gpio_af3 = 0b0011, /*< TIM9..11 */
    gpio_af4 = 0b0100, /*< I2C1..3 */
    gpio_af5 = 0b0101, /*< SPI1..4 */
    gpio_af6 = 0b0110, /*< SPI3 */
    gpio_af7 = 0b0111, /*< USART1..2 */
    gpio_af8 = 0b1000, /*< USART6 */
    gpio_af9 = 0b1001, /*< I2C2..3 */
    gpio_af10 = 0b1010, /*< OTG_FS */
    gpio_af11 = 0b1011, 
    gpio_af12 = 0b1100, /*< SDIO */
    gpio_af13 = 0b1101, 
    gpio_af14 = 0b1110,
    gpio_af15 = 0b1111 /*< EVENTOUT */
} GPIO_Alternate_t;

typedef struct
{
    uint8_t Pin;
    GPIO_Mode_t Mode;
    GPIO_Otype_t OType;
    GPIO_Speed_t Speed;
    GPIO_Pull_t Pull;
    GPIO_Alternate_t Alternate;
} GPIO_Config_t;

void GPIO_Init(GPIO_TypeDef *GPIO_Portx, const GPIO_Config_t *GPIO_Conf);
void GPIO_WritePin(GPIO_TypeDef *GPIO_Portx, uint8_t GPIO_Pinx, GPIO_State_t GPIO_State);
GPIO_State_t GPIO_ReadPin(GPIO_TypeDef *GPIO_Portx, uint8_t GPIO_Pinx);
void GPIO_TogglePin(GPIO_TypeDef *GPIO_Portx, uint8_t GPIO_Pinx);

#endif /* GPIO_H */