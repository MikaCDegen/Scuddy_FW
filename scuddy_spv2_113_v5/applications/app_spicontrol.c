#include "ch.h" // ChibiOS
#include "hal.h" // ChibiOS HAL
#include "mc_interface.h" // Motorsteuerungs-Funktionen
#include "hw.h" // Pinbelegung unserer Hardware
#include "timeout.h" // Timeout Reset
#include "commands.h" // printf für BLDC Terminal
#include "mcpwm.h"  // Funktionen zum Messen von Live-Daten
#include "mcpwm_foc.h"  // Funktionen zum Messen von Live-Daten
#include "mc_interface.h" // Funktionen zum Motorsteuerung
#include "conf_general.h"
#include "app_spicontrol.h"


SPI_HandleTypeDef hspi1;

uint8_t buffer_tx[10]={40,41,42,43,44,45,46,47,48,49};
uint8_t buffer_rx[10];


void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);



void MX_SPI1_Init(void) {
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;

  HAL_SPI_Init(&hspi1);

  // Konfiguriere NVIC für SPI-Interrupts
HAL_NVIC_SetPriority(SPI1_IRQn, 1, 0);
HAL_NVIC_EnableIRQ(SPI1_IRQn);
}



void SPI_Transmit_IT(uint8_t *data, uint16_t size)
{
    HAL_SPI_Transmit_IT(&hspi1, data, size);
}

void SPI_Receive_IT(uint8_t *buffer, uint16_t size)
{
    HAL_SPI_Receive_IT(&hspi1, buffer, size);
}

// SPI-Interrupt-Handler
void SPI1_IRQHandler(void)
{
    HAL_SPI_IRQHandler(&hspi1);
}

// Callback-Funktionen, die nach Abschluss der Übertragung/ des Empfangs aufgerufen werden
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
    // Code, der nach Abschluss der Übertragung ausgeführt werden soll
}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
    // Code, der nach Abschluss des Empfangs ausgeführt werden soll
}
