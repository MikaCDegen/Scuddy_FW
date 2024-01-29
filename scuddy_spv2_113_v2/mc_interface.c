/*
	Copyright 2016 - 2018 Benjamin Vedder	benjamin@vedder.se

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

#include "mc_interface.h"
#include "mcpwm.h"
#include "mcpwm_foc.h"
#include "ledpwm.h"
#include "stm32f4xx_conf.h"
#include "hw.h"
#include "terminal.h"
#include "utils.h"
#include "ch.h"
#include "hal.h"
#include "commands.h"
#include "encoder.h"
#include "drv8301.h"
#include "drv8320s.h"
#include "drv8323s.h"
#include "drv8350.h"
#include "buffer.h"
#include "gpdrive.h"
#include "comm_can.h"
#include "shutdown.h"
#include "app.h"

#include <math.h>
#include <stdlib.h>

// Macros
#define DIR_MULT		(m_conf.m_invert_direction ? -1.0 : 1.0)

// Global variables
volatile uint16_t ADC_Value[HW_ADC_CHANNELS];
volatile int ADC_curr_norm_value[3];

// Private variables
static volatile mc_configuration m_conf;
static mc_fault_code m_fault_now;
static bool drv_config_fault;
static int m_ignore_iterations;
static volatile unsigned int m_cycles_running;
static volatile bool m_lock_enabled;
static volatile bool m_lock_override_once;
static volatile float m_motor_current_sum;
static volatile float m_input_current_sum;
static volatile float m_motor_current_iterations;
static volatile float m_input_current_iterations;
static volatile float m_motor_id_sum;
static volatile float m_motor_iq_sum;
static volatile float m_motor_id_iterations;
static volatile float m_motor_iq_iterations;
static volatile float m_motor_vd_sum;
static volatile float m_motor_vq_sum;
static volatile float m_motor_vd_iterations;
static volatile float m_motor_vq_iterations;
static volatile float m_amp_seconds;
static volatile float m_amp_seconds_charged;
static volatile float m_watt_seconds;
static volatile float m_watt_seconds_charged;
static volatile float m_position_set;
static volatile uint32_t m_odo_start;
static volatile float m_temp_fet;
static volatile float m_temp_motor;
static volatile float m_gate_driver_voltage;
static volatile float m_motor_current_unbalance;
static volatile float m_motor_current_unbalance_error_rate;

static volatile uint16_t m_enviro;
static volatile float m_brk_reku;
static volatile float m_wheely_ctrl_angle;

static volatile float m_fractional_front=1.0;
static volatile float m_fractional_rear=1.0;

static volatile uint16_t m_raw_reku_value;
static volatile uint16_t m_raw_gas_value;

static volatile float m_voltage_display;
static volatile float m_voltage_bms;
static volatile float m_current_bms;
static volatile float m_voltage_cell[17] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
static volatile float m_NTC_bms[6] = {-273.0,-273.0,-273.0,-273.0,-273.0,-273.0};


static volatile float m_bms_ah_left;
static volatile float m_bms_ah_tot;

static volatile uint16_t m_bms_fet_status;

// Sampling variables
#define ADC_SAMPLE_MAX_LEN		1000
//#define curr2_statt_gesammt
__attribute__((section(".ram4"))) static volatile int16_t m_curr0_samples[ADC_SAMPLE_MAX_LEN];
__attribute__((section(".ram4"))) static volatile int16_t m_curr1_samples[ADC_SAMPLE_MAX_LEN];
#ifdef curr2_statt_gesammt 
__attribute__((section(".ram4"))) static volatile int16_t m_curr2_samples[ADC_SAMPLE_MAX_LEN];
#endif
__attribute__((section(".ram4"))) static volatile int16_t m_ph1_samples[ADC_SAMPLE_MAX_LEN];
__attribute__((section(".ram4"))) static volatile int16_t m_ph2_samples[ADC_SAMPLE_MAX_LEN];
__attribute__((section(".ram4"))) static volatile int16_t m_ph3_samples[ADC_SAMPLE_MAX_LEN];
__attribute__((section(".ram4"))) static volatile int16_t m_vzero_samples[ADC_SAMPLE_MAX_LEN];
__attribute__((section(".ram4"))) static volatile uint8_t m_status_samples[ADC_SAMPLE_MAX_LEN];
__attribute__((section(".ram4"))) static volatile int16_t m_curr_fir_samples[ADC_SAMPLE_MAX_LEN];
__attribute__((section(".ram4"))) static volatile int16_t m_f_sw_samples[ADC_SAMPLE_MAX_LEN];
__attribute__((section(".ram4"))) static volatile int8_t m_phase_samples[ADC_SAMPLE_MAX_LEN];

static volatile int m_sample_len;
static volatile int m_sample_int;
static volatile debug_sampling_mode m_sample_mode;
static volatile debug_sampling_mode m_sample_mode_last;
static volatile int m_sample_now;
static volatile int m_sample_trigger;
static volatile float m_last_adc_duration_sample;

#if !WS2811_ENABLE
static app_configuration m_tmp_appconf;
#endif

static app_configuration m_tmp_appconf; // Jörn 3.8.2020

// Private functions
static void update_override_limits(volatile mc_configuration *conf);

// Function pointers
static void(*pwn_done_func)(void) = 0;

// Threads
static THD_WORKING_AREA(timer_thread_wa, 1024);
static THD_FUNCTION(timer_thread, arg);
static THD_WORKING_AREA(sample_send_thread_wa, 1024);
static THD_FUNCTION(sample_send_thread, arg);
static thread_t *sample_send_tp;

void mc_interface_init(mc_configuration *configuration) {

	m_conf = *configuration;
	m_fault_now = FAULT_CODE_NONE;
	drv_config_fault= false;
	m_ignore_iterations = 0;
	m_cycles_running = 0;
	m_lock_enabled = false;
	m_lock_override_once = false;
	m_motor_current_sum = 0.0;
	m_input_current_sum = 0.0;
	m_motor_current_iterations = 0.0;
	m_input_current_iterations = 0.0;
	m_motor_id_sum = 0.0;
	m_motor_iq_sum = 0.0;
	m_motor_id_iterations = 0.0;
	m_motor_iq_iterations = 0.0;
	m_motor_vd_sum = 0.0;
	m_motor_vq_sum = 0.0;
	m_motor_vd_iterations = 0.0;
	m_motor_vq_iterations = 0.0;
	m_amp_seconds = 0.0;
	m_amp_seconds_charged = 0.0;
	m_watt_seconds = 0.0;
	m_watt_seconds_charged = 0.0;
	m_position_set = 0.0;
	m_last_adc_duration_sample = 0.0;
	m_temp_fet = 0.0;
	m_temp_motor = 0.0;
	m_gate_driver_voltage = 0.0;
	m_motor_current_unbalance = 0.0;
	m_motor_current_unbalance_error_rate = 0.0;

	m_sample_len = 1000;
	m_sample_int = 1;
	m_sample_now = 0;
	m_sample_trigger = 0;
	m_sample_mode = DEBUG_SAMPLING_OFF;
	m_sample_mode_last = DEBUG_SAMPLING_OFF;

	m_brk_reku = 0; //0% auf "nix"
	m_enviro = 0;
	m_wheely_ctrl_angle = 91.0;

	m_raw_reku_value = 0;
	m_raw_gas_value = 0;
	
	m_current_bms = 9999.9;
	m_voltage_bms = 0.0;
	m_voltage_display = 0.0;
	//for (int i=0;i<17;i++){m_voltage_cell[i]= 1;}
	
	m_bms_ah_left=0.0;
	m_bms_ah_tot=0.0;
	
	m_bms_fet_status=99;

	// Start threads
	chThdCreateStatic(timer_thread_wa, sizeof(timer_thread_wa), NORMALPRIO, timer_thread, NULL);
	chThdCreateStatic(sample_send_thread_wa, sizeof(sample_send_thread_wa), NORMALPRIO - 1, sample_send_thread, NULL);

#ifdef HW_HAS_DRV8301
	drv8301_set_oc_mode(configuration->m_drv8301_oc_mode);
	drv8301_set_oc_adj(configuration->m_drv8301_oc_adj);
#elif defined(HW_HAS_DRV8320S)
	drv8320s_set_oc_mode(configuration->m_drv8301_oc_mode);
	drv8320s_set_oc_adj(configuration->m_drv8301_oc_adj);
#elif defined(HW_HAS_DRV8323S)
	drv8323s_set_oc_mode(configuration->m_drv8301_oc_mode);
	drv8323s_set_oc_adj(configuration->m_drv8301_oc_adj);
#elif defined(HW_HAS_DRV8350)
	drv8350_set_oc_mode(configuration->m_drv8301_oc_mode);
	if(drv8350_set_oc_adj(configuration->m_drv8301_oc_adj)){ // DRV Config Fault
		drv_config_fault=true;
	};
#endif

	// Initialize encoder
#if !WS2811_ENABLE
	switch (m_conf.m_sensor_port_mode) {
	case SENSOR_PORT_MODE_ABI:
		encoder_init_abi(m_conf.m_encoder_counts);
		break;

	case SENSOR_PORT_MODE_AS5047_SPI:
		encoder_init_as5047p_spi();
		break;

	case SENSOR_PORT_MODE_AD2S1205:
		encoder_init_ad2s1205_spi();
		break;

	case SENSOR_PORT_MODE_SINCOS:
		encoder_init_sincos(m_conf.foc_encoder_sin_gain, m_conf.foc_encoder_sin_offset,
							m_conf.foc_encoder_cos_gain, m_conf.foc_encoder_cos_offset,
							m_conf.foc_encoder_sincos_filter_constant);
		break;

	case SENSOR_PORT_MODE_TS5700N8501:
		conf_general_read_app_configuration(&m_tmp_appconf);
		if (m_tmp_appconf.app_to_use == APP_ADC ||
				m_tmp_appconf.app_to_use == APP_UART ||
				m_tmp_appconf.app_to_use == APP_PPM_UART ||
				m_tmp_appconf.app_to_use == APP_ADC_UART) {
			m_tmp_appconf.app_to_use = APP_NONE;
			conf_general_store_app_configuration(&m_tmp_appconf);
		}
		encoder_init_ts5700n8501();
		break;

	default:
		break;
	}
#endif

	// Initialize selected implementation
	switch (m_conf.motor_type) {
	case MOTOR_TYPE_BLDC:
	case MOTOR_TYPE_DC:
		mcpwm_init(&m_conf);
		break;

	case MOTOR_TYPE_FOC:
		mcpwm_foc_init(&m_conf);
		break;

	case MOTOR_TYPE_GPD:
		gpdrive_init(&m_conf);
		break;

	default:
		break;
	}
}

const volatile mc_configuration* mc_interface_get_configuration(void) {
	return &m_conf;
}

void mc_interface_set_configuration(mc_configuration *configuration) {
#if !WS2811_ENABLE
	if (m_conf.m_sensor_port_mode != configuration->m_sensor_port_mode) {
		encoder_deinit();
		switch (configuration->m_sensor_port_mode) {
		case SENSOR_PORT_MODE_ABI:
			encoder_init_abi(configuration->m_encoder_counts);
			break;

		case SENSOR_PORT_MODE_AS5047_SPI:
			encoder_init_as5047p_spi();
			break;

		case SENSOR_PORT_MODE_AD2S1205:
			encoder_init_ad2s1205_spi();
			break;

		case SENSOR_PORT_MODE_SINCOS:
			encoder_init_sincos(m_conf.foc_encoder_sin_gain, m_conf.foc_encoder_sin_offset,
								m_conf.foc_encoder_cos_gain, m_conf.foc_encoder_cos_offset,
								m_conf.foc_encoder_sincos_filter_constant);
			break;

		case SENSOR_PORT_MODE_TS5700N8501: {
			m_tmp_appconf = *app_get_configuration();
			if (m_tmp_appconf.app_to_use == APP_ADC ||
					m_tmp_appconf.app_to_use == APP_UART ||
					m_tmp_appconf.app_to_use == APP_PPM_UART ||
					m_tmp_appconf.app_to_use == APP_ADC_UART) {
				m_tmp_appconf.app_to_use = APP_NONE;
				conf_general_store_app_configuration(&m_tmp_appconf);
				app_set_configuration(&m_tmp_appconf);
			}
			encoder_init_ts5700n8501();
		} break;

		default:
			break;
		}
	}

	if (configuration->m_sensor_port_mode == SENSOR_PORT_MODE_ABI) {
		encoder_set_counts(configuration->m_encoder_counts);
	}
#endif

#ifdef HW_HAS_DRV8301
	drv8301_set_oc_mode(configuration->m_drv8301_oc_mode);
	drv8301_set_oc_adj(configuration->m_drv8301_oc_adj);
#elif defined(HW_HAS_DRV8320S)
	drv8320s_set_oc_mode(configuration->m_drv8301_oc_mode);
	drv8320s_set_oc_adj(configuration->m_drv8301_oc_adj);
#elif defined(HW_HAS_DRV8323S)
	drv8323s_set_oc_mode(configuration->m_drv8301_oc_mode);
	drv8323s_set_oc_adj(configuration->m_drv8301_oc_adj);
#elif defined(HW_HAS_DRV8350)
	drv8350_set_oc_mode(configuration->m_drv8301_oc_mode);
	if(drv8350_set_oc_adj(configuration->m_drv8301_oc_adj)){ // DRV Config Fault
		drv_config_fault=true;
	};
#endif

	if (m_conf.motor_type != configuration->motor_type) {
		mcpwm_deinit();
		mcpwm_foc_deinit();
		gpdrive_deinit();

		m_conf = *configuration;

		switch (m_conf.motor_type) {
		case MOTOR_TYPE_BLDC:
		case MOTOR_TYPE_DC:
			mcpwm_init(&m_conf);
			break;

		case MOTOR_TYPE_FOC:
			mcpwm_foc_init(&m_conf);
			break;

		case MOTOR_TYPE_GPD:
			gpdrive_init(&m_conf);
			break;

		default:
			break;
		}
	} else {
		m_conf = *configuration;
	}

	update_override_limits(&m_conf);
	


	switch (m_conf.motor_type) {
	case MOTOR_TYPE_BLDC:
	case MOTOR_TYPE_DC:
		mcpwm_set_configuration(&m_conf);
		break;

	case MOTOR_TYPE_FOC:
		mcpwm_foc_set_configuration(&m_conf);
		break;

	case MOTOR_TYPE_GPD:
		gpdrive_set_configuration(&m_conf);
		break;

	default:
		break;
	}
}

bool mc_interface_dccal_done(void) {
	bool ret = false;
	switch (m_conf.motor_type) {
	case MOTOR_TYPE_BLDC:
	case MOTOR_TYPE_DC:
		ret = mcpwm_is_dccal_done();
		break;

	case MOTOR_TYPE_FOC:
		ret = mcpwm_foc_is_dccal_done();
		break;

	case MOTOR_TYPE_GPD:
		ret = gpdrive_is_dccal_done();
		break;

	default:
		break;
	}

	return ret;
}

/**
 * Set a function that should be called after each PWM cycle.
 *
 * Note: this function is called from an interrupt.
 *
 * @param p_func
 * The function to be called. 0 will not call any function.
 */
