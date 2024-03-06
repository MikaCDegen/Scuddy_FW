/*
	Copyright 2017 Benjamin Vedder	benjamin@vedder.se

	This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    */

#ifndef HWCONF_DRV8350_H_
#define HWCONF_DRV8350_H_

#include "datatypes.h"

// Functions
void drv8350_init(void);
bool drv8350_set_oc_adj(int val);
void drv8350_set_oc_mode(drv8301_oc_mode mode);
uint32_t drv8350_read_faults(void);
void drv8350_dccal_on(void);
void drv8350_dccal_off(void);
void drv8350_reset_faults(void);
char* drv8350_faults_to_string(int faults);
unsigned int drv8350_read_reg(int reg);
void drv8350_write_reg(int reg, int data);

// Defines

//Fault Status 1 ( Reg 0x00h )
#define DRV8350_FAULT_VDS_LC		(1 << 0)
#define DRV8350_FAULT_VDS_HC		(1 << 1)
#define DRV8350_FAULT_VDS_LB		(1 << 2)
#define DRV8350_FAULT_VDS_HB		(1 << 3)
#define DRV8350_FAULT_VDS_LA		(1 << 4)
#define DRV8350_FAULT_VDS_HA		(1 << 5)
#define DRV8350_FAULT_OTSD			(1 << 6)
#define DRV8350_FAULT_UVLO			(1 << 7)
#define DRV8350_FAULT_GDF			(1 << 8)
#define DRV8350_FAULT_VDS_OCP		(1 << 9)
#define DRV8350_FAULT_FAULT			(1 << 10)

#define DRV8350_OC_PROTECTION_MASK	0x63F

//VGS Status 2  ( Reg 0x01h )
#define DRV8350_FAULT_VGS_LC		(1 << 11)
#define DRV8350_FAULT_VGS_HC		(1 << 12)
#define DRV8350_FAULT_VGS_LB		(1 << 13)
#define DRV8350_FAULT_VGS_HB		(1 << 14)
#define DRV8350_FAULT_VGS_LA		(1 << 15)
#define DRV8350_FAULT_VGS_HA		(1 << 16)
#define DRV8350_FAULT_GDUV			(1 << 17)
#define DRV8350_FAULT_OTW			(1 << 18)
#define DRV8350_FAULT_SC_OC			(1 << 19)
#define DRV8350_FAULT_SB_OC			(1 << 20)
#define DRV8350_FAULT_SA_OC			(1 << 21)

#define DRV8350_REAL_FAULT_MASK		0x3FF9C0

//Clear Fault  ( Reg 0x02h )
#define DRV8350_CLEAR_FAULT		(1 << 0)
#define DRV8350_OCP_ACT			(0 << 10)

//Gate Driver HS  ( Reg 0x03h )
#define DRV8350_IDRIVEN_HS		(0x05 << 0)
#define DRV8350_IDRIVEP_HS		(0x06 << 4)
#define DRV8350_LOCK_BITS		(3 << 8)

//Gate Driver LS  ( Reg 0x04h )
#define DRV8350_IDRIVEN_LS		(0x06 << 0)
#define DRV8350_IDRIVEP_LS		(0x05 << 4)
#define DRV8350_TDRIVE			(3 << 8)
#define DRV8350_CBC			    (1 << 10)

//OCP Control  ( Reg 0x05h )
#define DRV8350_VDS_LVL			(0 << 0)
#define DRV8350_OCP_DEG			(1 << 4)
#define DRV8350_OCP_MODE		(0 << 6)
#define DRV8350_DEAD_TIME		(1 << 8)
#define DRV8350_TRETRY			(0 << 10)

//CSA Control  ( Reg 0x06h )
#define DRV8350_SEN_LVL			(0 << 0)    //0,25V
#define DRV8350_CSA_CAL_C		(0 << 2)
#define DRV8350_CSA_CAL_B		(0 << 3)
#define DRV8350_CSA_CAL_A		(0 << 4)
#define DRV8350_DIS_SEN			(0 << 5)
//#define DRV8350_CSA_GAIN		(0 << 6)    //00b = 5-V/V shunt amplifier gain
#define DRV8350_CSA_GAIN		(1 << 6)    //01b = 10-V/V shunt amplifier gain
//#define DRV8350_CSA_GAIN		(2 << 6)    //10b = 20-V/V shunt amplifier gain
//#define DRV8350_CSA_GAIN		(3 << 6)    //11b = 40-V/V shunt amplifier gain
#define DRV8350_LS_REF			(0 << 8)
#define DRV8350_VREF_DIV		(1 << 9)
#define DRV8350_CSA_FET			(0 << 10)

/*
#define DCCAL_ON()				drv8350_dccal_on()
#define DCCAL_OFF()				drv8350_dccal_off()
*/


#endif /* HWCONF_DRV8350_H_ */
