/*
	Copyright 2019 Benjamin Vedder	benjamin@vedder.se

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

#include "icm20948.h"
#include "terminal.h"
#include "commands.h"
#include "utils.h"

#include <stdio.h>
#include <string.h>

#define FAIL_DELAY_US			1000
#define MIN_ITERATION_DELAY_US	500
#define MAX_IDENTICAL_READS		5
#define USE_MAGNETOMETER		0

// Threads
static THD_FUNCTION(icm_thread, arg);

// Private functions
static bool reset_init_icm(ICM20948_STATE *s);
static void terminal_read_reg(int argc, const char **argv);
static uint8_t read_single_reg(ICM20948_STATE *s, uint8_t reg);
static bool write_single_reg(ICM20948_STATE *s, uint8_t reg, uint8_t value);


// Private variables
static ICM20948_STATE *m_terminal_state = 0;

void icm20948_init(ICM20948_STATE *s, i2c_bb_state *i2c_state, int ad0_val,
		stkalign_t *work_area, size_t work_area_size) {

	s->i2cs = i2c_state;
	s->i2c_address = ad0_val ? 0x69 : 0x68;
	s->read_callback = 0;
	s->should_stop = false;

	if (reset_init_icm(s)) {
		s->should_stop = false;
		chThdCreateStatic(work_area, work_area_size, NORMALPRIO, icm_thread, s);
	}

	// Only register terminal command for the first instance of this driver.
	if (m_terminal_state == 0) {
		m_terminal_state = s;
		terminal_register_command_callback(
				"icm_read_reg",
				"Read register of the ICM-20948",
				"[bank] [reg]",
				terminal_read_reg);
	}
}

void icm20948_set_read_callback(ICM20948_STATE *s, void(*func)(float *accel, float *gyro, float *mag)) {
	s->read_callback = func;
}

void icm20948_stop(ICM20948_STATE *s) {
	s->should_stop = true;
	while(s->is_running) {
		chThdSleep(1);
	}

	if (s == m_terminal_state) {
		terminal_unregister_callback(terminal_read_reg);
		m_terminal_state = 0;
	}
}

static void terminal_read_reg(int argc, const char **argv) {
	if (argc == 3) {
		int bank = -1;
		int reg = -1;
		sscanf(argv[1], "%d", &bank);
		sscanf(argv[2], "%d", &reg);

		if (reg >= 0 && (bank == 0 || bank == 1 || bank == 2)) {
			write_single_reg(m_terminal_state, ICM20948_BANK_SEL, bank << 4);
			unsigned int res = read_single_reg(m_terminal_state, reg);
			char bl[9];

			write_single_reg(m_terminal_state, ICM20948_BANK_SEL, 0 << 4);

			utils_byte_to_binary(res & 0xFF, bl);

			commands_printf("Reg 0x%02x: %s (0x%02x)\n", reg, bl, res);
		///* debug Jörn 11 2022
		} else if (reg >= 0 && bank > 2){
			write_single_reg(m_terminal_state, bank, reg);
		//*/
		} else {
			commands_printf("Invalid argument(s).\n");
		}
	} else {
		commands_printf("This command requires one argument.\n");
	}
}

static bool write_single_reg(ICM20948_STATE *s, uint8_t reg, uint8_t value) {
	uint8_t txb[2];

	txb[0] = reg;
	txb[1] = value;

	bool res = i2c_bb_tx_rx(s->i2cs, s->i2c_address, txb, 2, 0, 0);
	return res;
}

#if USE_MAGNETOMETER
static bool write_single_reg_AK09916(ICM20948_STATE *s, uint8_t reg, uint8_t value) {
	uint8_t txb[2];

	txb[0] = reg;
	txb[1] = value;

	bool res = i2c_bb_tx_rx(s->i2cs, AK09916_ADDRESS, txb, 2, 0, 0);
	return res;
}
#endif

static uint8_t read_single_reg(ICM20948_STATE *s, uint8_t reg) {
	uint8_t rxb[1];
	uint8_t txb[1];

	txb[0] = reg;
	bool res = i2c_bb_tx_rx(s->i2cs, s->i2c_address, txb, 1, rxb, 1);

	if (res) {
		return rxb[0];
	} else {
		return 0;
	}
}

#if USE_MAGNETOMETER
static uint8_t read_single_reg_AK09916(ICM20948_STATE *s, uint8_t reg) {
	uint8_t rxb[1];
	uint8_t txb[1];

	txb[0] = reg;
	bool res = i2c_bb_tx_rx(s->i2cs, AK09916_ADDRESS, txb, 1, rxb, 1);

	if (res) {
		return rxb[0];
	} else {
		return 0;
	}
}
#endif

