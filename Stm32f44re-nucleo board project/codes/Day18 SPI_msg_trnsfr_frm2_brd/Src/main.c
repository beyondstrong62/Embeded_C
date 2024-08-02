#include "stm32f446xx.h"
#include <stdbool.h>

//#define MASTER_BOARD
 #define SLAVE_BOARD

volatile uint32_t isVerified = 0;

void setUP_SPI1_Master();
void setUP_SPI1_Slave();

void button_PB13();
void Slave_LD5();

int main()
{
#ifdef SLAVE_BOARD

    setUP_SPI1_Slave();
    Slave_LD5();

    while (1)
    {
        while (!(SPI1->SR & (1U << 0))); // Wait until RXNE is set
        isVerified = SPI1->DR; // Read data
        if (isVerified == 1)
        {
            GPIOA->ODR ^= (1U << 5); // Toggle PA5
        }
    }

#endif

#ifdef MASTER_BOARD
    setUP_SPI1_Master();
    button_PB13();

    while (1)
    {
        if (!(GPIOC->IDR & (1U << 13)))
        {
            isVerified = 1;
            while (!(SPI1->SR & (1U << 1))); // Wait until TXE is set
            SPI1->DR = isVerified; // Send data
        }
    }

#endif

}

void setUP_SPI1_Master()
{
    RCC->APB2ENR |= (1U << 12);
    RCC->AHB1ENR |= (1U << 0) | (1U << 1);

    // SPI SCK, MISO, MOSI pin configuration (PA5, PA6, PA7)
    GPIOA->MODER |= (2U <<10) | (2U << 12) | (2U << 14); // AF
    GPIOA->AFR[0] |= (5U << 20) | (5U << 24) | (5U << 28); // AF5 for SPI1

    SPI1->CR1 = 0; // Clear CR1 register
    SPI1->CR1 |= (1U << 2) | (3U << 3) | (1U << 9) | (1U << 8); // Master mode, Baud rate, SSI, SSM
    SPI1->CR1 |= (1U << 6);
}

void setUP_SPI1_Slave()
{
    RCC->APB2ENR |= (1U << 12); // Enable SPI1 clock
    RCC->AHB1ENR |= (1U << 0) | (1U << 1); // Enable GPIOA and GPIOB clocks

    // SPI SCK, MISO, MOSI pin configuration (PA5, PA6, PA7)
    GPIOA->MODER |= (2U << (5 * 2)) | (2U << (6 * 2)) | (2U << (7 * 2)); // Alternate function mode
    GPIOA->AFR[0] |= (5U << (5 * 4)) | (5U << (6 * 4)) | (5U << (7 * 4)); // AF5 for SPI1

    SPI1->CR1 = 0; // Clear CR1 register
    SPI1->CR1 &= ~(1U << 2); // Slave mode
    SPI1->CR1 |= (1U << 9) | (1U << 8); // SSI, SSM
    SPI1->CR1 |= (1U << 6); // Enable SPI
}


void button_PB13()
{
    RCC->AHB1ENR |= (1U << 2); // Enable GPIOC clock
    GPIOC->MODER &= ~(3U << (13 * 2)); // Set PC13 as input
    GPIOC->PUPDR |= (2U << (13 * 2)); // Enable pull-down
}

void Slave_LD5()
{
    RCC->AHB1ENR |= (1U << 0); // Enable GPIOA clock
    GPIOA->MODER |= (1U << (5 * 2)); // Set PA5 as output
    GPIOA->OTYPER &= ~(1U << 5); // Push-pull
    GPIOA->OSPEEDR |= (3U << (5 * 2)); // High speed
    GPIOA->PUPDR &= ~(3U << (5 * 2)); // No pull-up/pull-down
}
