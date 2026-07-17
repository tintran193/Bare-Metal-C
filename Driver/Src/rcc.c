#include "rcc.h"

uint32_t RCC_GetSystemClockFreq(void) {
    // Assuming HSI is used as the system clock source
    return 16000000; // HSI frequency is 16 MHz
}

uint32_t RCC_GetHCLKFreq(void) {
    // Assuming HCLK is equal to the system clock frequency
    return RCC_GetSystemClockFreq();
}

uint32_t RCC_GetPCLK1Freq(void) {
    // Assuming PCLK1 is equal to HCLK frequency
    return RCC_GetHCLKFreq();
}

uint32_t RCC_GetPCLK2Freq(void) {
    // Assuming PCLK2 is equal to HCLK frequency
    return RCC_GetHCLKFreq();
}

/* GPIO Clock Enable Functions */
void RCC_EnableGPIOA(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // Enable GPIOA clock
}
void RCC_EnableGPIOB(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; // Enable GPIOB clock
}
void RCC_EnableGPIOC(void) {    
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; // Enable GPIOC clock
}
void RCC_EnableGPIOD(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; // Enable GPIOD clock
}
void RCC_EnableGPIOE(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN; // Enable GPIOE clock
}
void RCC_EnableGPIOH(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN; // Enable GPIOH clock
}
/* USART Clock Enable Functions */
void RCC_EnableUSART1(void) {
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN; // Enable USART1 clock
}
void RCC_EnableUSART2(void) {
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN; // Enable USART2 clock
}
void RCC_EnableUSART6(void) {       
    RCC->APB2ENR |= RCC_APB2ENR_USART6EN; // Enable USART6 clock
}

/* I2C Clock Enable Functions */
void RCC_EnableI2C1(void) {
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN; // Enable I2C1 clock
}
void RCC_EnableI2C2(void) {
    RCC->APB1ENR |= RCC_APB1ENR_I2C2EN; // Enable I2C2 clock
}
void RCC_EnableI2C3(void) {
    RCC->APB1ENR |= RCC_APB1ENR_I2C3EN; // Enable I2C3 clock
}

/* SPI Clock Enable Functions */
void RCC_EnableSPI1(void) {
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN; // Enable SPI1 clock
} 
void RCC_EnableSPI2(void) {
    RCC->APB1ENR |= RCC_APB1ENR_SPI2EN; // Enable SPI2 clock
}
void RCC_EnableSPI3(void) {
    RCC->APB1ENR |= RCC_APB1ENR_SPI3EN; // Enable SPI3 clock
}

/* TIM Clock Enable Functions */
void RCC_EnableTIM1(void) {
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN; // Enable TIM1 clock
}   
void RCC_EnableTIM2(void) {
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; // Enable TIM2 clock
}
void RCC_EnableTIM3(void) {
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; // Enable TIM3 clock
}
void RCC_EnableTIM4(void) {
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN; // Enable TIM4 clock
}
void RCC_EnableTIM5(void) {
    RCC->APB1ENR |= RCC_APB1ENR_TIM5EN; // Enable TIM5 clock
}
void RCC_EnableTIM9(void) {
    RCC->APB2ENR |= RCC_APB2ENR_TIM9EN; // Enable TIM9 clock
}
void RCC_EnableTIM10(void) {    
    RCC->APB2ENR |= RCC_APB2ENR_TIM10EN; // Enable TIM10 clock
}
void RCC_EnableTIM11(void) {    
    RCC->APB2ENR |= RCC_APB2ENR_TIM11EN; // Enable TIM11 clock
}