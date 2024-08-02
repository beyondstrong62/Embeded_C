#ifndef SPI_H_
#define SPI_H_

#include "stm32f446xx.h"

void GPIO_init(void);
void SPI1_master(void);
void SPI3_slave(void);

#endif /* SPI_H_ */