static bool reset_init_icm(ICM20948_STATE *s) {
	i2c_bb_restore_bus(s->i2cs);

	chThdSleep(1);

	// TODO: Check for errors
	
	// first try Jörn 11 2022
	write_single_reg(s, ICM20948_BANK_SEL, 0 << 4);
	//write_single_reg(s, ICM20948_PWR_MGMT_1, 0x80); // do reset
	//chThdSleepMilliseconds(35);
	//write_single_reg(s, ICM20948_PWR_MGMT_1, 0);
	uint8_t who = read_single_reg(s, ICM20948_WHO_AM_I);
	if (who!=I_AM_20948 && who!=I_AM_20649){
		if (s->i2c_address == 0x69){
			s->i2c_address = 0x68;
		} else {
			s->i2c_address = 0x69;
		}
		// second try --> andere adresse Jörn 11 2022
		write_single_reg(s, ICM20948_BANK_SEL, 0 << 4); 
		//write_single_reg(s, ICM20948_PWR_MGMT_1, 0x80); // do reset
		//chThdSleepMilliseconds(35);
		//write_single_reg(s, ICM20948_PWR_MGMT_1, 0);
		who = read_single_reg(s, ICM20948_WHO_AM_I);
	}

	// reset and Set clock source to auto
	//write_single_reg(s, ICM20948_PWR_MGMT_1, 0x80); // do reset
	//chThdSleepMilliseconds(100);
	//write_single_reg(s, ICM20948_BANK_SEL, 0 << 4); 
	write_single_reg(s, ICM20948_PWR_MGMT_1, 1);

	//Set Gyro sample rate divider
	write_single_reg(s, ICM20948_BANK_SEL, 2 << 4);
	write_single_reg(s, GYRO_SMPLRT_DIV,  0 );

	//Bank 2
	write_single_reg(s, ICM20948_BANK_SEL, 2 << 4);
	// Set gyro to +-500 dps and disable lp filter --> enable von erik auf 8,9Hz
	#define MAX_GYRO_VALUE 500.0
	if (who==I_AM_20948){
		write_single_reg(s, ICM20948_GYRO_CONFIG_1, (6 << 3) |  (1 << 1) | (1 << 0) );
	} else if(who==I_AM_20649){
		write_single_reg(s, ICM20948_GYRO_CONFIG_1, (6 << 3) |  (0 << 1) | (1 << 0) );
	} else {
		return false;
	}

	// Set accelerometer to +-4 G and disable lp filter --> enable auf 8Hz
	#define MAX_ACC_VALUE 4.0
	if (who==I_AM_20948){
		write_single_reg(s, ICM20948_ACCEL_CONFIG,  (6 << 3) |  (1 << 1) | (1 << 0) ); // DLPF ON, factor 6
		//write_single_reg(s, ICM20948_ACCEL_SMPLRT_DIV_2, (128 << 0) ); //sample rate
		write_single_reg(s, ICM20948_ACCEL_CONFIG_2, (3 << 0) ); //Average samples by 32
	} else if(who==I_AM_20649){
		write_single_reg(s, ICM20948_ACCEL_CONFIG,  (6 << 3) |  (0 << 1) | (1 << 0) ); // DLPF ON, factor 6
		//write_single_reg(s, ICM20948_ACCEL_SMPLRT_DIV_2, (128 << 0) ); //sample rate
		write_single_reg(s, ICM20948_ACCEL_CONFIG_2, (3 << 0) ); //Average samples by 32
	} else {
		return false;
	}


	// Select bank0 so that data can be polled.
	write_single_reg(s, ICM20948_BANK_SEL, 0 << 4);
	
	#if USE_MAGNETOMETER
		//MAGNETO
		if (who==I_AM_20948){
			#define MAX_MAG_VALUE 4912.0
			// I2C bypass to access magnetometer directly
			write_single_reg(s, ICM20948_BANK_SEL, 0);
			write_single_reg(s, ICM20948_PIN_CFG, 2);

			// Configure Interrupts and Bypass Enable
			// Set interrupt pin active high, push-pull, hold interrupt pin level HIGH
			// until interrupt cleared, clear on read of INT_STATUS, and enable
			// I2C_BYPASS_EN so additional chips can join the I2C bus and all can be
			// controlled by the Arduino as master.
				//writeByte(ICM20948_ADDRESS, INT_PIN_CFG, 0x22);
			// Enable data ready (bit 0) interrupt
			//writeByte(ICM20948_ADDRESS, INT_ENABLE_1, 0x01);
			
			// Set magnetometer data resolution and sample ODR
			write_single_reg_AK09916(s, AK09916_CNTL2, 0x08);
		}
	#endif

	return true;
}

