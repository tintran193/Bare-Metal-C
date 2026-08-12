#ifndef SYSTICK_H_
#define SYSTICK_H_

#include <stdint.h>

typedef struct
{
  volatile uint32_t CTRL; /*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
  volatile uint32_t LOAD; /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register */
  volatile uint32_t VAL; /*!< Offset: 0x008 (R/W)  SysTick Current Value Register */
  volatile  uint32_t CALIB; /*!< Offset: 0x00C (R/ )  SysTick Calibration Register */
} SysTick_Type;

/* Memory mapping of Cortex-M4 Hardware */
#define SCS_BASE (0xE000E000UL) /*!< System Control Space Base Address */

#define SysTick_BASE (SCS_BASE +  0x0010UL) /*!< SysTick Base Address */
#define SysTick ((SysTick_Type*) SysTick_BASE) /*!< SysTick configuration struct */

#define CTRL_ENABLE (1U << 0) /*!< Counter enable */
#define CTRL_TICKINT (1U << 1) 
#define CTRL_CLKSOURCE (1U << 2) /*!< Clock source selection */
#define CTRL_COUNTFLAG (1U << 16) 

void Sys_Delay (uint32_t delay);

#endif