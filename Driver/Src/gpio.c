#include "gpio.h"

void GPIO_Init(GPIO_TypeDef *GPIO_Portx, const GPIO_Config_t *GPIO_Conf)
{
    uint32_t Pos;
    if ((GPIO_Portx == 0) || (GPIO_Conf == 0))
    {
        return;
    }
    if (GPIO_Conf->Pin > 15U)
    {
        return;
    }

    Pos = GPIO_Conf->Pin * 2U;
    /* Moder */
    GPIO_Portx->MODER &= ~(0x3UL << Pos);
    GPIO_Portx->MODER |= ((uint32_t)GPIO_Conf->Mode << Pos);
    /* Otyper */
    GPIO_Portx->OTYPER &= ~(0x1UL << (GPIO_Conf->Pin));
    GPIO_Portx->OTYPER |= ((uint32_t)GPIO_Conf->OType << GPIO_Conf->Pin);
    /* Ospeedr*/
    GPIO_Portx->OSPEEDR &= ~(0x3UL << Pos);
    GPIO_Portx->OSPEEDR |= ((uint32_t)GPIO_Conf->Speed << Pos);
    /* PuPdr */
    GPIO_Portx->PUPDR &= ~(0x3UL << Pos);
    GPIO_Portx->PUPDR |= ((uint32_t)GPIO_Conf->Pull << Pos);
    /* AFR */
    if (GPIO_Conf->Mode == gpio_mode_alfunc)
    {
        uint32_t index;
        uint32_t shift;

        index = GPIO_Conf->Pin / 8U;
        shift = (GPIO_Conf->Pin % 8U) * 4U;

        GPIO_Portx->AFR[index] &= ~(0xFUL << shift);
        GPIO_Portx->AFR[index] |=
            ((uint32_t)GPIO_Conf->Alternate << shift);
    }
}

void GPIO_WritePin(GPIO_TypeDef *GPIO_Port,
                   uint8_t GPIO_Pin,
                   GPIO_State_t GPIO_State)
{
    if (GPIO_Pin > 15)
    {
        return;
    }

    if (GPIO_State == gpio_pin_set)
    {
        GPIO_Port->BSRR = (1UL << GPIO_Pin);
    }
    else
    {
        GPIO_Port->BSRR = (1UL << (GPIO_Pin + 16U));
    }
}

GPIO_State_t GPIO_ReadPin(GPIO_TypeDef *GPIO_Port,
                          uint8_t GPIO_Pin)
{
    if (GPIO_Pin > 15)
    {
        return gpio_pin_reset;
    }

    if (GPIO_Port->IDR & (1UL << GPIO_Pin))
    {
        return gpio_pin_set;
    }

    return gpio_pin_reset;
}

void GPIO_TogglePin(GPIO_TypeDef *GPIO_Port,
                    uint8_t GPIO_Pin)
{
    if (GPIO_Pin > 15)
    {
        return;
    }

    if (GPIO_ReadPin(GPIO_Port, GPIO_Pin) == gpio_pin_set)
    {
        GPIO_WritePin(GPIO_Port, GPIO_Pin, gpio_pin_reset);
    }
    else
    {
        GPIO_WritePin(GPIO_Port, GPIO_Pin, gpio_pin_set);
    }
}