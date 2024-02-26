/*
	Copyright 2016 - 2017 Benjamin Vedder	benjamin@vedder.se

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

#include "app.h"

#include "ch.h"
#include "hal.h"
#include "stm32f4xx_conf.h"
#include "mc_interface.h"
#include "timeout.h"
#include "imu/imu.h"
#include "imu/ahrs.h"
#include "utils.h"
#include "comm_can.h"
#include "hw.h"
#include <math.h>

// Settings
#define MAX_CAN_AGE						0.1
#define MIN_MS_WITHOUT_POWER			500
#define FILTER_SAMPLES					5
#define RPM_FILTER_SAMPLES				8

// Threads
static THD_FUNCTION(adc_thread, arg);
static THD_WORKING_AREA(adc_thread_wa, 1024);

// Private variables
static volatile adc_config config;
static volatile balance_config balance_conf;
static volatile imu_config imu_conf;

static volatile float ms_without_power = 0.0;
static volatile float decoded_level = 0.0;
static volatile float read_voltage = 0.0;
static volatile float decoded_level2 = 0.0;
static volatile float read_voltage2 = 0.0;
static volatile bool use_rx_tx_as_buttons = false;
static volatile bool use_can_adc_input = false;
static volatile bool stop_now = true;
static volatile bool is_running = false;

static float pitch_angle;
static float setpoint, setpoint_target, tiltback_step_size, startup_step_size;
static float pid_value;
//static float proportional, integral, derivative;
//static float last_proportional;
static float p_term;
static float i_term;
static float d_term, d_filter;
static float error, prev_error;
static float d_t;

static bool rev_button_last;
static float hill_value;
static int   hill_diff;
static float hill_counter;



void app_adc_configure(adc_config *conf, balance_config *conf2, imu_config *conf3) {
	config = *conf;
	balance_conf = *conf2;
	imu_conf = *conf3;
	ms_without_power = 0.0;
}



void app_adc_start(bool use_rx_tx, bool use_can_input) {
	
	pitch_angle = 0;
	mc_interface_set_wheely_crtl((uint16_t)balance_conf.pitch_fault); // wenn keine can info, dann app_conf wert
	setpoint_target = mc_interface_get_wheely_crtl();
	setpoint = setpoint_target;

	startup_step_size = balance_conf.startup_speed / config.update_rate_hz;
	tiltback_step_size = balance_conf.tiltback_speed / config.update_rate_hz;
	
	
	
	pid_value = 0;
	d_t = 1.0 / config.update_rate_hz;
	p_term = 0;	
	i_term = 0;
	d_term = 0;
	d_filter = 0;
	error = 0;	
	prev_error = 0;
	//proportional = 0;
	//integral = 0;
	//derivative = 0;
	//last_proportional = 0;

	
	hill_value=0;
	hill_diff=0;
	hill_counter=0;
	
	use_rx_tx_as_buttons = use_rx_tx;
	use_can_adc_input = use_can_input;
	stop_now = false;
	chThdCreateStatic(adc_thread_wa, sizeof(adc_thread_wa), NORMALPRIO, adc_thread, NULL);
}

void app_adc_stop(void) {
	stop_now = true;
	while (is_running) {
		chThdSleepMilliseconds(1);
	}
}

float app_adc_get_decoded_level(void) {
	return decoded_level;
}

float app_adc_get_voltage(void) {
	return read_voltage;
}

float app_adc_get_decoded_level2(void) {
	return decoded_level2;
}

float app_adc_get_voltage2(void) {
	return read_voltage2;
}


static THD_FUNCTION(adc_thread, arg) {
	(void)arg;

	chRegSetThreadName("APP_ADC");
		

	// Set servo pin as an input with pullup
	if (use_rx_tx_as_buttons) {
		palSetPadMode(HW_UART_TX_PORT, HW_UART_TX_PIN, PAL_MODE_INPUT_PULLUP);
		palSetPadMode(HW_UART_RX_PORT, HW_UART_RX_PIN, PAL_MODE_INPUT_PULLUP);
	} else {
		//palSetPadMode(HW_ICU_GPIO, HW_ICU_PIN, PAL_MODE_INPUT_PULLUP);
		//palSetPadMode(TACHO_GPIO, TACHO_PIN, PAL_MODE_INPUT_PULLUP); // wenn hardware input
	}

	is_running = true;

	for(;;) {
		// Sleep for a time according to the specified rate
		systime_t sleep_time = CH_CFG_ST_FREQUENCY / config.update_rate_hz;

		// At least one tick should be slept to not block the other threads
		if (sleep_time == 0) {
			sleep_time = 1;
		}
		chThdSleep(sleep_time);

		if (stop_now) {
			is_running = false;
			return;
		}

		// For safe start when fault codes occur
		if (mc_interface_get_fault() != FAULT_CODE_NONE) {
			ms_without_power = 0;
		}

		// Read the external ADC pin and convert the value to a voltage.
		float pwr = 0;	
		if(use_can_adc_input){
			pwr = mc_interface_get_gas();
		}
		else{
			pwr = (float)ADC_Value[ADC_IND_EXT];
		}
		
		pwr /= 4096.0;
		//pwr *= (V_REG * (VADC_R1 + VADC_R2) / VADC_R1);
		pwr *= V_REG;

		read_voltage = pwr;
		
		//throttle error
		if( !(ms_without_power < MIN_MS_WITHOUT_POWER))
		{
			if(pwr < (config.voltage_start -0.2)){
			//mc_interface_fault_info(FAULT_CODE_THROTTLE_UNDERVOLTAGE);
			} 

			if(pwr > (config.voltage_end +0.3)){
				mc_interface_fault_stop(FAULT_CODE_THROTTLE_OVERVOLTAGE);
				pwr=0;
			}
		}	

		// Optionally apply a mean value filter
		if (config.use_filter) {
			static float filter_buffer[FILTER_SAMPLES];
			static int filter_ptr = 0;

			filter_buffer[filter_ptr++] = pwr;
			if (filter_ptr >= FILTER_SAMPLES) {
				filter_ptr = 0;
			}

			pwr = 0.0;
			for (int i = 0;i < FILTER_SAMPLES;i++) {
				pwr += filter_buffer[i];
			}
			pwr /= FILTER_SAMPLES;
		}

		// Map the read voltage
		switch (config.ctrl_type) {
		case ADC_CTRL_TYPE_CURRENT_REV_CENTER:
		case ADC_CTRL_TYPE_CURRENT_REV_BUTTON_BRAKE_CENTER:
		case ADC_CTRL_TYPE_CURRENT_NOREV_BRAKE_CENTER:
		case ADC_CTRL_TYPE_DUTY_REV_CENTER:
		case ADC_CTRL_TYPE_PID_REV_CENTER:
			// Mapping with respect to center voltage
			if (pwr < config.voltage_center) {
				pwr = utils_map(pwr, config.voltage_start,
						config.voltage_center, 0.0, 0.5);
			} else {
				pwr = utils_map(pwr, config.voltage_center,
						config.voltage_end, 0.5, 1.0);
			}
			break;

		default:
			// Linear mapping between the start and end voltage

			pwr = utils_map(pwr, config.voltage_start, config.voltage_end, 0.0, 1.0);
			break;
		}

		// Truncate the read voltage
		utils_truncate_number(&pwr, 0.0, 1.0);

		// Optionally invert the read voltage
		if (config.voltage_inverted) {
			pwr = 1.0 - pwr;
		}
		
		//speed_now und Maxspeed holen
		float speed_now = mc_interface_get_speed() * 3.6; // in km/h
		float v_max_actual = mc_interface_get_v_max_actual() * 3.6; // in km/h
		const float gradient = 2.0;
		float pwr_reduction_overspeed = 0.0;
		// hier verrrechnung der Gasgriffwerte bei Overspeed
		if (speed_now < (v_max_actual + (0.5 * gradient)) ) {
			pwr_reduction_overspeed = 1.0; 
		} else if (speed_now > (v_max_actual + (2.0 * gradient)) ) {
			pwr_reduction_overspeed = 0.0;
		} else {
			pwr_reduction_overspeed = utils_map(speed_now, (v_max_actual + (0.5 * gradient) ), (v_max_actual + (2.0 * gradient) ), 
																	1.0, 		    					0.0);
		}
		pwr *= pwr_reduction_overspeed;
		
		// Truncate again for safety
		utils_truncate_number(&pwr, 0.0, 1.0);

		decoded_level = pwr;

		// Read the external ADC pin and convert the value to a voltage.
#ifdef ADC_IND_EXT2
		float brake =0;
		if(use_can_adc_input){
			brake = mc_interface_get_reku();
		}
		else{
			brake = (float)ADC_Value[ADC_IND_EXT2];
		}
		
		brake /= 4096.0;
		//brake *= (V_REG * (VADC_R1 + VADC_R2) / VADC_R1);
		brake *= V_REG;
		
#else
		float brake = 0.0;
#endif

		read_voltage2 = brake;
		
		//recu error
		if( !(ms_without_power < MIN_MS_WITHOUT_POWER))
		{
			if(brake < (config.voltage2_start -0.2)){
			//mc_interface_fault_info(FAULT_CODE_RECU_UNDERVOLTAGE);
			} 

			if(brake > (config.voltage2_end +0.3)){
				mc_interface_fault_info(FAULT_CODE_RECU_OVERVOLTAGE);
				brake=0;
			}
		}	
		// Optionally apply a mean value filter
		if (config.use_filter) {
			static float filter_buffer2[FILTER_SAMPLES];
			static int filter_ptr2 = 0;

			filter_buffer2[filter_ptr2++] = brake;
			if (filter_ptr2 >= FILTER_SAMPLES) {
				filter_ptr2 = 0;
			}

			brake = 0.0;
			for (int i = 0;i < FILTER_SAMPLES;i++) {
				brake += filter_buffer2[i];
			}
			brake /= FILTER_SAMPLES;
		}

		// Map and truncate the read voltage
		brake = utils_map(brake, config.voltage2_start, config.voltage2_end, 0.0, 1.0);
		utils_truncate_number(&brake, 0.0, 1.0);

		// Optionally invert the read voltage
		if (config.voltage2_inverted) {
			brake = 1.0 - brake;
		}
		
		float reku_apply_overspeed = 0.0;
		// hier verrrechnung der Rekugriffwerte bei Overspeed
		if (speed_now < (v_max_actual + (2.0 * gradient)) ) {
			reku_apply_overspeed = 0.0; 
		} else if (speed_now > (v_max_actual + (3.0 * gradient)) ) {
			reku_apply_overspeed = balance_conf.deadzone; //  wert missbraucht " APPCONF_BALANCE_DEADZONE "  
		} else {
			reku_apply_overspeed = utils_map(speed_now, (v_max_actual + (2.0 * gradient) ), (v_max_actual + (3.0 * gradient) ), 
																	0.0, 						balance_conf.deadzone);
		}
		brake += reku_apply_overspeed;

	
		utils_truncate_number(&brake, 0.0, 1.0);

		decoded_level2 = brake;

		// Read the button pins
		bool cc_button = false;
		bool rev_button = false;
		const float rpm_now = mc_interface_get_rpm();
		if (use_rx_tx_as_buttons) {
			cc_button = !palReadPad(HW_UART_TX_PORT, HW_UART_TX_PIN);
			if (config.cc_button_inverted) {
				cc_button = !cc_button;
			}
			rev_button = !palReadPad(HW_UART_RX_PORT, HW_UART_RX_PIN);
			if (config.rev_button_inverted) {
				rev_button = !rev_button;
			}
			
		} else {
			// When only one button input is available, use it differently depending on the control mode
			if (config.ctrl_type == ADC_CTRL_TYPE_CURRENT_REV_BUTTON ||
                    			config.ctrl_type == ADC_CTRL_TYPE_CURRENT_REV_BUTTON_BRAKE_CENTER ||
					config.ctrl_type == ADC_CTRL_TYPE_CURRENT_NOREV_BRAKE_BUTTON ||
					config.ctrl_type == ADC_CTRL_TYPE_CURRENT_REV_BUTTON_BRAKE_ADC ||
					config.ctrl_type == ADC_CTRL_TYPE_DUTY_REV_BUTTON ||
					config.ctrl_type == ADC_CTRL_TYPE_PID_REV_BUTTON) {
				//rev_button = !palReadPad(HW_ICU_GPIO, HW_ICU_PIN);
				rev_button = !palReadPad(TACHO_GPIO, TACHO_PIN);
				
				if (config.rev_button_inverted) {
					rev_button = !rev_button;
				}
			} else {
				cc_button = !palReadPad(HW_ICU_GPIO, HW_ICU_PIN);
				if (config.cc_button_inverted) {
					cc_button = !cc_button;
				}
			}
		}

		// All pins and buttons are still decoded for debugging, even
		// when output is disabled.
		if (app_is_output_disabled()) {
			continue;
		}

		switch (config.ctrl_type) {
		case ADC_CTRL_TYPE_CURRENT_REV_CENTER:
		case ADC_CTRL_TYPE_CURRENT_REV_BUTTON_BRAKE_CENTER:
		case ADC_CTRL_TYPE_CURRENT_NOREV_BRAKE_CENTER:
		case ADC_CTRL_TYPE_DUTY_REV_CENTER:
		case ADC_CTRL_TYPE_PID_REV_CENTER:
			// Scale the voltage and set 0 at the center
			pwr *= 2.0;
			pwr -= 1.0;

			//addon JJ 2023 0324
			if( (mc_interface_get_enviro() & (1 << 13)) || (mc_interface_get_enviro() & (1 << 15)) ) { // Bremse hinten gezogen oder auch für Autoreku "Hundemodus"
				brake += ( mc_interface_get_brk_reku_float() * (1.0-pwr) ); // bei 0% gas volle wirkung, sonst linear bis auf 0
				utils_truncate_number(&brake, 0.0, 1.0);
			}
			
			pwr -= brake; // rekugriff geht trotzden

			break;

		case ADC_CTRL_TYPE_CURRENT_NOREV_BRAKE_ADC:
		case ADC_CTRL_TYPE_CURRENT_REV_BUTTON_BRAKE_ADC:
			// Apply Brake lever Reku und Hundemodus
			if( (mc_interface_get_enviro() & (1 << 13)) || (mc_interface_get_enviro() & (1 << 15)) ) { // Bremse hinten gezogen oder auch für Autoreku "Hundemodus"
				brake += ( mc_interface_get_brk_reku_float() * (1.0-pwr) ); // bei 0% gas volle wirkung, sonst linear bis auf 0
				utils_truncate_number(&brake, 0.0, 1.0);
			}
			
			pwr -= brake;

			//}
			break;

		case ADC_CTRL_TYPE_CURRENT_REV_BUTTON:
		case ADC_CTRL_TYPE_CURRENT_NOREV_BRAKE_BUTTON:
		case ADC_CTRL_TYPE_DUTY_REV_BUTTON:
		case ADC_CTRL_TYPE_PID_REV_BUTTON:
			// Invert the voltage if the button is pressed
			if (rev_button) {
				pwr = -pwr;
			}
			break;

		default:
			break;
		}

		// Apply deadband
		utils_deadband(&pwr, config.hyst, 1.0);

		// Apply throttle curve
		pwr = utils_throttle_curve(pwr, config.throttle_exp, config.throttle_exp_brake, config.throttle_exp_mode);

		// Apply ramping
		static systime_t last_time = 0;
		static float pwr_ramp = 0.0;
		//float ramp_time = fabsf(pwr) > fabsf(pwr_ramp) ? config.ramp_time_pos : config.ramp_time_neg;
		float ramp_time = pwr > fabsf(pwr_ramp) ? config.ramp_time_pos : config.ramp_time_neg; // negativ soll immer schnell gehen auch richtung reku JJ04 2023

		if (fabsf(pwr) > 0.001) {
		//	ramp_time = fminf(config.ramp_time_pos, config.ramp_time_neg); // ergibt irgendwie keinen sinn JJ 04 2023
		}

		if (ramp_time > 0.01) {
			const float ramp_step = (float)ST2MS(chVTTimeElapsedSinceX(last_time)) / (ramp_time * 1000.0);
			utils_step_towards(&pwr_ramp, pwr, ramp_step);
			last_time = chVTGetSystemTimeX();
			pwr = pwr_ramp;
		}
		//Wheelie ctrl
		setpoint_target = mc_interface_get_wheely_crtl();
		if (setpoint_target<90.0){
			pitch_angle = imu_get_pitch() * 180.0f / M_PI; // bogemmass in grad
			
			if ( (pitch_angle > setpoint) && (setpoint > -5.0) && (balance_conf.overspeed_duty == 1) ){
				setpoint -= tiltback_step_size;
				balance_conf.ki = 0 ;
				i_term = 0 ;
				
			}


			if ( (pitch_angle > (setpoint-0.5)) && (setpoint<30) && (balance_conf.overspeed_duty == 0.5) ){
				setpoint += startup_step_size;
			}
			if ( (pwr<0.05) && (setpoint > setpoint_target) && (pitch_angle < (setpoint+0.5)) && (balance_conf.overspeed_duty == 0.5) ){
				setpoint -= startup_step_size;
			}
			

			if ( (pwr<0.05) && (setpoint < setpoint_target) && (balance_conf.overspeed_duty != 0.5)){
				setpoint = setpoint_target;
			}
			
			// Do PID maths
			error = setpoint - pitch_angle;
			
			p_term = error * balance_conf.kp;
			i_term += error * (balance_conf.ki * d_t);
			d_term = (error - prev_error) * (balance_conf.kd / d_t);
			
			// Store previous error
			prev_error = error;
			
			// Filter D
			if ( (d_term < 0.04) && (d_term > -0.04) ){
				d_term=0;
			}
			UTILS_LP_FAST(d_filter, d_term, balance_conf.tiltback_low_voltage);
			d_term = d_filter;
			
			if(p_term>1.0){
				d_term=0;
			} else if(p_term<0.5){
				d_term=d_term;
			} else{
				d_term = utils_map(p_term, 1.0, 0.5, 0, d_term);
			}
			
			// I-term wind-up protection
			utils_truncate_number(&p_term, -2.0, 2.0);	//2.0 muss so groß um das i vor regelbeginn zu begrenzen
			if ( (p_term - i_term)  > 2.0 ){
				i_term = p_term - 2.0;
			}
			if ( (p_term + i_term) < -2.0 ){ 
				i_term = -2.0 - p_term;
			}		
			utils_truncate_number(&i_term, -2.0, 0.0);
			utils_truncate_number(&p_term, -2.0, 0.0);

			// Calculate output
			pid_value = p_term + i_term + d_term;

			//Keine Reku bei flachen Winkeln
			if (pitch_angle < (setpoint-5) ){
				utils_truncate_number(&pid_value, -1.0, 0.0);
			} else {
				utils_truncate_number(&pid_value, -2.0, 0.0);
			}
			//mc_interface_set_current_bms(pid_value); // missbraucht für debuging


		}
		

		float current_rel = 0.0;
		bool current_mode = false;
		bool current_mode_brake = false;
		const volatile mc_configuration *mcconf = mc_interface_get_configuration();
		bool send_duty = false;
		
		//Hill Holder
		if( (!(ms_without_power < MIN_MS_WITHOUT_POWER && config.safe_start)) ){
			if (!rev_button)
			{
				hill_value += (-rpm_now * 3e-6);	
				if( rpm_now > 0){
					hill_value += (-rpm_now * 3e-6); // schnell wieder abbauen
				}
			} else {
				hill_value += (rpm_now * 3e-6);	
				if( rpm_now < 0){
					hill_value += (rpm_now * 3e-6); // schnell wieder abbauen
				}
			}	
			
		} else {
			hill_value = 0.0;
		}


		if (rev_button != rev_button_last){
			hill_value = 0.0;
			rev_button_last = rev_button;
		} 

		if( (!mcconf->s_pid_allow_braking) || (mc_interface_get_enviro() & (1 << 14)) ){
			hill_value = 0.0;
		}
						
		if ( (brake + hill_value) > 0.5 ){
			//hill_value = 0.5 - brake; // rückwärts schieben mit reku
		}
		utils_truncate_number(&hill_value, 0.0, 0.5);


		// Use the filtered and mapped voltage for control according to the configuration.
		switch (config.ctrl_type) {
		case ADC_CTRL_TYPE_CURRENT:
		case ADC_CTRL_TYPE_CURRENT_REV_CENTER:
		case ADC_CTRL_TYPE_CURRENT_REV_BUTTON:
			current_mode = true;

			//pwr+=pid_value;
			
			if ((pwr >= 0.0 && rpm_now > 0.0) || (pwr < 0.0 && rpm_now < 0.0)) {
				current_rel = pwr;
			} else {
				current_rel = pwr;
			}

			if (fabsf(pwr) < 0.001) {
				ms_without_power += (1000.0 * (float)sleep_time) / (float)CH_CFG_ST_FREQUENCY;
			}
		
			if (current_rel < -1.0) {
				current_rel=-1;
			}
			if (current_rel > 1.0) {
				current_rel=1;
			}
			break;

        case ADC_CTRL_TYPE_CURRENT_REV_BUTTON_BRAKE_CENTER:
		case ADC_CTRL_TYPE_CURRENT_NOREV_BRAKE_CENTER:
		case ADC_CTRL_TYPE_CURRENT_NOREV_BRAKE_BUTTON:
		case ADC_CTRL_TYPE_CURRENT_NOREV_BRAKE_ADC:
		case ADC_CTRL_TYPE_CURRENT_REV_BUTTON_BRAKE_ADC:
			current_mode = true;
		
			if (pwr < 0.001) {
				ms_without_power += (1000.0 * (float)sleep_time) / (float)CH_CFG_ST_FREQUENCY;
			}			

			//Wheely crtl
			pwr+=pid_value; 

						
			//Hillholder
			if( mc_interface_temp_motor_filtered() > (MCCONF_L_LIM_TEMP_MOTOR_START-10.0) && hill_counter < 118*APPCONF_ADC_UPDATE_RATE_HZ ){ // wenn motor heiß nicht zwei minuten bis piepen warten
				hill_counter = 118*APPCONF_ADC_UPDATE_RATE_HZ;
			} 

			if(hill_value>0.025 && hill_counter < 120*APPCONF_ADC_UPDATE_RATE_HZ){
				pwr += hill_value + brake; 
				hill_counter++;
			}
			else if (hill_value>0.02 && hill_counter == 120*APPCONF_ADC_UPDATE_RATE_HZ){ // piepen nach 120s // 500Hz
				pwr += hill_value*2.0 + brake; 
				hill_value -= 3e-6;
				hill_counter++;
			}
			else if (hill_value>0.02 && hill_counter > 1){ // piepen nach 10s
				pwr += hill_value/2.0 + brake; 
				hill_value -= 3e-6;
				hill_counter--;
			}
			else{
				hill_counter = 0;
			}
			/*
			if (pwr >= 0.0) {
				current_rel = pwr;
			}
			
			if (pwr < 0.0 && rpm_now > 100.0) {
				current_rel = pwr;
			} else {
				mc_interface_brake_now();
			}
			*/
			
			
			//	current_rel = pwr; // Jörn 2020 06 15 Für Freeliner
			


			
			if (pwr >= 0.0) {
				current_rel = pwr;	// Vorwärts und hillholder
				if(!rev_button && rpm_now < -mcconf->hall_sl_erpm ){ // erst bremsen, wenn rückwärtsfahrt und vorwärts beschleunigt werden soll JJ 06 2022, die hall_sl_erpm kommt von mcpwm für reku rampe
					current_mode_brake = true;
				}
			} else {
				current_rel = fabsf(pwr);	// Rückwärts schieben
				current_mode_brake = true;
			}
			



			


			if ((config.ctrl_type == ADC_CTRL_TYPE_CURRENT_REV_BUTTON_BRAKE_ADC ||
			    config.ctrl_type == ADC_CTRL_TYPE_CURRENT_REV_BUTTON_BRAKE_CENTER) && rev_button) {
				current_rel = -current_rel;
			}
			if (current_rel < -1.0) { // truncate number ist wohl eleganter..., oder? JJ 06 2022
				current_rel=-1;
			}
			if (current_rel > 1.0) {
				current_rel=1;
			}
			break;

		case ADC_CTRL_TYPE_DUTY:
		case ADC_CTRL_TYPE_DUTY_REV_CENTER:
		case ADC_CTRL_TYPE_DUTY_REV_BUTTON:
			if (fabsf(pwr) < 0.001) {
				ms_without_power += (1000.0 * (float)sleep_time) / (float)CH_CFG_ST_FREQUENCY;
			}

			if (!(ms_without_power < MIN_MS_WITHOUT_POWER && config.safe_start)) {
				mc_interface_set_duty(utils_map(pwr, -1.0, 1.0, -mcconf->l_max_duty, mcconf->l_max_duty));
				send_duty = true;
			}
			break;

		case ADC_CTRL_TYPE_PID:
		case ADC_CTRL_TYPE_PID_REV_CENTER:
		case ADC_CTRL_TYPE_PID_REV_BUTTON:
			if ((pwr >= 0.0 && rpm_now > 0.0) || (pwr < 0.0 && rpm_now < 0.0)) {
				current_rel = pwr;
			} else {
				current_rel = pwr;
			}

			if (!(ms_without_power < MIN_MS_WITHOUT_POWER && config.safe_start)) {
				float speed = 0.0;
				if (pwr >= 0.0) {
					speed = pwr * mcconf->l_max_erpm;
				} else {
					speed = pwr * fabsf(mcconf->l_min_erpm);
				}

				mc_interface_set_pid_speed(speed);
				send_duty = true;
			}

			if (fabsf(pwr) < 0.001) {
				ms_without_power += (1000.0 * (float)sleep_time) / (float)CH_CFG_ST_FREQUENCY;
			}
			break;

		default:
			continue;
		}

		// If safe start is enabled and the output has not been zero for long enough
		if (ms_without_power < MIN_MS_WITHOUT_POWER && config.safe_start) {
			static int pulses_without_power_before = 0;
			if (ms_without_power == pulses_without_power_before) {
				ms_without_power = 0;
			}
			pulses_without_power_before = ms_without_power;
			mc_interface_set_brake_current(timeout_get_brake_current());

			if (config.multi_esc) {
				for (int i = 0;i < CAN_STATUS_MSGS_TO_STORE;i++) {
					can_status_msg *msg = comm_can_get_status_msg_index(i);

					if (msg->id >= 0 && UTILS_AGE_S(msg->rx_time) < MAX_CAN_AGE) {
						comm_can_set_current_brake(msg->id, timeout_get_brake_current());
					}
				}
			}

			continue;
		}

		// Reset timeout
		if(use_can_adc_input){
			// timeout wird bei can receive zurückgesetzt
		}
		else{
			timeout_reset();
		}		
		

		// If c is pressed and no throttle is used, maintain the current speed with PID control
		static bool was_pid = false;

		// Filter RPM to avoid glitches
		static float filter_buffer[RPM_FILTER_SAMPLES];
		static int filter_ptr = 0;
		filter_buffer[filter_ptr++] = mc_interface_get_rpm();
		if (filter_ptr >= RPM_FILTER_SAMPLES) {
			filter_ptr = 0;
		}

		float rpm_filtered = 0.0;
		for (int i = 0;i < RPM_FILTER_SAMPLES;i++) {
			rpm_filtered += filter_buffer[i];
		}
		rpm_filtered /= RPM_FILTER_SAMPLES;

		if (current_mode && cc_button && fabsf(pwr) < 0.001) {
			static float pid_rpm = 0.0;

			if (!was_pid) {
				was_pid = true;
				pid_rpm = rpm_filtered;
			}

			mc_interface_set_pid_speed(pid_rpm);

			// Send the same duty cycle to the other controllers
			if (config.multi_esc) {
				float current = mc_interface_get_tot_current_directional_filtered();

				for (int i = 0;i < CAN_STATUS_MSGS_TO_STORE;i++) {
					can_status_msg *msg = comm_can_get_status_msg_index(i);

					if (msg->id >= 0 && UTILS_AGE_S(msg->rx_time) < MAX_CAN_AGE) {
						comm_can_set_current(msg->id, current);
					}
				}
			}

			continue;
		}

		was_pid = false;

		// Find lowest RPM (for traction control)
		float rpm_local = mc_interface_get_rpm();
		float rpm_lowest = rpm_local;
		if (config.multi_esc) {
			for (int i = 0;i < CAN_STATUS_MSGS_TO_STORE;i++) {
				can_status_msg *msg = comm_can_get_status_msg_index(i);

				if (msg->id >= 0 && UTILS_AGE_S(msg->rx_time) < MAX_CAN_AGE) {
					float rpm_tmp = msg->rpm;

					if (fabsf(rpm_tmp) < fabsf(rpm_lowest)) {
						rpm_lowest = rpm_tmp;
					}
				}
			}
		}

		// Optionally send the duty cycles to the other ESCs seen on the CAN-bus
		if (send_duty && config.multi_esc) {
			float duty = mc_interface_get_duty_cycle_now();

			for (int i = 0;i < CAN_STATUS_MSGS_TO_STORE;i++) {
				can_status_msg *msg = comm_can_get_status_msg_index(i);

				if (msg->id >= 0 && UTILS_AGE_S(msg->rx_time) < MAX_CAN_AGE) {
					comm_can_set_duty(msg->id, duty);
				}
			}
		}

	
		if (current_mode) {
			if (current_mode_brake) {
				
				
				mc_interface_set_brake_current_rel(current_rel);
				
				// Send brake command to all ESCs seen recently on the CAN bus
				if (config.multi_esc) {
					for (int i = 0;i < CAN_STATUS_MSGS_TO_STORE;i++) {
						can_status_msg *msg = comm_can_get_status_msg_index(i);

						if (msg->id >= 0 && UTILS_AGE_S(msg->rx_time) < MAX_CAN_AGE) {
							comm_can_set_current_brake_rel(msg->id, current_rel);
						}
					}
				}
			} else {
				float current_out = current_rel;
		
				
				bool is_reverse = false;
				if (current_out < 0.0) {
					is_reverse = true;
					current_out = -current_out;
					current_rel = -current_rel;
					rpm_local = -rpm_local;
					rpm_lowest = -rpm_lowest;
				}

				// Traction control
				if (config.multi_esc) {
					for (int i = 0;i < CAN_STATUS_MSGS_TO_STORE;i++) {
						can_status_msg *msg = comm_can_get_status_msg_index(i);

						if (msg->id >= 0 && UTILS_AGE_S(msg->rx_time) < MAX_CAN_AGE) {
							if (config.tc) {
								float rpm_tmp = msg->rpm;
								if (is_reverse) {
									rpm_tmp = -rpm_tmp;
								}

								float diff = rpm_tmp - rpm_lowest;
								current_out = utils_map(diff, 0.0, config.tc_max_diff, current_rel, 0.0);
							}

							if (is_reverse) {
								comm_can_set_current_rel(msg->id, -current_out);
							} else {
								comm_can_set_current_rel(msg->id, current_out);
							}
						}
					}

					if (config.tc) {
						float diff = rpm_local - rpm_lowest;
						current_out = utils_map(diff, 0.0, config.tc_max_diff, current_rel, 0.0);
					}
				}

				if (is_reverse) {
					mc_interface_set_current_rel(-current_out);
				} else {
					//mc_interface_set_current_rel(current_out);

					// intervallstrom für FATiG
					if ( balance_conf.use_switches && 0 ){ // hier funktion ein und ausschalten!!!!!
						static float degree_counter=0;
						if(degree_counter <= 360.0){
							degree_counter += ( 360.0 / config.update_rate_hz  ) * balance_conf.tiltback_high_voltage;
						} else {
							degree_counter -= 360.0;
						}
						float cosf(float x);
						current_out *= cosf((degree_counter/180)*M_PI);
						mc_interface_set_current_rel(current_out);
					} else {
						mc_interface_set_current_rel(current_out);
					}
								
				}
			}
		}
	}
}
