/******************************************************************************
 * @file    main.c
 * @brief   STM32F407VGT6 Bare-Metal LED Blink Example
 *
 * Description:
 * Demonstrates GPIO configuration and LED control using direct
 * register access without HAL or LL drivers.
 *
 * Target MCU : STM32F407VGT6
 * Board      : STM32F4 Discovery
 *
 * References:
 * - STM32F407 Reference Manual (RM0090)
 * - STM32F407VG Datasheet
 * - ARM Cortex-M4 Programming Manual
 *
 * Copyright (c) 2026 Hemant S Yaliballi
 * Licensed under the MIT License.
 ******************************************************************************/

#include <stdint.h>

/* RCC */
#define RCC_BASE        0x40023800U
#define RCC_AHB1ENR     (*(volatile uint32_t *)(RCC_BASE + 0x30))

/* GPIOD */
#define GPIOD_BASE      0x40020C00U
#define GPIOD_MODER     (*(volatile uint32_t *)(GPIOD_BASE + 0x00))
#define GPIOD_ODR       (*(volatile uint32_t *)(GPIOD_BASE + 0x14))


void delay(void)
{
    for(uint32_t i = 0; i < 500000; i++);
}

int main(void)
{
    /* Enable clock for GPIOD */
    RCC_AHB1ENR |= (1U << 3);

    /* Configure PD12 as output */
    GPIOD_MODER = (GPIOD_MODER & ~(3U << (12*2))) | (1U << (12*2));

    /* Configure PD13 as output */
    GPIOD_MODER = (GPIOD_MODER & ~(3U << (13*2))) | (1U << (13*2));

    /* Configure PD14 as output */
    GPIOD_MODER = (GPIOD_MODER & ~(3U << (14*2))) | (1U << (14*2));

    /* Configure PD15 as output */
    GPIOD_MODER = (GPIOD_MODER & ~(3U << (15*2))) | (1U << (15*2));


    while(1)
    {
        /* LED ON */
        GPIOD_ODR |= (1U << 12) | (1U << 13) | (1U << 14) | (1U << 15);
        delay();

        /* LED OFF */
        GPIOD_ODR &= ~((1U << 12) | (1U << 13) | (1U << 14) | (1U << 15));
        delay();
    }
}
