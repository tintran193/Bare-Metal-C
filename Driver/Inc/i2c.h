#ifndef I2C_H
#define I2C_H

#include <stdint.h>

typedef struct {
    volatile uint16_t CR1;
    volatile uint16_t RESERVED0;
    volatile uint16_t CR2;
    volatile uint16_t RESERVED1;
    volatile uint16_t OAR1;
    volatile uint16_t RESERVED2;
    volatile uint16_t OAR2;
    volatile uint16_t RESERVED3;
    volatile uint16_t DR;
    volatile uint16_t RESERVED4;
    volatile uint16_t SR1;
    volatile uint16_t RESERVED5;
    volatile uint16_t SR2;
    volatile uint16_t RESERVED6;
    volatile uint16_t CCR;
    volatile uint16_t RESERVED7;
    volatile uint16_t TRISE;
    volatile uint16_t RESERVED8;
    volatile uint16_t FLTR;
    volatile uint16_t RESERVED9;
} I2C_TypeDef;

#define I2C1_BASE 0x40005400UL
#define I2C2_BASE 0x40005800UL
#define I2C3_BASE 0x40005C00UL

#define I2C1 ((I2C_TypeDef *)I2C1_BASE) 
#define I2C2 ((I2C_TypeDef *)I2C2_BASE) 
#define I2C3 ((I2C_TypeDef *)I2C3_BASE)

/* CR1 */
#define I2C_CR1_PE (1U<<0) /*< I2C Peripheral enable*/
#define I2C_CR1_START (1U<<8) /*< I2C Start Generation */
#define I2C_CR1_STOP (1U<<9)
#define I2C_CR1_ACK (1U<<10)
#define I2C_CR1_SWRST (1U<<15)

/* CR2 */

#define I2C_CR2_FREQ_MASK 0x3FU
/* SR1 */

#define I2C_SR1_SB (1U<<0)
#define I2C_SR1_ADDR (1U<<1)
#define I2C_SR1_BTF (1U<<2)
#define I2C_SR1_RXNE (1U<<6)
#define I2C_SR1_TXE (1U<<7)
#define I2C_SR1_AF (1U<<10)

/* CCR */
#define I2C_CCR_DUTY (1U << 14)
#define I2C_CCR_FS (1U << 15)
#define I2C_CCR_CCR_MASK 0x3FFU

typedef enum {
    i2c_diection_read = 0,
    i2c_direction_write 
} I2C_Direction_t;

typedef enum {
    i2c_speed_std = 100000,
    i2c_speed_fast = 400000
} i2c_Speed_t;

typedef enum
{
    i2c_duty_2 = 0,
    i2c_duty_16_9
} I2C_DutyCycle_t;

typedef enum
{
    i2c_addr_7bit = 0,
    i2c_addr_10bit
} I2C_AddressMode_t;

typedef enum
{
    i2c_ack_disable = 0,
    i2c_ack_enable
} I2C_ACK_t;

typedef enum
{
    i2c_ok = 0,
    i2c_busy,
    i2c_timeout,
    i2c_ack_fail,
    i2c_error
} I2C_Status_t;

typedef struct
{
    uint32_t ClockSpeed;
    I2C_DutyCycle_t DutyCycle;
    I2C_AddressMode_t AddressMode;
    I2C_ACK_t ACK;
} I2C_Config_t;

void I2C_Reset (I2C_TypeDef *I2Cx);


#endif 