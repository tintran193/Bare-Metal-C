#include "i2c.h"
#include "rcc.h"
#include <stddef.h>


void I2C_Reset (I2C_TypeDef *I2Cx) {
    if (I2Cx == NULL) {
        return;
    }
    I2Cx->CR1 |= I2C_CR1_SWRST;
    I2Cx->CR1 &= ~I2C_CR1_SWRST;
}

void I2C_Enable (I2C_TypeDef *I2Cx) {
    I2Cx->CR1 |= I2C_CR1_PE;
}

void I2C_Init (I2C_TypeDef *I2Cx, const I2C_Config_t *I2C_Conf) {
    if (I2Cx == NULL || I2C_Conf == NULL) {
        return;
    }
    /* Disable peripheral */
    I2Cx->CR1 &= ~I2C_CR1_PE;
    /* Frequency */
    uint32_t pclk;
    pclk = RCC_GetPCLK1Freq();
    uint32_t freq;
    freq = pclk/1000000U;
    I2Cx->CR2 &= ~I2C_CR2_FREQ_MASK;
    I2Cx->CR2 |= (uint16_t)freq;
    /* CCR */
    /*
    Sm mode: T_high = CCR * T_pclk1
    Fm mode: 
        Duty2: T_high = CCR * T_pclk1
        Duty16_9: T_high = 9 * CCR * T_pclk1
    T_high = t_r(SCL) + t_w(SCLH) (Datasheet)
    */
    uint16_t ccr;
    if (I2C_Conf->ClockSpeed == i2c_speed_std) {
        ccr = pclk/(I2C_Conf->ClockSpeed*2U);
    } else {
        // Fm mode I2C selection
        if (I2C_Conf->DutyCycle == i2c_duty_2) {
            ccr = pclk/(I2C_Conf->ClockSpeed*3U);
            ccr &= ~I2C_CCR_DUTY; 
        } else {
            ccr = pclk/(I2C_Conf->ClockSpeed*25U);
            ccr |= I2C_CCR_DUTY;
        }
        ccr |= I2C_CCR_FS;
    }
    I2Cx->CCR = ccr;
    /* TRISE */
    if (I2C_Conf->ClockSpeed == i2c_speed_std) {
        I2Cx->TRISE = freq + 1U;
    } else {
        I2Cx->TRISE = ((freq*300U)/1000U)+1U;
    }
    /* Configure ACK */
    if (I2C_Conf->ACK == i2c_ack_enable) {
        I2Cx->CR1 |= I2C_CR1_ACK;
    } else {
        I2Cx->CR1 &= ~I2C_CR1_ACK;
    }
    /* Enable peripheral */
    I2Cx->CR1 |= I2C_CR1_PE;
} 

void I2C_Start (I2C_TypeDef *I2Cx) {
    if (I2Cx == NULL) {
        return;
    }
    I2Cx->CR1 |= I2C_CR1_START;
    while (!(I2Cx->SR1 & I2C_SR1_SB));
}

void I2C_SendAddress (I2C_TypeDef *I2Cx, uint8_t address, I2C_Direction_t direction) {
    if(I2Cx == NULL) {
        return;
    }
    I2Cx->DR = (uint16_t) ((address<<1U) |direction);
    while (!(I2Cx->SR1 & I2C_SR1_ADDR));
    volatile uint16_t temp;
    temp = I2Cx->SR1;
    temp = I2Cx->SR2; 
} 

void I2C_SendData (I2C_TypeDef *I2Cx, uint8_t data) {
    while (!(I2Cx->SR1 & I2C_SR1_TXE));
    I2Cx->DR = (uint16_t)data;
    while (!(I2Cx->SR1 & I2C_SR1_BTF));
}

void I2C_Stop (I2C_TypeDef *I2Cx) {
    if (I2Cx == NULL) {
        return;
    }
    I2Cx->CR1 |= I2C_CR1_STOP;
}