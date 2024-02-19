/*
 * UAVCAN data structure definition for libcanard.
 *
 * Autogenerated, do not edit.
 *
 * Source file: /home/benjamin/Skrivbord/tmp/uavcan/libcanard/dsdl_compiler/pyuavcan/uavcan/dsdl_files/uavcan/equipment/esc/1034.Status.uavcan
 */

#ifndef __UAVCAN_EQUIPMENT_ESC_STATUS
#define __UAVCAN_EQUIPMENT_ESC_STATUS

#include <stdint.h>
#include "canard.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************* Source text **********************************
#
# Generic ESC status.
# Unknown fields should be set to NAN.
#

uint32 error_count          # Resets when the motor restarts

float16 voltage             # Volt
float16 current             # Ampere. Can be negative in case of a regenerative braking.
float16 temperature         # Kelvin

int18 rpm                   # Negative value indicates reverse rotation

uint7 power_rating_pct      # Instant demand factor in percent (percent of maximum power); range 0% to 127%.

uint5 esc_index
******************************************************************************/

/********************* DSDL signature source definition ***********************
uavcan.equipment.esc.Status
saturated uint32 error_count
saturated float16 voltage
saturated float16 current
saturated float16 temperature
saturated int18 rpm
saturated uint7 power_rating_pct
saturated uint5 esc_index
******************************************************************************/

#define UAVCAN_EQUIPMENT_ESC_STATUS_ID                     1034
#define UAVCAN_EQUIPMENT_ESC_STATUS_NAME                   "uavcan.equipment.esc.Status"
#define UAVCAN_EQUIPMENT_ESC_STATUS_SIGNATURE              (0xA9AF28AEA2FBB254ULL)

#define UAVCAN_EQUIPMENT_ESC_STATUS_MAX_SIZE               ((110 + 7)/8)

// Constants

typedef struct
{
    // FieldTypes
    uint32_t   error_count;                   // bit len 32
    float      voltage;                       // float16 Saturate
    float      current;                       // float16 Saturate
    float      temperature;                   // float16 Saturate
    int32_t    rpm;                           // bit len 18
    uint8_t    power_rating_pct;              // bit len 7
    uint8_t    esc_index;                     // bit len 5

} uavcan_equipment_esc_Status;

extern
uint32_t uavcan_equipment_esc_Status_encode(uavcan_equipment_esc_Status* source, void* msg_buf);

extern
int32_t uavcan_equipment_esc_Status_decode(const CanardRxTransfer* transfer, uint16_t payload_len, uavcan_equipment_esc_Status* dest, uint8_t** dyn_arr_buf);

extern
uint32_t uavcan_equipment_esc_Status_encode_internal(uavcan_equipment_esc_Status* source, void* msg_buf, uint32_t offset, uint8_t root_item);

extern
int32_t uavcan_equipment_esc_Status_decode_internal(const CanardRxTransfer* transfer, uint16_t payload_len, uavcan_equipment_esc_Status* dest, uint8_t** dyn_arr_buf, int32_t offset, uint8_t tao);

#ifdef __cplusplus
} // extern "C"
#endif
#endif // __UAVCAN_EQUIPMENT_ESC_STATUS