void mc_interface_set_pwm_callback(void (*p_func)(void)) {
	pwn_done_func = p_func;
}

/**
 * Lock the control by disabling all control commands.
 */
void mc_interface_lock(void) {
	m_lock_enabled = true;
}

/**
 * Unlock all control commands.
 */
void mc_interface_unlock(void) {
	m_lock_enabled = false;
}

/**
 * Allow just one motor control command in the locked state.
 */
void mc_interface_lock_override_once(void) {
	m_lock_override_once = true;
}

mc_fault_code mc_interface_get_fault(void) {
	return m_fault_now;
}

const char* mc_interface_fault_to_string(mc_fault_code fault) {
	switch (fault) {
	case FAULT_CODE_NONE: return "FAULT_CODE_NONE"; break;
	case FAULT_CODE_OVER_VOLTAGE: return "FAULT_CODE_OVER_VOLTAGE"; break;
	case FAULT_CODE_UNDER_VOLTAGE: return "FAULT_CODE_UNDER_VOLTAGE"; break;
	case FAULT_CODE_DRV: return "FAULT_CODE_DRV"; break;
	case FAULT_CODE_ABS_OVER_CURRENT: return "FAULT_CODE_ABS_OVER_CURRENT"; break;
	case FAULT_CODE_OVER_TEMP_FET: return "FAULT_CODE_OVER_TEMP_FET"; break;
	case FAULT_CODE_OVER_TEMP_MOTOR: return "FAULT_CODE_OVER_TEMP_MOTOR"; break;
	case FAULT_CODE_GATE_DRIVER_OVER_VOLTAGE: return "FAULT_CODE_GATE_DRIVER_OVER_VOLTAGE"; break;
	case FAULT_CODE_GATE_DRIVER_UNDER_VOLTAGE: return "FAULT_CODE_GATE_DRIVER_UNDER_VOLTAGE"; break;
	case FAULT_CODE_MCU_UNDER_VOLTAGE: return "FAULT_CODE_MCU_UNDER_VOLTAGE"; break;
	case FAULT_CODE_BOOTING_FROM_WATCHDOG_RESET: return "FAULT_CODE_BOOTING_FROM_WATCHDOG_RESET"; break;
	case FAULT_CODE_ENCODER_SPI: return "FAULT_CODE_ENCODER_SPI"; break;
	case FAULT_CODE_ENCODER_SINCOS_BELOW_MIN_AMPLITUDE: return "FAULT_CODE_ENCODER_SINCOS_BELOW_MIN_AMPLITUDE"; break;
	case FAULT_CODE_ENCODER_SINCOS_ABOVE_MAX_AMPLITUDE: return "FAULT_CODE_ENCODER_SINCOS_ABOVE_MAX_AMPLITUDE"; break;
    case FAULT_CODE_FLASH_CORRUPTION: return "FAULT_CODE_FLASH_CORRUPTION";
    case FAULT_CODE_HIGH_OFFSET_CURRENT_SENSOR_1: return "FAULT_CODE_HIGH_OFFSET_CURRENT_SENSOR_1";
    case FAULT_CODE_HIGH_OFFSET_CURRENT_SENSOR_2: return "FAULT_CODE_HIGH_OFFSET_CURRENT_SENSOR_2";
    case FAULT_CODE_HIGH_OFFSET_CURRENT_SENSOR_3: return "FAULT_CODE_HIGH_OFFSET_CURRENT_SENSOR_3";
    case FAULT_CODE_UNBALANCED_CURRENTS: return "FAULT_CODE_UNBALANCED_CURRENTS";
    case FAULT_CODE_DRV_CONFIG: return "FAULT_CODE_DRV_CONFIG";
	case FAULT_CODE_THROTTLE_UNDERVOLTAGE: return "FAULT_CODE_THROTTLE_UNDERVOLTAGE";
	case FAULT_CODE_THROTTLE_OVERVOLTAGE: return "FAULT_CODE_THROTTLE_OVERVOLTAGE";
	case FAULT_CODE_RECU_UNDERVOLTAGE: return "FAULT_CODE_RECU_UNDERVOLTAGE";
	case FAULT_CODE_RECU_OVERVOLTAGE: return "FAULT_CODE_RECU_OVERVOLTAGE";
	default: return "FAULT_UNKNOWN"; break;
	}
}

mc_state mc_interface_get_state(void) {
	mc_state ret = MC_STATE_OFF;
	switch (m_conf.motor_type) {
	case MOTOR_TYPE_BLDC:
	case MOTOR_TYPE_DC:
		ret = mcpwm_get_state();
		break;

	case MOTOR_TYPE_FOC:
		ret = mcpwm_foc_get_state();
		break;

	default:
		break;
	}

	return ret;
}

void mc_interface_set_enviro(uint16_t enviro) {
	m_enviro = enviro;

	if (enviro & (1 << 0)) {
		LICHT_ON();
	} else {
		LICHT_OFF();
	}
	
	if (enviro & (1 << 1)) {
		BLICHT_ON();
	} else {
		BLICHT_OFF();
	}

	if (enviro & (1 << 2)) {
		BLL_ON();
	} else {
		BLL_OFF();
	}

	if (enviro & (1 << 3)) {
		BLR_ON();
	} else {
		BLR_OFF();
	}

	if (enviro & (1 << 4)) {
		TACHO_OFF(); // Freeliner Vorwärts
	} else {
		TACHO_ON();  // Freeliner Rückwärts
	}

	if (m_conf.m_out_aux_mode != OUT_AUX_MODE_ON_AFTER_10S){ // anschalten ohne CAN
		if (enviro & (1 << 5)) {
			m_conf.s_pid_allow_braking = 1; // Hillholder
		} else {
			m_conf.s_pid_allow_braking = 0;
		}

		if (enviro & (1 << 6)) {
			HUPE_ON();
		} else {
			HUPE_OFF();
		}	
	
		if (enviro & (1 << 8)) {
			m_conf.m_out_aux_mode = OUT_AUX_MODE_OFF;
		} else {
			m_conf.m_out_aux_mode = OUT_AUX_MODE_ON_AFTER_5S;
		}
		
	}	

	if (enviro & (1 << 12)) {
		// Bremse vorn gezogen
	} else {
		//
	}

	if (enviro & (1 << 13)) {
		// Bremse hinten gezogen
	} else {
		// 
	}
	
	if (enviro & (1 << 14)) {
		// Neutral für mcpwm_foc_set_current pwm ausschalten
	} else {
		// Drive
	}
	if (enviro & (1 << 15)) {
		// Hundemodus auto-reku
	} else {
		// 
	}
}
uint16_t mc_interface_get_enviro(void){
	return m_enviro;
}

	//set Enviro
void mc_interface_set_wheely_crtl(uint16_t raw){
	m_wheely_ctrl_angle = raw;
}
float mc_interface_get_wheely_crtl(void){
	return m_wheely_ctrl_angle;
}

	//set Fractional Front 
void mc_interface_set_fractional_front(float raw){
	utils_truncate_number(&raw , 0.0, 1.0);
	m_fractional_front = raw;
}
float mc_interface_get_fractional_front(void){
	return m_fractional_front;
}
	//set Fractional Rear
void mc_interface_set_fractional_rear(float raw){
	utils_truncate_number(&raw , 0.0, 1.0);
	m_fractional_rear = raw;
}
float mc_interface_get_fractional_rear(void){
	return m_fractional_rear;
}

	//Brake Reku
void mc_interface_set_brk_reku(uint16_t raw){
	//if (raw < 0) { // truncate number 
	//	raw=0;
	//}
	if (raw > 100) {
		raw=100;
	}
	m_brk_reku = raw;
}
uint16_t mc_interface_get_brk_reku(void){
	return m_brk_reku;
}
float mc_interface_get_brk_reku_float(void){
	
	return m_brk_reku/100.0;
}

	//Gas
void mc_interface_set_gas(uint16_t raw){
	m_raw_gas_value = raw;
}
uint16_t mc_interface_get_gas(void){
	return m_raw_gas_value;
}
float mc_interface_get_gas_float(void){
	return m_raw_gas_value;
}

	//Reku
void mc_interface_set_reku(uint16_t raw){
	m_raw_reku_value = raw;
}
uint16_t mc_interface_get_reku(void){
	return m_raw_reku_value;
}
float mc_interface_get_reku_float(void){
	return m_raw_reku_value;
}

	//Display Voltage
void mc_interface_set_voltage_display(float raw){
	m_voltage_display = raw;
}
float mc_interface_get_voltage_display(void){
	return m_voltage_display;
}


	//BMS Voltage
void mc_interface_set_voltage_bms(float raw){
	m_voltage_bms = raw;
}
float mc_interface_get_voltage_bms(void){
	return m_voltage_bms;
}

	//BMS current
void mc_interface_set_current_bms(float raw){
	m_current_bms = raw;
}
float mc_interface_get_current_bms(void){
	return m_current_bms;
}

	//Cell Voltage
void mc_interface_set_cell_voltage_bms(uint8_t raw_number, float raw_cell_voltage){
	m_voltage_cell[raw_number] = raw_cell_voltage;
}
float mc_interface_get_min_cell_voltage_bms(void){
	float min_cell=9.999;

	for (int i=0;i<17;i++){
		if(m_voltage_cell[i]<min_cell && m_voltage_cell[i]>0){
		min_cell=m_voltage_cell[i];
		}
	}	
	return min_cell;
}
float mc_interface_get_max_cell_voltage_bms(void){
	float max_cell=0;

	for (int i=0;i<17;i++){
		if(m_voltage_cell[i]>max_cell && m_voltage_cell[i]<6.000){
		max_cell=m_voltage_cell[i];
		}
	}	
	return max_cell;
}

//NTC Temps
void mc_interface_set_NTC_bms(uint8_t raw_number, float raw_NTC_bms){
	if(raw_number==5){
		m_NTC_bms[raw_number] = raw_NTC_bms - 20; //FETTEMP 2023 02 JJ künstlich 20 grad kühler da bei 68 batterie und 88 Fet abgeegelt werden soll
	} else {
		m_NTC_bms[raw_number] = raw_NTC_bms;
	}
}
float mc_interface_get_min_NTC_bms(void){
	float min_NTC_bms= 999.0;

	for (int i=0;i<5;i++){ // FET Temp ist unerheblich für MIN Temp
		if(m_NTC_bms[i]<min_NTC_bms && m_NTC_bms[i]>-273.0){
		min_NTC_bms=m_NTC_bms[i];
		}
	}	
	return min_NTC_bms;
}
float mc_interface_get_max_NTC_bms(void){ 
	float max_NTC_bms= -273.0;

	for (int i=0;i<6;i++){
		if(m_NTC_bms[i]>max_NTC_bms && m_NTC_bms[i]>-273.0){
			max_NTC_bms=m_NTC_bms[i];
		}
	}	
	return max_NTC_bms;
}
	
	//BMS FET STATUS
void mc_interface_set_bms_fet_status(uint16_t raw){
	m_bms_fet_status = raw;
}
uint16_t mc_interface_get_bms_fet_status(void){
	return m_bms_fet_status;
}

	//BMS Anzahl Zellen
