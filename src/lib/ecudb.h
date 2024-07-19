// Generator version : v3.1
// DBC filename      : EVCC_CAN_DB_V2_4.dbc
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

// DBC file version
#define VER_ECUDB_MAJ (0U)
#define VER_ECUDB_MIN (0U)

// include current dbc-driver compilation config
#include "ecudb-config.h"

#ifdef ECUDB_USE_DIAG_MONITORS
// This file must define:
// base monitor struct
#include "canmonitorutil.h"

#endif // ECUDB_USE_DIAG_MONITORS


// DLC maximum value which is used as the limit for frame's data buffer size.
// Client can set its own value (not sure why) in driver-config
// or can test it on some limit specified by application
// e.g.: static_assert(TESTDB_MAX_DLC_VALUE <= APPLICATION_FRAME_DATA_SIZE, "Max DLC value in the driver is too big")
#ifndef ECUDB_MAX_DLC_VALUE
// The value which was found out by generator (real max value)
#define ECUDB_MAX_DLC_VALUE 8U
#endif

// The limit is used for setting frame's data bytes
#define ECUDB_VALIDATE_DLC(msgDlc) (((msgDlc) <= (ECUDB_MAX_DLC_VALUE)) ? (msgDlc) : (ECUDB_MAX_DLC_VALUE))

// Initial byte value to be filles in data bytes of the frame before pack signals
// User can define its own custom value in driver-config file
#ifndef ECUDB_INITIAL_BYTE_VALUE
#define ECUDB_INITIAL_BYTE_VALUE 0U
#endif


// def @EVCC_RX_1 CAN Message (784  0x310)
#define EVCC_RX_1_IDE (1U)
#define EVCC_RX_1_DLC (8U)
#define EVCC_RX_1_CANID (0x310U)
// signal: @EV_MAX_CHRG_CURR_LIMIT_ro
#define ECUDB_EV_MAX_CHRG_CURR_LIMIT_ro_CovFactor (0.25)
#define ECUDB_EV_MAX_CHRG_CURR_LIMIT_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.25)) )
#define ECUDB_EV_MAX_CHRG_CURR_LIMIT_ro_fromS(x) ( (((x) * (0.25)) + (0.0)) )
// signal: @SOC_ro
#define ECUDB_SOC_ro_CovFactor (0.5)
#define ECUDB_SOC_ro_toS(x) ( (uint8_t) (((x) - (0.0)) / (0.5)) )
#define ECUDB_SOC_ro_fromS(x) ( (((x) * (0.5)) + (0.0)) )
// signal: @BATT_PACK_PRESENT_VOLTAGE_ro
#define ECUDB_BATT_PACK_PRESENT_VOLTAGE_ro_CovFactor (0.25)
#define ECUDB_BATT_PACK_PRESENT_VOLTAGE_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.25)) )
#define ECUDB_BATT_PACK_PRESENT_VOLTAGE_ro_fromS(x) ( (((x) * (0.25)) + (0.0)) )

// Value tables for @EVSE_Protocol_Priority_Selection signal

#ifndef EVSE_Protocol_Priority_Selection_EVCC_RX_1_ISO_1511822013
#define EVSE_Protocol_Priority_Selection_EVCC_RX_1_ISO_1511822013 (1)
#endif

#ifndef EVSE_Protocol_Priority_Selection_EVCC_RX_1_DIN_SPEC_701212014
#define EVSE_Protocol_Priority_Selection_EVCC_RX_1_DIN_SPEC_701212014 (0)
#endif


typedef struct
{
#ifdef ECUDB_USE_BITS_SIGNAL

  uint16_t EV_MAX_CHRG_CURR_LIMIT_ro;             //      Bits=16 Factor= 0.25            Unit:'Amps'

#ifdef ECUDB_USE_SIGFLOAT
  sigfloat_t EV_MAX_CHRG_CURR_LIMIT_phys;
#endif // ECUDB_USE_SIGFLOAT

  uint8_t SOC_ro;                                 //      Bits= 8 Factor= 0.5             Unit:'%'

#ifdef ECUDB_USE_SIGFLOAT
  sigfloat_t SOC_phys;
#endif // ECUDB_USE_SIGFLOAT

  uint8_t EV_CONTINEOUS_CHRG_CURR_LIMIT;          //      Bits= 8 Unit:'Amps'

  uint16_t BATT_PACK_PRESENT_VOLTAGE_ro;          //      Bits=16 Factor= 0.25            Unit:'Volt'

#ifdef ECUDB_USE_SIGFLOAT
  sigfloat_t BATT_PACK_PRESENT_VOLTAGE_phys;
#endif // ECUDB_USE_SIGFLOAT

  //  1 : "ISO 15118-2:2013"
  //  0 : "DIN SPEC 70121:2014"
  uint8_t EVSE_Protocol_Priority_Selection;       //      Bits= 8

#else

  uint16_t EV_MAX_CHRG_CURR_LIMIT_ro;             //      Bits=16 Factor= 0.25            Unit:'Amps'

#ifdef ECUDB_USE_SIGFLOAT
  sigfloat_t EV_MAX_CHRG_CURR_LIMIT_phys;
#endif // ECUDB_USE_SIGFLOAT

  uint8_t SOC_ro;                                 //      Bits= 8 Factor= 0.5             Unit:'%'

#ifdef ECUDB_USE_SIGFLOAT
  sigfloat_t SOC_phys;
#endif // ECUDB_USE_SIGFLOAT

  uint8_t EV_CONTINEOUS_CHRG_CURR_LIMIT;          //      Bits= 8 Unit:'Amps'

  uint16_t BATT_PACK_PRESENT_VOLTAGE_ro;          //      Bits=16 Factor= 0.25            Unit:'Volt'

#ifdef ECUDB_USE_SIGFLOAT
  sigfloat_t BATT_PACK_PRESENT_VOLTAGE_phys;
#endif // ECUDB_USE_SIGFLOAT

  //  1 : "ISO 15118-2:2013"
  //  0 : "DIN SPEC 70121:2014"
  uint8_t EVSE_Protocol_Priority_Selection;       //      Bits= 8

#endif // ECUDB_USE_BITS_SIGNAL

#ifdef ECUDB_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // ECUDB_USE_DIAG_MONITORS

} EVCC_RX_1_t;

// def @EVCC_RX_2 CAN Message (832  0x340)
#define EVCC_RX_2_IDE (1U)
#define EVCC_RX_2_DLC (8U)
#define EVCC_RX_2_CANID (0x340U)

// Value tables for @EV_READY_FLAG signal

#ifndef EV_READY_FLAG_EVCC_RX_2_Ready_Fro_Charging
#define EV_READY_FLAG_EVCC_RX_2_Ready_Fro_Charging (1)
#endif

#ifndef EV_READY_FLAG_EVCC_RX_2_Not_Ready
#define EV_READY_FLAG_EVCC_RX_2_Not_Ready (0)
#endif


// Value tables for @CHARGING_COMPLETE_FLAG signal

#ifndef CHARGING_COMPLETE_FLAG_EVCC_RX_2_Disable_Charging
#define CHARGING_COMPLETE_FLAG_EVCC_RX_2_Disable_Charging (1)
#endif

#ifndef CHARGING_COMPLETE_FLAG_EVCC_RX_2_Enable_Charging_
#define CHARGING_COMPLETE_FLAG_EVCC_RX_2_Enable_Charging_ (0)
#endif


// Value tables for @VEH_STOP_CHARGING_FLAG signal

#ifndef VEH_STOP_CHARGING_FLAG_EVCC_RX_2_Vehicle_Current_Zero
#define VEH_STOP_CHARGING_FLAG_EVCC_RX_2_Vehicle_Current_Zero (1)
#endif

#ifndef VEH_STOP_CHARGING_FLAG_EVCC_RX_2_None
#define VEH_STOP_CHARGING_FLAG_EVCC_RX_2_None (0)
#endif


// Value tables for @HV_READY signal

#ifndef HV_READY_EVCC_RX_2_Vehicle_HV_Isolation_OK
#define HV_READY_EVCC_RX_2_Vehicle_HV_Isolation_OK (1)
#endif

#ifndef HV_READY_EVCC_RX_2_Vehicle_HV_Isolation_Failure
#define HV_READY_EVCC_RX_2_Vehicle_HV_Isolation_Failure (0)
#endif


// Value tables for @FORCE_ACTUATOR_UNLOCK signal

#ifndef FORCE_ACTUATOR_UNLOCK_EVCC_RX_2_Actuator_Unlock_ENABLE
#define FORCE_ACTUATOR_UNLOCK_EVCC_RX_2_Actuator_Unlock_ENABLE (1)
#endif

#ifndef FORCE_ACTUATOR_UNLOCK_EVCC_RX_2_Actuator_Unlock_DISABLE
#define FORCE_ACTUATOR_UNLOCK_EVCC_RX_2_Actuator_Unlock_DISABLE (0)
#endif


// Value tables for @EV_ERROR_CODE signal

#ifndef EV_ERROR_CODE_EVCC_RX_2_ErrorCode_NoData
#define EV_ERROR_CODE_EVCC_RX_2_ErrorCode_NoData (11)
#endif

#ifndef EV_ERROR_CODE_EVCC_RX_2_ChargingSystemIncompatibility
#define EV_ERROR_CODE_EVCC_RX_2_ChargingSystemIncompatibility (10)
#endif

#ifndef EV_ERROR_CODE_EVCC_RX_2_Reserved_C
#define EV_ERROR_CODE_EVCC_RX_2_Reserved_C (9)
#endif

#ifndef EV_ERROR_CODE_EVCC_RX_2_Reserved_B
#define EV_ERROR_CODE_EVCC_RX_2_Reserved_B (8)
#endif

#ifndef EV_ERROR_CODE_EVCC_RX_2_Reserved_A
#define EV_ERROR_CODE_EVCC_RX_2_Reserved_A (7)
#endif

