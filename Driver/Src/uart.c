#include "uart.h"
#include "rcc.h"

#define USART_DIV_SAMPLING16_100(PCLK, BAUDRATE) (((PCLK)*25)/(4*(BAUDRATE)))

#define USART_DIV_SAMPLING8_100(PCLK, BAUDRATE) (((PCLK)*25)/(2*(BAUDRATE)))

void USART_Enable(USART_TypeDef *USARTx)
{
    if (USARTx == 0) return;
    USARTx->CR1 |= USART_CR1_UE;
}

void USART_Disable(USART_TypeDef *USARTx)
{
    if (USARTx == 0) return;
    USARTx->CR1 &= ~(USART_CR1_UE);
}

static void USART_SetBaudRate(USART_TypeDef *USARTx, uint32_t pclk, uint32_t baudrate)
{
    uint32_t usartdiv_100;
    uint32_t mantissa;
    uint32_t fraction;
    if (USARTx->CR1 & USART_CR1_OVER8)
    {
        /* Oversampling by 8 */
        usartdiv_100 = USART_DIV_SAMPLING8_100(pclk, baudrate);
        mantissa = usartdiv_100 / 100U;
        fraction = (((usartdiv_100 % 100U)*8) + 50U) / 100U;
        USARTx->BRR = (mantissa << 4) + ((fraction & 0xF8) << 1) + (fraction & 0x07);
    }
    else
    {
        /* Oversampling by 16 */
        usartdiv_100 = USART_DIV_SAMPLING16_100(pclk, baudrate);
        mantissa = usartdiv_100 / 100U;
        fraction = (((usartdiv_100 % 100U)*16) + 50U) / 100U;
        USARTx->BRR = (mantissa << 4) + (fraction & 0xF0) + (fraction & 0x0F);
    }
}
void USART_Init(USART_TypeDef *USARTx, const USART_Config_t *USART_Conf)
{
    if ((USARTx == 0) || (USART_Conf == 0))
    {
        return;
    }
    //Disable USART
    USARTx->CR1 &= ~USART_CR1_UE;
    //Configure word length
    if (USART_Conf->WordLength == usart_word_length_9b) {
        USARTx->CR1 |= USART_CR1_M; // Set M bit for 9 data bits
    } else {
        USARTx->CR1 &= ~USART_CR1_M; // Clear M bit for 8 data bits
    }
    //Configure Parity
    if (USART_Conf->Parity != usart_parity_none) {
        USARTx->CR1 |= USART_CR1_PCE; // Enable parity control
        if (USART_Conf->Parity == usart_parity_even) {
            USARTx->CR1 &= ~USART_CR1_PS; // Set even parity
        } else {
            USARTx->CR1 |= USART_CR1_PS; // Set odd parity
        }
    } else {
        USARTx->CR1 &= ~USART_CR1_PCE; // Disable parity control
    }
    //Configure stop bits
    USARTx->CR2 &= ~(3U << 12); // Clear stop bits
    USARTx->CR2 |= ((uint32_t)USART_Conf->StopBits << 12); // Set stop bits
    //Configure oversampling
    if (USART_Conf->OverSampling == usart_over_8) {
        USARTx->CR1 |= USART_CR1_OVER8; // Set OVER8 bit for oversampling by 8
    } else {
        USARTx->CR1 &= ~USART_CR1_OVER8; // Clear OVER8 bit for oversampling by 16
    }
    // Configure baud rate
    uint32_t pclk;
    if (USARTx == USART1 || USARTx == USART6)
    {
        pclk = RCC_GetPCLK2Freq();
    }
    else
    {
        pclk = RCC_GetPCLK1Freq();
    }
    USART_SetBaudRate(USARTx, pclk, USART_Conf->BaudRate);
    // Enable USART
    USARTx->CR1 |= USART_CR1_UE; 
    //Configure mode
    USARTx->CR1 &= ~(USART_CR1_TE | USART_CR1_RE);
    USARTx->CR1 |= (uint32_t)USART_Conf->Mode; // Set mode (transmitter, receiver, or both)
}


void USART_TransmitData8(USART_TypeDef *USARTx, uint8_t data)
{
    if (USARTx == 0) {
        return;
    }
    while (!(USARTx->SR & USART_SR_TXE)); // Wait until transmit data register is empty
    USARTx->DR = (uint32_t)data; // Write data to the data register 
}

uint8_t USART_ReceiveData8 (USART_TypeDef *USARTx) {
    uint8_t temp;
    if (USARTx == 0) {
        return -1;
    }
    while (!(USARTx->SR & USART_SR_RXNE));
    temp = USARTx->DR;
    return temp;
}