void mc_interface_set_cell_count(uint16_t raw){
	mc_configuration mcconf = *mc_interface_get_configuration();
	//mcconf.si_battery_cells = raw;
	/*
	//evtl noch 
	V_in_min
	v_in_max
	l_battery_cut_start
	l_battery_cut_end
	//ändern
	*/
	if(mcconf.si_battery_cells != raw)
	{
		mcconf.si_battery_cells = raw;
		mcconf.l_min_vin = 				(float)raw * (MCCONF_L_MIN_VOLTAGE/MCCONF_SI_BATTERY_CELLS);
		mcconf.l_max_vin = 				((4.200*(float)raw)+2.7);
		mcconf.l_battery_cut_start = 	(float)raw * (MCCONF_L_BATTERY_CUT_START/MCCONF_SI_BATTERY_CELLS);
		mcconf.l_battery_cut_end = 		(float)raw * (MCCONF_L_BATTERY_CUT_END/MCCONF_SI_BATTERY_CELLS); 
	}

	mc_interface_set_configuration(&mcconf);
}
uint16_t mc_interface_get_cell_count(void){
	const volatile mc_configuration *conf = mc_interface_get_configuration();
	return conf->si_battery_cells;
}

//weiter

void mc_interface_set_duty(float dutyCycle) {
	if (fabsf(dutyCycle) > 0.001) {
		SHUTDOWN_RESET();
	}

	if (mc_interface_try_input()) {
		return;
	}

	switch (m_conf.motor_type) {
	case MOTOR_TYPE_BLDC:
	case MOTOR_TYPE_DC:
		mcpwm_set_duty(DIR_MULT * dutyCycle);
		break;

	case MOTOR_TYPE_FOC:
		mcpwm_foc_set_duty(DIR_MULT * dutyCycle);
		break;

	default:
		break;
	}
}

void mc_interface_set_duty_noramp(float dutyCycle) {
	if (fabsf(dutyCycle) > 0.001) {
		SHUTDOWN_RESET();
	}

	if (mc_interface_try_input()) {
		return;
	}

	switch (m_conf.motor_type) {
	case MOTOR_TYPE_BLDC:
	case MOTOR_TYPE_DC:
		mcpwm_set_duty_noramp(DIR_MULT * dutyCycle);
		break;

	case MOTOR_TYPE_FOC:
		mcpwm_foc_set_duty_noramp(DIR_MULT * dutyCycle);
		break;

	default:
		break;
	}
}

void mc_interface_set_pid_speed(float rpm) {
	if (fabsf(rpm) > 0.001) {
		SHUTDOWN_RESET();
	}

	if (mc_interface_try_input()) {
		return;
	}

	switch (m_conf.motor_type) {
	case MOTOR_TYPE_BLDC:
	case MOTOR_TYPE_DC:
		mcpwm_set_pid_speed(DIR_MULT * rpm);
		break;

	case MOTOR_TYPE_FOC:
		mcpwm_foc_set_pid_speed(DIR_MULT * rpm);
		break;

	default:
		break;
	}
}

void mc_interface_set_pid_pos(float pos) {
	SHUTDOWN_RESET();

	if (mc_interface_try_input()) {
		return;
	}

	m_position_set = pos;

	pos *= DIR_MULT;
	utils_norm_angle(&pos);

	switch (m_conf.motor_type) {
	case MOTOR_TYPE_BLDC:
	case MOTOR_TYPE_DC:
		mcpwm_set_pid_pos(pos);
		break;

	case MOTOR_TYPE_FOC:
		mcpwm_foc_set_pid_pos(pos);
		break;

	default:
		break;
	}
}

void mc_interface_set_current(float current) {
	if (fabsf(current) > 0.001) {
		SHUTDOWN_RESET();
	}

	if (mc_interface_try_input()) {
		return;
	}

	switch (m_conf.motor_type) {
	case MOTOR_TYPE_BLDC:
	case MOTOR_TYPE_DC:
		mcpwm_set_current(DIR_MULT * current);
		break;

	case MOTOR_TYPE_FOC:
		mcpwm_foc_set_current(DIR_MULT * current);
		break;

	default:
		break;
	}
}

void mc_interface_set_brake_current(float current) {
	if (fabsf(current) > 0.001) {
		SHUTDOWN_RESET();
	}

	if (mc_interface_try_input()) {
		return;
	}

	switch (m_conf.motor_type) {
	case MOTOR_TYPE_BLDC:
	case MOTOR_TYPE_DC:
		mcpwm_set_brake_current(DIR_MULT * current);
		break;

	case MOTOR_TYPE_FOC:
		mcpwm_foc_set_brake_current(DIR_MULT * current);
		break;

	case MOTOR_TYPE_GPD:
		// For timeout to stop the output
		gpdrive_set_mode(GPD_OUTPUT_MODE_NONE);
		break;

	default:
		break;
	}
}

/**
 * Set current relative to the minimum and maximum current limits.
 *
 * @param current
 * The relative current value, range [-1.0 1.0]
 */
void mc_interface_set_current_rel(float val) {
	if (fabsf(val) > 0.001){ 
		SHUTDOWN_RESET();
	}

	mc_interface_set_current(val * m_conf.lo_current_motor_max_now);
	//mc_interface_set_current(val * 165.0);
}
float mc_interface_get_lo_current_motor_max_now(void) {
	return m_conf.lo_current_motor_max_now;
}


/**
 * Set brake current relative to the minimum current limit.
 *
 * @param current
 * The relative current value, range [0.0 1.0]
 */
void mc_interface_set_brake_current_rel(float val) {
	if (fabsf(val) > 0.001){ 
		SHUTDOWN_RESET();
	}

	mc_interface_set_brake_current(val * fabsf(m_conf.lo_current_motor_min_now));
	//mc_interface_set_brake_current(val * 165.0);

}

/**
 * Set open loop current vector to brake motor.
 *
 * @param current
 * The current value.
 */
void mc_interface_set_handbrake(float current) {
	if (fabsf(current) > 0.001) {
		SHUTDOWN_RESET();
	}

	if (mc_interface_try_input()) {
		return;
	}

	switch (m_conf.motor_type) {
	case MOTOR_TYPE_BLDC:
	case MOTOR_TYPE_DC:
		// TODO: Not implemented yet, use brake mode for now.
		mcpwm_set_brake_current(current);
		break;

	case MOTOR_TYPE_FOC:
		mcpwm_foc_set_handbrake(current);
		break;

	default:
		break;
	}
}

/**
 * Set handbrake brake current relative to the minimum current limit.
 *
 * @param current
 * The relative current value, range [0.0 1.0]
 */
void mc_interface_set_handbrake_rel(float val) {
	if (fabsf(val) > 0.001) {
		SHUTDOWN_RESET();
	}

	mc_interface_set_handbrake(val * fabsf(m_conf.lo_current_motor_min_now));
}

void mc_interface_brake_now(void) {
	SHUTDOWN_RESET();

	mc_interface_set_duty(0.0);
}

/**
 * Disconnect the motor and let it turn freely.
 */
void mc_interface_release_motor(void) {
	mc_interface_set_current(0.0);
}

/**
 * Stop the motor and use braking.
 */
float mc_interface_get_duty_cycle_set(void) {
	float ret = 0.0;

	switch (m_conf.motor_type) {
	case MOTOR_TYPE_BLDC:
	case MOTOR_TYPE_DC:
		ret = mcpwm_get_duty_cycle_set();
		break;

	case MOTOR_TYPE_FOC:
		ret = mcpwm_foc_get_duty_cycle_set();
		break;

	default:
		break;
	}

	return DIR_MULT * ret;
}

float mc_interface_get_duty_cycle_now(void) {
	float ret = 0.0;

	switch (m_conf.motor_type) {
	case MOTOR_TYPE_BLDC:
	case MOTOR_TYPE_DC:
		ret = mcpwm_get_duty_cycle_now();
		break;

	case MOTOR_TYPE_FOC:
		ret = mcpwm_foc_get_duty_cycle_now();
		break;

	default:
		break;
	}

	return DIR_MULT * ret;
}

float mc_interface_get_sampling_frequency_now(void) {
	float ret = 0.0;

	switch (m_conf.motor_type) {
	case MOTOR_TYPE_BLDC:
	case MOTOR_TYPE_DC:
		ret = mcpwm_get_switching_frequency_now();
		break;

	case MOTOR_TYPE_FOC:
		ret = mcpwm_foc_get_sampling_frequency_now();
		break;

	case MOTOR_TYPE_GPD:
		ret = gpdrive_get_switching_frequency_now();
		break;

	default:
		break;
	}

	return ret;
}

float mc_interface_get_rpm(void) {
	float ret = 0.0;

	switch (m_conf.motor_type) {
	case MOTOR_TYPE_BLDC:
	case MOTOR_TYPE_DC:
		ret = mcpwm_get_rpm();
		break;

	case MOTOR_TYPE_FOC:
		ret = mcpwm_foc_get_rpm();
		break;

	default:
		break;
	}

	return DIR_MULT * ret;
}

/**
 * Get the amount of amp hours drawn from the input source.
 *
 * @param reset
 * If true, the counter will be reset after this call.
 *
 * @return
 * The amount of amp hours drawn.
 */
float mc_interface_get_amp_hours(bool reset) {
	float val = m_amp_seconds / 3600;

	if (reset) {
		m_amp_seconds = 0.0;
	}
	
	return val;
}

/**
 * Get the amount of amp hours fed back into the input source.
 *
 * @param reset
 * If true, the counter will be reset after this call.
 *
 * @return
 * The amount of amp hours fed back.
 */
float mc_interface_get_amp_hours_charged(bool reset) {
	float val = m_amp_seconds_charged / 3600;

	if (reset) {
		m_amp_seconds_charged = 0.0;
	}

	return val;
}

/**
 * Get the amount of watt hours drawn from the input source.
 *
 * @param reset
 * If true, the counter will be reset after this call.
 *
 * @return
 * The amount of watt hours drawn.
 */
float mc_interface_get_watt_hours(bool reset) {
	float val = m_watt_seconds / 3600;

	if (reset) {
		m_watt_seconds = 0.0;
	}

	return val;
}

/**
 * Get the amount of watt hours fed back into the input source.
 *
 * @param reset
 * If true, the counter will be reset after this call.
 *
 * @return
 * The amount of watt hours fed back.
 */
float mc_interface_get_watt_hours_charged(bool reset) {
	float val = m_watt_seconds_charged / 3600;

	if (reset) {
		m_watt_seconds_charged = 0.0;
	}

	return val;
}

float mc_interface_get_tot_current(void) {
	float ret = 0.0;

	switch (m_conf.motor_type) {
	case MOTOR_TYPE_BLDC:
	case MOTOR_TYPE_DC:
		ret = mcpwm_get_tot_current();
		break;

	case MOTOR_TYPE_FOC:
		ret = mcpwm_foc_get_tot_current();
		break;

	default:
		break;
	}

	return ret;
}

float mc_interface_get_tot_current_filtered(void) {
	float ret = 0.0;

	switch (m_conf.motor_type) {
	case MOTOR_TYPE_BLDC:
	case MOTOR_TYPE_DC:
		ret = mcpwm_get_tot_current_filtered();
		break;

	case MOTOR_TYPE_FOC:
		ret = mcpwm_foc_get_tot_current_filtered();
		break;

	default:
		break;
	}

	return ret;
}

float mc_interface_get_tot_current_directional(void) {
	float ret = 0.0;

	switch (m_conf.motor_type) {
	case MOTOR_TYPE_BLDC:
	case MOTOR_TYPE_DC:
		ret = mcpwm_get_tot_current_directional();
		break;

	case MOTOR_TYPE_FOC:
		ret = mcpwm_foc_get_tot_current_directional();
		break;

	default:
		break;
	}

	return DIR_MULT * ret;
}

float mc_interface_get_tot_current_directional_filtered(void) {
	float ret = 0.0;

	switch (m_conf.motor_type) {
	case MOTOR_TYPE_BLDC:
	case MOTOR_TYPE_DC:
		ret = mcpwm_get_tot_current_directional_filtered();
		break;

	case MOTOR_TYPE_FOC:
		ret = mcpwm_foc_get_tot_current_directional_filtered();
		break;

	default:
		break;
	}

	return DIR_MULT * ret;
}


float mc_interface_get_max_proz_now(void) {
	float max_proz_now=0;
	max_proz_now = utils_min_abs( ((m_conf.lo_current_max / m_conf.l_current_max) *100) , ((m_conf.lo_in_current_max / m_conf.l_in_current_max) *100) );
	return max_proz_now;
}

float mc_interface_get_min_proz_now(void) {
	float min_proz_now=0;
	min_proz_now = utils_min_abs( ((m_conf.lo_current_min / m_conf.l_current_min) *100) , ((m_conf.lo_in_current_min / m_conf.l_in_current_min) *100) );
	return min_proz_now;
}

float mc_interface_get_tot_current_in(void) {
	float ret = 0.0;

	switch (m_conf.motor_type) {
	case MOTOR_TYPE_BLDC:
	case MOTOR_TYPE_DC:
		ret = mcpwm_get_tot_current_in();
		break;

	case MOTOR_TYPE_FOC:
		ret = mcpwm_foc_get_tot_current_in();
		break;

	default:
		break;
	}

	return ret;
}

float mc_interface_get_tot_current_in_filtered(void) {
	float ret = 0.0;

	switch (m_conf.motor_type) {
	case MOTOR_TYPE_BLDC:
	case MOTOR_TYPE_DC:
		ret = mcpwm_get_tot_current_in_filtered();
		break;

	case MOTOR_TYPE_FOC:
		ret = mc_interface_get_current_bms();
		if(ret == 9999.9){
			ret = mcpwm_foc_get_tot_current_in_filtered();
		}
		break;

	default:
		break;
	}

	return ret;
}

