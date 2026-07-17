#include <stdio.h>
#include "gpio.h"
#include "rcc.h"
#include "uart.h"

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
        // GPIO_TogglePin(GPIOA, 5);
        // for (volatile int i = 0; i < 100000; i++); // Delay
        uint8_t data = USART_ReceiveData8(USART1);
        USART_TransmitData8(USART1,data);
    }
    return 0;
}

// #include "gpio.h"
// #include "rcc.h"
// #include "uart.h"

// int main(void) {
//     /* 1. Kích hoạt Clock hệ thống trước */
//     RCC_EnableGPIOA();
//     RCC_EnableUSART1();
    
//     // Tạo độ trễ nhỏ để clock bus của GPIOA và USART2 thực sự ổn định
//     volatile uint32_t delay_clk = 0;
//     for (delay_clk = 0; delay_clk < 100; delay_clk++);

//     /* 2. Cấu hình chân TX (PA2) - Alternate Function 7 (USART2 TX) */
//     GPIO_Config_t USART1_TX;
//     USART1_TX.Pin = 9;
//     USART1_TX.Mode = gpio_mode_alfunc;
//     USART1_TX.OType = gpio_otype_pushpull; 
//     USART1_TX.Speed = gpio_speed_high;
//     USART1_TX.Pull = gpio_nopull;          // TX không cần kéo vì MCU chủ động kéo high/low
//     USART1_TX.Alternate = gpio_af7;

//     /* 3. Cấu hình chân RX (PA3) - Alternate Function 7 (USART2 RX) */
//     GPIO_Config_t USART1_RX;
//     USART1_RX.Pin = 10;
//     USART1_RX.Mode = gpio_mode_alfunc;
//     USART1_RX.OType = gpio_otype_pushpull; // STM32 tự ngắt tầng pushpull khi nhận, để đồng bộ cấu hình
//     USART1_RX.Speed = gpio_speed_high;
//     USART1_RX.Pull = gpio_pullup;          // QUAN TRỌNG: Kéo trở lên cao để tránh nhiễu đường truyền Idle
//     USART1_RX.Alternate = gpio_af7;

//     /* 4. Cấu hình chân LED (PA5) - Output */
//     GPIO_Config_t LED;
//     LED.Pin = 5;
//     LED.Mode = gpio_mode_output;
//     LED.OType = gpio_otype_pushpull;
//     LED.Speed = gpio_speed_high;
//     LED.Pull = gpio_nopull;
//     LED.Alternate = gpio_af0;

//     /* 5. Khởi tạo phần cứng ghi xuống thanh ghi */
//     GPIO_Init(GPIOA, &LED);
//     GPIO_Init(GPIOA, &USART1_TX);
//     GPIO_Init(GPIOA, &USART1_RX);
    
//     /* 6. Khởi tạo cấu hình USART2 */
//     USART_Config_t USART1_ConFig;
//     USART1_ConFig.BaudRate = 9600;
//     USART1_ConFig.WordLength = usart_word_length_8b;
//     USART1_ConFig.Parity = usart_parity_none;
//     USART1_ConFig.StopBits = usart_stop_bits_1;
//     USART1_ConFig.Mode = usart_mode_tx_rx;
//     USART1_ConFig.OverSampling = usart_over_16;

//     USART_Init(USART1, &USART1_ConFig);

//     /* Loop vô tận */
//     while (1) {
//         // Chớp tắt LED PA5
//         GPIO_TogglePin(GPIOA, 5);
        
//         // Gửi ký tự 'A' qua USART2 để test truyền nhận dữ liệu
//         USART_TransmitData8(USART1, 'A');
//         USART_TransmitData8(USART1, '\r'); // Đưa con trỏ về đầu dòng
//         USART_TransmitData8(USART1, '\n'); // Xuống dòng (ép in ra Terminal)
        
//         // Vòng lặp tạo delay tương đối (khoảng vài trăm ms ở HSI 16MHz)
//         for (volatile int i = 0; i < 200000; i++); 
//     }

//     return 0;
// }