#ifndef EV_ERROR_CODE_EVCC_RX_2_FAILED_ChargingVoltageOutOfRange
#define EV_ERROR_CODE_EVCC_RX_2_FAILED_ChargingVoltageOutOfRange (6)
#endif

#ifndef EV_ERROR_CODE_EVCC_RX_2_FAILED_ChargingCurrentDiff
#define EV_ERROR_CODE_EVCC_RX_2_FAILED_ChargingCurrentDiff (5)
#endif

#ifndef EV_ERROR_CODE_EVCC_RX_2_FAILED_EVRESSMalfunction
#define EV_ERROR_CODE_EVCC_RX_2_FAILED_EVRESSMalfunction (4)
#endif

#ifndef EV_ERROR_CODE_EVCC_RX_2_FAILED_ChargerConnectorLockFault
#define EV_ERROR_CODE_EVCC_RX_2_FAILED_ChargerConnectorLockFault (3)
#endif

#ifndef EV_ERROR_CODE_EVCC_RX_2_FAILED_EVShiftPosition
#define EV_ERROR_CODE_EVCC_RX_2_FAILED_EVShiftPosition (2)
#endif

#ifndef EV_ERROR_CODE_EVCC_RX_2_FAILED_RESSTemperatureInhibit
#define EV_ERROR_CODE_EVCC_RX_2_FAILED_RESSTemperatureInhibit (1)
#endif

#ifndef EV_ERROR_CODE_EVCC_RX_2_NO_Error
#define EV_ERROR_CODE_EVCC_RX_2_NO_Error (0)
#endif


typedef struct
{
#ifdef ECUDB_USE_BITS_SIGNAL

  //  1 : "Ready Fro Charging"
  //  0 : "Not Ready"
  uint8_t EV_READY_FLAG : 1;                 //      Bits= 1

  //  1 : "Disable Charging"
  //  0 : "Enable Charging "
  uint8_t CHARGING_COMPLETE_FLAG : 1;        //      Bits= 1

  //  1 : "Vehicle_Current_Zero"
  //  0 : "None"
  uint8_t VEH_STOP_CHARGING_FLAG : 1;        //      Bits= 1

  //  1 : "Vehicle HV Isolation OK"
  //  0 : "Vehicle HV Isolation Failure"
  uint8_t HV_READY : 1;                      //      Bits= 1

  //  1 : "Actuator Unlock ENABLE"
  //  0 : "Actuator Unlock DISABLE"
  uint8_t FORCE_ACTUATOR_UNLOCK : 1;         //      Bits= 1

  //  11 : "ErrorCode_NoData"
  //  10 : "ChargingSystemIncompatibility"
  //  9 : "Reserved_C"
  //  8 : "Reserved_B"
  //  7 : "Reserved_A"
  //  6 : "FAILED_ChargingVoltageOutOfRange"
  //  5 : "FAILED_ChargingCurrentDiff"
  //  4 : "FAILED_EVRESSMalfunction"
  //  3 : "FAILED_ChargerConnectorLockFault"
  //  2 : "FAILED_EVShiftPosition"
  //  1 : "FAILED_RESSTemperatureInhibit"
  //  0 : "NO_Error"
  uint8_t EV_ERROR_CODE;                     //      Bits= 8

  uint8_t REMAINING_BATT_CAPACITY;           //      Bits= 8 Unit:'KWh'

  uint16_t NOMINAL_BATT_CAPACITY;            //      Bits=16 Unit:'Ah'

#else

  //  1 : "Ready Fro Charging"
  //  0 : "Not Ready"
  uint8_t EV_READY_FLAG;                     //      Bits= 1

  //  1 : "Disable Charging"
  //  0 : "Enable Charging "
  uint8_t CHARGING_COMPLETE_FLAG;            //      Bits= 1

  //  1 : "Vehicle_Current_Zero"
  //  0 : "None"
  uint8_t VEH_STOP_CHARGING_FLAG;            //      Bits= 1

  //  1 : "Vehicle HV Isolation OK"
  //  0 : "Vehicle HV Isolation Failure"
  uint8_t HV_READY;                          //      Bits= 1

  //  1 : "Actuator Unlock ENABLE"
  //  0 : "Actuator Unlock DISABLE"
  uint8_t FORCE_ACTUATOR_UNLOCK;             //      Bits= 1

  //  11 : "ErrorCode_NoData"
  //  10 : "ChargingSystemIncompatibility"
  //  9 : "Reserved_C"
  //  8 : "Reserved_B"
  //  7 : "Reserved_A"
  //  6 : "FAILED_ChargingVoltageOutOfRange"
  //  5 : "FAILED_ChargingCurrentDiff"
  //  4 : "FAILED_EVRESSMalfunction"
  //  3 : "FAILED_ChargerConnectorLockFault"
  //  2 : "FAILED_EVShiftPosition"
  //  1 : "FAILED_RESSTemperatureInhibit"
  //  0 : "NO_Error"
  uint8_t EV_ERROR_CODE;                     //      Bits= 8

  uint8_t REMAINING_BATT_CAPACITY;           //      Bits= 8 Unit:'KWh'

  uint16_t NOMINAL_BATT_CAPACITY;            //      Bits=16 Unit:'Ah'

#endif // ECUDB_USE_BITS_SIGNAL

#ifdef ECUDB_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // ECUDB_USE_DIAG_MONITORS

} EVCC_RX_2_t;

// def @EVCC_TX_1 CAN Message (848  0x350)
#define EVCC_TX_1_IDE (1U)
#define EVCC_TX_1_DLC (8U)
#define EVCC_TX_1_CANID (0x350U)

// Value tables for @EVCC_STATUS_CODE signal

#ifndef EVCC_STATUS_CODE_EVCC_TX_1_Session_End
#define EVCC_STATUS_CODE_EVCC_TX_1_Session_End (35)
#endif

#ifndef EVCC_STATUS_CODE_EVCC_TX_1_Type2_unlock_enabled_exit
#define EVCC_STATUS_CODE_EVCC_TX_1_Type2_unlock_enabled_exit (134)
#endif

#ifndef EVCC_STATUS_CODE_EVCC_TX_1_Type2_Status_GunLockFault
#define EVCC_STATUS_CODE_EVCC_TX_1_Type2_Status_GunLockFault (133)
#endif

#ifndef EVCC_STATUS_CODE_EVCC_TX_1_Type2_TerminateChargingEvcc
#define EVCC_STATUS_CODE_EVCC_TX_1_Type2_TerminateChargingEvcc (132)
#endif

#ifndef EVCC_STATUS_CODE_EVCC_TX_1_Type2_Status_duty_fault
#define EVCC_STATUS_CODE_EVCC_TX_1_Type2_Status_duty_fault (131)
#endif

#ifndef EVCC_STATUS_CODE_EVCC_TX_1_Type2_Status_charging_ongoing
#define EVCC_STATUS_CODE_EVCC_TX_1_Type2_Status_charging_ongoing (130)
#endif

#ifndef EVCC_STATUS_CODE_EVCC_TX_1_Type2_Status_vehicle_immobilise
#define EVCC_STATUS_CODE_EVCC_TX_1_Type2_Status_vehicle_immobilise (129)
#endif

#ifndef EVCC_STATUS_CODE_EVCC_TX_1_Type2_Status_gun_detected
#define EVCC_STATUS_CODE_EVCC_TX_1_Type2_Status_gun_detected (128)
#endif

#ifndef EVCC_STATUS_CODE_EVCC_TX_1_Welding_Detection_Failed
#define EVCC_STATUS_CODE_EVCC_TX_1_Welding_Detection_Failed (34)
#endif

#ifndef EVCC_STATUS_CODE_EVCC_TX_1_Welding_Detection_Success
#define EVCC_STATUS_CODE_EVCC_TX_1_Welding_Detection_Success (33)
#endif

#ifndef EVCC_STATUS_CODE_EVCC_TX_1_Welding_Detection_Ongoing
#define EVCC_STATUS_CODE_EVCC_TX_1_Welding_Detection_Ongoing (32)
#endif

#ifndef EVCC_STATUS_CODE_EVCC_TX_1_Charging_Failed
#define EVCC_STATUS_CODE_EVCC_TX_1_Charging_Failed (31)
#endif

#ifndef EVCC_STATUS_CODE_EVCC_TX_1_Charging_Success
#define EVCC_STATUS_CODE_EVCC_TX_1_Charging_Success (30)
#endif

#ifndef EVCC_STATUS_CODE_EVCC_TX_1_Charging_Ongoing
#define EVCC_STATUS_CODE_EVCC_TX_1_Charging_Ongoing (29)
#endif

#ifndef EVCC_STATUS_CODE_EVCC_TX_1_Precharge_Failed
#define EVCC_STATUS_CODE_EVCC_TX_1_Precharge_Failed (28)
#endif

#ifndef EVCC_STATUS_CODE_EVCC_TX_1_Precharge_Success
#define EVCC_STATUS_CODE_EVCC_TX_1_Precharge_Success (27)
#endif

#ifndef EVCC_STATUS_CODE_EVCC_TX_1_Precharge_Ongoing
#define EVCC_STATUS_CODE_EVCC_TX_1_Precharge_Ongoing (26)
#endif

#ifndef EVCC_STATUS_CODE_EVCC_TX_1_Cable_Check_Isolation_Failed
#define EVCC_STATUS_CODE_EVCC_TX_1_Cable_Check_Isolation_Failed (25)
#endif

#ifndef EVCC_STATUS_CODE_EVCC_TX_1_Cable_Check_Isolation_Success
#define EVCC_STATUS_CODE_EVCC_TX_1_Cable_Check_Isolation_Success (24)
#endif

#ifndef EVCC_STATUS_CODE_EVCC_TX_1_Cable_Check_Isolation_Ongoing
#define EVCC_STATUS_CODE_EVCC_TX_1_Cable_Check_Isolation_Ongoing (23)
#endif

#ifndef EVCC_STATUS_CODE_EVCC_TX_1_Charging_Params_Exchange_Failed
#define EVCC_STATUS_CODE_EVCC_TX_1_Charging_Params_Exchange_Failed (22)
#endif