float mc_interface_get_abs_motor_current_unbalance(void) {
	float ret = 0.0;

#ifdef HW_HAS_3_SHUNTS
	switch (m_conf.motor_type) {
	case MOTOR_TYPE_BLDC:
	case MOTOR_TYPE_DC:
		break;

	case MOTOR_TYPE_FOC:
		ret = mcpwm_foc_get_abs_motor_current_unbalance();
		break;

	default:
		break;
	}
#endif
	return ret;
}

int mc_interface_set_tachometer_value(int steps)
{
	int ret = 0;
	switch (m_conf.motor_type)
	{
	case MOTOR_TYPE_BLDC:
	case MOTOR_TYPE_DC:
		ret = mcpwm_set_tachometer_value(DIR_MULT * steps);
		break;

	case MOTOR_TYPE_FOC:
		ret = mcpwm_foc_set_tachometer_value(DIR_MULT * steps);
		break;

	default:
		break;
	}

	return DIR_MULT * ret;
}

int mc_interface_get_tachometer_value(bool reset) {
	int ret = 0;

	switch (m_conf.motor_type) {
	case MOTOR_TYPE_BLDC:
	case MOTOR_TYPE_DC:
		ret = mcpwm_get_tachometer_value(reset);
		break;

	case MOTOR_TYPE_FOC:
		ret = mcpwm_foc_get_tachometer_value(reset);
		break;

	default:
		break;
	}

	return DIR_MULT * ret;
}

uint32_t mc_interface_get_tachometer_abs_value(bool reset) {
	uint32_t ret = 0;

	switch (m_conf.motor_type) {
	case MOTOR_TYPE_BLDC:
	case MOTOR_TYPE_DC:
		ret = mcpwm_get_tachometer_abs_value(reset) ;
		break;

	case MOTOR_TYPE_FOC:
		ret = mcpwm_foc_get_tachometer_abs_value(reset); //6 ticks je ERP
		break;

	default:
		break;
	}

	return ret;
}

void mc_interface_set_tachometer_abs_value(int addition){
	mcpwm_foc_set_tachometer_abs_value(addition);

}


uint32_t mc_interface_get_odo_value(void) { // in m
	const volatile mc_configuration *conf = mc_interface_get_configuration();
	const float tacho_scale = (conf->si_wheel_diameter * M_PI) / (3.0 * conf->si_motor_poles * conf->si_gear_ratio);
	uint32_t ret = 0x12; // debugging Jörn 2021 06 23

	switch (m_conf.motor_type) {
	case MOTOR_TYPE_BLDC:
	case MOTOR_TYPE_DC:
		ret = m_odo_start + mcpwm_get_tachometer_abs_value(false) * tacho_scale;
		break;

	case MOTOR_TYPE_FOC:
		ret = m_odo_start + mcpwm_foc_get_tachometer_abs_value(false) * tacho_scale; // //6 ticks je ERP
		// nach debugging 2021 06 23 hier kann manchmal auch eine 0 zurück kommen. Gefahr!!!
		break;

	default:
		break;
	}

	return ret;
}

void mc_interface_set_odo_value(int addition){	
	m_odo_start += addition;
}


float mc_interface_get_last_inj_adc_isr_duration(void) {
	float ret = 0.0;

	switch (m_conf.motor_type) {
	case MOTOR_TYPE_BLDC:
	case MOTOR_TYPE_DC:
		ret = mcpwm_get_last_inj_adc_isr_duration();
		break;

	case MOTOR_TYPE_FOC:
		ret = mcpwm_foc_get_last_adc_isr_duration();
		break;

	case MOTOR_TYPE_GPD:
		ret = gpdrive_get_last_adc_isr_duration();
		break;

	default:
		break;
	}

	return ret;
}

float mc_interface_read_reset_avg_motor_current(void) {
	if (m_conf.motor_type == MOTOR_TYPE_GPD) {
		return gpdrive_get_current_filtered();
	}

	float res = m_motor_current_sum / m_motor_current_iterations;
	m_motor_current_sum = 0.0;
	m_motor_current_iterations = 0.0;
	return res;
}

float mc_interface_read_reset_avg_input_current(void) {
	if (m_conf.motor_type == MOTOR_TYPE_GPD) {
		return gpdrive_get_current_filtered() * gpdrive_get_modulation();
	}

	float res = m_input_current_sum / m_input_current_iterations;
	m_input_current_sum = 0.0;
	m_input_current_iterations = 0.0;
	return res;
}

/**
 * Read and reset the average direct axis motor current. (FOC only)
 *
 * @return
 * The average D axis current.
 */
float mc_interface_read_reset_avg_id(void) {
	float res = m_motor_id_sum / m_motor_id_iterations;
	m_motor_id_sum = 0.0;
	m_motor_id_iterations = 0.0;
	return DIR_MULT * res; // TODO: DIR_MULT?
}

/**
 * Read and reset the average quadrature axis motor current. (FOC only)
 *
 * @return
 * The average Q axis current.
 */
float mc_interface_read_reset_avg_iq(void) {
	float res = m_motor_iq_sum / m_motor_iq_iterations;
	m_motor_iq_sum = 0.0;
	m_motor_iq_iterations = 0.0;
	return DIR_MULT * res;
}

/**
 * Read and reset the average direct axis motor voltage. (FOC only)
 *
 * @return
 * The average D axis voltage.
 */
float mc_interface_read_reset_avg_vd(void) {
	float res = m_motor_vd_sum / m_motor_vd_iterations;
	m_motor_vd_sum = 0.0;
	m_motor_vd_iterations = 0.0;
	return DIR_MULT * res; // TODO: DIR_MULT?
}

/**
 * Read and reset the average quadrature axis motor voltage. (FOC only)
 *
 * @return
 * The average Q axis voltage.
 */
float mc_interface_read_reset_avg_vq(void) {
	float res = m_motor_vq_sum / m_motor_vq_iterations;
	m_motor_vq_sum = 0.0;
	m_motor_vq_iterations = 0.0;
	return DIR_MULT * res;
}

float mc_interface_get_pid_pos_set(void) {
	return m_position_set;
}

float mc_interface_get_pid_pos_now(void) {
	float ret = 0.0;

	switch (m_conf.motor_type) {
	case MOTOR_TYPE_BLDC:
	case MOTOR_TYPE_DC:
		ret = encoder_read_deg();
		break;

	case MOTOR_TYPE_FOC:
		ret = mcpwm_foc_get_pid_pos_now();
		break;

	default:
		break;
	}

	ret *= DIR_MULT;
	utils_norm_angle(&ret);

	return ret;
}

float mc_interface_get_last_sample_adc_isr_duration(void) {
	return m_last_adc_duration_sample;
}

void mc_interface_sample_print_data(debug_sampling_mode mode, uint16_t len, uint8_t decimation) {
	if (len > ADC_SAMPLE_MAX_LEN) {
		len = ADC_SAMPLE_MAX_LEN;
	}

	if (mode == DEBUG_SAMPLING_SEND_LAST_SAMPLES) {
		chEvtSignal(sample_send_tp, (eventmask_t) 1);
	} else {
		m_sample_trigger = -1;
		m_sample_now = 0;
		m_sample_len = len;
		m_sample_int = decimation;
		m_sample_mode = mode;
	}
}

/**
 * Get filtered MOSFET temperature. The temperature is pre-calculated, so this
 * functions is fast.
 *
 * @return
 * The filtered MOSFET temperature.
 */
float mc_interface_temp_fet_filtered(void) {
	return m_temp_fet;
}

/**
 * Get filtered motor temperature. The temperature is pre-calculated, so this
 * functions is fast.
 *
 * @return
 * The filtered motor temperature.
 */
float mc_interface_temp_motor_filtered(void) {
	return m_temp_motor;
}

/**
 * Get the battery level, based on battery settings in configuration. Notice that
 * this function is based on remaining watt hours, and not amp hours.
 *
 * @param wh_left
 * Pointer to where to store the remaining watt hours, can be null.
 *
 * @return
 * Battery level, range 0 to 1
 */






void mc_interface_set_battery_level(float raw_tot, float raw_left){
	if(raw_tot>0){
		if(m_bms_ah_tot==0) { // wird nur einmal gemacht
			mc_configuration mcconf = *mc_interface_get_configuration();
			if(SET_IN_CURRENT_MAX_BY_BATTERY && ( (SET_IN_CURRENT_MAX_BY_BATTERY * raw_tot) < MCCONF_L_IN_CURRENT_MAX) ){
				mcconf.l_in_current_max = SET_IN_CURRENT_MAX_BY_BATTERY * raw_tot;
			}
			if(SET_IN_CURRENT_MIN_BY_BATTERY && ( (SET_IN_CURRENT_MIN_BY_BATTERY * raw_tot) > MCCONF_L_IN_CURRENT_MIN) ){
				mcconf.l_in_current_min = SET_IN_CURRENT_MIN_BY_BATTERY * raw_tot; // achtung ist negativ
			}
			mc_interface_set_configuration(&mcconf);
		}
		m_bms_ah_left = raw_left;
		m_bms_ah_tot = raw_tot;
	}
}

float mc_interface_get_battery_level(float *wh_left) {
	const volatile mc_configuration *conf = mc_interface_get_configuration();
	const float v_in = GET_INPUT_VOLTAGE();
	float battery_avg_voltage = 0.0;
	float battery_avg_voltage_left = 0.0;
	float ah_left = 0;

	switch (conf->si_battery_type) {
	case BATTERY_TYPE_LIION_3_0__4_2:
		battery_avg_voltage = ((3.2 + 4.2) / 2.0) * (float)(conf->si_battery_cells);
		battery_avg_voltage_left = ((3.2 * (float)(conf->si_battery_cells) + v_in) / 2.0);
		ah_left = utils_map(v_in / (float)(conf->si_battery_cells),
				3.2, 4.2, 0.0, conf->si_battery_ah);
		break;

	case BATTERY_TYPE_LIIRON_2_6__3_6:
		battery_avg_voltage = ((2.8 + 3.6) / 2.0) * (float)(conf->si_battery_cells);
		battery_avg_voltage_left = ((2.8 * (float)(conf->si_battery_cells) + v_in) / 2.0);
		ah_left = utils_map(v_in / (float)(conf->si_battery_cells),
				2.6, 3.6, 0.0, conf->si_battery_ah);
		break;

	case BATTERY_TYPE_LEAD_ACID:
		// TODO: This does not really work for lead-acid batteries
		battery_avg_voltage = ((2.1 + 2.36) / 2.0) * (float)(conf->si_battery_cells);
		battery_avg_voltage_left = ((2.1 * (float)(conf->si_battery_cells) + v_in) / 2.0);
		ah_left = utils_map(v_in / (float)(conf->si_battery_cells),
				2.1, 2.36, 0.0, conf->si_battery_ah);
		break;

	default:
		break;
	}

	const float wh_batt_tot = conf->si_battery_ah * battery_avg_voltage;
	const float wh_batt_left = ah_left * battery_avg_voltage_left;

	if (wh_left) {
		*wh_left = wh_batt_left;
	}
	
	
	if(m_bms_ah_tot != 0.0){
		return m_bms_ah_left / m_bms_ah_tot;
	} else {
		return wh_batt_left / wh_batt_tot;
	}
	
}

/**
 * Get the speed based on wheel diameter, gearing and motor pole settings.
 *
 * @return
 * Speed, in m/s
 */
float mc_interface_get_speed(void) { // in m/s !!!!
	const volatile mc_configuration *conf = mc_interface_get_configuration();
	const float rpm = mc_interface_get_rpm() / (conf->si_motor_poles / 2.0);
	return (rpm / 60.0) * conf->si_wheel_diameter * M_PI / conf->si_gear_ratio;
}

float mc_interface_get_v_max_actual(void) { // in m/s !!!!
	const volatile mc_configuration *conf = mc_interface_get_configuration();
	const float rpm = conf->l_max_erpm / (conf->si_motor_poles / 2.0);
	return (rpm / 60.0) * conf->si_wheel_diameter * M_PI / conf->si_gear_ratio;
}

/**
 * Get the distance traveled based on wheel diameter, gearing and motor pole settings.
 *
 * @return
 * Distance traveled since boot, in meters
 */
float mc_interface_get_distance(void) {
	const volatile mc_configuration *conf = mc_interface_get_configuration();
	const float tacho_scale = (conf->si_wheel_diameter * M_PI) / (3.0 * conf->si_motor_poles * conf->si_gear_ratio); // in 6 ticks
	return mc_interface_get_tachometer_value(false) * tacho_scale;
}

/**
 * Get the absolute distance traveled based on wheel diameter, gearing and motor pole settings.
 *
 * @return
 * Absolute distance traveled since boot, in meters
 */
float mc_interface_get_distance_abs(void) {
	const volatile mc_configuration *conf = mc_interface_get_configuration();
	const float tacho_scale = (conf->si_wheel_diameter * M_PI) / (3.0 * conf->si_motor_poles * conf->si_gear_ratio);
	//const float tacho_scale = (conf->si_wheel_diameter * M_PI) / (conf->si_motor_poles * 2.0 * conf->si_gear_ratio); // in elektronischen ERPM ### 7fffFFFF* scale~=40.000km 
	return mc_interface_get_tachometer_abs_value(false) * tacho_scale;
}

