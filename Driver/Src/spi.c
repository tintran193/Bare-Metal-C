#include "spi.h"
#include "rcc.h"

void SPI_Enable(SPI_TypeDef *SPIx)
{
    SPIx->CR1 |= SPI_CR1_SPE;
}

void SPI_Disable(SPI_TypeDef *SPIx)
{
    SPIx->CR1 &= ~SPI_CR1_SPE;
}

void SPI_Init(SPI_TypeDef *SPIx, const SPI_Config_t *SPI_Conf)
{
    if ((SPIx == 0) || (SPI_Conf == 0))
    {
        return;
    }
    // Disable SPI
    SPIx->CR1 &= ~SPI_CR1_SPE;
    // Configure mode
    if (SPI_Conf->Mode == spi_mode_master)
    {
        SPIx->CR1 |= SPI_CR1_MSTR; // Set MSTR bit for master mode
    }
    else
    {
        SPIx->CR1 &= ~SPI_CR1_MSTR; // Clear MSTR bit for slave mode
    }
    // Configure data width
    if (SPI_Conf->DataWidth == spi_data_width_16b)
    {
        SPIx->CR1 |= SPI_CR1_DFF; // Set DFF bit for 16-bit data frame
    }
    else
    {
        SPIx->CR1 &= ~SPI_CR1_DFF; // Clear DFF bit for 8-bit data frame
    }
    // Configure clock polarity
    if (SPI_Conf->ClockPolarity == spi_clock_polarity_high)
    {
        SPIx->CR1 |= SPI_CR1_CPOL; // Set CPOL bit for high polarity
    }
    else
    {
        SPIx->CR1 &= ~SPI_CR1_CPOL; // Clear CPOL bit for low polarity
    }
    // Configure clock phase
    if (SPI_Conf->ClockPhase == spi_clock_phase_2edge)
    {
        SPIx->CR1 |= SPI_CR1_CPHA; // Set CPHA bit for second edge
    }
    else
    {
        SPIx->CR1 &= ~SPI_CR1_CPHA; // Clear CPHA bit for first edge
    }
    // Configure NSS management
    if (SPI_Conf->NSS == spi_nss_soft)
    {
        SPIx->CR1 |= SPI_CR1_SSM; // Set SSM bit for software NSS management
        SPIx->CR1 |= SPI_CR1_SSI; // Set SSI bit to indicate that the NSS pin is high
    }
    else
    {
        SPIx->CR1 &= ~SPI_CR1_SSM; // Clear SSM bit for hardware NSS management
    }   
    // Configure baud rate
    SPIx->CR1 &= ~(SPI_CR1_BR_0 | SPI_CR1_BR_1 | SPI_CR1_BR_2); // Clear baud rate bits
    SPIx->CR1 |= (SPI_Conf->BaudRate << 3); // Set baud rate bits
    // Configure bit order
    if (SPI_Conf->BitOrder == spi_lsb_first)
    {
        SPIx->CR1 |= SPI_CR1_LSBFIRST; // Set LSBFIRST bit for LSB first
    }
    else
    {
        SPIx->CR1 &= ~SPI_CR1_LSBFIRST; // Clear LSBFIRST bit for MSB first
    }
    // Enable SPI
    SPIx->CR1 |= SPI_CR1_SPE;
}

void SPI_TransmitData8(SPI_TypeDef *SPIx, uint8_t data)
{
    if (SPIx == 0) {
        return;
    }
    // Wait until TXE (Transmit buffer empty) flag is set
    while (!(SPIx->SR & SPI_SR_TXE));
    // Write data to the data register
    SPIx->DR = data;
}

uint8_t SPI_ReceiveData8(SPI_TypeDef *SPIx) {
    if(SPIx == 0) {
        return -1;
    }
    uint8_t temp;
    while (!(SPIx->SR & SPI_SR_RXNE));
    temp = SPIx->DR;
    return temp;
}