#ifndef EVCC_STATUS_CODE_EVCC_TX_1_Charging_Params_Exchange_Success
#define EVCC_STATUS_CODE_EVCC_TX_1_Charging_Params_Exchange_Success (21)
#endif

#ifndef EVCC_STATUS_CODE_EVCC_TX_1_Charging_Params_Exchange_Ongoing
#define EVCC_STATUS_CODE_EVCC_TX_1_Charging_Params_Exchange_Ongoing (20)
#endif

#ifndef EVCC_STATUS_CODE_EVCC_TX_1_Authenticating_Failed
#define EVCC_STATUS_CODE_EVCC_TX_1_Authenticating_Failed (19)
#endif

#ifndef EVCC_STATUS_CODE_EVCC_TX_1_Authenticating_Success
#define EVCC_STATUS_CODE_EVCC_TX_1_Authenticating_Success (18)
#endif

#ifndef EVCC_STATUS_CODE_EVCC_TX_1_Authenticating_Ongoing
#define EVCC_STATUS_CODE_EVCC_TX_1_Authenticating_Ongoing (17)
#endif

#ifndef EVCC_STATUS_CODE_EVCC_TX_1_Payment_Selection_Failed
#define EVCC_STATUS_CODE_EVCC_TX_1_Payment_Selection_Failed (16)
#endif

#ifndef EVCC_STATUS_CODE_EVCC_TX_1_Payment_Selection_Success
#define EVCC_STATUS_CODE_EVCC_TX_1_Payment_Selection_Success (15)
#endif

#ifndef EVCC_STATUS_CODE_EVCC_TX_1_Service_Discovery_Failed
#define EVCC_STATUS_CODE_EVCC_TX_1_Service_Discovery_Failed (14)
#endif

#ifndef EVCC_STATUS_CODE_EVCC_TX_1_Service_Discovery_Success
#define EVCC_STATUS_CODE_EVCC_TX_1_Service_Discovery_Success (13)
#endif

#ifndef EVCC_STATUS_CODE_EVCC_TX_1_Session_Setup_Failed
#define EVCC_STATUS_CODE_EVCC_TX_1_Session_Setup_Failed (12)
#endif

#ifndef EVCC_STATUS_CODE_EVCC_TX_1_Session_Setup_Success
#define EVCC_STATUS_CODE_EVCC_TX_1_Session_Setup_Success (11)
#endif

#ifndef EVCC_STATUS_CODE_EVCC_TX_1_Protocol_Handshake_Failed
#define EVCC_STATUS_CODE_EVCC_TX_1_Protocol_Handshake_Failed (10)
#endif

#ifndef EVCC_STATUS_CODE_EVCC_TX_1_Protocol_Handshake_Success
#define EVCC_STATUS_CODE_EVCC_TX_1_Protocol_Handshake_Success (9)
#endif

#ifndef EVCC_STATUS_CODE_EVCC_TX_1_TCP_link_Failed
#define EVCC_STATUS_CODE_EVCC_TX_1_TCP_link_Failed (8)
#endif

#ifndef EVCC_STATUS_CODE_EVCC_TX_1_TCP_link_established
#define EVCC_STATUS_CODE_EVCC_TX_1_TCP_link_established (7)
#endif

#ifndef EVCC_STATUS_CODE_EVCC_TX_1_SECC_discovery_Failed
#define EVCC_STATUS_CODE_EVCC_TX_1_SECC_discovery_Failed (6)
#endif

#ifndef EVCC_STATUS_CODE_EVCC_TX_1_SECC_discovery_Success
#define EVCC_STATUS_CODE_EVCC_TX_1_SECC_discovery_Success (5)
#endif

#ifndef EVCC_STATUS_CODE_EVCC_TX_1_SECC_discovery_ongoing
#define EVCC_STATUS_CODE_EVCC_TX_1_SECC_discovery_ongoing (4)
#endif

#ifndef EVCC_STATUS_CODE_EVCC_TX_1_Slac_Failed
#define EVCC_STATUS_CODE_EVCC_TX_1_Slac_Failed (3)
#endif

#ifndef EVCC_STATUS_CODE_EVCC_TX_1_Slac_Success
#define EVCC_STATUS_CODE_EVCC_TX_1_Slac_Success (2)
#endif

#ifndef EVCC_STATUS_CODE_EVCC_TX_1_Slacc_Ongoing
#define EVCC_STATUS_CODE_EVCC_TX_1_Slacc_Ongoing (1)
#endif

#ifndef EVCC_STATUS_CODE_EVCC_TX_1_Intilizing
#define EVCC_STATUS_CODE_EVCC_TX_1_Intilizing (0)
#endif


// Value tables for @EVCC_READY signal

#ifndef EVCC_READY_EVCC_TX_1_Ready_Fro_Charging
#define EVCC_READY_EVCC_TX_1_Ready_Fro_Charging (1)
#endif

#ifndef EVCC_READY_EVCC_TX_1_Not_Ready
#define EVCC_READY_EVCC_TX_1_Not_Ready (0)
#endif


// Value tables for @GUN_DETECTED signal

#ifndef GUN_DETECTED_EVCC_TX_1_GUN_Detected
#define GUN_DETECTED_EVCC_TX_1_GUN_Detected (1)
#endif

#ifndef GUN_DETECTED_EVCC_TX_1_GUN_Not_Detected
#define GUN_DETECTED_EVCC_TX_1_GUN_Not_Detected (0)
#endif


// Value tables for @POSITIVE_CONTACTOR_CONTROL signal

#ifndef POSITIVE_CONTACTOR_CONTROL_EVCC_TX_1_Close_Charging_Contactor
#define POSITIVE_CONTACTOR_CONTROL_EVCC_TX_1_Close_Charging_Contactor (1)
#endif

#ifndef POSITIVE_CONTACTOR_CONTROL_EVCC_TX_1_Open_Charging_Contactor
#define POSITIVE_CONTACTOR_CONTROL_EVCC_TX_1_Open_Charging_Contactor (0)
#endif


// Value tables for @CHARGING_STATUS signal

#ifndef CHARGING_STATUS_EVCC_TX_1_Vehicle_Charging
#define CHARGING_STATUS_EVCC_TX_1_Vehicle_Charging (1)
#endif

#ifndef CHARGING_STATUS_EVCC_TX_1_Vehicle_Not_Charging
#define CHARGING_STATUS_EVCC_TX_1_Vehicle_Not_Charging (0)
#endif


// Value tables for @NEGATIVE_CONTACTOR_CONTROL signal

#ifndef NEGATIVE_CONTACTOR_CONTROL_EVCC_TX_1_Close_Charging_Contactor
#define NEGATIVE_CONTACTOR_CONTROL_EVCC_TX_1_Close_Charging_Contactor (1)
#endif

#ifndef NEGATIVE_CONTACTOR_CONTROL_EVCC_TX_1_Open_Charging_Contactor
#define NEGATIVE_CONTACTOR_CONTROL_EVCC_TX_1_Open_Charging_Contactor (0)
#endif


// Value tables for @EV_Error_Code signal

#ifndef EV_Error_Code_EVCC_TX_1_ErrorCode_NoData
#define EV_Error_Code_EVCC_TX_1_ErrorCode_NoData (11)
#endif

#ifndef EV_Error_Code_EVCC_TX_1_ChargingSystemIncompatibility
#define EV_Error_Code_EVCC_TX_1_ChargingSystemIncompatibility (10)
#endif

#ifndef EV_Error_Code_EVCC_TX_1_Reserved_C
#define EV_Error_Code_EVCC_TX_1_Reserved_C (9)
#endif

#ifndef EV_Error_Code_EVCC_TX_1_Reserved_B
#define EV_Error_Code_EVCC_TX_1_Reserved_B (8)
#endif

#ifndef EV_Error_Code_EVCC_TX_1_Reserved_A
#define EV_Error_Code_EVCC_TX_1_Reserved_A (7)
#endif

#ifndef EV_Error_Code_EVCC_TX_1_FAILED_ChargingVoltageOutOfRange
#define EV_Error_Code_EVCC_TX_1_FAILED_ChargingVoltageOutOfRange (6)
#endif

#ifndef EV_Error_Code_EVCC_TX_1_FAILED_ChargingCurrentDiff
#define EV_Error_Code_EVCC_TX_1_FAILED_ChargingCurrentDiff (5)
#endif

#ifndef EV_Error_Code_EVCC_TX_1_FAILED_EVRESSMalfunction
#define EV_Error_Code_EVCC_TX_1_FAILED_EVRESSMalfunction (4)
#endif

#ifndef EV_Error_Code_EVCC_TX_1_FAILED_ChargerConnectorLockFault
#define EV_Error_Code_EVCC_TX_1_FAILED_ChargerConnectorLockFault (3)
#endif

#ifndef EV_Error_Code_EVCC_TX_1_FAILED_EVShiftPosition
#define EV_Error_Code_EVCC_TX_1_FAILED_EVShiftPosition (2)
#endif

#ifndef EV_Error_Code_EVCC_TX_1_FAILED_RESSTemperatureInhibit
#define EV_Error_Code_EVCC_TX_1_FAILED_RESSTemperatureInhibit (1)
#endif

#ifndef EV_Error_Code_EVCC_TX_1_NO_Error
#define EV_Error_Code_EVCC_TX_1_NO_Error (0)
#endif


