/*
	Copyright 2016 - 2019 Benjamin Vedder	benjamin@vedder.se

	This file is part of the VESC firmware.

	The VESC firmware is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    The VESC firmware is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    */

#include "ch.h"
#include "hal.h"
#include "stm32f4xx_conf.h"

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#include "hw.h"
#include "mc_interface.h"
#include "mcpwm.h"
#include "mcpwm_foc.h"
#include "ledpwm.h"
#include "comm_usb.h"
#include "ledpwm.h"
#include "terminal.h"
#include "app.h"
#include "packet.h"
#include "commands.h"
#include "timeout.h"
#include "comm_can.h"
#include "ws2811.h"
#include "led_external.h"
#include "encoder.h"
#include "servo_simple.h"
#include "utils.h"
#include "nrf_driver.h"
#include "rfhelp.h"
#include "spi_sw.h"
#include "timer.h"
#include "imu.h"
#include "flash_helper.h"
#if HAS_BLACKMAGIC
#include "bm_if.h"
#endif
#include "shutdown.h"

/*
 * HW resources used:
 *
 * TIM1: mcpwm
 * TIM5: timer
 * TIM8: mcpwm
 * TIM3: servo_dec/Encoder (HW_R2)/servo_simple
 * TIM4: WS2811/WS2812 LEDs/Encoder (other HW)
 *
 * DMA/stream	Device		Function
 * 1, 2			I2C1		Nunchuk, temp on rev 4.5
 * 1, 7			I2C1		Nunchuk, temp on rev 4.5
 * 2, 4			ADC			mcpwm
 * 1, 0			TIM4		WS2811/WS2812 LEDs CH1 (Ch 1)
 * 1, 3			TIM4		WS2811/WS2812 LEDs CH2 (Ch 2)
 *
 */

// Private variables
static THD_WORKING_AREA(periodic_thread_wa, 1024);
static THD_WORKING_AREA(timer_thread_wa, 128);
static THD_WORKING_AREA(flash_integrity_check_thread_wa, 256);

static THD_FUNCTION(flash_integrity_check_thread, arg) {
	(void)arg;

	chRegSetThreadName("Flash check");
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, ENABLE);

	for(;;) {
		if (flash_helper_verify_flash_memory_chunk() == FAULT_CODE_FLASH_CORRUPTION) {
			NVIC_SystemReset();
		}

		chThdSleepMilliseconds(6);
	}
}

static THD_FUNCTION(periodic_thread, arg) {
	(void)arg;

	chRegSetThreadName("Main periodic");

	for(;;) {
		if (mc_interface_get_state() == MC_STATE_RUNNING) {
			ledpwm_set_intensity(LED_GREEN, 1.0);
		} else {
			ledpwm_set_intensity(LED_GREEN, 0.2);
		}

		mc_fault_code fault = mc_interface_get_fault();
		if (fault != FAULT_CODE_NONE) {
			for (int i = 0;i < (int)fault;i++) {
				ledpwm_set_intensity(LED_RED, 1.0);
				chThdSleepMilliseconds(250);
				ledpwm_set_intensity(LED_RED, 0.0);
				chThdSleepMilliseconds(250);
			}

			chThdSleepMilliseconds(500);
		} else {
			ledpwm_set_intensity(LED_RED, 0.0);
		}

		if (mc_interface_get_state() == MC_STATE_DETECTING) {
			commands_send_rotor_pos(mcpwm_get_detect_pos());
		}

		disp_pos_mode display_mode = commands_get_disp_pos_mode();

		switch (display_mode) {
		case DISP_POS_MODE_ENCODER:
			commands_send_rotor_pos(encoder_read_deg());
			break;

		case DISP_POS_MODE_PID_POS:
			commands_send_rotor_pos(mc_interface_get_pid_pos_now());
			break;

		case DISP_POS_MODE_PID_POS_ERROR:
			commands_send_rotor_pos(utils_angle_difference(mc_interface_get_pid_pos_set(), mc_interface_get_pid_pos_now()));
			break;

		default:
			break;
		}

		if (mc_interface_get_configuration()->motor_type == MOTOR_TYPE_FOC) {
			switch (display_mode) {
			case DISP_POS_MODE_OBSERVER:
				commands_send_rotor_pos(mcpwm_foc_get_phase_observer());
				break;

			case DISP_POS_MODE_ENCODER_OBSERVER_ERROR:
				commands_send_rotor_pos(utils_angle_difference(mcpwm_foc_get_phase_observer(), mcpwm_foc_get_phase_encoder()));
				break;

			default:
				break;
			}
		}

		chThdSleepMilliseconds(10);
	}
}

static THD_FUNCTION(timer_thread, arg) {
	(void)arg;

	chRegSetThreadName("msec_timer");

	for(;;) {
		packet_timerfunc();
		timeout_feed_WDT(THREAD_TIMER);
		chThdSleepMilliseconds(1);
	}
}

// When assertions enabled halve PWM frequency. The control loop ISR runs 40% slower
void assert_failed(uint8_t* file, uint32_t line) {
	commands_printf("Wrong parameters value: file %s on line %d\r\n", file, line);
	mc_interface_release_motor();
	while(1) {
		chThdSleepMilliseconds(1);
	}
}


//SPI
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
	
	GPIOA->MODER |= (2<<10)|(2<<12)|(2<<14)|(1<<8);  // Alternate functions for PA5, PA6, PA7 and Output for PA9
	
	GPIOA->OSPEEDR |= (3<<10)|(3<<12)|(3<<14)|(3<<8);  // HIGH Speed for PA5, PA6, PA7, PA9
	
	GPIOA->AFRL |= (5<<20)|(5<<24)|(5<<28);    // AF5(SPI1) for PA5, PA6, PA7
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
	uint8_t temp = SPI1->DR;
					temp = SPI1->SR;
}
	uint8_t data[8];

