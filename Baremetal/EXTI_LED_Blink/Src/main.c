#include <stdint.h>

/* RCC */
#define RCC_BASE       0x40023800U
#define RCC_AHB1ENR    (*(volatile uint32_t *)(RCC_BASE + 0x30))
#define RCC_APB2ENR    (*(volatile uint32_t *)(RCC_BASE + 0x44))

/* SYSCFG */
#define SYS_CFG_BASE   0x40013800U
#define SYSCFG_EXTICR1 (*(volatile uint32_t *)(SYS_CFG_BASE + 0x08))

/* EXTI */
#define EXTI_BASE      0x40013C00U
#define EXTI_IMR       (*(volatile uint32_t *)(EXTI_BASE + 0x00))
#define EXTI_RTSR      (*(volatile uint32_t *)(EXTI_BASE + 0x08))
#define EXTI_FTSR      (*(volatile uint32_t *)(EXTI_BASE + 0x0C))
#define EXTI_PR        (*(volatile uint32_t *)(EXTI_BASE + 0x14))

/* NVIC */
#define NVIC_BASE      0xE000E000U
#define NVIC_ISER      (*(volatile uint32_t *)(NVIC_BASE + 0x100))
#define NVIC_IPR       ((volatile uint8_t *)(NVIC_BASE + 0x400))

/* GPIOA */
#define GPIOA_BASE     0x40020000U
#define GPIOA_MODER    (*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_IDR      (*(volatile uint32_t *)(GPIOA_BASE + 0x10))

/* GPIOD */
#define GPIOD_BASE     0x40020C00U
#define GPIOD_MODER    (*(volatile uint32_t *)(GPIOD_BASE + 0x00))
#define GPIOD_ODR      (*(volatile uint32_t *)(GPIOD_BASE + 0x14))

int main(void)
{
    // Enable Clock for GPIOA (bit 0) and GPIOD (bit 3)
    RCC_AHB1ENR |= (1U << 0) | (1U << 3);

    // Enable clock for System configuration controller (bit 14 on APB2)
    RCC_APB2ENR |= (1U << 14);

    // Map PA0 to EXTI0
    SYSCFG_EXTICR1 &= ~(0xF << 0);  // clear bits
    SYSCFG_EXTICR1 |=  (0x0 << 0);  // Port A = 0000

    // Configure PA0 as input
    GPIOA_MODER &= ~(3 << (0 * 2));

    // Configure PD15 as output
    GPIOD_MODER &= ~(3 << (15 * 2));
    GPIOD_MODER |=  (1 << (15 * 2));

    // Configure EXTI0 line
    EXTI_IMR  |= (1 << 0);   // Unmask EXTI0
    EXTI_RTSR |= (1 << 0);   // Rising edge trigger
    // EXTI_FTSR |= (1 << 0); // Falling edge if needed

    // Enable EXTI0 interrupt in NVIC
    NVIC_ISER |= (1 << 6);
    NVIC_IPR[6] = (2 << 4);  // Priority = 2

    while (1) {

    }
}

/* ISR */
void EXTI0_IRQHandler(void)
{
    if (EXTI_PR & (1 << 0)) {
        EXTI_PR |= (1 << 0);       // Clear pending bit by writing 1
        GPIOD_ODR ^= (1 << 15);    // Toggle LED
    }
}
