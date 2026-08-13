#ifndef SPI_H
#define SPI_H

#include <stdint.h>

typedef struct
{
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t CRCPR;
    volatile uint32_t RXCRCR;
    volatile uint32_t TXCRCR;
    volatile uint32_t I2SCFGR;
    volatile uint32_t I2SPR;
} SPI_TypeDef;

#define SPI1_BASE 0x40013000UL
#define SPI2_BASE 0x40003800UL
#define SPI3_BASE 0x40003C00UL

#define SPI1 ((SPI_TypeDef *)SPI1_BASE)
#define SPI2 ((SPI_TypeDef *)SPI2_BASE)
#define SPI3 ((SPI_TypeDef *)SPI3_BASE)

/* CR1 bits */
#define SPI_CR1_CPHA (1U << 0)
#define SPI_CR1_CPOL (1U << 1)
#define SPI_CR1_BR (7U << 3)
#define SPI_CR1_BR_0 (1U << 3)
#define SPI_CR1_BR_1 (2U << 3)
#define SPI_CR1_BR_2 (4U << 3)
#define SPI_CR1_SPE (1U << 6)
#define SPI_CR1_DFF (1U << 11)

/* SR bits */
#define SPI_SR_RXNE (1U << 0)
#define SPI_SR_TXE (1U << 1)
#define SPI_SR_OVR (1U << 6)
#define SPI_SR_BSY (1U << 7)

typedef enum
{
    spi_mode_master = 0,
    spi_mode_slave = 1
} SPI_Mode;

typedef enum
{
    spi_data_width_8b = 0,
    spi_data_width_16b = 1
} SPI_DataWidth;

typedef enum
{
    spi_clock_polarity_low = 0,
    spi_clock_polarity_high = 1
} SPI_ClockPolarity;

typedef enum
{
    spi_clock_phase_1edge = 0,
    spi_clock_phase_2edge = 1
} SPI_ClockPhase;

typedef enum
{
    spi_baud_rate_div_2 = 0,
    spi_baud_rate_div_4 = 1,
    spi_baud_rate_div_8 = 2,
    spi_baud_rate_div_16 = 3,
    spi_baud_rate_div_32 = 4,
    spi_baud_rate_div_64 = 5,
    spi_baud_rate_div_128 = 6,
    spi_baud_rate_div_256 = 7
} SPI_BaudRate;

typedef struct
{
    SPI_Mode Mode;
    SPI_DataWidth DataWidth;
    SPI_ClockPolarity ClockPolarity;
    SPI_ClockPhase ClockPhase;
    SPI_BaudRate BaudRate;
} SPI_Config_t;

void SPI_Enable(SPI_TypeDef *SPIx);
void SPI_Disable(SPI_TypeDef *SPIx);
void SPI_Init(SPI_TypeDef *SPIx, SPI_Config_t *config);
void SPI_ReceiveData8(SPI_TypeDef *SPIx);
void SPI_TransmitData8(SPI_TypeDef *SPIx, uint8_t data);


#endif /* SPI_H */