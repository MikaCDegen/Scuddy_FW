/*
	Copyright 2016 Benjamin Vedder	benjamin@vedder.se

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

#include "hw.h"
#ifdef HW_HAS_DRV8350

#include "drv8350.h"
#include "ch.h"
#include "hal.h"
#include "stm32f4xx_conf.h"
#include "utils.h"
#include "terminal.h"
#include "commands.h"
#include <string.h>
#include <stdio.h>

// Private functions
static uint16_t spi_exchange(uint16_t x);
static void spi_transfer(uint16_t *in_buf, const uint16_t *out_buf, int length);
static void spi_begin(void);
static void spi_end(void);
static void spi_delay(void);
static void terminal_read_reg(int argc, const char **argv);
static void terminal_write_reg(int argc, const char **argv);
static void terminal_set_oc_adj(int argc, const char **argv);
static void terminal_print_faults(int argc, const char **argv);
static void terminal_reset_faults(int argc, const char **argv);
static void terminal_dccal_on(int argc, const char **argv);
static void terminal_dccal_off(int argc, const char **argv);

// Private variables
static char m_fault_print_buffer[120];

void drv8350_init(void) {
	// DRV8350 SPI
	palSetPadMode(DRV8350_MISO_GPIO, DRV8350_MISO_PIN, PAL_MODE_INPUT);
	palSetPadMode(DRV8350_SCK_GPIO, DRV8350_SCK_PIN, PAL_MODE_OUTPUT_PUSHPULL | PAL_STM32_OSPEED_HIGHEST);
	palSetPadMode(DRV8350_CS_GPIO, DRV8350_CS_PIN, PAL_MODE_OUTPUT_PUSHPULL | PAL_STM32_OSPEED_HIGHEST);
	palSetPadMode(DRV8350_MOSI_GPIO, DRV8350_MOSI_PIN, PAL_MODE_OUTPUT_PUSHPULL | PAL_STM32_OSPEED_HIGHEST);
	palSetPad(DRV8350_MOSI_GPIO, DRV8350_MOSI_PIN);

	chThdSleepMilliseconds(100);

	

	drv8350_write_reg(2, ( (DRV8350_CLEAR_FAULT & 0x0001) | (DRV8350_OCP_ACT & 0x0400) )); 	 
	drv8350_write_reg(3, ( (DRV8350_IDRIVEN_HS & 0x000F) | (DRV8350_IDRIVEP_HS & 0x00F0) | (DRV8350_LOCK_BITS & 0x0700) ));
	drv8350_write_reg(4, ( (DRV8350_IDRIVEN_LS & 0x000F) | (DRV8350_IDRIVEP_LS & 0x00F0) | (DRV8350_TDRIVE & 0x0300) | (DRV8350_CBC & 0x0400) ));
	drv8350_write_reg(5, ( (DRV8350_VDS_LVL & 0x000F) | (DRV8350_OCP_DEG & 0x0030) | (DRV8350_OCP_MODE & 0x00C0) | (DRV8350_DEAD_TIME & 0x0300) | (DRV8350_TRETRY & 0x0400) ));
	drv8350_write_reg(6, ( (DRV8350_SEN_LVL & 0x0003) | (DRV8350_CSA_CAL_C & 0x0004) | (DRV8350_CSA_CAL_B & 0x0008) | (DRV8350_CSA_CAL_A & 0x0010) | (DRV8350_DIS_SEN & 0x0020) | (DRV8350_CSA_GAIN & 0x00C0) | (DRV8350_LS_REF & 0x0100) | (DRV8350_VREF_DIV & 0x0200) | (DRV8350_CSA_FET & 0x0400) ));
	drv8350_write_reg(7, 0x0000);
	
	terminal_register_command_callback(
			"drv8350_read_reg",
			"Read a register from the DRV8350 and print it.",
			"[reg]",
			terminal_read_reg);

	terminal_register_command_callback(
			"drv8350_write_reg",
			"Write to a DRV8350 register.",
			"[reg] [hexvalue]",
			terminal_write_reg);

	terminal_register_command_callback(
			"drv8350_set_oc_adj",
			"Set the DRV8350 OC ADJ register.",
			"[value]",
			terminal_set_oc_adj);

	terminal_register_command_callback(
			"drv8350_print_faults",
			"Print all current DRV8350 faults.",
			0,
			terminal_print_faults);

	terminal_register_command_callback(
			"drv8350_reset_faults",
			"Reset all latched DRV8350 faults.",
			0,
			terminal_reset_faults);

	terminal_register_command_callback(
			"drv8301_reset_faults",
			"Reset all latched DRV8350 faults by terminal click.",
			0,
			terminal_reset_faults);
	
	terminal_register_command_callback(
			"drv8350_dccal_on",
			"Short amplifier inputs.",
			0,
			terminal_dccal_on);

	terminal_register_command_callback(
			"drv8350_dccal_off",
			"Normal operationg mode.",
			0,
			terminal_dccal_off);
	
	/*
	terminal_register_command_callback(
			"drv8350_do_dccal",
			"Do DC calibration.",
			0,
			do_dc_cal);
	*/
}

