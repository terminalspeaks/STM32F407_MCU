# STM32F407VGT6 LED Blink (Bare-Metal)

This project demonstrates how to blink all four onboard LEDs on the STM32F407VGT6 Discovery board using direct register access.

No HAL, LL, or middleware libraries are used. The implementation is based entirely on information available in the STM32 reference manuals and datasheets.

## Learning Objectives

After studying this project, you will understand:

- How peripheral clocks are enabled on STM32 MCUs
- How GPIO pins are configured as outputs
- How memory-mapped registers are accessed in C
- How multiple GPIO pins are controlled through GPIO registers
- How to use STM32 documentation effectively

## Hardware

- STM32F407VGT6 Discovery Board

### Onboard LEDs

| LED | GPIO Pin | Color |
|------|----------|--------|
| LD4 | PD12 | Green |
| LD3 | PD13 | Orange |
| LD5 | PD14 | Red |
| LD6 | PD15 | Blue |

## Implementation Overview

The LED blinking sequence is implemented as follows:

1. Enable the GPIOD peripheral clock.
2. Configure PD12, PD13, PD14, and PD15 as GPIO outputs.
3. Turn all LEDs ON by setting the corresponding bits in `GPIOD_ODR`.
4. Delay for a visible interval.
5. Turn all LEDs OFF by clearing the corresponding bits.
6. Repeat continuously.

## Documentation Guide

The code in this project was derived directly from the following STM32 documentation.

### 1. Understanding the ARM Cortex-M4 Core

Start here if you are new to STM32.

Reference:


[STM32-PROGRAMMING-MANUAL](../../Docs/STM32F407VGT6/stm32-programming-manual-stmicroelectronics.pdf)

Topics:

- Processor architecture
- Memory map
- Register access concepts
- Cortex-M4 programming model

---

### 2. Understanding Peripheral Clocks (RCC)

Reference:

[STM32F407_Reference_Manual](\..\..\Docs\STM32F407VGT6\STM32F407_Reference_Manual.pdf)


Read:

- RCC (Reset and Clock Control) Chapter

Relevant Register:

```c
RCC_AHB1ENR
```

Used For:

- Enabling the clock for GPIO Port D before accessing GPIO registers.

Code:

```c
RCC_AHB1ENR |= (1U << 3);
```

---

### 3. Understanding GPIO Configuration

Reference:


[STM32F407_Reference_Manual](\..\..\Docs\STM32F407VGT6\STM32F407_Reference_Manual.pdf)


Read:

- General-Purpose I/O (GPIO) Chapter

Relevant Registers:

```c
GPIOD_MODER
GPIOD_ODR
```

Used For:

- Configuring PD12, PD13, PD14, and PD15 as output pins
- Controlling LED states

Code:

```c
GPIOD_MODER = (GPIOD_MODER & ~(3U << (12 * 2))) | (1U << (12 * 2));
GPIOD_MODER = (GPIOD_MODER & ~(3U << (13 * 2))) | (1U << (13 * 2));
GPIOD_MODER = (GPIOD_MODER & ~(3U << (14 * 2))) | (1U << (14 * 2));
GPIOD_MODER = (GPIOD_MODER & ~(3U << (15 * 2))) | (1U << (15 * 2));
```

Turn LEDs ON:

```c
GPIOD_ODR |= (1U << 12) |
             (1U << 13) |
             (1U << 14) |
             (1U << 15);
```

Turn LEDs OFF:

```c
GPIOD_ODR &= ~((1U << 12) |
               (1U << 13) |
               (1U << 14) |
               (1U << 15));
```

---

### 4. Understanding GPIO Pins

Reference:

[STM32-DATASHEET](../../Docs/STM32F407VGT6/stm32f407vg_Datasheet.pdf)


Read:

- Pinouts and Pin Description

Topics:

- PD12, PD13, PD14, and PD15 pin locations
- Alternate functions
- Electrical characteristics
- GPIO capabilities

This document explains the physical pins and their capabilities, while the Reference Manual explains how to configure and use them.

## Source Files

```text
Src/main.c
```

Contains:

- Clock initialization
- GPIO configuration
- Multi-LED control logic
- Software delay implementation

## Build

Build and flash using STM32CubeIDE or any ARM GCC-based toolchain.

## Expected Result

After programming the board:

- Green LED (PD12)
- Orange LED (PD13)
- Red LED (PD14)
- Blue LED (PD15)

will turn ON simultaneously, remain ON for a short delay, then