static THD_FUNCTION(icm_thread, arg) {
	ICM20948_STATE *s = (ICM20948_STATE*)arg;

	chRegSetThreadName("ICM Sampling");

	s->is_running = true;
	static systime_t iteration_timer = 0;

	iteration_timer = chVTGetSystemTime();

	for(;;) {
		uint8_t txb[1];
		uint8_t rxb[12];
		static uint8_t rxb_last[12];
		
		txb[0] = ICM20948_ACCEL_XOUT_H;
		bool res = i2c_bb_tx_rx(s->i2cs, s->i2c_address, txb, 1, rxb, 12);
		
		//kommunikation ok ? Jörn 11 2022
		static uint8_t is_identical = 0;
		is_identical++;
		for (int i = 6;i < 12;i++) {
			if (rxb[i] != rxb_last[i] && rxb[i]!=0xff && rxb[i]!=0x00) {
				is_identical = 0;
				break;
			}
		}
		memcpy(rxb_last, rxb, sizeof(rxb));
		if (is_identical >= MAX_IDENTICAL_READS) { // wenn identical dann evtl adresse falsch?
			if (s->i2c_address == 0x69){
				s->i2c_address = 0x68;
			} else {
				s->i2c_address = 0x69;
			}
		}
		if (is_identical >= MAX_IDENTICAL_READS*2) { // da ist keiner zu Hause --> neu initialisiren
			res=false;
			is_identical=MAX_IDENTICAL_READS*2;
		}

		if (res) {
			static float accel[3]={0,0,1}, gyro[3]={0,0,0}, mag[3]={20,0,0};

			accel[0] = accel[0]*0.95 + 0.05*((float)((int16_t)((int16_t)rxb[0] << 8 | (int16_t)rxb[1])) * MAX_ACC_VALUE / 32768.0); // MOD Jörn 2021 06 25 Dämpfung für Kopfsteinpflaster
			accel[1] = accel[1]*0.95 + 0.05*((float)((int16_t)((int16_t)rxb[2] << 8 | (int16_t)rxb[3])) * MAX_ACC_VALUE / 32768.0);
			accel[2] = accel[2]*0.95 + 0.05*((float)((int16_t)((int16_t)rxb[4] << 8 | (int16_t)rxb[5])) * MAX_ACC_VALUE / 32768.0);

			gyro[0] = (float)((int16_t)((int16_t)rxb[6] << 8 | (int16_t)rxb[7])) * MAX_GYRO_VALUE / 32768.0 ;
			gyro[1] = (float)((int16_t)((int16_t)rxb[8] << 8 | (int16_t)rxb[9])) * MAX_GYRO_VALUE / 32768.0;
			gyro[2] = (float)((int16_t)((int16_t)rxb[10] << 8 | (int16_t)rxb[11])) * MAX_GYRO_VALUE / 32768.0;

			// TODO: Read magnetometer as well
			//memset(mag, 0, sizeof(mag)); // 0, wenn nicht gelesen werden soll
			
			// x/y/z gyro register data, ST2 register stored here, must read ST2 at end
			// of data acquisition
			#if USE_MAGNETOMETER
			// Wait for magnetometer data ready bit to be set
			if (read_single_reg_AK09916(s , AK09916_ST1) & 0x01){
				
				// Read the six raw data and ST2 registers sequentially into data array
				//readBytes(AK09916_ADDRESS, AK09916_XOUT_L, 8, &rawData[0]);
			
				txb[0] = AK09916_XOUT_L;
				res = i2c_bb_tx_rx(s->i2cs, AK09916_ADDRESS, txb, 1, rxb, 8);
				//uint8_t c = rxb[7]; // End data read by reading ST2 register
				// Check if magnetic sensor overflow set, if not then report data
				// Remove once finished
				
				if ( (!(rxb[7] & 0x08)) && res ){
					// Turn the MSB and LSB into a signed 16-bit value
					
					mag[0] = (float)((int16_t)((int16_t)rxb[1] << 8 | (int16_t)rxb[0])) * MAX_MAG_VALUE / 32752.0;
					mag[1] = (float)((int16_t)((int16_t)rxb[3] << 8 | (int16_t)rxb[2])) * -MAX_MAG_VALUE / 32752.0;// Y and Z are negativ
					mag[2] = (float)((int16_t)((int16_t)rxb[5] << 8 | (int16_t)rxb[4])) * -MAX_MAG_VALUE / 32752.0;
					
				}
			}
			#endif

			if (s->read_callback) {
				s->read_callback(accel, gyro, mag);
			}
		} else {
			chThdSleepMicroseconds(FAIL_DELAY_US);
			reset_init_icm(s);
		}

		if (s->should_stop) {
			s->is_running = false;
			return;
		}

		iteration_timer += US2ST(1e6 / s->rate_hz);
		systime_t time_start = chVTGetSystemTime();
		if (iteration_timer > time_start) {
			chThdSleep(iteration_timer - time_start);
		} else {
			chThdSleepMicroseconds(MIN_ITERATION_DELAY_US);
			iteration_timer = chVTGetSystemTime();
		}
	}
}