void arraybau(void)
{
	float rpmf = mcpwm_foc_get_rpm();
	float ampf = mcpwm_foc_get_tot_current_filtered();
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

	
}

int main(void) {
	halInit();
	chSysInit();
	GPIOConfig();
	SPI_Config();
	SPI_Enable();
	arraybau();
	while (1)
	{
		CS_Enable();
		SPI_Transmit(data, 8);
		CS_Disable();
		chThdSleepMilliseconds(1);
	}
	
	
	

	// Initialize the enable pins here and disable them
	// to avoid excessive current draw at boot because of
	// floating pins.
#ifdef HW_HAS_DRV8313
	INIT_BR();
#endif

	HW_EARLY_INIT();

	chThdSleepMilliseconds(100);

	hw_init_gpio();
	LED_RED_OFF();
	LED_GREEN_OFF();

	timer_init();
	conf_general_init();

	if( flash_helper_verify_flash_memory() == FAULT_CODE_FLASH_CORRUPTION )	{
		// Loop here, it is not safe to run any code
		while (1) {
			chThdSleepMilliseconds(100);
			LED_RED_ON();
			chThdSleepMilliseconds(75);
			LED_RED_OFF();
		}
	}

	ledpwm_init();

	mc_configuration mcconf;
	conf_general_read_mc_configuration(&mcconf);

	mc_interface_init(&mcconf);

	custom_configuration customconf;
	conf_general_read_custom_configuration(&customconf);

	commands_init();
	

#if COMM_USE_USB
	comm_usb_init();
#endif

#if CAN_ENABLE
	comm_can_init();
#endif

	app_configuration appconf;
	conf_general_read_app_configuration(&appconf);
	app_set_configuration(&appconf);	



	//custom_configuration customconf = *custom_get_configuration();
	//mc_interface_get_tachometer_abs_value(true); // erst 0 setzen
	mc_interface_set_odo_value(customconf.odo_save); // dann aus eeprom addieren
	
	app_uartcomm_start_permanent();

#ifdef HW_HAS_PERMANENT_NRF
	conf_general_permanent_nrf_found = nrf_driver_init();
	if (conf_general_permanent_nrf_found) {
		rfhelp_restart();
	} else {
		nrf_driver_stop();
		// Set the nrf SPI pins to the general SPI interface so that
		// an external NRF can be used with the NRF app.
		spi_sw_change_pins(
				HW_SPI_PORT_NSS, HW_SPI_PIN_NSS,
				HW_SPI_PORT_SCK, HW_SPI_PIN_SCK,
				HW_SPI_PORT_MOSI, HW_SPI_PIN_MOSI,
				HW_SPI_PORT_MISO, HW_SPI_PIN_MISO);
		HW_PERMANENT_NRF_FAILED_HOOK();
	}
#endif

#if WS2811_ENABLE
	ws2811_init();
#if !WS2811_TEST
	led_external_init();
#endif
#endif

#if SERVO_OUT_ENABLE
	servo_simple_init();
#endif

	// Threads
	chThdCreateStatic(periodic_thread_wa, sizeof(periodic_thread_wa), NORMALPRIO, periodic_thread, NULL);
	chThdCreateStatic(timer_thread_wa, sizeof(timer_thread_wa), NORMALPRIO, timer_thread, NULL);
	chThdCreateStatic(flash_integrity_check_thread_wa, sizeof(flash_integrity_check_thread_wa), LOWPRIO, flash_integrity_check_thread, NULL);

#if WS2811_TEST
	unsigned int color_ind = 0;
	const int num = 4;
	const uint32_t colors[] = {COLOR_RED, COLOR_GOLD, COLOR_GRAY, COLOR_MAGENTA, COLOR_BLUE};
	const int brightness_set = 100;

	for (;;) {
		chThdSleepMilliseconds(1000);

		for (int i = 0;i < brightness_set;i++) {
			ws2811_set_brightness(i);
			chThdSleepMilliseconds(10);
		}

		chThdSleepMilliseconds(1000);

		for(int i = -num;i <= WS2811_LED_NUM;i++) {
			ws2811_set_led_color(i - 1, COLOR_BLACK);
			ws2811_set_led_color(i + num, colors[color_ind]);

			ws2811_set_led_color(0, COLOR_RED);
			ws2811_set_led_color(WS2811_LED_NUM - 1, COLOR_GREEN);

			chThdSleepMilliseconds(50);
		}

		for (int i = 0;i < brightness_set;i++) {
			ws2811_set_brightness(brightness_set - i);
			chThdSleepMilliseconds(10);
		}

		color_ind++;
		if (color_ind >= sizeof(colors) / sizeof(uint32_t)) {
			color_ind = 0;
		}

		static int asd = 0;
		asd++;
		if (asd >= 3) {
			asd = 0;

			for (unsigned int i = 0;i < sizeof(colors) / sizeof(uint32_t);i++) {
				ws2811_set_all(colors[i]);

				for (int i = 0;i < brightness_set;i++) {
					ws2811_set_brightness(i);
					chThdSleepMilliseconds(2);
				}

				chThdSleepMilliseconds(100);

				for (int i = 0;i < brightness_set;i++) {
					ws2811_set_brightness(brightness_set - i);
					chThdSleepMilliseconds(2);
				}
			}
		}
	}
#endif

	timeout_init();
	timeout_configure(appconf.timeout_msec, appconf.timeout_brake_current);
	imu_init(&appconf.imu_conf);

#if HAS_BLACKMAGIC
	bm_init();
#endif

#ifdef HW_SHUTDOWN_HOLD_ON
	shutdown_init();
#endif

	for(;;) {
		chThdSleepMilliseconds(10);
	}
}