typedef struct
{
#ifdef ECUDB_USE_BITS_SIGNAL

  //  35 : "Session_End"
  //  134 : "Type2_unlock_enabled_exit"
  //  133 : "Type2_Status_GunLockFault"
  //  132 : "Type2_TerminateChargingEvcc"
  //  131 : "Type2_Status_duty_fault"
  //  130 : "Type2_Status_charging_ongoing"
  //  129 : "Type2_Status_vehicle_immobilise"
  //  128 : "Type2_Status_gun_detected"
  //  34 : "Welding_Detection_Failed"
  //  33 : "Welding_Detection_Success"
  //  32 : "Welding_Detection_Ongoing"
  //  31 : "Charging_Failed"
  //  30 : "Charging_Success"
  //  29 : "Charging_Ongoing"
  //  28 : "Precharge_Failed"
  //  27 : "Precharge_Success"
  //  26 : "Precharge_Ongoing"
  //  25 : "Cable_Check_Isolation_Failed"
  //  24 : "Cable_Check_Isolation_Success"
  //  23 : "Cable_Check_Isolation_Ongoing"
  //  22 : "Charging_Params_Exchange_Failed"
  //  21 : "Charging_Params_Exchange_Success"
  //  20 : "Charging_Params_Exchange_Ongoing"
  //  19 : "Authenticating_Failed"
  //  18 : "Authenticating_Success"
  //  17 : "Authenticating_Ongoing"
  //  16 : "Payment_Selection_Failed"
  //  15 : "Payment_Selection_Success"
  //  14 : "Service_Discovery_Failed"
  //  13 : "Service_Discovery_Success"
  //  12 : "Session_Setup_Failed"
  //  11 : "Session_Setup_Success"
  //  10 : "Protocol_Handshake_Failed"
  //  9 : "Protocol_Handshake_Success"
  //  8 : "TCP_link_Failed"
  //  7 : "TCP_link_established"
  //  6 : "SECC_discovery_Failed"
  //  5 : "SECC_discovery_Success"
  //  4 : "SECC_discovery_ongoing"
  //  3 : "Slac_Failed"
  //  2 : "Slac_Success"
  //  1 : "Slacc_Ongoing"
  //  0 : "Intilizing"
  uint8_t EVCC_STATUS_CODE;                  //      Bits= 8

  uint16_t PP_GUN_RESISTANCE;                //      Bits=16 Unit:'Ohm'

  uint8_t CP_DUTY_CYCLE;                     //      Bits= 8 Unit:'%'

  //  1 : "Ready Fro Charging"
  //  0 : "Not Ready"
  uint8_t EVCC_READY : 1;                    //      Bits= 1

  //  1 : "GUN Detected"
  //  0 : "GUN Not Detected"
  uint8_t GUN_DETECTED : 1;                  //      Bits= 1

  // 0 : Open charging contactor
  // 1 : Close charging contactor
  //  1 : "Close Charging Contactor"
  //  0 : "Open Charging Contactor"
  uint8_t POSITIVE_CONTACTOR_CONTROL : 1;    //      Bits= 1

  // 0 : Vehicle not charging
  // 1 : Vehicle charging
  //  1 : "Vehicle Charging"
  //  0 : "Vehicle Not Charging"
  uint8_t CHARGING_STATUS : 1;               //      Bits= 1

  // 0 : Open charging contactor
  // 1 : Close charging contactor
  //  1 : "Close Charging Contactor"
  //  0 : "Open Charging Contactor"
  uint8_t NEGATIVE_CONTACTOR_CONTROL : 1;    //      Bits= 1

  uint8_t SELECTED_ATTENUATION_IN_DB;        //      Bits= 8

  //  11 : "ErrorCode_NoData"
  //  10 : "ChargingSystemIncompatibility"
  //  9 : "Reserved_C"
  //  8 : "Reserved_B"
  //  7 : "Reserved_A"
  //  6 : "FAILED_ChargingVoltageOutOfRange"
  //  5 : "FAILED_ChargingCurrentDiff"
  //  4 : "FAILED_EVRESSMalfunction"
  //  3 : "FAILED_ChargerConnectorLockFault"
  //  2 : "FAILED_EVShiftPosition"
  //  1 : "FAILED_RESSTemperatureInhibit"
  //  0 : "NO_Error"
  uint8_t EV_Error_Code;                     //      Bits= 8

  // Deviation of Set current with Actual current
  uint8_t DIFFERENTIAL_CURRENT_MEAS;         //      Bits= 8

#else

  //  35 : "Session_End"
  //  134 : "Type2_unlock_enabled_exit"
  //  133 : "Type2_Status_GunLockFault"
  //  132 : "Type2_TerminateChargingEvcc"
  //  131 : "Type2_Status_duty_fault"
  //  130 : "Type2_Status_charging_ongoing"
  //  129 : "Type2_Status_vehicle_immobilise"
  //  128 : "Type2_Status_gun_detected"
  //  34 : "Welding_Detection_Failed"
  //  33 : "Welding_Detection_Success"
  //  32 : "Welding_Detection_Ongoing"
  //  31 : "Charging_Failed"
  //  30 : "Charging_Success"
  //  29 : "Charging_Ongoing"
  //  28 : "Precharge_Failed"
  //  27 : "Precharge_Success"
  //  26 : "Precharge_Ongoing"
  //  25 : "Cable_Check_Isolation_Failed"
  //  24 : "Cable_Check_Isolation_Success"
  //  23 : "Cable_Check_Isolation_Ongoing"
  //  22 : "Charging_Params_Exchange_Failed"
  //  21 : "Charging_Params_Exchange_Success"
  //  20 : "Charging_Params_Exchange_Ongoing"
  //  19 : "Authenticating_Failed"
  //  18 : "Authenticating_Success"
  //  17 : "Authenticating_Ongoing"
  //  16 : "Payment_Selection_Failed"
  //  15 : "Payment_Selection_Success"
  //  14 : "Service_Discovery_Failed"
  //  13 : "Service_Discovery_Success"
  //  12 : "Session_Setup_Failed"
  //  11 : "Session_Setup_Success"
  //  10 : "Protocol_Handshake_Failed"
  //  9 : "Protocol_Handshake_Success"
  //  8 : "TCP_link_Failed"
  //  7 : "TCP_link_established"
  //  6 : "SECC_discovery_Failed"
  //  5 : "SECC_discovery_Success"
  //  4 : "SECC_discovery_ongoing"
  //  3 : "Slac_Failed"
  //  2 : "Slac_Success"
  //  1 : "Slacc_Ongoing"
  //  0 : "Intilizing"
  uint8_t EVCC_STATUS_CODE;                  //      Bits= 8

  uint16_t PP_GUN_RESISTANCE;                //      Bits=16 Unit:'Ohm'

  uint8_t CP_DUTY_CYCLE;                     //      Bits= 8 Unit:'%'

  //  1 : "Ready Fro Charging"
  //  0 : "Not Ready"
  uint8_t EVCC_READY;                        //      Bits= 1

  //  1 : "GUN Detected"
  //  0 : "GUN Not Detected"
  uint8_t GUN_DETECTED;                      //      Bits= 1

  // 0 : Open charging contactor
  // 1 : Close charging contactor
  //  1 : "Close Charging Contactor"
  //  0 : "Open Charging Contactor"
  uint8_t POSITIVE_CONTACTOR_CONTROL;        //      Bits= 1

  // 0 : Vehicle not charging
  // 1 : Vehicle charging
  //  1 : "Vehicle Charging"
  //  0 : "Vehicle Not Charging"
  uint8_t CHARGING_STATUS;                   //      Bits= 1

  // 0 : Open charging contactor
  // 1 : Close charging contactor
  //  1 : "Close Charging Contactor"
  //  0 : "Open Charging Contactor"
  uint8_t NEGATIVE_CONTACTOR_CONTROL;        //      Bits= 1

  uint8_t SELECTED_ATTENUATION_IN_DB;        //      Bits= 8

  //  11 : "ErrorCode_NoData"
  //  10 : "ChargingSystemIncompatibility"
  //  9 : "Reserved_C"
  //  8 : "Reserved_B"
  //  7 : "Reserved_A"
  //  6 : "FAILED_ChargingVoltageOutOfRange"
  //  5 : "FAILED_ChargingCurrentDiff"
  //  4 : "FAILED_EVRESSMalfunction"
  //  3 : "FAILED_ChargerConnectorLockFault"
  //  2 : "FAILED_EVShiftPosition"
  //  1 : "FAILED_RESSTemperatureInhibit"
  //  0 : "NO_Error"
  uint8_t EV_Error_Code;                     //      Bits= 8

  // Deviation of Set current with Actual current
  uint8_t DIFFERENTIAL_CURRENT_MEAS;         //      Bits= 8

#endif // ECUDB_USE_BITS_SIGNAL

#ifdef ECUDB_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // ECUDB_USE_DIAG_MONITORS

} EVCC_TX_1_t;

// def @EVCC_TX_3 CAN Message (864  0x360)
#define EVCC_TX_3_IDE (1U)
#define EVCC_TX_3_DLC (8U)
#define EVCC_TX_3_CANID (0x360U)
// signal: @SOFTWARE_VERSION_ro
#define ECUDB_SOFTWARE_VERSION_ro_CovFactor (0.1)
#define ECUDB_SOFTWARE_VERSION_ro_toS(x) ( (uint8_t) (((x) - (0.0)) / (0.1)) )
#define ECUDB_SOFTWARE_VERSION_ro_fromS(x) ( (((x) * (0.1)) + (0.0)) )
// signal: @CHARGER_MAX_CURRENT_ro
#define ECUDB_CHARGER_MAX_CURRENT_ro_CovFactor (0.1)
#define ECUDB_CHARGER_MAX_CURRENT_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.1)) )
#define ECUDB_CHARGER_MAX_CURRENT_ro_fromS(x) ( (((x) * (0.1)) + (0.0)) )
// signal: @CHARGER_MIN_CURRENT_ro
#define ECUDB_CHARGER_MIN_CURRENT_ro_CovFactor (0.1)
#define ECUDB_CHARGER_MIN_CURRENT_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.1)) )
#define ECUDB_CHARGER_MIN_CURRENT_ro_fromS(x) ( (((x) * (0.1)) + (0.0)) )
// signal: @CHARGER_MAX_VOLTAGE_ro
#define ECUDB_CHARGER_MAX_VOLTAGE_ro_CovFactor (0.1)
#define ECUDB_CHARGER_MAX_VOLTAGE_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.1)) )
#define ECUDB_CHARGER_MAX_VOLTAGE_ro_fromS(x) ( (((x) * (0.1)) + (0.0)) )

