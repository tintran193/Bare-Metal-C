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
        SPIx->CR1 |= (1U << 2); // Set MSTR bit for master mode
    }
    else
    {
        SPIx->CR1 &= ~(1U << 2); // Clear MSTR bit for slave mode
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
        SPIx->CR1 |= (1U << 1); // Set CPOL bit for high polarity
    }
    else
    {
        SPIx->CR1 &= ~(1U << 1); // Clear CPOL bit for low polarity
    }
    // Configure clock phase
    if (SPI_Conf->ClockPhase == spi_clock_phase_2edge)
    {
        SPIx->CR1 |= (1U << 0); // Set CPHA bit for second edge
    }
    else
    {
        SPIx->CR1 &= ~(1U << 0); // Clear CPHA bit for first edge
    }
    // Configure baud rate
    SPIx->CR1 &= ~(SPI_CR1_BR_0 | SPI_CR1_BR_1 | SPI_CR1_BR_2); // Clear baud rate bits
    SPIx->CR1 |= (SPI_Conf->BaudRate << 3); // Set baud rate bits
    // Enable SPI
    SPIx->CR1 |= SPI_CR1_SPE;
}