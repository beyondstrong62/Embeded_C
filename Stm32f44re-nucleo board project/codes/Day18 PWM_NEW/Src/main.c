/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include "stm32f446xx.h"

void PA5_PWM_Config(void);
void TIM2_PWM_Config(void);
void TIM2_PA5_DutyCycle(uint32_t DutyCycle);
void delay(uint32_t delay);

int main(void) {
    PA5_PWM_Config();
    TIM2_PWM_Config();

    while (1) {
        for (int i = 0; i <= 100; i++) {
            TIM2_PA5_DutyCycle(i);
            delay(10000); // Adjust delay for smooth transition
        }
        for (int i = 100; i >= 0; i--) {
            TIM2_PA5_DutyCycle(i);
            delay(10000); // Adjust delay for smooth transition
        }
    }
}

void PA5_PWM_Config(void) {
    // Enable clock for GPIOA
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    // Set PA5 to alternate function mode (AF1)
    GPIOA->MODER &= ~(3UL << (5 * 2));  // Clear mode bits for PA5
    GPIOA->MODER |= (2UL << (5 * 2));   // Set PA5 to alternate function mode

    // Set AF1 for PA5
    GPIOA->AFR[0] &= ~(0xF << (5 * 4)); // Clear AF bits for PA5
    GPIOA->AFR[0] |= (1 << (5 * 4));    // Set AF1 for PA5
}

void TIM2_PWM_Config(void) {
    // Enable clock for Timer 2
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    // Set the auto-reload register value
    TIM2->ARR = 999; // Assuming 1kHz PWM frequency with a 1MHz timer clock

    // Set PWM mode 1 and enable preload for TIM2->CCR1
    TIM2->CCMR1 &= ~TIM_CCMR1_OC1M; // Clear the OC1M bits
    TIM2->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2; // Set PWM mode 1
    TIM2->CCMR1 |= TIM_CCMR1_OC1PE; // Enable preload for TIM2->CCR1

    // Enable the output for channel 1
    TIM2->CCER |= TIM_CCER_CC1E;

    // Start Timer 2
    TIM2->CR1 |= TIM_CR1_CEN;
}

void TIM2_PA5_DutyCycle(uint32_t DutyCycle) {
    // Set the duty cycle
    TIM2->CCR1 = (DutyCycle * TIM2->ARR) / 100;
}

void delay(uint32_t delay) {
    // Simple delay loop
    for (uint32_t i = 0; i < delay; i++) {
        __asm("NOP");
    }
}