typedef struct
{
#ifdef ECUDB_USE_BITS_SIGNAL

  uint8_t SOFTWARE_VERSION_ro;               //      Bits= 8 Factor= 0.1             Unit:'Num'

#ifdef ECUDB_USE_SIGFLOAT
  sigfloat_t SOFTWARE_VERSION_phys;
#endif // ECUDB_USE_SIGFLOAT

  uint16_t CHARGER_MAX_CURRENT_ro;           //      Bits=16 Factor= 0.1             Unit:'Amps'

#ifdef ECUDB_USE_SIGFLOAT
  sigfloat_t CHARGER_MAX_CURRENT_phys;
#endif // ECUDB_USE_SIGFLOAT

  uint16_t CHARGER_MIN_CURRENT_ro;           //      Bits=16 Factor= 0.1             Unit:'Amps'

#ifdef ECUDB_USE_SIGFLOAT
  sigfloat_t CHARGER_MIN_CURRENT_phys;
#endif // ECUDB_USE_SIGFLOAT

  uint16_t CHARGER_MAX_VOLTAGE_ro;           //      Bits=16 Factor= 0.1             Unit:'Volts'

#ifdef ECUDB_USE_SIGFLOAT
  sigfloat_t CHARGER_MAX_VOLTAGE_phys;
#endif // ECUDB_USE_SIGFLOAT

#else

  uint8_t SOFTWARE_VERSION_ro;               //      Bits= 8 Factor= 0.1             Unit:'Num'

#ifdef ECUDB_USE_SIGFLOAT
  sigfloat_t SOFTWARE_VERSION_phys;
#endif // ECUDB_USE_SIGFLOAT

  uint16_t CHARGER_MAX_CURRENT_ro;           //      Bits=16 Factor= 0.1             Unit:'Amps'

#ifdef ECUDB_USE_SIGFLOAT
  sigfloat_t CHARGER_MAX_CURRENT_phys;
#endif // ECUDB_USE_SIGFLOAT

  uint16_t CHARGER_MIN_CURRENT_ro;           //      Bits=16 Factor= 0.1             Unit:'Amps'

#ifdef ECUDB_USE_SIGFLOAT
  sigfloat_t CHARGER_MIN_CURRENT_phys;
#endif // ECUDB_USE_SIGFLOAT

  uint16_t CHARGER_MAX_VOLTAGE_ro;           //      Bits=16 Factor= 0.1             Unit:'Volts'

#ifdef ECUDB_USE_SIGFLOAT
  sigfloat_t CHARGER_MAX_VOLTAGE_phys;
#endif // ECUDB_USE_SIGFLOAT

#endif // ECUDB_USE_BITS_SIGNAL

#ifdef ECUDB_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // ECUDB_USE_DIAG_MONITORS

} EVCC_TX_3_t;

// def @EVCC_TX_4 CAN Message (865  0x361)
#define EVCC_TX_4_IDE (1U)
#define EVCC_TX_4_DLC (8U)
#define EVCC_TX_4_CANID (0x361U)
// signal: @CHARGER_MIN_VOLTAGE_ro
#define ECUDB_CHARGER_MIN_VOLTAGE_ro_CovFactor (0.1)
#define ECUDB_CHARGER_MIN_VOLTAGE_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.1)) )
#define ECUDB_CHARGER_MIN_VOLTAGE_ro_fromS(x) ( (((x) * (0.1)) + (0.0)) )
// signal: @CHARGER_MAX_POWER_ro
#define ECUDB_CHARGER_MAX_POWER_ro_CovFactor (10)
#define ECUDB_CHARGER_MAX_POWER_ro_toS(x) ( (uint16_t) ((x) / (10)) )
#define ECUDB_CHARGER_MAX_POWER_ro_fromS(x) ( ((x) * (10)) )
// signal: @CHARGER_PRESENT_VOLTAGE_ro
#define ECUDB_CHARGER_PRESENT_VOLTAGE_ro_CovFactor (0.1)
#define ECUDB_CHARGER_PRESENT_VOLTAGE_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.1)) )
#define ECUDB_CHARGER_PRESENT_VOLTAGE_ro_fromS(x) ( (((x) * (0.1)) + (0.0)) )
// signal: @CHARGER_PRESENT_CURRENT_ro
#define ECUDB_CHARGER_PRESENT_CURRENT_ro_CovFactor (0.1)
#define ECUDB_CHARGER_PRESENT_CURRENT_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.1)) )
#define ECUDB_CHARGER_PRESENT_CURRENT_ro_fromS(x) ( (((x) * (0.1)) + (0.0)) )

typedef struct
{
#ifdef ECUDB_USE_BITS_SIGNAL

  uint16_t CHARGER_MIN_VOLTAGE_ro;           //      Bits=16 Factor= 0.1             Unit:'Volts'

#ifdef ECUDB_USE_SIGFLOAT
  sigfloat_t CHARGER_MIN_VOLTAGE_phys;
#endif // ECUDB_USE_SIGFLOAT

  uint16_t CHARGER_MAX_POWER_ro;             //      Bits=16 Factor= 10              Unit:'Watt'

#ifdef ECUDB_USE_SIGFLOAT
  uint32_t CHARGER_MAX_POWER_phys;
#endif // ECUDB_USE_SIGFLOAT

  uint16_t CHARGER_PRESENT_VOLTAGE_ro;       //      Bits=16 Factor= 0.1             Unit:'Volts'

#ifdef ECUDB_USE_SIGFLOAT
  sigfloat_t CHARGER_PRESENT_VOLTAGE_phys;
#endif // ECUDB_USE_SIGFLOAT

  uint16_t CHARGER_PRESENT_CURRENT_ro;       //      Bits=16 Factor= 0.1             Unit:'Amps'

#ifdef ECUDB_USE_SIGFLOAT
  sigfloat_t CHARGER_PRESENT_CURRENT_phys;
#endif // ECUDB_USE_SIGFLOAT

#else

  uint16_t CHARGER_MIN_VOLTAGE_ro;           //      Bits=16 Factor= 0.1             Unit:'Volts'

#ifdef ECUDB_USE_SIGFLOAT
  sigfloat_t CHARGER_MIN_VOLTAGE_phys;
#endif // ECUDB_USE_SIGFLOAT

  uint16_t CHARGER_MAX_POWER_ro;             //      Bits=16 Factor= 10              Unit:'Watt'

#ifdef ECUDB_USE_SIGFLOAT
  uint32_t CHARGER_MAX_POWER_phys;
#endif // ECUDB_USE_SIGFLOAT

  uint16_t CHARGER_PRESENT_VOLTAGE_ro;       //      Bits=16 Factor= 0.1             Unit:'Volts'

#ifdef ECUDB_USE_SIGFLOAT
  sigfloat_t CHARGER_PRESENT_VOLTAGE_phys;
#endif // ECUDB_USE_SIGFLOAT

  uint16_t CHARGER_PRESENT_CURRENT_ro;       //      Bits=16 Factor= 0.1             Unit:'Amps'

#ifdef ECUDB_USE_SIGFLOAT
  sigfloat_t CHARGER_PRESENT_CURRENT_phys;
#endif // ECUDB_USE_SIGFLOAT

#endif // ECUDB_USE_BITS_SIGNAL

#ifdef ECUDB_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // ECUDB_USE_DIAG_MONITORS

} EVCC_TX_4_t;

// def @EVCC_TX_2 CAN Message (969729 0xecc01)
#define EVCC_TX_2_IDE (1U)
#define EVCC_TX_2_DLC (8U)
#define EVCC_TX_2_CANID (0xecc01U)
// signal: @TEMPERATURE_1_VALUE_ro
#define ECUDB_TEMPERATURE_1_VALUE_ro_CovFactor (0.1)
#define ECUDB_TEMPERATURE_1_VALUE_ro_toS(x) ( (int16_t) (((x) - (0.0)) / (0.1)) )
#define ECUDB_TEMPERATURE_1_VALUE_ro_fromS(x) ( (((x) * (0.1)) + (0.0)) )
// signal: @TEMPERATURE_2_VALUE_ro
#define ECUDB_TEMPERATURE_2_VALUE_ro_CovFactor (0.1)
#define ECUDB_TEMPERATURE_2_VALUE_ro_toS(x) ( (int16_t) (((x) - (0.0)) / (0.1)) )
#define ECUDB_TEMPERATURE_2_VALUE_ro_fromS(x) ( (((x) * (0.1)) + (0.0)) )

// Value tables for @TEMP_1_FAULT signal

#ifndef TEMP_1_FAULT_EVCC_TX_2_Temp_Greater_than_70_DegC
#define TEMP_1_FAULT_EVCC_TX_2_Temp_Greater_than_70_DegC (1)
#endif

#ifndef TEMP_1_FAULT_EVCC_TX_2_Temp_Under_Permissible_Limit
#define TEMP_1_FAULT_EVCC_TX_2_Temp_Under_Permissible_Limit (0)
#endif


// Value tables for @TEMP_2_FAULT signal

#ifndef TEMP_2_FAULT_EVCC_TX_2_Temp_Greater_than_70_DegC
#define TEMP_2_FAULT_EVCC_TX_2_Temp_Greater_than_70_DegC (1)
#endif

#ifndef TEMP_2_FAULT_EVCC_TX_2_Temp_Under_Permissible_Limit
#define TEMP_2_FAULT_EVCC_TX_2_Temp_Under_Permissible_Limit (0)
#endif


// Value tables for @GUN_LOCK_FAULT signal

#ifndef GUN_LOCK_FAULT_EVCC_TX_2_GUN_Lock_Fault
#define GUN_LOCK_FAULT_EVCC_TX_2_GUN_Lock_Fault (1)
#endif

#ifndef GUN_LOCK_FAULT_EVCC_TX_2_GUN_Lock_OK
#define GUN_LOCK_FAULT_EVCC_TX_2_GUN_Lock_OK (0)
#endif


// Value tables for @VEHICLE_IMMOBILIZE signal

