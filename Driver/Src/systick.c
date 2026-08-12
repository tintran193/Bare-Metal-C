#include "systick.h"
#include "rcc.h"

void Sys_Delay (uint32_t delay) {
    SysTick->LOAD = ((RCC_GetHCLKFreq() / 1000)) - 1; // Set reload register
    SysTick->VAL = 0; // Reset the SysTick counter value
    SysTick->CTRL = CTRL_ENABLE | CTRL_CLKSOURCE; // Enable SysTick with processor clock
    for (uint32_t i = 0; i < delay; i++) {
        while ((SysTick->CTRL & CTRL_COUNTFLAG) == 0); // Wait until the COUNTFLAG is set
    }
    SysTick->CTRL = 0; // Disable SysTick
}