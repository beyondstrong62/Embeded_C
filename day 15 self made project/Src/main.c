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

#include "stm32f446xx.h"

void SysClockConfig (void)
{
//		/>>>>>>> STEPS FOLLOWED <<<<<<<<***********

//	1. ENABLE HSE and wait for the HSE to become Ready
//	2. Set the POWER ENABLE CLOCK and VOLTAGE REGULATOR
//	3. Configure the FLASH PREFETCH and the LATENCY Related Settings
//	4. Configure the PRESCALARS HCLK, PCLK1, PCLK2
//	5. Configure the MAIN PLL
//	6. Enable the PLL and wait for it to become ready
//	7. Select the Clock Source and wait for it to be set

//	********************************************************/


	#define PLL_M 	4
	#define PLL_N 	180
	#define PLL_P 	0  // PLLP = 2

	// 1. ENABLE HSE and wait for the HSE to become Ready
	RCC->CR |= RCC_CR_HSEON;
	while (!(RCC->CR & RCC_CR_HSERDY));

	// 2. Set the POWER ENABLE CLOCK and VOLTAGE REGULATOR
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;
	PWR->CR |= PWR_CR_VOS;


	// 3. Configure the FLASH PREFETCH and the LATENCY Related Settings
	FLASH->ACR = FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY_5WS;

	// 4. Configure the PRESCALARS HCLK, PCLK1, PCLK2
	// AHB PR
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;

	// APB1 PR
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;

	// APB2 PR
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;


	// 5. Configure the MAIN PLL
	RCC->PLLCFGR = (PLL_M <<0) | (PLL_N << 6) | (PLL_P <<16) | (RCC_PLLCFGR_PLLSRC_HSE);

	// 6. Enable the PLL and wait for it to become ready
	RCC->CR |= RCC_CR_PLLON;
	while (!(RCC->CR & RCC_CR_PLLRDY));

	// 7. Select the Clock Source and wait for it to be set
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
}


void UART2_SendChar(char ch)
{
	USART2->DR=ch;
	while(!(USART2->SR &(1<<6))); //wait for bit to set -> TC: Transmission complete

	return;
}
void UART2_SendString(char *string)
{
	while(*string !='\0')
	{
		UART2_SendChar(*string);
		string++;
	}
}
void Usart2_config(void)
{
	//	1. Enable the UART CLOCK and GPIO CLOCK
	//		2. Configure the UART PINs for ALternate
	//		 	 Functions
	//		3. Enable the USART by writing the UE bit
	//			in USART_CR1 register to 1.
	//		4. Program the M bit in USART_CR1 to define
	//			the word length.
	//		5. Select the desired baud rate using the
	//		    USART_BRR register.
	//		6. Enable the Transmitter/Receiver by Setting the TE and RE
	//		   bits in USART_CR1 Register
	RCC->AHB1ENR |=(1<<0); //gpioa enabled
	RCC->AHB1ENR |=(1<<2); //gpioc enabled
	RCC->APB1ENR |=(1<<17); //USART2 enabled

	GPIOC->MODER &=~(1<<26);
	GPIOC->MODER &=~(1<<27);

	GPIOC->PUPDR |=(1<<26);
	GPIOC->PUPDR &=~(1<<27);

	//PA2 , PA3 --> USART2 IS DEFINE IN THIS PAGE-SM->46
	GPIOA->MODER |= (2<<4);  // alternate function of moder 2
	GPIOA->MODER |= (2<<6);  // alternate function of moder 3

	GPIOA->OSPEEDR |=(3<<4);
	GPIOA->OSPEEDR |=(3<<6);

	GPIOA->AFR[0] |=(7<<8); // bytes (11:10:9:8)  ->0111
	GPIOA->AFR[0] |=(7<<12); // bytes (15:14:13:12)  ->0111

	USART2->CR1 = 0x00; //clear all
	USART2->CR1 |=(1<<13); //enable usart2, UE=1

	USART2->CR1 &=~(1<<12); //M bit in USART_CR1 to define the word length.

	USART2->BRR |= (1<<0); //USART_BRR register.
	USART2->BRR |= (24<<4); //USART_BRR register. --> 8,7,6,5,4 ->11000

	USART2->CR1 |= (1<<2); //  Receiver RE enabled
	USART2->CR1 |= (1<<3); //  Receiver TE enabled
}
int btn_pressed(int pos)
{
	return (GPIOC->IDR &(1<<pos))?1:0;
}
int main(void)
{

	SysClockConfig();
	Usart2_config();

	char ch='a'-1;
	while(1)
	{
		if(!btn_pressed(13))
		{
			if(ch>'z') ch=('a');
			UART2_SendChar(ch);
			UART2_SendChar('\r');
			UART2_SendChar('\n');
			ch++;
			while(!btn_pressed(13));
		}

	}

	return 0;
}