setup_values mc_interface_get_setup_values(void) {
	setup_values val = {0};
	val.num_vescs = 1;

	val.ah_tot += mc_interface_get_amp_hours(false);
	val.ah_charge_tot += mc_interface_get_amp_hours_charged(false);
	val.wh_tot += mc_interface_get_watt_hours(false);
	val.wh_charge_tot += mc_interface_get_watt_hours_charged(false);
	val.current_tot += mc_interface_get_tot_current_filtered();
	val.current_in_tot += mc_interface_get_tot_current_in_filtered();

	for (int i = 0;i < CAN_STATUS_MSGS_TO_STORE;i++) {
		can_status_msg *msg = comm_can_get_status_msg_index(i);
		if (msg->id >= 0 && UTILS_AGE_S(msg->rx_time) < 0.1) {
			val.current_tot += msg->current;
			val.num_vescs++;
		}

		can_status_msg_2 *msg2 = comm_can_get_status_msg_2_index(i);
		if (msg2->id >= 0 && UTILS_AGE_S(msg2->rx_time) < 0.1) {
			val.ah_tot += msg2->amp_hours;
			val.ah_charge_tot += msg2->amp_hours_charged;
		}

		can_status_msg_3 *msg3 = comm_can_get_status_msg_3_index(i);
		if (msg3->id >= 0 && UTILS_AGE_S(msg3->rx_time) < 0.1) {
			val.wh_tot += msg3->watt_hours;
			val.wh_charge_tot += msg3->watt_hours_charged;
		}

		can_status_msg_4 *msg4 = comm_can_get_status_msg_4_index(i);
		if (msg4->id >= 0 && UTILS_AGE_S(msg4->rx_time) < 0.1) {
			val.current_in_tot += msg4->current_in;
		}
	}

	return val;
}

// MC implementation functions

/**
 * A helper function that should be called before sending commands to control
 * the motor. If the state is detecting, the detection will be stopped.
 *
 * @return
 * The amount if milliseconds left until user commands are allowed again.
 *
 */
int mc_interface_try_input(void) {
	// TODO: Remove this later
	if (mc_interface_get_state() == MC_STATE_DETECTING) {
		mcpwm_stop_pwm();
		m_ignore_iterations = MCPWM_DETECT_STOP_TIME;
	}

	int retval = m_ignore_iterations;

	if (!m_ignore_iterations && m_lock_enabled) {
		if (!m_lock_override_once) {
			retval = 1;
		} else {
			m_lock_override_once = false;
		}
	}

	switch (m_conf.motor_type) {
	case MOTOR_TYPE_BLDC:
	case MOTOR_TYPE_DC:
		if (!mcpwm_init_done()) {
			retval = 1;
		}
		break;

	case MOTOR_TYPE_FOC:
		if (!mcpwm_foc_init_done()) {
			retval = 1;
		}
		break;

	default:
		break;
	}

	return retval;
}

void mc_interface_fault_info(mc_fault_code fault) {
	
	if ( (m_fault_now == FAULT_CODE_NONE ) && (terminal_get_fault_vec_write() < 3) ) {
	
		fault_data fdata;
		fdata.fault = fault;
		fdata.current = mc_interface_get_tot_current();
		fdata.current_filtered = mc_interface_get_tot_current_filtered();
		fdata.voltage = GET_INPUT_VOLTAGE();
		fdata.voltage_display = mc_interface_get_voltage_display();
		fdata.voltage_bms = mc_interface_get_voltage_bms();
		fdata.voltage_gas = mc_interface_get_gas_float();
		fdata.voltage_recu = mc_interface_get_reku_float();
		fdata.bms_fet_status = mc_interface_get_bms_fet_status();
		fdata.gate_driver_voltage = m_gate_driver_voltage;
		fdata.duty = mc_interface_get_duty_cycle_now();
		fdata.rpm = mc_interface_get_rpm();
		fdata.tacho = mc_interface_get_tachometer_value(false);
		fdata.cycles_running = m_cycles_running;
		fdata.tim_val_samp = 0;
		fdata.tim_current_samp = 0;
		fdata.tim_top = 0;
		fdata.comm_step = mcpwm_get_comm_step();
		fdata.temperature = NTC_TEMP(ADC_IND_TEMP_MOS);

		terminal_add_fault_data(&fdata);
	}
	//m_fault_now = fault;

}

void mc_interface_fault_stop(mc_fault_code fault) {
	if (m_fault_now == fault) {
		m_ignore_iterations = m_conf.m_fault_stop_time_ms;
		return;
	}

	if ( mc_interface_dccal_done() && m_fault_now == FAULT_CODE_NONE) {
		// Sent to terminal fault logger so that all faults and their conditions
		// can be printed for debugging.
		utils_sys_lock_cnt();
		volatile int val_samp = TIM8->CCR1;
		volatile int current_samp = TIM1->CCR4;
		volatile int tim_top = TIM1->ARR;
		utils_sys_unlock_cnt();

		fault_data fdata;
		fdata.fault = fault;
		fdata.current = mc_interface_get_tot_current();
		fdata.current_filtered = mc_interface_get_tot_current_filtered();
		fdata.voltage = GET_INPUT_VOLTAGE();
		fdata.voltage_display = mc_interface_get_voltage_display();
		fdata.voltage_bms = mc_interface_get_voltage_bms();
		fdata.voltage_gas = mc_interface_get_gas_float();
		fdata.voltage_recu = mc_interface_get_reku_float();
		fdata.bms_fet_status = mc_interface_get_bms_fet_status();
		fdata.gate_driver_voltage = m_gate_driver_voltage;
		fdata.duty = mc_interface_get_duty_cycle_now();
		fdata.rpm = mc_interface_get_rpm();
		fdata.tacho = mc_interface_get_tachometer_value(false);
		fdata.cycles_running = m_cycles_running;
		fdata.tim_val_samp = val_samp;
		fdata.tim_current_samp = current_samp;
		fdata.tim_top = tim_top;
		fdata.comm_step = mcpwm_get_comm_step();
		fdata.temperature = NTC_TEMP(ADC_IND_TEMP_MOS);
#ifdef HW_HAS_DRV8301
		if (fault == FAULT_CODE_DRV) {
			fdata.drv8301_faults = drv8301_read_faults();
		}
#elif defined(HW_HAS_DRV8320S)
 		if (fault == FAULT_CODE_DRV) {
			fdata.drv8301_faults = drv8320s_read_faults();
		}
#elif defined(HW_HAS_DRV8323S)
		if (fault == FAULT_CODE_DRV) {
			fdata.drv8301_faults = drv8323s_read_faults();
 		}
#elif defined(HW_HAS_DRV8350)
		if (fault == FAULT_CODE_DRV) {
			//fdata.drv8301_faults = act_drv_fault;
			fdata.drv8301_faults = drv8350_read_faults();
 		}
#endif
		terminal_add_fault_data(&fdata);
	}

	m_ignore_iterations = m_conf.m_fault_stop_time_ms;
	
	m_fault_now = fault;

	switch (m_conf.motor_type) {
	case MOTOR_TYPE_BLDC:
	case MOTOR_TYPE_DC:
		mcpwm_stop_pwm();
		break;

	case MOTOR_TYPE_FOC:
		mcpwm_foc_stop_pwm();
		break;

	case MOTOR_TYPE_GPD:
		gpdrive_set_mode(GPD_OUTPUT_MODE_NONE);
		break;

	default:
		break;
	}

	
}

