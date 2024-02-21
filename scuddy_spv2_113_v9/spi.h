#ifndef SPI_H
#define SPI_H

#include "hal.h"

void spiInit(void);
void spiSendData(uint8_t *data, size_t len);
void spiReceiveData(uint8_t *buffer, size_t len);

#endif // SPI_H
