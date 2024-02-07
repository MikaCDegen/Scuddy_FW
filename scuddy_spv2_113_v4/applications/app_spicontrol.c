#include "stm32f4xx_hal.h"
#include "commands.h"

SPI_HandleTypeDef hspi1;

void MX_SPI1_Init(void) {
  // GPIO-Initialisierung für SPI1 Pins
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  // SPI1 GPIO Clocks aktivieren
  __HAL_RCC_GPIOA_CLK_ENABLE();

  // SPI1 Pins konfigurieren: SCK, MISO und MOSI
  GPIO_InitStruct.Pin = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  // SPI1 initialisieren (wie vorher definiert)
  hspi1.Instance = SPI1;
  // ... (restliche SPI-Konfiguration)


    hspi1.Instance = SPI1;
    hspi1.Init.Mode = SPI_MODE_MASTER;
    hspi1.Init.Direction = SPI_DIRECTION_2LINES;
    hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
    hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
    hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
    hspi1.Init.NSS = SPI_NSS_SOFT;
    hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256; // Hier ggf. anpassen, um 1000 Hz zu erreichen
    hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
    hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    hspi1.Init.CRCPolynomial = 10;

    if (HAL_SPI_Init(&hspi1) != HAL_OK) {
        // Fehler bei der Initialisierung
        Error_Handler();
    }
}
void MX_SPI1_Init(void) {
    // GPIO-Initialisierung für SPI1 Pins
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // SPI1 GPIO Clocks aktivieren
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // SPI1 Pins konfigurieren: SCK, MISO und MOSI
    GPIO_InitStruct.Pin = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // SPI1 initialisieren (wie vorher definiert)
    hspi1.Instance = SPI1;
    // ... (restliche SPI-Konfiguration)
}


void Error_Handler(void) {
    commands_printf("Fehler bei SPI");
}

void SPI_Send(SPI_HandleTypeDef *hspi, uint8_t *data, uint16_t size) {
    // Übertragen der Daten
    if (HAL_SPI_Transmit(hspi, data, size, HAL_MAX_DELAY) != HAL_OK) {
        // Fehlerbehandlung
        Error_Handler();
    }
}

void SPI_Receive(SPI_HandleTypeDef *hspi, uint8_t *data, uint16_t size) {
    // Daten empfangen
    if (HAL_SPI_Receive(hspi, data, size, HAL_MAX_DELAY) != HAL_OK) {
        // Fehlerbehandlung
        Error_Handler();
    }
}




int main(void) {
    HAL_Init();
    // Initialisieren aller konfigurierten Peripheriegeräte
    MX_SPI1_Init();
    //Senden der SPI schnittstelle
    SPI_Send();
    //Empfangen der SPI schnittstelle
    SPI_Receive();

}