void mc_interface_mc_timer_isr(void) {
	ledpwm_update_pwm(); // LED PWM Driver update
	/*
	float winkel;
	winkel=mc_interface_get_pid_pos_now();

	if ((winkel>=0) && (winkel<90)) {
		TACHO_ON();
	} 
	if ((winkel>=180) && (winkel<270))  {
		TACHO_OFF();
	}
	*/
	const float input_voltage = GET_INPUT_VOLTAGE();

	// Check for faults that should stop the motor
	static int wrong_voltage_iterations = 0;
	if (input_voltage < m_conf.l_min_vin ||
			input_voltage > m_conf.l_max_vin) {
		wrong_voltage_iterations++;

		if ((wrong_voltage_iterations >= 20)) { // 2023 04 28 JJ geändert von 8, da nur mit 1kHz geregelt wird. da können 15Khz zu schnell sein
			mc_interface_fault_stop(input_voltage < m_conf.l_min_vin ?
					FAULT_CODE_UNDER_VOLTAGE : FAULT_CODE_OVER_VOLTAGE);
			
		}
	} else {
		wrong_voltage_iterations = 0;
	}

	// Monitor currents balance. The sum of the 3 currents should be zero
#ifdef HW_HAS_3_SHUNTS
	if (!m_conf.foc_sample_high_current) { // This won't work when high current sampling is used
		m_motor_current_unbalance = mc_interface_get_abs_motor_current_unbalance();

		if (m_motor_current_unbalance > MCCONF_MAX_CURRENT_UNBALANCE) {
			UTILS_LP_FAST(m_motor_current_unbalance_error_rate, 1.0, (1 / 20000.0));
		} else {
			UTILS_LP_FAST(m_motor_current_unbalance_error_rate, 0.0, (1 / 20000.0));
		}

		if (m_motor_current_unbalance_error_rate > MCCONF_MAX_CURRENT_UNBALANCE_RATE) {
			mc_interface_fault_stop(FAULT_CODE_UNBALANCED_CURRENTS);
		}
	}
#endif

	if (mc_interface_get_state() == MC_STATE_RUNNING) {
		m_cycles_running++;
	} else {
		m_cycles_running = 0;
	}

	if (pwn_done_func) {
		pwn_done_func();
	}

	const float current = mc_interface_get_tot_current_filtered();
	const float current_in = mc_interface_get_tot_current_in_filtered();
	m_motor_current_sum += current;
	m_input_current_sum += current_in;
	m_motor_current_iterations++;
	m_input_current_iterations++;

	m_motor_id_sum += mcpwm_foc_get_id();
	m_motor_iq_sum += mcpwm_foc_get_iq();
	m_motor_id_iterations++;
	m_motor_iq_iterations++;

	m_motor_vd_sum += mcpwm_foc_get_vd();
	m_motor_vq_sum += mcpwm_foc_get_vq();
	m_motor_vd_iterations++;
	m_motor_vq_iterations++;

	float abs_current = mc_interface_get_tot_current();
	float abs_current_filtered = current;
	if (m_conf.motor_type == MOTOR_TYPE_FOC) {
		// TODO: Make this more general
		abs_current = mcpwm_foc_get_abs_motor_current();
		abs_current_filtered = mcpwm_foc_get_abs_motor_current_filtered();
	}

	// Current fault code
	if (m_conf.l_slow_abs_current) {
		if (fabsf(abs_current_filtered) > m_conf.l_abs_current_max) {
			mc_interface_fault_stop(FAULT_CODE_ABS_OVER_CURRENT);
		}
	} else {
		if (fabsf(abs_current) > m_conf.l_abs_current_max) {
			mc_interface_fault_stop(FAULT_CODE_ABS_OVER_CURRENT);
		}
	}

	// DRV fault code
#ifdef HW_HAS_DRV8350
static int wrong_DRV_iterations = 0;
	if (IS_DRV_FAULT() || drv_config_fault) {
		wrong_DRV_iterations++;
			if ((wrong_DRV_iterations == 1)) {
				//fault_data fdata;
				//fdata.drv8301_faults = drv8350_read_faults();
				//terminal_add_fault_data(&fdata);
				//commands_printf(drv8350_faults_to_string(drv8350_read_faults()));
				
				fault_data fdata;
				if(drv_config_fault){
					fdata.fault = FAULT_CODE_DRV_CONFIG;
				}else{
					fdata.fault = FAULT_CODE_DRV;
				}	
				fdata.current = mc_interface_get_tot_current();
				fdata.current_filtered = mc_interface_get_tot_current_filtered();
				fdata.voltage = GET_INPUT_VOLTAGE();
				fdata.voltage_display = mc_interface_get_voltage_display();
				fdata.voltage_bms = mc_interface_get_voltage_bms();
				fdata.voltage_gas = mc_interface_get_gas_float();
				fdata.voltage_recu = mc_interface_get_reku_float();
				fdata.bms_fet_status = mc_interface_get_bms_fet_status();
				fdata.gate_driver_voltage = m_gate_driver_voltage;
				fdata.duty = mc_interface_get_duty_cycle_now();
				fdata.rpm = mc_interface_get_rpm();
				fdata.tacho = mc_interface_get_tachometer_value(false);
				fdata.cycles_running = m_cycles_running;
				fdata.tim_val_samp = 0;
				fdata.tim_current_samp = 0;
				fdata.tim_top = 0;
				fdata.comm_step = mcpwm_get_comm_step();
				fdata.temperature = NTC_TEMP(ADC_IND_TEMP_MOS);
				fdata.drv8301_faults = drv8350_read_faults();
				terminal_add_fault_data(&fdata);

				if(drv_config_fault){ 
					mc_interface_fault_stop(FAULT_CODE_DRV_CONFIG);
				}	

				if (fabsf(abs_current) > m_conf.l_abs_current_max) {
					mc_interface_fault_stop(FAULT_CODE_DRV);
				}
			}
		if ((wrong_DRV_iterations >= 2)) {
			mc_interface_fault_stop(FAULT_CODE_DRV);
		}
	}
	else {
		wrong_DRV_iterations = 0;
	}

#else
	if (IS_DRV_FAULT()) {
		mc_interface_fault_stop(FAULT_CODE_DRV);
	}
#endif

#ifdef HW_VERSION_AXIOM
	if( m_gate_driver_voltage > HW_GATE_DRIVER_SUPPLY_MAX_VOLTAGE) {
		mc_interface_fault_stop(FAULT_CODE_GATE_DRIVER_OVER_VOLTAGE);
	}

	if( m_gate_driver_voltage < HW_GATE_DRIVER_SUPPLY_MIN_VOLTAGE) {
		mc_interface_fault_stop(FAULT_CODE_GATE_DRIVER_UNDER_VOLTAGE);
	}
#endif

	// Watt and ah counters
	const float f_samp = mc_interface_get_sampling_frequency_now();
	if (fabsf(current) > 1.0) {
		// Some extra filtering
		static float curr_diff_sum = 0.0;
		static float curr_diff_samples = 0;

		curr_diff_sum += current_in / f_samp; // hier Ah berechnung
		curr_diff_samples += 1.0 / f_samp;

		if (curr_diff_samples >= 0.01) {
			if (curr_diff_sum > 0.0) {
				m_amp_seconds += curr_diff_sum;
				if(mc_interface_get_voltage_bms() > 0.0){
					m_watt_seconds += curr_diff_sum * mc_interface_get_voltage_bms();
				} else {
					m_watt_seconds += curr_diff_sum * input_voltage; // hier wh berechnung
				}
			} else {
				m_amp_seconds_charged -= curr_diff_sum;
				if(mc_interface_get_voltage_bms() > 0.0){
					m_watt_seconds_charged -= curr_diff_sum * mc_interface_get_voltage_bms();
				} else {
					m_watt_seconds_charged -= curr_diff_sum * input_voltage;
				}
			}

			curr_diff_samples = 0.0;
			curr_diff_sum = 0.0;
		}
	}

	bool sample = false;

	switch (m_sample_mode) {
	case DEBUG_SAMPLING_NOW:
		if (m_sample_now == m_sample_len) {
			m_sample_mode = DEBUG_SAMPLING_OFF;
			m_sample_mode_last = DEBUG_SAMPLING_NOW;
			chSysLockFromISR();
			chEvtSignalI(sample_send_tp, (eventmask_t) 1);
			chSysUnlockFromISR();
		} else {
			sample = true;
		}
		break;

	case DEBUG_SAMPLING_START:
		if (mc_interface_get_state() == MC_STATE_RUNNING || m_sample_now > 0) {
			sample = true;
		}

		if (m_sample_now == m_sample_len) {
			m_sample_mode_last = m_sample_mode;
			m_sample_mode = DEBUG_SAMPLING_OFF;
			chSysLockFromISR();
			chEvtSignalI(sample_send_tp, (eventmask_t) 1);
			chSysUnlockFromISR();
		}
		break;

	case DEBUG_SAMPLING_TRIGGER_START:
	case DEBUG_SAMPLING_TRIGGER_START_NOSEND: {
		sample = true;

		int sample_last = -1;
		if (m_sample_trigger >= 0) {
			sample_last = m_sample_trigger - m_sample_len;
			if (sample_last < 0) {
				sample_last += ADC_SAMPLE_MAX_LEN;
			}
		}

		if (m_sample_now == sample_last) {
			m_sample_mode_last = m_sample_mode;
			sample = false;

			if (m_sample_mode == DEBUG_SAMPLING_TRIGGER_START) {
				chSysLockFromISR();
				chEvtSignalI(sample_send_tp, (eventmask_t) 1);
				chSysUnlockFromISR();
			}

			m_sample_mode = DEBUG_SAMPLING_OFF;
		}

		if (mc_interface_get_state() == MC_STATE_RUNNING && m_sample_trigger < 0) {
			m_sample_trigger = m_sample_now;
		}
	} break;

	case DEBUG_SAMPLING_TRIGGER_FAULT:
	case DEBUG_SAMPLING_TRIGGER_FAULT_NOSEND: {
		sample = true;

		int sample_last = -1;
		if (m_sample_trigger >= 0) {
			sample_last = m_sample_trigger - m_sample_len;
			if (sample_last < 0) {
				sample_last += ADC_SAMPLE_MAX_LEN;
			}
		}

		if (m_sample_now == sample_last) {
			m_sample_mode_last = m_sample_mode;
			sample = false;

			if (m_sample_mode == DEBUG_SAMPLING_TRIGGER_FAULT) {
				chSysLockFromISR();
				chEvtSignalI(sample_send_tp, (eventmask_t) 1);
				chSysUnlockFromISR();
			}

			m_sample_mode = DEBUG_SAMPLING_OFF;
		}

		if (m_fault_now != FAULT_CODE_NONE && m_sample_trigger < 0) {
			m_sample_trigger = m_sample_now;
		}
	} break;

	default:
		break;
	}

	if (sample) {
		static int a = 0;
		a++;

		if (a >= m_sample_int) {
			a = 0;

			if (m_sample_now >= ADC_SAMPLE_MAX_LEN) {
				m_sample_now = 0;
			}

			int16_t zero;
			if (m_conf.motor_type == MOTOR_TYPE_FOC) {
				zero = (ADC_V_L1 + ADC_V_L2 + ADC_V_L3) / 3;
				m_phase_samples[m_sample_now] = (uint8_t)(mcpwm_foc_get_phase() / 360.0 * 250.0);
//				m_phase_samples[m_sample_now] = (uint8_t)(mcpwm_foc_get_phase_observer() / 360.0 * 250.0);
//				float ang = utils_angle_difference(mcpwm_foc_get_phase_observer(), mcpwm_foc_get_phase_encoder()) + 180.0;
//				m_phase_samples[m_sample_now] = (uint8_t)(ang / 360.0 * 250.0);
			} else {
				zero = mcpwm_vzero;
				m_phase_samples[m_sample_now] = 0;
			}

			if (mc_interface_get_state() == MC_STATE_DETECTING) {
				m_curr0_samples[m_sample_now] = (int16_t)mcpwm_detect_currents[mcpwm_get_comm_step() - 1];
				m_curr1_samples[m_sample_now] = (int16_t)mcpwm_detect_currents_diff[mcpwm_get_comm_step() - 1];

				m_ph1_samples[m_sample_now] = (int16_t)mcpwm_detect_voltages[0];
				m_ph2_samples[m_sample_now] = (int16_t)mcpwm_detect_voltages[1];
				m_ph3_samples[m_sample_now] = (int16_t)mcpwm_detect_voltages[2];
			} else {
				m_curr0_samples[m_sample_now] = ADC_curr_norm_value[0];
				m_curr1_samples[m_sample_now] = ADC_curr_norm_value[1];
				#ifdef curr2_statt_gesammt 
				m_curr2_samples[m_sample_now] = ADC_curr_norm_value[2];
				#endif

				m_ph1_samples[m_sample_now] = ADC_V_L1 - zero;
				m_ph2_samples[m_sample_now] = ADC_V_L2 - zero;
				m_ph3_samples[m_sample_now] = ADC_V_L3 - zero;
			}

			m_vzero_samples[m_sample_now] = zero;
			m_curr_fir_samples[m_sample_now] = (int16_t)(mc_interface_get_tot_current() * (8.0 / FAC_CURRENT));
			m_f_sw_samples[m_sample_now] = (int16_t)(f_samp / 10.0);
			m_status_samples[m_sample_now] = mcpwm_get_comm_step() | (mcpwm_read_hall_phase() << 3);

			m_sample_now++;

			m_last_adc_duration_sample = mc_interface_get_last_inj_adc_isr_duration();
		}
	}
}

void mc_interface_adc_inj_int_handler(void) {
	switch (m_conf.motor_type) {
	case MOTOR_TYPE_BLDC:
	case MOTOR_TYPE_DC:
		mcpwm_adc_inj_int_handler();
		break;

	case MOTOR_TYPE_FOC:
		break;

	default:
		break;
	}
}

/**
 * Update the override limits for a configuration based on MOSFET temperature etc.
 *
 * @param conf
 * The configaration to update.
 */