/**
 * Set the threshold of the over current protection of the DRV8350. It works by measuring
 * the voltage drop across drain-source of the MOSFETs and activates when it is higher than
 * a set value. Notice that this current limit is not very accurate.
 *
 * @param val
 * The value to use. Range [0 15]. A lower value corresponds to a lower current limit. See
 * the drv8350 datasheet for how to convert these values to currents.
 */
bool drv8350_set_oc_adj(int val) {
	int reg = drv8350_read_reg(5);
	reg &= 0xFFF0; 
	reg |= (val & 0x0F) << 0;
	drv8350_write_reg(5, reg);
	
	//SPI check
	
	reg = drv8350_read_reg(5);
	if (reg == ( (val & 0x0F) | (DRV8350_OCP_DEG) | (reg & 0xC0) | (DRV8350_DEAD_TIME) |  (DRV8350_TRETRY) ) ) { // 1<<9 fehler
		//commands_printf("DRV comm. OK \n");
		//HUPE_OFF();
		//LICHT_ON();
		return false;
	} else {
		//commands_printf("DRV comm. def. \n");
		// Setzte DRV Fault PIN
		//palSetPadMode(GPIOB, 7,
		//	PAL_MODE_OUTPUT_PUSHPULL |
		//	PAL_STM32_OSPEED_HIGHEST);
		//palClearPad(GPIOB, 7);

		//HUPE_ON();
		//LICHT_OFF();
		return true;
	}

}

/**
 * Set the over current protection mode of the DRV8350.
 *
 * @param mode
 * The over current protection mode.
 */
void drv8350_set_oc_mode(drv8301_oc_mode mode) {
	
	switch (mode){					// mode shift DRV8301 --> DRV8350s
		case 0:mode = 1; break;
		case 1: mode = 0; break;
		case 2: mode = 2; break;
		case 3: mode = 3; break;
		default:
		break;
	}
	int reg = drv8350_read_reg(5);
	reg &= 0xFF3F;
	reg |= (mode & 0x03) << 6;
	drv8350_write_reg(5, reg);
}

/**
 * Read the fault codes of the DRV8350.
 *
 * @return
 * The fault codes, where the bits represent the following:
	b0: 	VDS_LC		
	b1: 	VDS_HC		
	b2: 	VDS_LB		
	b3: 	VDS_HB		
	b4: 	VDS_LA		
	b5: 	VDS_HA		
	b6: 	OTSD			
	b7: 	UVLO			
	b8: 	GDF			
	b9: 	VDS_OCP		
	b10: 	FAULT			

	b11:	VGS_LC		
	b12:	VGS_HC		
	b13:	VGS_LB		
	b14:	VGS_HB	
	b15:	VGS_LA	
	b16:	VGS_HA		
	b17:	GDUV			
	b18:	OTW			
	b19:	SC_OC			
	b20: 	SB_OC			
	b21:	SA_OC			
 *
 */
uint32_t drv8350_read_faults(void) {
	int r0 = drv8350_read_reg(0);
	int r1 = drv8350_read_reg(1);
	//drv8350_reset_faults();
	return (r0 & 0x7FF) | ((r1 & 0x7FF) << 11);
	
}

/**
 * Reset all latched faults.
 */
void drv8350_reset_faults(void) {
	int reg = drv8350_read_reg(2);
	reg |= 1 << 0;
	drv8350_write_reg(2, reg);
}

/**
 * DC Cal on
 */
void drv8350_dccal_on(void) {
	int reg = drv8350_read_reg(6);
	reg |= (1 << 2);
	reg |= (1 << 3);
	reg |= (1 << 4);
	drv8350_write_reg(6, reg);
}

/**
 * DC Cal off
 */
void drv8350_dccal_off(void) {
	int reg = drv8350_read_reg(6);
	reg &=~(1 << 2);
	reg &=~(1 << 3);
	reg &=~(1 << 4);
	drv8350_write_reg(6, reg);
}



