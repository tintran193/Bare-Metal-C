#include <stdio.h>
#include "gpio.h"
#include "rcc.h"
#include "uart.h"
#include "systick.h"

int main(void) {
    // Enable GPIOA clock
    RCC_EnableGPIOA();
    RCC_EnableUSART1();
    
    GPIO_Config_t usart1_tx;
    usart1_tx.Pin = 9;
    usart1_tx.Mode = gpio_mode_alfunc;
    usart1_tx.OType = gpio_otype_pushpull;
    usart1_tx.Speed = gpio_speed_high;
    usart1_tx.Pull = gpio_nopull; // No pull-up/pull-down
    usart1_tx.Alternate = gpio_af7;

    GPIO_Config_t usart1_rx;
    usart1_rx.Pin = 10;
    usart1_rx.Mode = gpio_mode_alfunc;
    usart1_rx.OType = gpio_otype_pushpull;
    usart1_rx.Speed = gpio_speed_high;
    usart1_rx.Pull = gpio_nopull;
    usart1_rx.Alternate = gpio_af7;

    //Config USART2 
    USART_Config_t usart1_config;
    usart1_config.BaudRate = 9600;
    usart1_config.WordLength = usart_word_length_8b;
    usart1_config.Parity = usart_parity_none;
    usart1_config.StopBits = usart_stop_bits_1;
    usart1_config.Mode = usart_mode_tx_rx;
    usart1_config.OverSampling = usart_over_16;

    GPIO_Config_t led;
    led.Pin = 5;
    led.Mode = gpio_mode_output;
    led.OType = gpio_otype_pushpull;
    led.Speed = gpio_speed_high;
    led.Pull = gpio_nopull;
    led.Alternate = gpio_af0;

    //Init
    GPIO_Init(GPIOA, &led);
    GPIO_Init(GPIOA,&usart1_tx);
    GPIO_Init(GPIOA,&usart1_rx);
    USART_Init(USART1, &usart1_config);

    // Toggle GPIOA pin 5 in an infinite loop
    while (1) {
        GPIO_TogglePin(GPIOA, 5);
        Sys_Delay(1000);
        // uint8_t data = USART_ReceiveData8(USART1);
        // USART_TransmitData8(USART1,data);
    }
    return 0;
}