static void update_override_limits(volatile mc_configuration *conf) {
	float v_in = GET_INPUT_VOLTAGE() ;
	static float v_in_filtered_fast = MCCONF_L_MIN_VOLTAGE ;
	v_in_filtered_fast = v_in * 0.5f + v_in_filtered_fast * 0.5f ; // V_in Glätten für Spannungsregler
	/*
	if ( v_in > conf->l_max_vin ){
		v_in_filtered_fast = v_in ;
	} else {
		UTILS_LP_FAST(v_in_filtered_fast, v_in, 0.5);
	}
	*/

	//v_in = GET_INPUT_VOLTAGE() * 0.5f + v_in * 0.5f ; // V_in Glätten für Spannungsregler
	
	static float v_in_filtered_slow;
	UTILS_LP_FAST(v_in_filtered_slow, v_in, 0.05);

	const float min_cell = mc_interface_get_min_cell_voltage_bms();
	const float max_cell = mc_interface_get_max_cell_voltage_bms();

	const float min_cell_temp = mc_interface_get_min_NTC_bms();
	const float max_cell_temp = mc_interface_get_max_NTC_bms();

	float rpm_now = mc_interface_get_rpm();
	// Filter RPM
	static float filter_rpm = 0.0;
	UTILS_LP_FAST(filter_rpm, rpm_now, conf->s_pid_kd_filter);
	rpm_now = filter_rpm;

	float duty_abs = fabsf(mc_interface_get_duty_cycle_now());
	duty_abs *= SQRT3_BY_2;	
	
	// float mod_q_now_abs = fabsf(mcpwm_foc_get_mod_q_now());
	//ggfs mod_q filtern? es quietscht in der watt und battsrombegrenzung 2023 03 23
	static float mod_q_now_abs = 0.01;
	mod_q_now_abs = fabsf(mcpwm_foc_get_mod_q_now()) * 0.2f + mod_q_now_abs * 0.8f ; 
	
	UTILS_LP_FAST(m_temp_fet, NTC_TEMP(ADC_IND_TEMP_MOS), 0.1);
	//old JJ 2022 05
	//UTILS_LP_FAST(m_temp_motor, NTC_TEMP_MOTOR(conf->m_ntc_motor_beta), 0.01);
	//new JJ 2022 05 with KTY83_122
 	if( conf->m_ntc_motor_beta == 122) {
		float temp_motor = 0.0;
		float res = NTC_RES_MOTOR(ADC_Value[ADC_IND_TEMP_MOTOR]);
		float pow2 = res * res;
		temp_motor = 0.0000000102114874947423 * pow2 * res - 0.000069967997703501 * pow2 +
				0.243402040973194 * res - 160.145048329356;
		UTILS_LP_FAST(m_temp_motor, temp_motor, 0.01);
	} else {
		UTILS_LP_FAST(m_temp_motor, NTC_TEMP_MOTOR(conf->m_ntc_motor_beta), 0.01);
	}

	// hier abfrage wieviele Vescs im system
	uint8_t number_of_vescs = 1;
	#ifdef DIVIDE_WATTAGE_BY_NBR_OF_VESCS
		for (int i = 0;i < CAN_STATUS_MSGS_TO_STORE;i++) {
			can_status_msg *msg = comm_can_get_status_msg_index(i);
			if (msg->id >= 0 && UTILS_AGE_S(msg->rx_time) < 0.1) {
				number_of_vescs++;
			}
		}
	#endif
	

#ifdef HW_VERSION_AXIOM
	UTILS_LP_FAST(m_gate_driver_voltage, GET_GATE_DRIVER_SUPPLY_VOLTAGE(), 0.01);
#endif
	
	const float l_current_min_tmp = conf->l_current_min;
	const float l_current_max_tmp = conf->l_current_max;

	// Temperature MOSFET
	float lo_min_mos = l_current_min_tmp;
	float lo_max_mos = l_current_max_tmp;
	if (m_temp_fet < conf->l_temp_fet_start) {
		// Keep values
	} else if (m_temp_fet > conf->l_temp_fet_end) {
		lo_min_mos = 0.0;
		lo_max_mos = 0.0;
		mc_interface_fault_stop(FAULT_CODE_OVER_TEMP_FET);
	} else {
		float maxc = fabsf(l_current_max_tmp);
		if (fabsf(l_current_min_tmp) > maxc) {
			maxc = fabsf(l_current_min_tmp);
		}

		maxc = utils_map(m_temp_fet, conf->l_temp_fet_start, conf->l_temp_fet_end, maxc, 0.0);

		if (fabsf(l_current_min_tmp) > maxc) {
			lo_min_mos = SIGN(l_current_min_tmp) * maxc;
		}

		if (fabsf(l_current_max_tmp) > maxc) {
			lo_max_mos = SIGN(l_current_max_tmp) * maxc;
		}
	}

	// Temperature MOTOR
	float lo_min_mot = l_current_min_tmp;
	float lo_max_mot = l_current_max_tmp;
	if (m_temp_motor < conf->l_temp_motor_start) {
		// Keep values
	} else if (m_temp_motor > conf->l_temp_motor_end+10) {
		lo_min_mot = 0.0;
		lo_max_mot = 0.0;
		mc_interface_fault_stop(FAULT_CODE_OVER_TEMP_MOTOR);
	} else if (m_temp_motor > conf->l_temp_motor_end) {
		lo_min_mot = 0.0;
		lo_max_mot = 0.0;
	} else {
		float maxc = fabsf(l_current_max_tmp);
		if (fabsf(l_current_min_tmp) > maxc) {
			maxc = fabsf(l_current_min_tmp);
		}

		maxc = utils_map(m_temp_motor, conf->l_temp_motor_start, conf->l_temp_motor_end, maxc, 0.0);

		if (fabsf(l_current_min_tmp) > maxc) {
			lo_min_mot = SIGN(l_current_min_tmp) * maxc;
		}

		if (fabsf(l_current_max_tmp) > maxc) {
			lo_max_mot = SIGN(l_current_max_tmp) * maxc;
		}
	}

	// Decreased temperatures during acceleration
	// in order to still have braking torque available
	const float temp_fet_accel_start   = utils_map(conf->l_temp_accel_dec, 0.0, 1.0, conf->l_temp_fet_start, 25.0);
	const float temp_fet_accel_end     = utils_map(conf->l_temp_accel_dec, 0.0, 1.0, conf->l_temp_fet_end, 25.0);
	const float temp_motor_accel_start = utils_map(conf->l_temp_accel_dec, 0.0, 1.0, conf->l_temp_motor_start, 25.0);
	const float temp_motor_accel_end   = utils_map(conf->l_temp_accel_dec, 0.0, 1.0, conf->l_temp_motor_end, 25.0);

	float lo_fet_temp_accel = l_current_max_tmp;;
	if (m_temp_fet < temp_fet_accel_start) {
		// Keep values
	} else if (m_temp_fet > temp_fet_accel_end) {
		lo_fet_temp_accel = 0.0;
	} else {
		lo_fet_temp_accel = utils_map(m_temp_fet, temp_fet_accel_start, temp_fet_accel_end, 
														l_current_max_tmp, 0.0);
	}

	float lo_motor_temp_accel = l_current_max_tmp;
	if (m_temp_motor < temp_motor_accel_start) {
		// Keep values
	} else if (m_temp_motor > temp_motor_accel_end) {
		lo_motor_temp_accel = 0.0;
	} else {
		lo_motor_temp_accel = utils_map(m_temp_motor, temp_motor_accel_start, temp_motor_accel_end, 
															l_current_max_tmp, 0.0);
	}
	

	float lo_max = utils_min_abs(lo_max_mos, lo_max_mot);
	float lo_min = utils_min_abs(lo_min_mos, lo_min_mot);

	lo_max = utils_min_abs(lo_max, lo_fet_temp_accel);
	lo_max = utils_min_abs(lo_max, lo_motor_temp_accel);

	if (lo_max < conf->cc_min_current) {
		lo_max = conf->cc_min_current;
	}

	if (lo_min > -conf->cc_min_current) {
		lo_min = -conf->cc_min_current;
	}

	conf->lo_current_max = lo_max;
	conf->lo_current_min = lo_min;

	//ab hier Batterieströme

	

	// Battery cutoff
	float lo_in_max_batt = 0.0;
	if (v_in_filtered_fast > conf->l_battery_cut_start) {
		lo_in_max_batt = conf->l_in_current_max;
	} else if (v_in_filtered_fast < conf->l_battery_cut_end) {
		lo_in_max_batt = 0.0;
	} else {
		lo_in_max_batt = utils_map(v_in_filtered_fast, conf->l_battery_cut_start, conf->l_battery_cut_end, 
											conf->l_in_current_max, 0.0);
	}


	// Max Recu Voltage cutoff 	// von Jörn
	/*#ifdef METOR
	static float lo_in_min_batt = 0.0;
	if (v_in_filtered_fast < (conf->l_max_vin-2.0)) { // start der Regelung fix 3V unter U Max  // JJ 2023 07 03 von 2 auf 3 V angepasst
		lo_in_min_batt =  conf->l_in_current_min ;
	} else if (v_in_filtered_fast > (conf->l_max_vin-1.0)) {	//Ladeschluss 58,8V --> 59,8V einstellen
		lo_in_min_batt = 0.0;
	} else {
		lo_in_min_batt = utils_map(v_in_filtered_fast, (conf->l_max_vin-2.0), (conf->l_max_vin-1.0),				// hier auch -2V fix
				 									  conf->l_in_current_min, 0.0) ;
	}
	#else */
	static float lo_in_min_batt = 0.0;
	if (v_in_filtered_fast < (conf->l_max_vin-4.0)) { // start der Regelung fix 3V unter U Max  // JJ 2023 07 03 von 2 auf 3 V angepasst
		lo_in_min_batt = utils_min_abs( (lo_in_min_batt - 0.01) , conf->l_in_current_min );
		//lo_in_min_batt =  conf->l_in_current_min ;
	} else if (v_in_filtered_fast > (conf->l_max_vin-2.0)) {	//Ladeschluss 58,8V --> 59,8V einstellen
		lo_in_min_batt = 0.2*lo_in_min_batt;
	} else {
		lo_in_min_batt = utils_min_abs( (lo_in_min_batt - 0.01) , ( utils_map(v_in_filtered_fast, conf->l_max_vin-4.0, conf->l_max_vin-2.0,				// hier auch -2V fix
				 															 conf->l_in_current_min, 0.2*lo_in_min_batt)) );
		//lo_in_min_batt = utils_map(v_in_filtered_fast, (conf->l_max_vin-3.0), (conf->l_max_vin-1.0),				// hier auch -2V fix
		//		 									  conf->l_in_current_min, 0.0) ;
	}
	
	
	// hier auch noch MIN CAN einzelzell spannungen abfragen und lo_in_max_batt weiter reduzieren
	#define CELL_MIN_ADDITION 0.001 // 0,001A * 1000/s mehr ( 1 A / sec )
	//#define CELL_MIN_START 2.900
	//#define CELL_MIN_STOP 2.500
	#define CELL_MIN_START (conf->l_battery_cut_start/conf->si_battery_cells)
	#define CELL_MIN_STOP (conf->l_battery_cut_end/conf->si_battery_cells)
	static float lo_in_max_cell=99999.0;
	if (min_cell > CELL_MIN_START) {
		if(lo_in_max_cell < conf->l_in_current_max){
			lo_in_max_cell += CELL_MIN_ADDITION;
		} else{
			lo_in_max_cell = conf->l_in_current_max;
		} 
	} else if (min_cell < CELL_MIN_STOP) {
		lo_in_max_cell = 0.0;
	} else {
		lo_in_max_cell = utils_min_abs(lo_in_max_cell+CELL_MIN_ADDITION, utils_map(min_cell, CELL_MIN_START, CELL_MIN_STOP, 
																							conf->l_in_current_max, 0.0) );
		// 0,001A * 1000/s mehr ( 1 A / sec )
	}

	/*
	// hier auch noch MAX CAN einzelzell spannungen abfragen und recu weiter reduzieren
	#define CELL_MAX_ADDITION 0.001 // 0,001A * 1000/s mehr ( 1 A / sec )
	#define CELL_MAX_START 4.200
	#define CELL_MAX_STOP 4.280
	static float lo_in_min_cell=-99999.0;
	if (max_cell < CELL_MAX_START) {
		if(lo_in_min_cell > conf->l_in_current_min){
			lo_in_min_cell -= CELL_MAX_ADDITION;
		} else{
			lo_in_min_cell = conf->l_in_current_min;
		} 
	} else if (max_cell > CELL_MAX_STOP) {
		lo_in_min_cell = 0.0;
	} else {
		lo_in_min_cell = utils_min_abs(lo_in_min_cell-CELL_MAX_ADDITION, utils_map(max_cell, CELL_MAX_START, CELL_MAX_STOP, 
																							conf->l_in_current_min, 0.0) );
	}
	*/

	#define CELL_MAX_COUNTER (conf->l_in_current_min / 7000.0)  // ACHTUNG ist NEGATIV
	#define CELL_MAX_START 4.050
	#define CELL_MAX_STOP 4.280
	#define CELL_MAX_CRITICAL 4.450
	static float lo_in_min_cell = -99999.9;
	if(lo_in_min_cell < conf->l_in_current_min){
		lo_in_min_cell = conf->l_in_current_min; // init
	} 
	if (max_cell < CELL_MAX_START) {
			lo_in_min_cell = conf->l_in_current_min;
	} else if (max_cell > (CELL_MAX_STOP + 0.030) ) {
		if(lo_in_min_cell < 0.0 ){ 
			lo_in_min_cell -= CELL_MAX_COUNTER *2 ; // in 3,5 sec auf 0
		}	
	} else if (max_cell > CELL_MAX_CRITICAL) {
		lo_in_min_cell = 0.0; // sofort auf 0	
	} else if (max_cell > CELL_MAX_STOP) {
		if(lo_in_min_cell < 0.0 ){ 
			lo_in_min_cell -= CELL_MAX_COUNTER; // in 7 sec auf 0
		}	
	} else {
		if(lo_in_min_cell > conf->l_in_current_min ){ 
			lo_in_min_cell += CELL_MAX_COUNTER; // in 7 sec wieder auf vollstrom
		}																					
	}


	//Batt Hot
	#define CELL_MAX_TEMP_START 60.0
	#define CELL_MAX_TEMP_STOP  68.0
	float lo_in_max_cell_temp_hot=0.0;
	float lo_in_min_cell_temp_hot=0.0;
	if (max_cell_temp > CELL_MAX_TEMP_STOP) {
		lo_in_max_cell_temp_hot = 4.0;
		lo_in_min_cell_temp_hot = -1.0;
	} else if ( (max_cell_temp < CELL_MAX_TEMP_START) || (max_cell_temp == -273.0) ) {
		lo_in_max_cell_temp_hot = conf->l_in_current_max;
		lo_in_min_cell_temp_hot = conf->l_in_current_min;
	} else {
		lo_in_max_cell_temp_hot = utils_map(max_cell_temp, CELL_MAX_TEMP_START, CELL_MAX_TEMP_STOP, 
													conf->l_in_current_max, 4.0);
		lo_in_min_cell_temp_hot = utils_map(max_cell_temp, CELL_MAX_TEMP_START, CELL_MAX_TEMP_STOP, 
													conf->l_in_current_min, -1.0);
	}

	//Batt cold
	#define CELL_MIN_TEMP_START 10.0
	#define CELL_MIN_TEMP_RECU_STOP 2.0
	#define CELL_MIN_TEMP_STOP -15.0
	float lo_in_max_cell_temp_cold=0.0;
	float lo_in_min_cell_temp_cold=0.0;
	if ( (min_cell_temp > CELL_MIN_TEMP_START) || (min_cell_temp == -273.0) ) { /// >10
		lo_in_max_cell_temp_cold = conf->l_in_current_max;
		lo_in_min_cell_temp_cold = conf->l_in_current_min;
	} else if (min_cell_temp < CELL_MIN_TEMP_STOP) { // < -20
		lo_in_max_cell_temp_cold = 4.0;
		lo_in_min_cell_temp_cold = -1.0;
	} else if (min_cell_temp < CELL_MIN_TEMP_RECU_STOP) { // -20 bis 2
		lo_in_max_cell_temp_cold = utils_map(min_cell_temp, CELL_MIN_TEMP_START, CELL_MIN_TEMP_STOP, 
													conf->l_in_current_max, 4.0);
		lo_in_min_cell_temp_cold = -1.0;// ab hier keine Recu mehr
	} else { 									// 2 bis 10
		lo_in_max_cell_temp_cold = utils_map(min_cell_temp, CELL_MIN_TEMP_START, CELL_MIN_TEMP_STOP, 
													conf->l_in_current_max, 4.0);
		lo_in_min_cell_temp_cold = utils_map(min_cell_temp, CELL_MIN_TEMP_START, CELL_MIN_TEMP_RECU_STOP, 
													conf->l_in_current_min, -1.0);
	}

	// mindestwerte bestimmen
	const float lo_in_max = utils_min_abs(lo_in_max_cell, utils_min_abs(lo_in_max_batt, utils_min_abs(lo_in_max_cell_temp_hot, lo_in_max_cell_temp_cold)) ); // entladen max
	const float lo_in_min = utils_min_abs(lo_in_min_cell, utils_min_abs(lo_in_min_batt, utils_min_abs(lo_in_min_cell_temp_hot, lo_in_min_cell_temp_cold)) ); // recu max

	conf->lo_in_current_max = utils_min_abs(conf->l_in_current_max, lo_in_max); // noch ohne watt limit, für die Prozentanzeige
	conf->lo_in_current_min = utils_min_abs(conf->l_in_current_min, lo_in_min);
	
	//RPM_limits

	const float dt = 0.001; //THD eine MS

		// RPM max
		float lo_max_watt_rpm = 0.0;
		static float i_term_rpm_max = 0.0;
		static float prev_error_rpm_max = 0.0;
		float p_term_rpm_max;
		float d_term_rpm_max;

		//const float rpm = mcpwm_foc_get_rpm();
		float error_rpm_max = conf->l_max_erpm - rpm_now;

		// Compute parameters
		p_term_rpm_max = error_rpm_max * conf->s_pid_kp * (1.0 / 20.0); 
		i_term_rpm_max += error_rpm_max * (conf->s_pid_ki * dt) * (1.0 / 20.0); 
		d_term_rpm_max = (error_rpm_max - prev_error_rpm_max) * (conf->s_pid_kd / dt) * (1.0 / 20.0);

		// RPM_Limit Fault
		if(0){
			if(p_term_rpm_max < -1.1){
 			mc_interface_fault_stop(FAULT_CODE_ENCODER_SINCOS_ABOVE_MAX_AMPLITUDE);
			}
		} 

		// Filter D
		static float d_filter_rpm_max = 0.0;
		UTILS_LP_FAST(d_filter_rpm_max, d_term_rpm_max, conf->s_pid_kd_filter);
		d_term_rpm_max = d_filter_rpm_max;

		// I-term wind-up protection
		utils_truncate_number(&p_term_rpm_max, -1.0, 1.0);	
		if ( (p_term_rpm_max + i_term_rpm_max) > 1.0 ){
			i_term_rpm_max = 1.0 - p_term_rpm_max;
		}
		if ( (p_term_rpm_max + i_term_rpm_max) < -0.0 ){ // änderung 08 2020 - i wurde zu schnell klein
			i_term_rpm_max = -0.0 - p_term_rpm_max; // rückholen aus viel zu schnell ohne negativen überschwinger um erst wieder i zu produzieren
			//i_term_rpm_max = -0.1 - p_term_rpm_max; // rückholen aus viel zu schnell ohne negativen überschwinger um erst wieder i zu produzieren
		}		
		utils_truncate_number(&i_term_rpm_max, 0.0, 1.0);

		// Store previous error
		prev_error_rpm_max = error_rpm_max;

		// Calculate output
		float output_rpm_max = p_term_rpm_max + i_term_rpm_max + d_term_rpm_max;
		utils_truncate_number(&output_rpm_max, 0.0, 1.0);
		lo_max_watt_rpm = MCCONF_L_WATT_MAX * output_rpm_max;

		
		
		

		// RPM min
		float lo_min_watt_rpm = 0.0;
		static float i_term_rpm_min = 0.0;
		static float prev_error_rpm_min = 0.0;
		float p_term_rpm_min;
		float d_term_rpm_min;

		float error_rpm_min = -conf->l_min_erpm + rpm_now;

		// Compute parameters
		p_term_rpm_min = error_rpm_min * conf->s_pid_kp * (1.0 / 20.0);
		i_term_rpm_min += error_rpm_min * (conf->s_pid_ki * dt) * (1.0 / 20.0);
		d_term_rpm_min = (error_rpm_min - prev_error_rpm_min) * (conf->s_pid_kd / dt) * (1.0 / 20.0);

		// Filter D
		static float d_filter_rpm_min = 0.0;
		UTILS_LP_FAST(d_filter_rpm_min, d_term_rpm_min, conf->s_pid_kd_filter);
		d_term_rpm_min = d_filter_rpm_min;

		// I-term wind-up protection
		utils_truncate_number(&p_term_rpm_min, -1.0, 1.0);	
		if ( (p_term_rpm_min + i_term_rpm_min) > 1.0 ){
			i_term_rpm_min = 1.0 - p_term_rpm_min;
		}
		if ( (p_term_rpm_min + i_term_rpm_min) < 0.0 ){ // änderung 08 2020 - i wurde zu schnell klein
			i_term_rpm_min = 0.0 - p_term_rpm_min;
		}		
		utils_truncate_number(&i_term_rpm_min, 0.0, 1.0);

		// Store previous error
		prev_error_rpm_min = error_rpm_min;

		// Calculate output
		float output_rpm_min = p_term_rpm_min + i_term_rpm_min + d_term_rpm_min;
		utils_truncate_number(&output_rpm_min, 0.0, 1.0);
		lo_min_watt_rpm = MCCONF_L_WATT_MAX * output_rpm_min;
		
	/*
	lo_max = utils_min_abs(lo_max, lo_max_rpm);
	if( !palReadPad(TACHO_GPIO, TACHO_PIN) ){ /// ?????? was soll das? Rückwärts beschleunigen?
		lo_max = utils_min_abs(lo_max, lo_min_rpm); 
	}
	*/

	// Wattage limits in Battcurrent 
	const float lo_in_max_watt = utils_min_abs( (conf->l_watt_max / number_of_vescs) / v_in_filtered_slow, utils_min_abs( lo_max_watt_rpm / v_in_filtered_slow , lo_min_watt_rpm / v_in_filtered_slow ) );
	const float lo_in_min_watt = (conf->l_watt_min / number_of_vescs) / v_in_filtered_slow;

	// Maximum current right now


	//Fractional calculations JJ 03 2023
	#if defined(FRONT)
		const float l_current_max_scl_frac = conf->l_current_max_scale * m_fractional_front;
	#elif defined(REAR)
		const float l_current_max_scl_frac = conf->l_current_max_scale * m_fractional_rear;
	#else
		const float l_current_max_scl_frac = conf->l_current_max_scale;
	#endif
	
	// TODO: This is not an elegant solution.
	if (m_conf.motor_type == MOTOR_TYPE_FOC) {

		// old bis 13 05 2022
		//if (duty_abs < 0.01) {duty_abs = 0.01;}
		//	conf->lo_current_motor_max_now = utils_min_abs(conf->lo_current_max, (utils_min_abs(lo_in_max_watt, conf->lo_in_current_max) / duty_abs) );
		//	conf->lo_current_motor_min_now = utils_min_abs(conf->lo_current_min, (utils_min_abs(lo_in_min_watt, conf->lo_in_current_min) / duty_abs) );
		//new // ca 50W bei 2200W im scuddy
		if (mod_q_now_abs < 0.01) {mod_q_now_abs = 0.01;} 
		conf->lo_current_motor_max_now = utils_min_abs(	(conf->lo_current_max * l_current_max_scl_frac), 
										(utils_min_abs(	lo_in_max_watt, 
														(conf->lo_in_current_max / number_of_vescs) ) / mod_q_now_abs) );

		conf->lo_current_motor_min_now = utils_min_abs(	(conf->lo_current_min * conf->l_current_min_scale), 
										(utils_min_abs(	lo_in_min_watt, 
														(conf->lo_in_current_min / number_of_vescs) ) / mod_q_now_abs) );
		
		/* eventuell so: so macht es die mc_pwm_foc // ja, umgesetzt 13 05 2022
		const float mod_q = m_motor_state.mod_q;
		if (mod_q > 0.001) {
			utils_truncate_number(&iq_set_tmp, m_conf->lo_in_current_min / mod_q, m_conf->lo_in_current_max / mod_q);
		} else if (mod_q < -0.001) {
			utils_truncate_number(&iq_set_tmp, m_conf->lo_in_current_max / mod_q, m_conf->lo_in_current_min / mod_q);
		}
		*/
		
	} else { 

	// Note: The above code should work, but many people have reported issues with it. Leaving it
	// disabled for now until I have done more investigation.
	conf->lo_current_motor_max_now = conf->lo_current_max;
	conf->lo_current_motor_min_now = conf->lo_current_min;
	}	
}