char* drv8350_faults_to_string(int faults) {
	if (faults == 0) {
		strcpy(m_fault_print_buffer, "No DRV8350 faults");
	} else {
		strcpy(m_fault_print_buffer, "|");	
		
		//Fault Status 1 ( Reg 0x00h )
		
		if (faults & DRV8350_FAULT_VDS_LC) {
			strcat(m_fault_print_buffer, " VDS_LC_OC |");
		}
		
		if (faults & DRV8350_FAULT_VDS_HC) {
			strcat(m_fault_print_buffer, " VDS_HC_OC |");
		}
		
		if (faults & DRV8350_FAULT_VDS_LB) {
			strcat(m_fault_print_buffer, " VDS_LB_OC |");
		}
		
		if (faults & DRV8350_FAULT_VDS_HB) {
			strcat(m_fault_print_buffer, " VDS_HB_OC |");
		}
		
		if (faults & DRV8350_FAULT_VDS_LA) {
			strcat(m_fault_print_buffer, " VDS_LA_OC |");
		}
		
		if (faults & DRV8350_FAULT_VDS_HA) {
			strcat(m_fault_print_buffer, " VDS_HA_OC |");
		}
		
		if (faults & DRV8350_FAULT_OTSD) {
			strcat(m_fault_print_buffer, " OTSD |");
		}
		
		if (faults & DRV8350_FAULT_UVLO) {
			strcat(m_fault_print_buffer, " UVLO |");
		}
		
		if (faults & DRV8350_FAULT_GDF) {
			strcat(m_fault_print_buffer, " GDF |");
		}
		
		if (faults & DRV8350_FAULT_VDS_OCP) {
			strcat(m_fault_print_buffer, " VDS_monitor_OverCurr |");
		}
		
		if (faults & DRV8350_FAULT_FAULT) {
			strcat(m_fault_print_buffer, " Fault |");
		}
		
		//VGS Status 2  ( Reg 0x01h )
		
		if (faults & DRV8350_FAULT_VGS_LC) {
			strcat(m_fault_print_buffer, " GDF_LC |");
		}
		
		if (faults & DRV8350_FAULT_VGS_HC) {
			strcat(m_fault_print_buffer, " GDF_HC |");
		}
		
		if (faults & DRV8350_FAULT_VGS_LB) {
			strcat(m_fault_print_buffer, " GDF_LB |");
		}
		
		if (faults & DRV8350_FAULT_VGS_HB) {
			strcat(m_fault_print_buffer, " GDF_HB |");
		}
		
		if (faults & DRV8350_FAULT_VGS_LA) {
			strcat(m_fault_print_buffer, " GDF_LA |");
		}
		
		if (faults & DRV8350_FAULT_VGS_HA) {
			strcat(m_fault_print_buffer, " GDF_HA |");
		}
		
		if (faults & DRV8350_FAULT_GDUV) {
			strcat(m_fault_print_buffer, " VGLS_or_VCP_UV |");
		}
		
		if (faults & DRV8350_FAULT_OTW) {
			strcat(m_fault_print_buffer, " OTW |");
		}
		
		if (faults & DRV8350_FAULT_SC_OC) {
			strcat(m_fault_print_buffer, " Sense_C_OC |");
		}
		
		if (faults & DRV8350_FAULT_SB_OC) {
			strcat(m_fault_print_buffer, " Sense_B_OC |");
		}
		
		if (faults & DRV8350_FAULT_SA_OC) {
			strcat(m_fault_print_buffer, " Sense_A_OC |");
		}
	}

	return m_fault_print_buffer;
}

unsigned int drv8350_read_reg(int reg) {
	uint16_t out = 0;
	out |= (1 << 15); // B15: read
	out |= (reg & 0x0F) << 11; // B14-B11: address
	out |= 0x7FF;

	uint16_t res = spi_exchange(out);
	
	
	return res;
	
}

void drv8350_write_reg(int reg, int data) {
	uint16_t out = 0;
	out |= (reg & 0x0F) << 11;
	out |= (data & 0x7FF);

	spi_exchange(out);

}

// Software SPI
static uint16_t spi_exchange(uint16_t x) {
	uint16_t rx;
	spi_begin();
	spi_delay();	
	spi_transfer(&rx, &x, 1);
	spi_delay();
	spi_end();
	spi_delay();
	return rx;
}

