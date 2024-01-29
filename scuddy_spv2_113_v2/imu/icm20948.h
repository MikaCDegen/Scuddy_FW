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

#ifndef IMU_ICM20948_H_
#define IMU_ICM20948_H_

#include "ch.h"
#include "hal.h"

#include <stdint.h>
#include <stdbool.h>

#include "i2c_bb.h"

typedef struct {
	i2c_bb_state *i2cs;
	uint8_t i2c_address;
	void(*read_callback)(float *accel, float *gyro, float *mag);
	volatile bool is_running;
	volatile bool should_stop;
	int rate_hz;
} ICM20948_STATE;

void icm20948_init(ICM20948_STATE *s, i2c_bb_state *i2c_state, int ad0_val,
		stkalign_t *work_area, size_t work_area_size);
void icm20948_set_read_callback(ICM20948_STATE *s, void(*func)(float *accel, float *gyro, float *mag));
void icm20948_stop(ICM20948_STATE *s);

// All banks
#define ICM20948_BANK_SEL						0x7F

// Bank 0 registers
#define ICM20948_WHO_AM_I						0x00
#define I_AM_20948						0xEA
#define I_AM_20649						0xE1
#define ICM20948_PWR_MGMT_1						0x06
#define ICM20948_PIN_CFG						0x0F
#define ICM20948_ACCEL_XOUT_H					0x2D

// Bank 2 registers
#define GYRO_SMPLRT_DIV                         0x00
#define ICM20948_GYRO_CONFIG_1					0x01
#define ICM20948_ACCEL_SMPLRT_DIV_1             0x10
#define ICM20948_ACCEL_SMPLRT_DIV_2             0x11
#define ICM20948_ACCEL_CONFIG					0x14
#define ICM20948_ACCEL_CONFIG_2					0x15

//Magnetometer Registers
#define AK09916_ADDRESS  0x0C 
#define WHO_AM_I_AK09916 0x01 // (AKA WIA2) should return 0x09
#define AK09916_ST1      0x10  // data ready status bit 0
#define AK09916_XOUT_L   0x11  // data
#define AK09916_XOUT_H   0x12
#define AK09916_YOUT_L   0x13
#define AK09916_YOUT_H   0x14
#define AK09916_ZOUT_L   0x15
#define AK09916_ZOUT_H   0x16
#define AK09916_ST2      0x18  // Data overflow bit 3 and data read error status bit 2
#define AK09916_CNTL     0x30  // Power down (0000), single-measurement (0001), self-test (1000) and Fuse ROM (1111) modes on bits 3:0
#define AK09916_CNTL2    0x31  // Normal (0), Reset (1)

#endif /* IMU_ICM20948_H_ */