#ifndef VEHICLE_IMMOBILIZE_EVCC_TX_2_Vehicle_Immobilise
#define VEHICLE_IMMOBILIZE_EVCC_TX_2_Vehicle_Immobilise (1)
#endif

#ifndef VEHICLE_IMMOBILIZE_EVCC_TX_2_Vehicle_Mobilise
#define VEHICLE_IMMOBILIZE_EVCC_TX_2_Vehicle_Mobilise (0)
#endif


// Value tables for @GUN_LOCK_FEEDBACK signal

#ifndef GUN_LOCK_FEEDBACK_EVCC_TX_2_GUN_Locked
#define GUN_LOCK_FEEDBACK_EVCC_TX_2_GUN_Locked (1)
#endif

#ifndef GUN_LOCK_FEEDBACK_EVCC_TX_2_GUN_Unlocked
#define GUN_LOCK_FEEDBACK_EVCC_TX_2_GUN_Unlocked (0)
#endif


// Value tables for @EVCC_GUN_LOCK_REQUEST_STATUS signal

#ifndef EVCC_GUN_LOCK_REQUEST_STATUS_EVCC_TX_2_GUN_Lock_Req_Pending
#define EVCC_GUN_LOCK_REQUEST_STATUS_EVCC_TX_2_GUN_Lock_Req_Pending (1)
#endif

#ifndef EVCC_GUN_LOCK_REQUEST_STATUS_EVCC_TX_2_GUN_Lock_Req_Processed
#define EVCC_GUN_LOCK_REQUEST_STATUS_EVCC_TX_2_GUN_Lock_Req_Processed (0)
#endif


// Value tables for @EVCC_GUN_UNLOCK_REQUEST_STATUS signal

#ifndef EVCC_GUN_UNLOCK_REQUEST_STATUS_EVCC_TX_2_GUN_Unlock_Req_Pending
#define EVCC_GUN_UNLOCK_REQUEST_STATUS_EVCC_TX_2_GUN_Unlock_Req_Pending (1)
#endif

#ifndef EVCC_GUN_UNLOCK_REQUEST_STATUS_EVCC_TX_2_GUN_Unlock_Req_Processed
#define EVCC_GUN_UNLOCK_REQUEST_STATUS_EVCC_TX_2_GUN_Unlock_Req_Processed (0)
#endif


typedef struct
{
#ifdef ECUDB_USE_BITS_SIGNAL

  int16_t TEMPERATURE_1_VALUE_ro;               //  [-] Bits=16 Factor= 0.1             Unit:'DegC'

#ifdef ECUDB_USE_SIGFLOAT
  sigfloat_t TEMPERATURE_1_VALUE_phys;
#endif // ECUDB_USE_SIGFLOAT

  int16_t TEMPERATURE_2_VALUE_ro;               //  [-] Bits=16 Factor= 0.1             Unit:'DegC'

#ifdef ECUDB_USE_SIGFLOAT
  sigfloat_t TEMPERATURE_2_VALUE_phys;
#endif // ECUDB_USE_SIGFLOAT

  uint8_t OBC_DERATING_FACTOR;                  //      Bits= 8 Unit:'%'

  // 0 : Temperature is under set limit
  // 1 : Temperature Greater Than set limit
  //  1 : "Temp Greater than 70 DegC"
  //  0 : "Temp Under Permissible Limit"
  uint8_t TEMP_1_FAULT : 1;                     //      Bits= 1

  // 0 : Temperature is under set limit
  // 1 : Temperature Greater Than set limit
  //  1 : "Temp Greater than 70 DegC"
  //  0 : "Temp Under Permissible Limit"
  uint8_t TEMP_2_FAULT : 1;                     //      Bits= 1

  // 0 : Gun Lock OK
  // 1 : Gun Lock Fault Detected
  //  1 : "GUN Lock Fault"
  //  0 : "GUN Lock OK"
  uint8_t GUN_LOCK_FAULT : 1;                   //      Bits= 1

  // 0 : Vehicle Mobilize
  // 1 : Vehicle Immobilize
  //  1 : "Vehicle Immobilise"
  //  0 : "Vehicle Mobilise"
  uint8_t VEHICLE_IMMOBILIZE : 1;               //      Bits= 1

  //  1 : "GUN_Locked"
  //  0 : "GUN_Unlocked"
  uint8_t GUN_LOCK_FEEDBACK : 1;                //      Bits= 1

  //  1 : "GUN Lock Req Pending"
  //  0 : "GUN Lock Req Processed"
  uint8_t EVCC_GUN_LOCK_REQUEST_STATUS : 1;     //      Bits= 1

  //  1 : "GUN Unlock Req Pending"
  //  0 : "GUN Unlock Req Processed"
  uint8_t EVCC_GUN_UNLOCK_REQUEST_STATUS : 1;   //      Bits= 1

#else

  int16_t TEMPERATURE_1_VALUE_ro;               //  [-] Bits=16 Factor= 0.1             Unit:'DegC'

#ifdef ECUDB_USE_SIGFLOAT
  sigfloat_t TEMPERATURE_1_VALUE_phys;
#endif // ECUDB_USE_SIGFLOAT

  int16_t TEMPERATURE_2_VALUE_ro;               //  [-] Bits=16 Factor= 0.1             Unit:'DegC'

#ifdef ECUDB_USE_SIGFLOAT
  sigfloat_t TEMPERATURE_2_VALUE_phys;
#endif // ECUDB_USE_SIGFLOAT

  uint8_t OBC_DERATING_FACTOR;                  //      Bits= 8 Unit:'%'

  // 0 : Temperature is under set limit
  // 1 : Temperature Greater Than set limit
  //  1 : "Temp Greater than 70 DegC"
  //  0 : "Temp Under Permissible Limit"
  uint8_t TEMP_1_FAULT;                         //      Bits= 1

  // 0 : Temperature is under set limit
  // 1 : Temperature Greater Than set limit
  //  1 : "Temp Greater than 70 DegC"
  //  0 : "Temp Under Permissible Limit"
  uint8_t TEMP_2_FAULT;                         //      Bits= 1

  // 0 : Gun Lock OK
  // 1 : Gun Lock Fault Detected
  //  1 : "GUN Lock Fault"
  //  0 : "GUN Lock OK"
  uint8_t GUN_LOCK_FAULT;                       //      Bits= 1

  // 0 : Vehicle Mobilize
  // 1 : Vehicle Immobilize
  //  1 : "Vehicle Immobilise"
  //  0 : "Vehicle Mobilise"
  uint8_t VEHICLE_IMMOBILIZE;                   //      Bits= 1

  //  1 : "GUN_Locked"
  //  0 : "GUN_Unlocked"
  uint8_t GUN_LOCK_FEEDBACK;                    //      Bits= 1

  //  1 : "GUN Lock Req Pending"
  //  0 : "GUN Lock Req Processed"
  uint8_t EVCC_GUN_LOCK_REQUEST_STATUS;         //      Bits= 1

  //  1 : "GUN Unlock Req Pending"
  //  0 : "GUN Unlock Req Processed"
  uint8_t EVCC_GUN_UNLOCK_REQUEST_STATUS;       //      Bits= 1

#endif // ECUDB_USE_BITS_SIGNAL

#ifdef ECUDB_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // ECUDB_USE_DIAG_MONITORS

} EVCC_TX_2_t;

// def @EVCC_TX_5 CAN Message (969730 0xecc02)
#define EVCC_TX_5_IDE (1U)
#define EVCC_TX_5_DLC (8U)
#define EVCC_TX_5_CANID (0xecc02U)

// Value tables for @TERMINATION_DETAIL signal

#ifndef TERMINATION_DETAIL_EVCC_TX_5_EV_Ready_Flag_Reception_Failure
#define TERMINATION_DETAIL_EVCC_TX_5_EV_Ready_Flag_Reception_Failure (9)
#endif

#ifndef TERMINATION_DETAIL_EVCC_TX_5_Extrenal_Actuator_Unlock
#define TERMINATION_DETAIL_EVCC_TX_5_Extrenal_Actuator_Unlock (8)
#endif

#ifndef TERMINATION_DETAIL_EVCC_TX_5_Actuator_Locking_Fault
#define TERMINATION_DETAIL_EVCC_TX_5_Actuator_Locking_Fault (7)
#endif

#ifndef TERMINATION_DETAIL_EVCC_TX_5_Emergency_PLC_Chip_Status
#define TERMINATION_DETAIL_EVCC_TX_5_Emergency_PLC_Chip_Status (36)
#endif

#ifndef TERMINATION_DETAIL_EVCC_TX_5_Emergency_Pilot_Status
#define TERMINATION_DETAIL_EVCC_TX_5_Emergency_Pilot_Status (35)
#endif

#ifndef TERMINATION_DETAIL_EVCC_TX_5_Emergency_Proximity_Status
#define TERMINATION_DETAIL_EVCC_TX_5_Emergency_Proximity_Status (34)
#endif

#ifndef TERMINATION_DETAIL_EVCC_TX_5_Emergency_High_Temperature
#define TERMINATION_DETAIL_EVCC_TX_5_Emergency_High_Temperature (33)
#endif

#ifndef TERMINATION_DETAIL_EVCC_TX_5_Emergency_HeartBeat_Error
#define TERMINATION_DETAIL_EVCC_TX_5_Emergency_HeartBeat_Error (32)
#endif

#ifndef TERMINATION_DETAIL_EVCC_TX_5_Emergency_From_Evse
#define TERMINATION_DETAIL_EVCC_TX_5_Emergency_From_Evse (31)
#endif

#ifndef TERMINATION_DETAIL_EVCC_TX_5_Vehicle_Hv_Failure
#define TERMINATION_DETAIL_EVCC_TX_5_Vehicle_Hv_Failure (6)
#endif

#ifndef TERMINATION_DETAIL_EVCC_TX_5_Evse_Invalid_Isolation_Status
#define TERMINATION_DETAIL_EVCC_TX_5_Evse_Invalid_Isolation_Status (5)
#endif

