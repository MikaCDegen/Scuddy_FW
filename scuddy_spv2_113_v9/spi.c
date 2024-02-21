#include "spi.h"

// SPI-Konfiguration
static const SPIConfig spiCfg = {
    .end_cb = NULL,
    .ssport = GPIOA, // Beispiel: SS Pin auf Port A anpassen
    .sspad = 4,      // Beispiel: SS Pin Nummer anpassen
    .cr1 = SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0,

};

void spiInit(void) {
    // SPI1 initialisieren, Beispiel: SPI1 verwenden
    spiStart(&SPID1, &spiCfg);
    // SS Pin als Ausgang konfigurieren, falls benötigt
    palSetPadMode(GPIOA, 4, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPad(GPIOA, 4); // SS auf High, um nicht zu selektieren
}

void spiSendData(uint8_t *data, size_t len) {
    spiSelect(&SPID1); // SS aktivieren (niedrig)
    spiSend(&SPID1, len, data);
    spiUnselect(&SPID1); // SS deaktivieren (hoch)
}

void spiReceiveData(uint8_t *buffer, size_t len) {
    spiSelect(&SPID1); // SS aktivieren (niedrig)
    spiReceive(&SPID1, len, buffer);
    spiUnselect(&SPID1); // SS deaktivieren (hoch)
}
