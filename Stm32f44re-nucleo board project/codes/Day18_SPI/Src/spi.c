/*
 * spi.c
 *
 *  Created on: Jul 25, 2024
 *      Author: SATHYAJIT
 */

#include "spi.h"

void GPIO_init()
{
	RCC->AHB1ENR |= (1<<0);
	GPIOA->MODER &= ~((3<<10) | (3<<12) | (3<<14));
	GPIOA->MODER |= (2<<10)|(2<<12)|(2<<14);
	//GPIOA->OTYPER &= ~(7<<5);
	GPIOA->OSPEEDR &= ~((3<<10)|(3<<12)|(3<<14));
	GPIOA->OSPEEDR |= (2<<10)|(2<<12)|(2<<14);
	GPIOA->AFR[0] &= ~(0xFFF<<20);
	GPIOA->AFR[0] |= (0x555<<20);

	RCC->AHB1ENR |= (1<<2);
	GPIOC->MODER &=~((3<<20) | (3<<22) | (3<<24));
	GPIOC->MODER |= (2<<20)|(2<<22)|(2<<24);
	//GPIOC->OTYPER &= ~(7<<10);
	GPIOC->OSPEEDR &= ~((3<<20)|(3<<22)|(3<<24));
	GPIOC->OSPEEDR |= (2<<20)|(2<<22)|(2<<24);
	GPIOC->AFR[1] &= ~(0xFFF<<8);
	GPIOC->AFR[1] |= (0x666<<8);

}

void SPI1_master()
{
	RCC->APB2ENR |= (1<<12);
	SPI1->CR1 |= (1<<2); // master
	SPI1->CR1 |= (1<<0) | (1<<1);
	SPI1->CR1 &= ~(7U<<3);
	SPI1->CR1 |= (3U<<3);
	SPI1->CR1 &=~(1<<7);
	SPI1->CR1 |=(1<<9);
	SPI1->CR1 |=(1<<8);
	SPI1->CR1 &=~(1<<10);
	SPI1->CR1 &=~(1<<11);
	SPI1->CR1 &=~(3<<12);
	SPI1->CR1 &=~(1<<15);
	SPI1->CR1 |= (1<<6);
	SPI1->CR2=0;
}

void SPI3_slave()
{
	RCC->APB1ENR |= (1<<15);
	SPI3->CR1 &= ~(1<<2); // slave
	SPI3->CR1 |= (1<<0) | (1<<1);
	SPI3->CR1 &= ~(1<<7);
	SPI3->CR1 |= (1<<9);
	SPI3->CR1 &=~(1<<8);
	SPI3->CR1 &=~(1<<10);
	SPI3->CR1 &=~(1<<11);
	SPI3->CR1 &=~(3<<12);
	SPI3->CR1 &=~(1<<15);
	SPI3->CR1 |= (1<<6);

}
