# STM32F407VGT6 LED Blink (Bare-Metal)

This project demonstrates how to blink the onboard Green LED (PD12) on the STM32F407VGT6 Discovery board using direct register access.

No HAL, LL, or middleware libraries are used. The implementation is based entirely on information available in the STM32 reference manuals and datasheets.

## Learning Objectives

After studying this project, you will understand:

- How peripheral clocks are enabled on STM32 MCUs
- How GPIO pins are configured as outputs
- How memory-mapped registers are accessed in C
- How LEDs are controlled through GPIO registers
- How to use STM32 documentation effectively

## Hardware

- STM32F407VGT6 Discovery Board
- Onboard Green LED connected to PD12

## Implementation Overview

The LED blinking sequence is implemented as follows:

1. Enable the GPIOD peripheral clock.
2. Configure PD12 as a GPIO output.
3. Set the PD12 output bit to turn the LED ON.
4. Clear the PD12 output bit to turn the LED OFF.
5. Repeat continuously.

## Documentation Guide

The code in this project was derived directly from the following STM32 documentation.

### 1. Understanding the ARM Cortex-M4 Core

Start here if you are new to STM32.

Reference:
- ../../../Docs/STM32F407VGT6/stm32-programming-manual-stmicroelectronics.pdf

Topics:
- Processor architecture
- Memory map
- Register access concepts
- Cortex-M4 programming model

---

### 2. Understanding Peripheral Clocks (RCC)

Reference:
- ../../../Docs/STM32F407VGT6/STM32F407_Reference_Manual.pdf

Read:
- RCC (Reset and Clock Control) Chapter

Relevant Register:
- `RCC_AHB1ENR`

Used For:
- Enabling the clock for GPIO Port D before accessing GPIO registers.

Code:

```c
RCC_AHB1ENR |= (1U << 3);
```

---

### 3. Understanding GPIO Configuration

Reference:
- [STM32F407 Reference Manual](../../.7_Reference_Manual.pdf

Read:
- General-Purpose I/O (GPIO) Chapter

Relevant Registers:
- `GPIOD_MODER`
- `GPIOD_ODR`

Used For:
- Configuring PD12 as an output pin
- Controlling the LED state

Code:

```c
GPIOD_MODER &= ~(3U << (12 * 2));
GPIOD_MODER |=  (1U << (12 * 2));
```

```c
GPIOD_ODR |= (1U << 12);
GPIOD_ODR &= ~(1U << 12);
```

---

### 4. Understanding the PD12 Pin

Reference:
- [./../../Docs/STM32F407VGT6/stm32f407vg_Datasheet.pdf

Read:
- Pinouts and Pin Description

Topics:
- PD12 pin location
- Alternate functions
- Electrical characteristics

This document explains the physical pin and its capabilities, while the Reference Manual explains how to configure and use it.

## Source Files

```text
Src/main.c
```

Contains:
- Clock initialization
- GPIO configuration
- LED control logic
- Software delay implementation

## Build

Build and flash using STM32CubeIDE or any ARM GCC-based toolchain.