# STM32F407VG Bare-Metal EXTI LED Toggle

## Overview

This project demonstrates how to configure an **External Interrupt (EXTI)** on the STM32F407VG microcontroller using direct register programming.

A push button connected to **PA0** generates an interrupt on a rising edge. When the interrupt occurs, the ISR (`EXTI0_IRQHandler`) toggles the onboard LED connected to **PD15**.

The project is intentionally implemented without HAL or LL libraries to help understand how STM32 peripherals operate at the register level.

---

## Learning Objectives

After completing this project, you should understand:

- How peripheral clocks are enabled using RCC
- How GPIO pins are configured as input and output
- Why SYSCFG is required for EXTI configuration
- How EXTI detects external events
- How NVIC delivers interrupts to the CPU
- How an Interrupt Service Routine (ISR) is executed
- Why interrupt pending flags must be cleared

---

## Hardware Used

| Component | Pin |
|------------|-----|
| User Button | PA0 |
| Orange LED | PD15 |

---

## High-Level Flow

```text
Button Press (PA0)
        │
        ▼
      EXTI0
        │
        ▼
      NVIC
        │
        ▼
EXTI0_IRQHandler()
        │
        ▼
    Toggle PD15
```

---

## Configuration Summary

### 1. RCC (Reset and Clock Control)

Before any peripheral can be used, its clock must be enabled.

This project enables clocks for:

- GPIOA
- GPIOD
- SYSCFG

Without enabling the clock, register writes will not affect the peripheral.

---

### 2. GPIO Configuration

#### PA0

Configured as:

```text
Input Mode
```

Used as the source for the external interrupt.

#### PD15

Configured as:

```text
Output Mode
```

Used to drive the onboard LED.

---

### 3. SYSCFG Configuration

EXTI lines are independent of GPIO ports.

For example, EXTI0 can be connected to:

```text
PA0
PB0
PC0
PD0
...
```

Therefore, STM32 requires a mapping configuration that selects which GPIO pin drives the EXTI line.

This project maps:

```text
PA0 → EXTI0
```

using the SYSCFG peripheral.

---

### 4. EXTI Configuration

The project configures:

```text
EXTI Line : 0
Trigger   : Rising Edge
Mode      : Interrupt
```

A rising edge means:

```text
0 → 1 Transition
```

When this transition occurs on PA0, EXTI0 generates an interrupt request.

---

### 5. NVIC Configuration

EXTI does not directly execute the ISR.

The interrupt request must first pass through the NVIC.

This project enables:

```text
IRQ  : EXTI0_IRQn
IRQ# : 6
Priority : 2
```

Interrupt flow:

```text
PA0
 ↓
EXTI0
 ↓
NVIC
 ↓
CPU
 ↓
EXTI0_IRQHandler()
```

---

## Interrupt Service Routine

```c
void EXTI0_IRQHandler(void)
{
    if (EXTI_PR & (1 << 0))
    {
        EXTI_PR |= (1 << 0);
        GPIOD_ODR ^= (1 << 15);
    }
}
```

### What Happens Inside The ISR?

#### Clear Pending Flag

```c
EXTI_PR |= (1 << 0);
```

STM32 EXTI pending bits use a **Write-1-to-Clear (W1C)** mechanism.

If the pending flag is not cleared, the interrupt may continuously retrigger.

#### Toggle LED

```c
GPIOD_ODR ^= (1 << 15);
```

Changes LED state:

```text
OFF → ON
ON  → OFF
```

---

## Expected Behaviour

```text
Power On     → LED OFF

Button Press → LED ON

Button Press → LED OFF

Button Press → LED ON
```

Each button press toggles the current LED state.

---

## Debug Checklist

If the interrupt is not working:

- [ ] GPIOA clock enabled
- [ ] GPIOD clock enabled
- [ ] SYSCFG clock enabled
- [ ] PA0 mapped to EXTI0
- [ ] EXTI0 unmasked in IMR
- [ ] Rising edge enabled in RTSR
- [ ] NVIC IRQ enabled
- [ ] ISR name matches `EXTI0_IRQHandler`
- [ ] Pending flag cleared inside ISR

---

# Documentation References

All reference documents are available in:

```text
Docs/STM32F407VGT6/
```

## STM32F407 Datasheet

📄 ./Docs/STM32F407VGT6/stm32f407vg_Datasheet.pdf

Useful Sections:

- Device Overview
- Pin Description
- Alternate Function Mapping

---

## STM32F407 Reference Manual

📄 ./Docs/STM32F407VGT6/STM32F407_Reference_Manual.pdf

Recommended Chapters:

### RCC

Learn:

- Clock Architecture
- AHB1ENR
- APB2ENR

### GPIO

Learn:

- MODER
- IDR
- ODR

### SYSCFG

Learn:

- EXTI Configuration Registers (EXTICR)

### EXTI

Learn:

- IMR
- RTSR
- FTSR
- PR

These chapters explain nearly every peripheral register used in this project.

---

## Cortex-M4 Programming Manual

📄 ./Docs/STM32F407VGT6/stm32-programming-manual-stmicroelectronics.pdf

Recommended Sections:

### NVIC

Learn:

- Interrupt Enable Registers
- Interrupt Priorities

### Exception Model

Learn:

- Interrupt Entry
- Interrupt Exit
- ISR Execution Flow

### Vector Table

Learn:

- How IRQ6 maps to `EXTI0_IRQHandler()`

---

## Key Takeaway

The most important concept to understand from this project is:

```text
Button Press
      ↓
GPIOA (PA0)
      ↓
SYSCFG Mapping
      ↓
EXTI0
      ↓
NVIC
      ↓
CPU
      ↓
EXTI0_IRQHandler()
      ↓
PD15 LED Toggle
```

Once this flow is clear, the same interrupt concepts can be applied to timers, UART, SPI, I2C, ADC, DMA, and other STM32 peripherals.