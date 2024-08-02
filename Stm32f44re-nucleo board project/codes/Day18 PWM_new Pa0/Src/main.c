/**
 ******************************************************************************
 * @file           : main.c
 * @author         :
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

void PA0_PWM_Config(void);
void TIM2_PWM_Config(void);
void delay(uint32_t delay);

int main(void) {
    PA0_PWM_Config();
    TIM2_PWM_Config();

    short brightness = 0;
    short fadeAmount = 2;

    while (1) {
        TIM2->CCR1 = brightness;
        brightness += fadeAmount;

        if (brightness <= 0 || brightness >= 255) {
            fadeAmount = -fadeAmount;
        }

        delay(10000); // Adjust delay for smooth transition
    }
}

void PA0_PWM_Config(void) {
    // PA clock enable
    RCC->AHB1ENR |= (1 << 0);

    // Set PA0 to alternate function mode
    GPIOA->MODER &= ~(3UL << (0 * 2));
    GPIOA->MODER |= (2UL << (0 * 2));

    // Specify the specific alternate function (AF1) for PA0
    GPIOA->AFR[0] &= ~(0xF << (0 * 4));
    GPIOA->AFR[0] |= (1 << (0 * 4));
}

void TIM2_PWM_Config(void) {
    // Tim2 clock enable
    RCC->APB1ENR |= (1 << 0);

    // Set the auto-reload register value
    TIM2->ARR = 255; // Assuming 1kHz PWM frequency with a 1MHz timer clock

    // Configure TIM_CCMR1_OC1M_1 and TIM_CCMR1_OC1M_2
    TIM2->CCMR1 &= ~TIM_CCMR1_OC1M;
    TIM2->CCMR1 |= (1 << 5) | (1 << 6); // Set PWM mode 1
    TIM2->CCMR1 |= TIM_CCMR1_OC1PE; // Enable preload for TIM2->CCR1

    // Configure TIM_CCER_CC1E
    TIM2->CCER |= (1 << 0); // TIM_CCER_CC1E

    // Start timer on CEN bit
    TIM2->CR1 |= (1 << 0); // Start Timer 2
}

void delay(uint32_t delay) {
    // Simple delay loop
    for (uint32_t i = 0; i < delay; i++) {
        __asm("NOP");
    }
}