static void spi_transfer(uint16_t *in_buf, const uint16_t *out_buf, int length) {
	for (int i = 0;i < length;i++) {
		uint16_t send = out_buf ? out_buf[i] : 0xFFFF;
		uint16_t recieve = 0;

		for (int bit = 0;bit < 16;bit++) {
			palWritePad(DRV8350_MOSI_GPIO, DRV8350_MOSI_PIN, send >> 15);
			send <<= 1;

			palSetPad(DRV8350_SCK_GPIO, DRV8350_SCK_PIN);
			spi_delay();

			palClearPad(DRV8350_SCK_GPIO, DRV8350_SCK_PIN);

			int r1, r2, r3;
			r1 = palReadPad(DRV8350_MISO_GPIO, DRV8350_MISO_PIN);
			__NOP();
			r2 = palReadPad(DRV8350_MISO_GPIO, DRV8350_MISO_PIN);
			__NOP();
			r3 = palReadPad(DRV8350_MISO_GPIO, DRV8350_MISO_PIN);

			recieve <<= 1;
			if (utils_middle_of_3_int(r1, r2, r3)) {
				recieve |= 1;
			}

			spi_delay();
		}

		if (in_buf) {
			in_buf[i] = recieve;
		}
	}
}

static void spi_begin(void) {
	palClearPad(DRV8350_CS_GPIO, DRV8350_CS_PIN);
}

static void spi_end(void) {
	palSetPad(DRV8350_CS_GPIO, DRV8350_CS_PIN);
}

static void spi_delay(void) {
	for (volatile int i = 0;i < 10;i++) {
		__NOP();
	}
}

static void terminal_read_reg(int argc, const char **argv) {
	if (argc == 2) {
		int reg = -1;
		sscanf(argv[1], "%x", &reg);

		if (reg < 0xa) {
			unsigned int res = drv8350_read_reg(reg);
			char bl[9];
			char bh[9];

			utils_byte_to_binary((res >> 8) & 0xFF, bh);
			utils_byte_to_binary(res & 0xFF, bl);

			commands_printf("Reg 0x%02x: %s %s (0x%04x)\n", reg, bh, bl, res);
		} 
		else if (reg == 0xa) {
			for (reg = 0;reg <= 7; reg++ ){
			unsigned int res = drv8350_read_reg(reg);
			char bl[9];
			char bh[9];

			utils_byte_to_binary((res >> 8) & 0xFF, bh);
			utils_byte_to_binary(res & 0xFF, bl);

			commands_printf("Reg 0x%02x: %s %s (0x%04x)\n", reg, bh, bl, res);
			}

		} 
		else {
			commands_printf("Invalid argument(s).\n");
		}
	} else {
		commands_printf("This command requires one argument.\n");
	}
}

static void terminal_write_reg(int argc, const char **argv) {
	if (argc == 3) {
		int reg = -1;
		int val = -1;
		sscanf(argv[1], "%d", &reg);
		sscanf(argv[2], "%x", &val);

		if (reg >= 0 && val >= 0) {
			drv8350_write_reg(reg, val);
			unsigned int res = drv8350_read_reg(reg);
			char bl[9];
			char bh[9];

			utils_byte_to_binary((res >> 8) & 0xFF, bh);
			utils_byte_to_binary(res & 0xFF, bl);

			commands_printf("New reg value 0x%02x: %s %s (0x%04x)\n", reg, bh, bl, res);
		} else {
			commands_printf("Invalid argument(s).\n");
		}
	} else {
		commands_printf("This command requires two arguments.\n");
	}
}

static void terminal_set_oc_adj(int argc, const char **argv) {
	if (argc == 2) {
		int val = -1;
		sscanf(argv[1], "%d", &val);

		if (val >= 0 && val < 16) {
			drv8350_set_oc_adj(val);
			unsigned int res = drv8350_read_reg(5);
			char bl[9];
			char bh[9];

			utils_byte_to_binary((res >> 8) & 0xFF, bh);
			utils_byte_to_binary(res & 0xFF, bl);

			commands_printf("New reg value 0x%02x: %s %s (0x%04x)\n", 5, bh, bl, res);
		} else {
			commands_printf("Invalid argument(s).\n");
		}
	} else {
		commands_printf("This command requires one argument.\n");
	}
}

static void terminal_print_faults(int argc, const char **argv) {
	(void)argc;
	(void)argv;
	commands_printf(drv8350_faults_to_string(drv8350_read_faults()));
}

static void terminal_reset_faults(int argc, const char **argv) {
	(void)argc;
	(void)argv;
	drv8350_reset_faults();
}

static void terminal_dccal_on(int argc, const char **argv) {
	(void)argc;
	(void)argv;
	drv8350_dccal_on();
}

static void terminal_dccal_off(int argc, const char **argv) {
	(void)argc;
	(void)argv;
	drv8350_dccal_off();
}

#endif
