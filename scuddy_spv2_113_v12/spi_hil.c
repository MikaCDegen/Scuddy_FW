uint8_t data[9];

uint32_t crchil(uint8_t *data, size_t len) {
    uint32_t crc = 0xFFFFFFFF;
    for (size_t i = 0; i < len; ++i) {
        crc = crc ^ data[i];
        for (uint8_t j = 0; j < 8; j++) {
            if (crc & 1)
                crc = (crc >> 1) ^ 0xEDB88320;
            else
                crc >>= 1;
        }
    }
    return ~crc;
}

void arraybau(void)
{
	float rpmf = 2345;	//mcpwm_foc_get_rpm();
	float ampf = 7892;	//mcpwm_foc_get_tot_current_filtered();
	//uint8_t data[8]; // volt high(0) -> volt low(3) - amp high(4) -> amp low(7)
	uint32_t rpm = (int32_t)(rpmf); //2345
	uint32_t amp = (int32_t)(ampf); //7892

	data[0] = (rpm & 0xFF000000) >> 24;
	data[1] = (rpm & 0x00FF0000) >> 16;
	data[2] = (rpm & 0x0000FF00) >> 8;
	data[3] = (rpm & 0x000000FF);
	// Für Matlab: volt = (data[0] * 4278190080 + data[1] * 16711680 + data[2] * 65280 + data[3]) / 2000000

	data[4] = (amp & 0xFF000000) >> 24;
	data[5] = (amp & 0x00FF0000) >> 16;
	data[6] = (amp & 0x0000FF00) >> 8;
	data[7] = (amp & 0x000000FF);

	data[8] = crchil(data, 8);
}

void SPI_Config (void)
{
  RCC->APB2ENR |= (1<<12);  // Enable SPI1 CLock
	
  SPI1->CR1 |= (1<<0)|(1<<1);   // CPOL=1, CPHA=1
	
  SPI1->CR1 |= (1<<2);  // Master Mode
	
  SPI1->CR1 |= (7<<3);  // BR[2:0] = 011: fPCLK/16, PCLK2 = 80MHz, SPI clk = 5MHz
	
  SPI1->CR1 &= ~(1<<7);  // LSBFIRST = 0, MSB first
	
  SPI1->CR1 |= (1<<8) | (1<<9);  // SSM=1, SSi=1 -> Software Slave Management
	
  SPI1->CR1 &= ~(1<<10);  // RXONLY = 0, full-duplex
	
  SPI1->CR1 &= ~(1<<11);  // DFF=0, 8 bit data
	
  SPI1->CR2 = 0;
}

void GPIOConfig (void)
{
	RCC->AHB1ENR |= (1<<0);  // Enable GPIO Clock
	
	GPIOA->MODER |= (2<<10)|(2<<12)|(2<<14)|(1<<8);  // Alternate functions for PA5, PA6, PA7 and Output for PA4
	
	GPIOA->OSPEEDR |= (3<<10)|(3<<12)|(3<<14)|(3<<8);  // HIGH Speed for PA5, PA6, PA7, PA4
	
	GPIOA->AFRL |= (5<<20)|(5<<24)|(5<<28);   // AF5(SPI1) for PA5, PA6, PA7
}

void SPI_Enable (void)
{
	SPI1->CR1 |= (1<<6);   // SPE=1, Peripheral enabled
}

void SPI_Disable (void)
{
	SPI1->CR1 &= ~(1<<6);   // SPE=0, Peripheral Disabled
}

void CS_Enable (void)
{
	palClearPad(GPIOA, 4); // Setzt Bit 25, um Pin 9 zurückzusetzen
}

void CS_Disable (void)
{
	palSetPad(GPIOA, 4);
}

void SPI_Transmit (uint8_t *data, int size)
{
	
	/************** STEPS TO FOLLOW *****************
	1. Wait for the TXE bit to set in the Status Register
	2. Write the data to the Data Register
	3. After the data has been transmitted, wait for the BSY bit to reset in Status Register
	4. Clear the Overrun flag by reading DR and SR
	************************************************/		
	
	int i=0;
	while (i<size)
	{
	   while (!((SPI1->SR)&(1<<1))) {};  // wait for TXE bit to set -> This will indicate that the buffer is empty
	   SPI1->DR = data[i];  // load the data into the Data Register
	   i++;
	}	
	
	
/*During discontinuous communications, there is a 2 APB clock period delay between the
write operation to the SPI_DR register and BSY bit setting. As a consequence it is
mandatory to wait first until TXE is set and then until BSY is cleared after writing the last
data.
*/
	while (!((SPI1->SR)&(1<<1))) {};  // wait for TXE bit to set -> This will indicate that the buffer is empty
	while (((SPI1->SR)&(1<<7))) {};  // wait for BSY bit to Reset -> This will indicate that SPI is not busy in communication	
	
	//  Clear the Overrun flag by reading DR and SR
	volatile uint8_t temp = SPI1->DR;
	temp = SPI1->SR;
}

void senddata()
{
	arraybau();
	CS_Enable();
	
	SPI_Transmit(data, 9);
	CS_Disable();
}