#ifndef TERMINATION_DETAIL_EVCC_TX_5_Evse_Wrong_Charge_Parameter
#define TERMINATION_DETAIL_EVCC_TX_5_Evse_Wrong_Charge_Parameter (4)
#endif

#ifndef TERMINATION_DETAIL_EVCC_TX_5_Evse_Wrong_Response_Code
#define TERMINATION_DETAIL_EVCC_TX_5_Evse_Wrong_Response_Code (3)
#endif

#ifndef TERMINATION_DETAIL_EVCC_TX_5_NONE
#define TERMINATION_DETAIL_EVCC_TX_5_NONE (0)
#endif


// Value tables for @EVCC_ERROR_CODES signal

#ifndef EVCC_ERROR_CODES_EVCC_TX_5_EVSE_Emergency
#define EVCC_ERROR_CODES_EVCC_TX_5_EVSE_Emergency (39)
#endif

#ifndef EVCC_ERROR_CODES_EVCC_TX_5_EVSE_Isolation_Status_Error
#define EVCC_ERROR_CODES_EVCC_TX_5_EVSE_Isolation_Status_Error (38)
#endif

#ifndef EVCC_ERROR_CODES_EVCC_TX_5_Wrong_Charge_Parameter
#define EVCC_ERROR_CODES_EVCC_TX_5_Wrong_Charge_Parameter (37)
#endif

#ifndef EVCC_ERROR_CODES_EVCC_TX_5_Locking_Actuator_Error
#define EVCC_ERROR_CODES_EVCC_TX_5_Locking_Actuator_Error (36)
#endif

#ifndef EVCC_ERROR_CODES_EVCC_TX_5_Temperature_Fault
#define EVCC_ERROR_CODES_EVCC_TX_5_Temperature_Fault (34)
#endif

#ifndef EVCC_ERROR_CODES_EVCC_TX_5_Response_Code_Error
#define EVCC_ERROR_CODES_EVCC_TX_5_Response_Code_Error (33)
#endif

#ifndef EVCC_ERROR_CODES_EVCC_TX_5_Evse_Sequence_Error
#define EVCC_ERROR_CODES_EVCC_TX_5_Evse_Sequence_Error (32)
#endif

#ifndef EVCC_ERROR_CODES_EVCC_TX_5_CP_PP_Lost
#define EVCC_ERROR_CODES_EVCC_TX_5_CP_PP_Lost (31)
#endif

#ifndef EVCC_ERROR_CODES_EVCC_TX_5_HeartBeat_Error
#define EVCC_ERROR_CODES_EVCC_TX_5_HeartBeat_Error (30)
#endif

#ifndef EVCC_ERROR_CODES_EVCC_TX_5_Warning_No_PWM
#define EVCC_ERROR_CODES_EVCC_TX_5_Warning_No_PWM (27)
#endif

#ifndef EVCC_ERROR_CODES_EVCC_TX_5_Step_Precharge
#define EVCC_ERROR_CODES_EVCC_TX_5_Step_Precharge (26)
#endif

#ifndef EVCC_ERROR_CODES_EVCC_TX_5_Step_Cable_Check
#define EVCC_ERROR_CODES_EVCC_TX_5_Step_Cable_Check (25)
#endif

#ifndef EVCC_ERROR_CODES_EVCC_TX_5_Step_CPD
#define EVCC_ERROR_CODES_EVCC_TX_5_Step_CPD (24)
#endif

#ifndef EVCC_ERROR_CODES_EVCC_TX_5_Step_Auth
#define EVCC_ERROR_CODES_EVCC_TX_5_Step_Auth (23)
#endif

#ifndef EVCC_ERROR_CODES_EVCC_TX_5_Step_Communcation_Setup
#define EVCC_ERROR_CODES_EVCC_TX_5_Step_Communcation_Setup (20)
#endif

#ifndef EVCC_ERROR_CODES_EVCC_TX_5_Timeout_Session_Stop_Resp
#define EVCC_ERROR_CODES_EVCC_TX_5_Timeout_Session_Stop_Resp (15)
#endif

#ifndef EVCC_ERROR_CODES_EVCC_TX_5_Timeout_Welding_Detection_Resp
#define EVCC_ERROR_CODES_EVCC_TX_5_Timeout_Welding_Detection_Resp (14)
#endif

#ifndef EVCC_ERROR_CODES_EVCC_TX_5_Timeout_Current_Demand_Resp
#define EVCC_ERROR_CODES_EVCC_TX_5_Timeout_Current_Demand_Resp (13)
#endif

#ifndef EVCC_ERROR_CODES_EVCC_TX_5_Timeout_Power_Delivery_Resp
#define EVCC_ERROR_CODES_EVCC_TX_5_Timeout_Power_Delivery_Resp (12)
#endif

#ifndef EVCC_ERROR_CODES_EVCC_TX_5_Timeout_Precharge_Resp
#define EVCC_ERROR_CODES_EVCC_TX_5_Timeout_Precharge_Resp (11)
#endif

#ifndef EVCC_ERROR_CODES_EVCC_TX_5_Timeout_Cable_Check_Resp
#define EVCC_ERROR_CODES_EVCC_TX_5_Timeout_Cable_Check_Resp (10)
#endif

#ifndef EVCC_ERROR_CODES_EVCC_TX_5_Timeout_CPD_Response
#define EVCC_ERROR_CODES_EVCC_TX_5_Timeout_CPD_Response (9)
#endif

#ifndef EVCC_ERROR_CODES_EVCC_TX_5_Timeout_Auth_Response
#define EVCC_ERROR_CODES_EVCC_TX_5_Timeout_Auth_Response (8)
#endif

#ifndef EVCC_ERROR_CODES_EVCC_TX_5_Timeout_Payment_Selection_Resp
#define EVCC_ERROR_CODES_EVCC_TX_5_Timeout_Payment_Selection_Resp (7)
#endif

#ifndef EVCC_ERROR_CODES_EVCC_TX_5_Timeout_Service_Discovery_Resp
#define EVCC_ERROR_CODES_EVCC_TX_5_Timeout_Service_Discovery_Resp (6)
#endif

#ifndef EVCC_ERROR_CODES_EVCC_TX_5_Timeout_Session_Setup_Response
#define EVCC_ERROR_CODES_EVCC_TX_5_Timeout_Session_Setup_Response (5)
#endif

#ifndef EVCC_ERROR_CODES_EVCC_TX_5_Timeout_SAP_Response
#define EVCC_ERROR_CODES_EVCC_TX_5_Timeout_SAP_Response (4)
#endif

#ifndef EVCC_ERROR_CODES_EVCC_TX_5_Timout_SDP_Sequence
#define EVCC_ERROR_CODES_EVCC_TX_5_Timout_SDP_Sequence (3)
#endif

#ifndef EVCC_ERROR_CODES_EVCC_TX_5_Timeout_Link_Detection
#define EVCC_ERROR_CODES_EVCC_TX_5_Timeout_Link_Detection (2)
#endif

#ifndef EVCC_ERROR_CODES_EVCC_TX_5_Timeout_Slac_Sequence
#define EVCC_ERROR_CODES_EVCC_TX_5_Timeout_Slac_Sequence (1)
#endif

#ifndef EVCC_ERROR_CODES_EVCC_TX_5_NONE
#define EVCC_ERROR_CODES_EVCC_TX_5_NONE (0)
#endif


// Value tables for @EVSE_ERROR_CODE signal

#ifndef EVSE_ERROR_CODE_EVCC_TX_5_Wrong_Energy_Transfer_Mode
#define EVSE_ERROR_CODE_EVCC_TX_5_Wrong_Energy_Transfer_Mode (19)
#endif

#ifndef EVSE_ERROR_CODE_EVCC_TX_5_No_Charge_Service_Selected
#define EVSE_ERROR_CODE_EVCC_TX_5_No_Charge_Service_Selected (18)
#endif

#ifndef EVSE_ERROR_CODE_EVCC_TX_5_Charging_Profile_Invalid
#define EVSE_ERROR_CODE_EVCC_TX_5_Charging_Profile_Invalid (16)
#endif

#ifndef EVSE_ERROR_CODE_EVCC_TX_5_Power_Delivery_Not_Applied
#define EVSE_ERROR_CODE_EVCC_TX_5_Power_Delivery_Not_Applied (14)
#endif

#ifndef EVSE_ERROR_CODE_EVCC_TX_5_Wrong_Charge_Parameter
#define EVSE_ERROR_CODE_EVCC_TX_5_Wrong_Charge_Parameter (13)
#endif

#ifndef EVSE_ERROR_CODE_EVCC_TX_5_Payment_Selection_Invalid
#define EVSE_ERROR_CODE_EVCC_TX_5_Payment_Selection_Invalid (6)
#endif

#ifndef EVSE_ERROR_CODE_EVCC_TX_5_Service_ID_Invalid
#define EVSE_ERROR_CODE_EVCC_TX_5_Service_ID_Invalid (5)
#endif

#ifndef EVSE_ERROR_CODE_EVCC_TX_5_Sequence_Error
#define EVSE_ERROR_CODE_EVCC_TX_5_Sequence_Error (2)
#endif

#ifndef EVSE_ERROR_CODE_EVCC_TX_5_No_Error
#define EVSE_ERROR_CODE_EVCC_TX_5_No_Error (0)
#endif


// Value tables for @CP_STATE signal

#ifndef CP_STATE_EVCC_TX_5_CP_STATE_E
#define CP_STATE_EVCC_TX_5_CP_STATE_E (4)
#endif

#ifndef CP_STATE_EVCC_TX_5_CP_STATE_D
#define CP_STATE_EVCC_TX_5_CP_STATE_D (3)
#endif

#ifndef CP_STATE_EVCC_TX_5_CP_STATE_C
#define CP_STATE_EVCC_TX_5_CP_STATE_C (2)
#endif

#ifndef CP_STATE_EVCC_TX_5_CP_STATE_B
#define CP_STATE_EVCC_TX_5_CP_STATE_B (1)
#endif

