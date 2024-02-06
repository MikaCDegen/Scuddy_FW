#ifndef SPI_COMM_H
#define SPI_COMM_H

#include "hal.h"

void MX_SPI1_Init(void);
void SPI_Transmit(uint8_t *data, uint16_t size);
void SPI_Receive(uint8_t *buffer, uint16_t size);

#endif // SPI_COMM_H
