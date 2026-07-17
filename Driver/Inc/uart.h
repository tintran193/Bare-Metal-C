#ifndef USART_H
#define USART_H

#include <stdint.h>

typedef struct
{
    volatile uint32_t SR;   /*< USART status register */
    volatile uint32_t DR;   /*< USART data register */
    volatile uint32_t BRR;  /*< USART baud rate register */
    volatile uint32_t CR1;  /*< USART control register 1 */
    volatile uint32_t CR2;  /*< USART control register 2 */
    volatile uint32_t CR3;  /*< USART control register 3 */
    volatile uint32_t GTPR; /*< USART guard time and prescaler register */
} USART_TypeDef;

#define APB2PERIPH_BASE 0x40010000UL
#define APB1PERIPH_BASE 0x40000000UL

#define USART1_BASE (APB2PERIPH_BASE + 0x1000UL)
#define USART6_BASE (APB2PERIPH_BASE + 0x1400UL)
#define USART2_BASE (APB1PERIPH_BASE + 0x4400UL)

#define USART1 ((USART_TypeDef *)USART1_BASE)
#define USART6 ((USART_TypeDef *)USART6_BASE)
#define USART2 ((USART_TypeDef *)USART2_BASE)

/* SR bits */
#define USART_SR_PE (1U << 0)   /* Parity error */
#define USART_SR_FE (1U << 1)   /* Framing error */
#define USART_SR_NE (1U << 2)   /* Noise error */
#define USART_SR_ORE (1U << 3)  /* Overrun error */
#define USART_SR_IDLE (1U << 4) /* IDLE line detected */
#define USART_SR_RXNE (1U << 5) /* Read data register not empty */
#define USART_SR_TC (1U << 6)   /* Transmission complete */
#define USART_SR_TXE (1U << 7)  /* Transmit data register empty */
#define USART_SR_LBD (1U << 8)  /* LIN break detection flag */
#define USART_SR_CTS (1U << 9)  /* CTS flag */

/* CR1 bits */
#define USART_CR1_SBK (1U << 0)    /* Send break */
#define USART_CR1_RWU (1U << 1)    /* Receiver wakeup */
#define USART_CR1_RE (1U << 2)     /* Receiver enable */
#define USART_CR1_TE (1U << 3)     /* Transmitter enable */
#define USART_CR1_IDLEIE (1U << 4) /* IDLE interrupt enable */
#define USART_CR1_RXNEIE (1U << 5) /* RXNE interrupt enable */
#define USART_CR1_TCIE (1U << 6)   /* Transmission complete interrupt enable */
#define USART_CR1_TXEIE (1U << 7)  /* TXE interrupt enable */
#define USART_CR1_PEIE (1U << 8)   /* PE interrupt enable */
#define USART_CR1_PS (1U << 9)     /* Parity selection */
#define USART_CR1_PCE (1U << 10)   /* Parity control enable */
#define USART_CR1_WAKE (1U << 11)  /* Wakeup method */
#define USART_CR1_M (1U << 12)     /* Word length */
#define USART_CR1_UE (1U << 13)    /* USART enable */
#define USART_CR1_OVER8 (1U << 15) /* Oversampling mode */

typedef enum
{ // CR1
    usart_word_length_8b = 0,
    usart_word_length_9b
} USART_WordLength_t;

typedef enum
{ // CR2
    usart_stop_bits_1 = 0b00,
    usart_stop_bits_0_5 = 0b01,
    usart_stop_bits_2 = 0b10,
    usart_stop_bits_1_5 = 0b11
} USART_StopBits_t;

typedef enum
{ // CR1
    usart_parity_none = 0,
    usart_parity_even,
    usart_parity_odd
} USART_Parity_t;

typedef enum
{
    usart_mode_tx = USART_CR1_TE,
    usart_mode_rx = USART_CR1_RE,
    usart_mode_tx_rx = (USART_CR1_TE | USART_CR1_RE)
} USART_Mode_t;

typedef enum {
    usart_over_16 = 0,
    usart_over_8 = 1
} USART_OverSampling_t;

typedef struct
{   
    uint32_t BaudRate;
    USART_WordLength_t WordLength;
    USART_StopBits_t StopBits;
    USART_Parity_t Parity;
    USART_Mode_t Mode;
    USART_OverSampling_t OverSampling;   
} USART_Config_t;

void USART_Enable(USART_TypeDef *USARTx);
void USART_Disable(USART_TypeDef *USARTx);
void USART_Init(USART_TypeDef *USARTx, const USART_Config_t *USART_Conf);
void USART_TransmitData8(USART_TypeDef *USARTx, uint8_t data);
uint8_t USART_ReceiveData8(USART_TypeDef *USARTx);
#endif /* USART_H */