#ifndef CP_STATE_EVCC_TX_5_CP_STATE_A
#define CP_STATE_EVCC_TX_5_CP_STATE_A (0)
#endif


// Value tables for @SELECTED_APP_PROTOCOL signal

#ifndef SELECTED_APP_PROTOCOL_EVCC_TX_5_ISO1511822013
#define SELECTED_APP_PROTOCOL_EVCC_TX_5_ISO1511822013 (2)
#endif

#ifndef SELECTED_APP_PROTOCOL_EVCC_TX_5_DIN701212012
#define SELECTED_APP_PROTOCOL_EVCC_TX_5_DIN701212012 (1)
#endif

#ifndef SELECTED_APP_PROTOCOL_EVCC_TX_5_NONE
#define SELECTED_APP_PROTOCOL_EVCC_TX_5_NONE (0)
#endif


typedef struct
{
#ifdef ECUDB_USE_BITS_SIGNAL

  //  9 : "EV_Ready Flag Reception Failure"
  //  8 : "Extrenal Actuator Unlock"
  //  7 : "Actuator Locking Fault"
  //  36 : "Emergency PLC Chip Status"
  //  35 : "Emergency Pilot Status"
  //  34 : "Emergency Proximity Status"
  //  33 : "Emergency High Temperature"
  //  32 : "Emergency HeartBeat Error"
  //  31 : "Emergency From Evse"
  //  6 : "Vehicle Hv Failure"
  //  5 : "Evse Invalid Isolation Status"
  //  4 : "Evse Wrong Charge Parameter"
  //  3 : "Evse Wrong Response Code"
  //  0 : "NONE"
  uint8_t TERMINATION_DETAIL;                //      Bits= 8

  //  39 : "EVSE Emergency"
  //  38 : "EVSE Isolation Status Error"
  //  37 : "Wrong Charge Parameter"
  //  36 : "Locking Actuator Error"
  //  34 : "Temperature Fault"
  //  33 : "Response Code Error"
  //  32 : "Evse Sequence Error"
  //  31 : "CP PP Lost"
  //  30 : "HeartBeat Error"
  //  27 : "Warning No PWM"
  //  26 : "Step Precharge"
  //  25 : "Step Cable Check"
  //  24 : "Step CPD"
  //  23 : "Step Auth"
  //  20 : "Step Communcation Setup"
  //  15 : "Timeout Session Stop Resp"
  //  14 : "Timeout Welding Detection Resp"
  //  13 : "Timeout Current Demand Resp"
  //  12 : "Timeout Power Delivery Resp"
  //  11 : "Timeout Precharge Resp"
  //  10 : "Timeout Cable Check Resp"
  //  9 : "Timeout CPD Response"
  //  8 : "Timeout Auth Response"
  //  7 : "Timeout Payment Selection Resp"
  //  6 : "Timeout Service Discovery Resp"
  //  5 : "Timeout Session Setup Response"
  //  4 : "Timeout SAP Response"
  //  3 : "Timout SDP Sequence"
  //  2 : "Timeout Link Detection"
  //  1 : "Timeout Slac Sequence"
  //  0 : "NONE"
  uint8_t EVCC_ERROR_CODES;                  //      Bits= 8

  //  19 : "Wrong_Energy_Transfer_Mode"
  //  18 : "No_Charge_Service_Selected"
  //  16 : "Charging_Profile_Invalid"
  //  14 : "Power_Delivery_Not_Applied"
  //  13 : "Wrong_Charge_Parameter"
  //  6 : "Payment_Selection_Invalid"
  //  5 : "Service_ID_Invalid"
  //  2 : "Sequence_Error"
  //  0 : "No_Error"
  uint8_t EVSE_ERROR_CODE;                   //      Bits= 8

  //  4 : "CP_STATE E"
  //  3 : "CP_STATE D"
  //  2 : "CP_STATE C"
  //  1 : "CP_STATE B"
  //  0 : "CP_STATE A"
  uint8_t CP_STATE;                          //      Bits= 8

  //  2 : "ISO:15118:2:2013"
  //  1 : "DIN:70121:2012"
  //  0 : "NONE"
  uint8_t SELECTED_APP_PROTOCOL;             //      Bits= 8

#else

  //  9 : "EV_Ready Flag Reception Failure"
  //  8 : "Extrenal Actuator Unlock"
  //  7 : "Actuator Locking Fault"
  //  36 : "Emergency PLC Chip Status"
  //  35 : "Emergency Pilot Status"
  //  34 : "Emergency Proximity Status"
  //  33 : "Emergency High Temperature"
  //  32 : "Emergency HeartBeat Error"
  //  31 : "Emergency From Evse"
  //  6 : "Vehicle Hv Failure"
  //  5 : "Evse Invalid Isolation Status"
  //  4 : "Evse Wrong Charge Parameter"
  //  3 : "Evse Wrong Response Code"
  //  0 : "NONE"
  uint8_t TERMINATION_DETAIL;                //      Bits= 8

  //  39 : "EVSE Emergency"
  //  38 : "EVSE Isolation Status Error"
  //  37 : "Wrong Charge Parameter"
  //  36 : "Locking Actuator Error"
  //  34 : "Temperature Fault"
  //  33 : "Response Code Error"
  //  32 : "Evse Sequence Error"
  //  31 : "CP PP Lost"
  //  30 : "HeartBeat Error"
  //  27 : "Warning No PWM"
  //  26 : "Step Precharge"
  //  25 : "Step Cable Check"
  //  24 : "Step CPD"
  //  23 : "Step Auth"
  //  20 : "Step Communcation Setup"
  //  15 : "Timeout Session Stop Resp"
  //  14 : "Timeout Welding Detection Resp"
  //  13 : "Timeout Current Demand Resp"
  //  12 : "Timeout Power Delivery Resp"
  //  11 : "Timeout Precharge Resp"
  //  10 : "Timeout Cable Check Resp"
  //  9 : "Timeout CPD Response"
  //  8 : "Timeout Auth Response"
  //  7 : "Timeout Payment Selection Resp"
  //  6 : "Timeout Service Discovery Resp"
  //  5 : "Timeout Session Setup Response"
  //  4 : "Timeout SAP Response"
  //  3 : "Timout SDP Sequence"
  //  2 : "Timeout Link Detection"
  //  1 : "Timeout Slac Sequence"
  //  0 : "NONE"
  uint8_t EVCC_ERROR_CODES;                  //      Bits= 8

  //  19 : "Wrong_Energy_Transfer_Mode"
  //  18 : "No_Charge_Service_Selected"
  //  16 : "Charging_Profile_Invalid"
  //  14 : "Power_Delivery_Not_Applied"
  //  13 : "Wrong_Charge_Parameter"
  //  6 : "Payment_Selection_Invalid"
  //  5 : "Service_ID_Invalid"
  //  2 : "Sequence_Error"
  //  0 : "No_Error"
  uint8_t EVSE_ERROR_CODE;                   //      Bits= 8

  //  4 : "CP_STATE E"
  //  3 : "CP_STATE D"
  //  2 : "CP_STATE C"
  //  1 : "CP_STATE B"
  //  0 : "CP_STATE A"
  uint8_t CP_STATE;                          //      Bits= 8

  //  2 : "ISO:15118:2:2013"
  //  1 : "DIN:70121:2012"
  //  0 : "NONE"
  uint8_t SELECTED_APP_PROTOCOL;             //      Bits= 8

#endif // ECUDB_USE_BITS_SIGNAL

#ifdef ECUDB_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // ECUDB_USE_DIAG_MONITORS

} EVCC_TX_5_t;

// Function signatures

uint32_t Unpack_EVCC_RX_1_ecudb(EVCC_RX_1_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef ECUDB_USE_CANSTRUCT
uint32_t Pack_EVCC_RX_1_ecudb(EVCC_RX_1_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_EVCC_RX_1_ecudb(EVCC_RX_1_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // ECUDB_USE_CANSTRUCT

uint32_t Unpack_EVCC_RX_2_ecudb(EVCC_RX_2_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef ECUDB_USE_CANSTRUCT
uint32_t Pack_EVCC_RX_2_ecudb(EVCC_RX_2_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_EVCC_RX_2_ecudb(EVCC_RX_2_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // ECUDB_USE_CANSTRUCT

uint32_t Unpack_EVCC_TX_1_ecudb(EVCC_TX_1_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef ECUDB_USE_CANSTRUCT
uint32_t Pack_EVCC_TX_1_ecudb(EVCC_TX_1_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_EVCC_TX_1_ecudb(EVCC_TX_1_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // ECUDB_USE_CANSTRUCT

uint32_t Unpack_EVCC_TX_3_ecudb(EVCC_TX_3_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef ECUDB_USE_CANSTRUCT
uint32_t Pack_EVCC_TX_3_ecudb(EVCC_TX_3_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_EVCC_TX_3_ecudb(EVCC_TX_3_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // ECUDB_USE_CANSTRUCT

uint32_t Unpack_EVCC_TX_4_ecudb(EVCC_TX_4_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef ECUDB_USE_CANSTRUCT
uint32_t Pack_EVCC_TX_4_ecudb(EVCC_TX_4_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_EVCC_TX_4_ecudb(EVCC_TX_4_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // ECUDB_USE_CANSTRUCT

uint32_t Unpack_EVCC_TX_2_ecudb(EVCC_TX_2_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef ECUDB_USE_CANSTRUCT
uint32_t Pack_EVCC_TX_2_ecudb(EVCC_TX_2_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_EVCC_TX_2_ecudb(EVCC_TX_2_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // ECUDB_USE_CANSTRUCT

uint32_t Unpack_EVCC_TX_5_ecudb(EVCC_TX_5_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef ECUDB_USE_CANSTRUCT
uint32_t Pack_EVCC_TX_5_ecudb(EVCC_TX_5_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_EVCC_TX_5_ecudb(EVCC_TX_5_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // ECUDB_USE_CANSTRUCT

#ifdef __cplusplus
}
#endif