static THD_FUNCTION(timer_thread, arg) {
	(void)arg;

	chRegSetThreadName("mcif timer");

	for(;;) {
		static bool tacho_save_flag = true;
		// Decrease fault iterations
		if (m_ignore_iterations > 0) {
			m_ignore_iterations--;
		} else {
			if ( (!IS_DRV_FAULT()) && (fabsf(mc_interface_get_rpm())<=20.0)) {
				m_fault_now = FAULT_CODE_NONE;
				tacho_save_flag = true;
			} 
		}

		update_override_limits(&m_conf);
		
		if( (m_fault_now == FAULT_CODE_UNDER_VOLTAGE) && tacho_save_flag ){
				// app wert setzen
				// app config schreiben --> km speichern
				save_odo_value(mc_interface_get_odo_value());
				tacho_save_flag = false;
		}

		// Update auxiliary output
		switch (m_conf.m_out_aux_mode) {
			case OUT_AUX_MODE_OFF:
				AUX_OFF();
				break;

			case OUT_AUX_MODE_ON_AFTER_2S:
				if (chVTGetSystemTimeX() >= MS2ST(200) && (GET_INPUT_VOLTAGE() > m_conf.l_battery_cut_end) ) {
					AUX_ON();
				}
				break;

			case OUT_AUX_MODE_ON_AFTER_5S:
				if (chVTGetSystemTimeX() >= MS2ST(500) && (GET_INPUT_VOLTAGE() > m_conf.l_battery_cut_end) ) {
					AUX_ON();
				}
				break;

			case OUT_AUX_MODE_ON_AFTER_10S:
				if (chVTGetSystemTimeX() >= MS2ST(1000) && (GET_INPUT_VOLTAGE() > m_conf.l_battery_cut_end) ) { // diese einstellen für starten ohne CAN
					AUX_ON();
				}
				break;

			default:
				break;
		}


		// Trigger encoder error rate fault, using 1% errors as threshold.
		// Relevant only in FOC mode with encoder enabled
		if(m_conf.motor_type == MOTOR_TYPE_FOC &&
			m_conf.foc_sensor_mode == FOC_SENSOR_MODE_ENCODER &&
			mcpwm_foc_is_using_encoder() &&
			encoder_spi_get_error_rate() > 0.05) {
			mc_interface_fault_stop(FAULT_CODE_ENCODER_SPI);
		}

		if(m_conf.motor_type == MOTOR_TYPE_FOC &&
			m_conf.foc_sensor_mode == FOC_SENSOR_MODE_ENCODER &&
			m_conf.m_sensor_port_mode == SENSOR_PORT_MODE_SINCOS) {

			if (encoder_sincos_get_signal_below_min_error_rate() > 0.05)
				mc_interface_fault_stop(FAULT_CODE_ENCODER_SINCOS_BELOW_MIN_AMPLITUDE);
			if (encoder_sincos_get_signal_above_max_error_rate() > 0.05)
				mc_interface_fault_stop(FAULT_CODE_ENCODER_SINCOS_ABOVE_MAX_AMPLITUDE);
		}

		// TODO: Implement for BLDC and GPDRIVE
		if(m_conf.motor_type == MOTOR_TYPE_FOC) {
			int curr0_offset;
			int curr1_offset;
			int curr2_offset;

			mcpwm_foc_get_current_offsets(&curr0_offset, &curr1_offset, &curr2_offset);

			if (abs(curr0_offset - 2048) > HW_MAX_CURRENT_OFFSET) {
				mc_interface_fault_stop(FAULT_CODE_HIGH_OFFSET_CURRENT_SENSOR_1);
			}
			if (abs(curr1_offset - 2048) > HW_MAX_CURRENT_OFFSET) {
				mc_interface_fault_stop(FAULT_CODE_HIGH_OFFSET_CURRENT_SENSOR_2);
			}
#ifdef HW_HAS_3_SHUNTS
			if (abs(curr2_offset - 2048) > HW_MAX_CURRENT_OFFSET) {
				mc_interface_fault_stop(FAULT_CODE_HIGH_OFFSET_CURRENT_SENSOR_3);
			}
#endif
		}

		chThdSleepMilliseconds(1);
	}
}

static THD_FUNCTION(sample_send_thread, arg) {
	(void)arg;

	chRegSetThreadName("SampleSender");

	sample_send_tp = chThdGetSelfX();

	for(;;) {
		chEvtWaitAny((eventmask_t) 1);

		int len = 0;
		int offset = 0;

		switch (m_sample_mode_last) {
		case DEBUG_SAMPLING_NOW:
		case DEBUG_SAMPLING_START:
			len = m_sample_len;
			break;

		case DEBUG_SAMPLING_TRIGGER_START:
		case DEBUG_SAMPLING_TRIGGER_FAULT:
		case DEBUG_SAMPLING_TRIGGER_START_NOSEND:
		case DEBUG_SAMPLING_TRIGGER_FAULT_NOSEND:
			len = ADC_SAMPLE_MAX_LEN;
			offset = m_sample_trigger - m_sample_len;
			break;

		default:
			break;
		}

		for (int i = 0;i < len;i++) {
			uint8_t buffer[40];
			int32_t index = 0;
			int ind_samp = i + offset;

			while (ind_samp >= ADC_SAMPLE_MAX_LEN) {
				ind_samp -= ADC_SAMPLE_MAX_LEN;
			}

			while (ind_samp < 0) {
				ind_samp += ADC_SAMPLE_MAX_LEN;
			}

			buffer[index++] = COMM_SAMPLE_PRINT;
		
			buffer_append_float32_auto(buffer, (float)m_curr0_samples[ind_samp] * FAC_CURRENT, &index);
			buffer_append_float32_auto(buffer, (float)m_curr1_samples[ind_samp] * FAC_CURRENT, &index);
			buffer_append_float32_auto(buffer, ((float)m_ph1_samples[ind_samp] / 4096.0 * V_REG) * ((VIN_R1 + VIN_R2) / VIN_R2), &index);
			buffer_append_float32_auto(buffer, ((float)m_ph2_samples[ind_samp] / 4096.0 * V_REG) * ((VIN_R1 + VIN_R2) / VIN_R2), &index);
			buffer_append_float32_auto(buffer, ((float)m_ph3_samples[ind_samp] / 4096.0 * V_REG) * ((VIN_R1 + VIN_R2) / VIN_R2), &index);
			buffer_append_float32_auto(buffer, ((float)m_vzero_samples[ind_samp] / 4096.0 * V_REG) * ((VIN_R1 + VIN_R2) / VIN_R2), &index);
			#ifdef curr2_statt_gesammt 
			buffer_append_float32_auto(buffer, (float)m_curr2_samples[ind_samp] * FAC_CURRENT, &index);
			#else
			buffer_append_float32_auto(buffer, (float)m_curr_fir_samples[ind_samp] / (8.0 / FAC_CURRENT), &index);
			#endif
			buffer_append_float32_auto(buffer, (float)m_f_sw_samples[ind_samp] * 10.0, &index);
			buffer[index++] = m_status_samples[ind_samp];
			buffer[index++] = m_phase_samples[ind_samp];
	

			commands_send_packet(buffer, index);
		}
	}
}
