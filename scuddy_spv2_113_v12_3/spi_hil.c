#include "crc.h"
#include "hal.h"
#include "ch.h"

//SPIDriver SPID1;

const SPIConfig hs_spicfg = {
//    .circular         = false,
//    .slave            = false,
//    .data_cb          = NULL,
//    .error_cb         = NULL,
    .ssport           = HW_SPI_PORT_NSS,
    .sspad            = HW_SPI_PIN_NSS,
    .cr1              = 0U
};

unsigned char data[10];
const unsigned char data_size = 10;

void arraybau(void)
{
    float rpmf = 2345;    //mcpwm_foc_get_rpm();
    float ampf = 7892;    //mcpwm_foc_get_tot_current_filtered();
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

    
	unsigned short crc = crc16(data, data_size);
	data[8] = (crc & 0xFF00) >> 8;
	data[9] = (crc & 0x00FF);
}

void SPI_Config (void)
{
    // Pins Init
    palSetPadMode(HW_SPI_PORT_NSS, HW_SPI_PIN_NSS, PAL_MODE_OUTPUT_PUSHPULL);
    //palSetPadMode(HW_SPI_PORT_SCK, HW_SPI_PORT_SCK, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(HW_SPI_PORT_MOSI, HW_SPI_PIN_MOSI, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(HW_SPI_PORT_MISO, HW_SPI_PIN_MISO,  PAL_MODE_OUTPUT_PUSHPULL);

    // SPI Init
    spiInit();
    spiStart(&SPID1, &hs_spicfg);
}

void senddata()
{
    arraybau();
    spiStartSend(&SPID1, data_size, &data);
}