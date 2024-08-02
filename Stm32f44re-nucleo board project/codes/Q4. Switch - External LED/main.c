/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
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
#include <stdio.h>
#define __IO volatile

#define RCC_BASE (0x40023800)
#define RCC_OFFSET (0x30)
#define RCC ((__IO uint32_t*)(RCC_BASE+RCC_OFFSET))

typedef struct{
	__IO uint32_t MODER;
	__IO uint32_t OTYPER;
	__IO uint32_t OSPEEDR;
	__IO uint32_t PUPDR;
	__IO uint32_t IDR;
	__IO uint32_t ODR;
	__IO uint32_t BSRR;
	__IO uint32_t LCKR;
	__IO uint32_t AFR[2];
}GPIO_TypeDef;

#define GPIOA_BASE (0x40020000)
#define GPIOA ((GPIO_TypeDef *)GPIOA_BASE)

#define GPIOC_BASE (0x40020800)
#define GPIOC ((GPIO_TypeDef *)GPIOC_BASE)

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

void delay(int n){
	for(uint32_t i=0; i<n; i++);
}

int main(void)
{
	*RCC|=(1<<0)| (1<<2);

	GPIOA->MODER |=1;  //Port-A0 made output
	GPIOA->OTYPER &=~1;
	GPIOA->OSPEEDR |=1;
	GPIOA->PUPDR &=~3;

	GPIOC->MODER &=~(3<<27);  //Port-C13 made input
	GPIOC->OSPEEDR |=(1<<26);
	GPIOC->PUPDR |=(1<<26);

	printf("Hello World\n");

	for(;;){
		if((GPIOC->IDR)&(1<<13)){
			printf("Button Not Pressed\n");
			GPIOA->ODR &=~1;
		}else{
			printf("Button Pressed\n");
			GPIOA->ODR |=1;
		}
	}
}
