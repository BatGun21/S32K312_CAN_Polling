// Generator version : v3.1
// DBC filename      : EVCC_CAN_DB_V2_4.dbc
#include "ecudb.h"


// DBC file version
#if (VER_ECUDB_MAJ != (0U)) || (VER_ECUDB_MIN != (0U))
#error The ECUDB dbc source files have different versions
#endif

#ifdef ECUDB_USE_DIAG_MONITORS
// Function prototypes to be called each time CAN frame is unpacked
// FMon function may detect RC, CRC or DLC violation
#include "ecudb-fmon.h"

#endif // ECUDB_USE_DIAG_MONITORS

// This macro guard for the case when you need to enable
// using diag monitors but there is no necessity in proper
// SysTick provider. For providing one you need define macro
// before this line - in dbccodeconf.h

#ifndef GetSystemTick
#define GetSystemTick() (0u)
#endif

// This macro guard is for the case when you want to build
// app with enabled optoin auto CSM, but don't yet have
// proper getframehash implementation

#ifndef GetFrameHash
#define GetFrameHash(a,b,c,d,e) (0u)
#endif

// This function performs extension of sign for the signals
// whose bit width value is not aligned to one of power of 2 or less than 8.
// The types 'bitext_t' and 'ubitext_t' define the biggest bit width which
// can be correctly handled. You need to select type which can contain
// n+1 bits where n is the largest signed signal width. For example if
// the most wide signed signal has a width of 31 bits you need to set
// bitext_t as int32_t and ubitext_t as uint32_t
// Defined these typedefs in @dbccodeconf.h or locally in 'dbcdrvname'-config.h
static bitext_t __ext_sig__(ubitext_t val, uint8_t bits)
{
  ubitext_t const m = (ubitext_t) (1u << (bits - 1u));
  return ((val ^ m) - m);
}

uint32_t Unpack_EVCC_RX_1_ecudb(EVCC_RX_1_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->EV_MAX_CHRG_CURR_LIMIT_ro = (uint16_t) ( ((_d[1] & (0xFFU)) << 8U) | (_d[2] & (0xFFU)) );
#ifdef ECUDB_USE_SIGFLOAT
  _m->EV_MAX_CHRG_CURR_LIMIT_phys = (sigfloat_t)(ECUDB_EV_MAX_CHRG_CURR_LIMIT_ro_fromS(_m->EV_MAX_CHRG_CURR_LIMIT_ro));
#endif // ECUDB_USE_SIGFLOAT

  _m->SOC_ro = (uint8_t) ( (_d[3] & (0xFFU)) );
#ifdef ECUDB_USE_SIGFLOAT
  _m->SOC_phys = (sigfloat_t)(ECUDB_SOC_ro_fromS(_m->SOC_ro));
#endif // ECUDB_USE_SIGFLOAT

  _m->EV_CONTINEOUS_CHRG_CURR_LIMIT = (uint8_t) ( (_d[4] & (0xFFU)) );
  _m->BATT_PACK_PRESENT_VOLTAGE_ro = (uint16_t) ( ((_d[5] & (0xFFU)) << 8U) | (_d[6] & (0xFFU)) );
#ifdef ECUDB_USE_SIGFLOAT
  _m->BATT_PACK_PRESENT_VOLTAGE_phys = (sigfloat_t)(ECUDB_BATT_PACK_PRESENT_VOLTAGE_ro_fromS(_m->BATT_PACK_PRESENT_VOLTAGE_ro));
#endif // ECUDB_USE_SIGFLOAT

  _m->EVSE_Protocol_Priority_Selection = (uint8_t) ( (_d[7] & (0xFFU)) );

#ifdef ECUDB_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < EVCC_RX_1_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_EVCC_RX_1_ecudb(&_m->mon1, EVCC_RX_1_CANID);
#endif // ECUDB_USE_DIAG_MONITORS

  return EVCC_RX_1_CANID;
}

#ifdef ECUDB_USE_CANSTRUCT

uint32_t Pack_EVCC_RX_1_ecudb(EVCC_RX_1_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < ECUDB_VALIDATE_DLC(EVCC_RX_1_DLC); cframe->Data[i++] = ECUDB_INITIAL_BYTE_VALUE);

#ifdef ECUDB_USE_SIGFLOAT
  _m->EV_MAX_CHRG_CURR_LIMIT_ro = (uint16_t) ECUDB_EV_MAX_CHRG_CURR_LIMIT_ro_toS(_m->EV_MAX_CHRG_CURR_LIMIT_phys);
  _m->SOC_ro = (uint8_t) ECUDB_SOC_ro_toS(_m->SOC_phys);
  _m->BATT_PACK_PRESENT_VOLTAGE_ro = (uint16_t) ECUDB_BATT_PACK_PRESENT_VOLTAGE_ro_toS(_m->BATT_PACK_PRESENT_VOLTAGE_phys);
#endif // ECUDB_USE_SIGFLOAT

  cframe->Data[1] |= (uint8_t) ( ((_m->EV_MAX_CHRG_CURR_LIMIT_ro >> 8U) & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( (_m->EV_MAX_CHRG_CURR_LIMIT_ro & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( (_m->SOC_ro & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( (_m->EV_CONTINEOUS_CHRG_CURR_LIMIT & (0xFFU)) );
  cframe->Data[5] |= (uint8_t) ( ((_m->BATT_PACK_PRESENT_VOLTAGE_ro >> 8U) & (0xFFU)) );
  cframe->Data[6] |= (uint8_t) ( (_m->BATT_PACK_PRESENT_VOLTAGE_ro & (0xFFU)) );
  cframe->Data[7] |= (uint8_t) ( (_m->EVSE_Protocol_Priority_Selection & (0xFFU)) );

  cframe->MsgId = (uint32_t) EVCC_RX_1_CANID;
  cframe->DLC = (uint8_t) EVCC_RX_1_DLC;
  cframe->IDE = (uint8_t) EVCC_RX_1_IDE;
  return EVCC_RX_1_CANID;
}

#else

uint32_t Pack_EVCC_RX_1_ecudb(EVCC_RX_1_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < ECUDB_VALIDATE_DLC(EVCC_RX_1_DLC); _d[i++] = ECUDB_INITIAL_BYTE_VALUE);

#ifdef ECUDB_USE_SIGFLOAT
  _m->EV_MAX_CHRG_CURR_LIMIT_ro = (uint16_t) ECUDB_EV_MAX_CHRG_CURR_LIMIT_ro_toS(_m->EV_MAX_CHRG_CURR_LIMIT_phys);
  _m->SOC_ro = (uint8_t) ECUDB_SOC_ro_toS(_m->SOC_phys);
  _m->BATT_PACK_PRESENT_VOLTAGE_ro = (uint16_t) ECUDB_BATT_PACK_PRESENT_VOLTAGE_ro_toS(_m->BATT_PACK_PRESENT_VOLTAGE_phys);
#endif // ECUDB_USE_SIGFLOAT

  _d[1] |= (uint8_t) ( ((_m->EV_MAX_CHRG_CURR_LIMIT_ro >> 8U) & (0xFFU)) );
  _d[2] |= (uint8_t) ( (_m->EV_MAX_CHRG_CURR_LIMIT_ro & (0xFFU)) );
  _d[3] |= (uint8_t) ( (_m->SOC_ro & (0xFFU)) );
  _d[4] |= (uint8_t) ( (_m->EV_CONTINEOUS_CHRG_CURR_LIMIT & (0xFFU)) );
  _d[5] |= (uint8_t) ( ((_m->BATT_PACK_PRESENT_VOLTAGE_ro >> 8U) & (0xFFU)) );
  _d[6] |= (uint8_t) ( (_m->BATT_PACK_PRESENT_VOLTAGE_ro & (0xFFU)) );
  _d[7] |= (uint8_t) ( (_m->EVSE_Protocol_Priority_Selection & (0xFFU)) );

  *_len = (uint8_t) EVCC_RX_1_DLC;
  *_ide = (uint8_t) EVCC_RX_1_IDE;
  return EVCC_RX_1_CANID;
}

#endif // ECUDB_USE_CANSTRUCT

uint32_t Unpack_EVCC_RX_2_ecudb(EVCC_RX_2_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->EV_READY_FLAG = (uint8_t) ( (_d[0] & (0x01U)) );
  _m->CHARGING_COMPLETE_FLAG = (uint8_t) ( ((_d[0] >> 1U) & (0x01U)) );
  _m->VEH_STOP_CHARGING_FLAG = (uint8_t) ( ((_d[0] >> 2U) & (0x01U)) );
  _m->HV_READY = (uint8_t) ( ((_d[0] >> 3U) & (0x01U)) );
  _m->FORCE_ACTUATOR_UNLOCK = (uint8_t) ( ((_d[0] >> 4U) & (0x01U)) );
  _m->EV_ERROR_CODE = (uint8_t) ( (_d[1] & (0xFFU)) );
  _m->REMAINING_BATT_CAPACITY = (uint8_t) ( (_d[4] & (0xFFU)) );
  _m->NOMINAL_BATT_CAPACITY = (uint16_t) ( ((_d[5] & (0xFFU)) << 8U) | (_d[6] & (0xFFU)) );

#ifdef ECUDB_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < EVCC_RX_2_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_EVCC_RX_2_ecudb(&_m->mon1, EVCC_RX_2_CANID);
#endif // ECUDB_USE_DIAG_MONITORS

  return EVCC_RX_2_CANID;
}

#ifdef ECUDB_USE_CANSTRUCT

uint32_t Pack_EVCC_RX_2_ecudb(EVCC_RX_2_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < ECUDB_VALIDATE_DLC(EVCC_RX_2_DLC); cframe->Data[i++] = ECUDB_INITIAL_BYTE_VALUE);

  cframe->Data[0] |= (uint8_t) ( (_m->EV_READY_FLAG & (0x01U)) | ((_m->CHARGING_COMPLETE_FLAG & (0x01U)) << 1U) | ((_m->VEH_STOP_CHARGING_FLAG & (0x01U)) << 2U) | ((_m->HV_READY & (0x01U)) << 3U) | ((_m->FORCE_ACTUATOR_UNLOCK & (0x01U)) << 4U) );
  cframe->Data[1] |= (uint8_t) ( (_m->EV_ERROR_CODE & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( (_m->REMAINING_BATT_CAPACITY & (0xFFU)) );
  cframe->Data[5] |= (uint8_t) ( ((_m->NOMINAL_BATT_CAPACITY >> 8U) & (0xFFU)) );
  cframe->Data[6] |= (uint8_t) ( (_m->NOMINAL_BATT_CAPACITY & (0xFFU)) );

  cframe->MsgId = (uint32_t) EVCC_RX_2_CANID;
  cframe->DLC = (uint8_t) EVCC_RX_2_DLC;
  cframe->IDE = (uint8_t) EVCC_RX_2_IDE;
  return EVCC_RX_2_CANID;
}

#else

uint32_t Pack_EVCC_RX_2_ecudb(EVCC_RX_2_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < ECUDB_VALIDATE_DLC(EVCC_RX_2_DLC); _d[i++] = ECUDB_INITIAL_BYTE_VALUE);

  _d[0] |= (uint8_t) ( (_m->EV_READY_FLAG & (0x01U)) | ((_m->CHARGING_COMPLETE_FLAG & (0x01U)) << 1U) | ((_m->VEH_STOP_CHARGING_FLAG & (0x01U)) << 2U) | ((_m->HV_READY & (0x01U)) << 3U) | ((_m->FORCE_ACTUATOR_UNLOCK & (0x01U)) << 4U) );
  _d[1] |= (uint8_t) ( (_m->EV_ERROR_CODE & (0xFFU)) );
  _d[4] |= (uint8_t) ( (_m->REMAINING_BATT_CAPACITY & (0xFFU)) );
  _d[5] |= (uint8_t) ( ((_m->NOMINAL_BATT_CAPACITY >> 8U) & (0xFFU)) );
  _d[6] |= (uint8_t) ( (_m->NOMINAL_BATT_CAPACITY & (0xFFU)) );

  *_len = (uint8_t) EVCC_RX_2_DLC;
  *_ide = (uint8_t) EVCC_RX_2_IDE;
  return EVCC_RX_2_CANID;
}

#endif // ECUDB_USE_CANSTRUCT

uint32_t Unpack_EVCC_TX_1_ecudb(EVCC_TX_1_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->EVCC_STATUS_CODE = (uint8_t) ( (_d[0] & (0xFFU)) );
  _m->PP_GUN_RESISTANCE = (uint16_t) ( ((_d[1] & (0xFFU)) << 8U) | (_d[2] & (0xFFU)) );
  _m->CP_DUTY_CYCLE = (uint8_t) ( (_d[3] & (0xFFU)) );
  _m->EVCC_READY = (uint8_t) ( (_d[4] & (0x01U)) );
  _m->GUN_DETECTED = (uint8_t) ( ((_d[4] >> 1U) & (0x01U)) );
  _m->POSITIVE_CONTACTOR_CONTROL = (uint8_t) ( ((_d[4] >> 2U) & (0x01U)) );
  _m->CHARGING_STATUS = (uint8_t) ( ((_d[4] >> 3U) & (0x01U)) );
  _m->NEGATIVE_CONTACTOR_CONTROL = (uint8_t) ( ((_d[4] >> 4U) & (0x01U)) );
  _m->SELECTED_ATTENUATION_IN_DB = (uint8_t) ( (_d[5] & (0xFFU)) );
  _m->EV_Error_Code = (uint8_t) ( (_d[6] & (0xFFU)) );
  _m->DIFFERENTIAL_CURRENT_MEAS = (uint8_t) ( (_d[7] & (0xFFU)) );

#ifdef ECUDB_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < EVCC_TX_1_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_EVCC_TX_1_ecudb(&_m->mon1, EVCC_TX_1_CANID);
#endif // ECUDB_USE_DIAG_MONITORS

  return EVCC_TX_1_CANID;
}

#ifdef ECUDB_USE_CANSTRUCT

uint32_t Pack_EVCC_TX_1_ecudb(EVCC_TX_1_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < ECUDB_VALIDATE_DLC(EVCC_TX_1_DLC); cframe->Data[i++] = ECUDB_INITIAL_BYTE_VALUE);

  cframe->Data[0] |= (uint8_t) ( (_m->EVCC_STATUS_CODE & (0xFFU)) );
  cframe->Data[1] |= (uint8_t) ( ((_m->PP_GUN_RESISTANCE >> 8U) & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( (_m->PP_GUN_RESISTANCE & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( (_m->CP_DUTY_CYCLE & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( (_m->EVCC_READY & (0x01U)) | ((_m->GUN_DETECTED & (0x01U)) << 1U) | ((_m->POSITIVE_CONTACTOR_CONTROL & (0x01U)) << 2U) | ((_m->CHARGING_STATUS & (0x01U)) << 3U) | ((_m->NEGATIVE_CONTACTOR_CONTROL & (0x01U)) << 4U) );
  cframe->Data[5] |= (uint8_t) ( (_m->SELECTED_ATTENUATION_IN_DB & (0xFFU)) );
  cframe->Data[6] |= (uint8_t) ( (_m->EV_Error_Code & (0xFFU)) );
  cframe->Data[7] |= (uint8_t) ( (_m->DIFFERENTIAL_CURRENT_MEAS & (0xFFU)) );

  cframe->MsgId = (uint32_t) EVCC_TX_1_CANID;
  cframe->DLC = (uint8_t) EVCC_TX_1_DLC;
  cframe->IDE = (uint8_t) EVCC_TX_1_IDE;
  return EVCC_TX_1_CANID;
}

#else

uint32_t Pack_EVCC_TX_1_ecudb(EVCC_TX_1_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < ECUDB_VALIDATE_DLC(EVCC_TX_1_DLC); _d[i++] = ECUDB_INITIAL_BYTE_VALUE);

  _d[0] |= (uint8_t) ( (_m->EVCC_STATUS_CODE & (0xFFU)) );
  _d[1] |= (uint8_t) ( ((_m->PP_GUN_RESISTANCE >> 8U) & (0xFFU)) );
  _d[2] |= (uint8_t) ( (_m->PP_GUN_RESISTANCE & (0xFFU)) );
  _d[3] |= (uint8_t) ( (_m->CP_DUTY_CYCLE & (0xFFU)) );
  _d[4] |= (uint8_t) ( (_m->EVCC_READY & (0x01U)) | ((_m->GUN_DETECTED & (0x01U)) << 1U) | ((_m->POSITIVE_CONTACTOR_CONTROL & (0x01U)) << 2U) | ((_m->CHARGING_STATUS & (0x01U)) << 3U) | ((_m->NEGATIVE_CONTACTOR_CONTROL & (0x01U)) << 4U) );
  _d[5] |= (uint8_t) ( (_m->SELECTED_ATTENUATION_IN_DB & (0xFFU)) );
  _d[6] |= (uint8_t) ( (_m->EV_Error_Code & (0xFFU)) );
  _d[7] |= (uint8_t) ( (_m->DIFFERENTIAL_CURRENT_MEAS & (0xFFU)) );

  *_len = (uint8_t) EVCC_TX_1_DLC;
  *_ide = (uint8_t) EVCC_TX_1_IDE;
  return EVCC_TX_1_CANID;
}

#endif // ECUDB_USE_CANSTRUCT

uint32_t Unpack_EVCC_TX_3_ecudb(EVCC_TX_3_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->SOFTWARE_VERSION_ro = (uint8_t) ( (_d[0] & (0xFFU)) );
#ifdef ECUDB_USE_SIGFLOAT
  _m->SOFTWARE_VERSION_phys = (sigfloat_t)(ECUDB_SOFTWARE_VERSION_ro_fromS(_m->SOFTWARE_VERSION_ro));
#endif // ECUDB_USE_SIGFLOAT

  _m->CHARGER_MAX_CURRENT_ro = (uint16_t) ( ((_d[1] & (0xFFU)) << 8U) | (_d[2] & (0xFFU)) );
#ifdef ECUDB_USE_SIGFLOAT
  _m->CHARGER_MAX_CURRENT_phys = (sigfloat_t)(ECUDB_CHARGER_MAX_CURRENT_ro_fromS(_m->CHARGER_MAX_CURRENT_ro));
#endif // ECUDB_USE_SIGFLOAT

  _m->CHARGER_MIN_CURRENT_ro = (uint16_t) ( ((_d[3] & (0xFFU)) << 8U) | (_d[4] & (0xFFU)) );
#ifdef ECUDB_USE_SIGFLOAT
  _m->CHARGER_MIN_CURRENT_phys = (sigfloat_t)(ECUDB_CHARGER_MIN_CURRENT_ro_fromS(_m->CHARGER_MIN_CURRENT_ro));
#endif // ECUDB_USE_SIGFLOAT

  _m->CHARGER_MAX_VOLTAGE_ro = (uint16_t) ( ((_d[5] & (0xFFU)) << 8U) | (_d[6] & (0xFFU)) );
#ifdef ECUDB_USE_SIGFLOAT
  _m->CHARGER_MAX_VOLTAGE_phys = (sigfloat_t)(ECUDB_CHARGER_MAX_VOLTAGE_ro_fromS(_m->CHARGER_MAX_VOLTAGE_ro));
#endif // ECUDB_USE_SIGFLOAT

#ifdef ECUDB_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < EVCC_TX_3_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_EVCC_TX_3_ecudb(&_m->mon1, EVCC_TX_3_CANID);
#endif // ECUDB_USE_DIAG_MONITORS

  return EVCC_TX_3_CANID;
}

#ifdef ECUDB_USE_CANSTRUCT

uint32_t Pack_EVCC_TX_3_ecudb(EVCC_TX_3_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < ECUDB_VALIDATE_DLC(EVCC_TX_3_DLC); cframe->Data[i++] = ECUDB_INITIAL_BYTE_VALUE);

#ifdef ECUDB_USE_SIGFLOAT
  _m->SOFTWARE_VERSION_ro = (uint8_t) ECUDB_SOFTWARE_VERSION_ro_toS(_m->SOFTWARE_VERSION_phys);
  _m->CHARGER_MAX_CURRENT_ro = (uint16_t) ECUDB_CHARGER_MAX_CURRENT_ro_toS(_m->CHARGER_MAX_CURRENT_phys);
  _m->CHARGER_MIN_CURRENT_ro = (uint16_t) ECUDB_CHARGER_MIN_CURRENT_ro_toS(_m->CHARGER_MIN_CURRENT_phys);
  _m->CHARGER_MAX_VOLTAGE_ro = (uint16_t) ECUDB_CHARGER_MAX_VOLTAGE_ro_toS(_m->CHARGER_MAX_VOLTAGE_phys);
#endif // ECUDB_USE_SIGFLOAT

  cframe->Data[0] |= (uint8_t) ( (_m->SOFTWARE_VERSION_ro & (0xFFU)) );
  cframe->Data[1] |= (uint8_t) ( ((_m->CHARGER_MAX_CURRENT_ro >> 8U) & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( (_m->CHARGER_MAX_CURRENT_ro & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( ((_m->CHARGER_MIN_CURRENT_ro >> 8U) & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( (_m->CHARGER_MIN_CURRENT_ro & (0xFFU)) );
  cframe->Data[5] |= (uint8_t) ( ((_m->CHARGER_MAX_VOLTAGE_ro >> 8U) & (0xFFU)) );
  cframe->Data[6] |= (uint8_t) ( (_m->CHARGER_MAX_VOLTAGE_ro & (0xFFU)) );

  cframe->MsgId = (uint32_t) EVCC_TX_3_CANID;
  cframe->DLC = (uint8_t) EVCC_TX_3_DLC;
  cframe->IDE = (uint8_t) EVCC_TX_3_IDE;
  return EVCC_TX_3_CANID;
}

#else

uint32_t Pack_EVCC_TX_3_ecudb(EVCC_TX_3_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < ECUDB_VALIDATE_DLC(EVCC_TX_3_DLC); _d[i++] = ECUDB_INITIAL_BYTE_VALUE);

#ifdef ECUDB_USE_SIGFLOAT
  _m->SOFTWARE_VERSION_ro = (uint8_t) ECUDB_SOFTWARE_VERSION_ro_toS(_m->SOFTWARE_VERSION_phys);
  _m->CHARGER_MAX_CURRENT_ro = (uint16_t) ECUDB_CHARGER_MAX_CURRENT_ro_toS(_m->CHARGER_MAX_CURRENT_phys);
  _m->CHARGER_MIN_CURRENT_ro = (uint16_t) ECUDB_CHARGER_MIN_CURRENT_ro_toS(_m->CHARGER_MIN_CURRENT_phys);
  _m->CHARGER_MAX_VOLTAGE_ro = (uint16_t) ECUDB_CHARGER_MAX_VOLTAGE_ro_toS(_m->CHARGER_MAX_VOLTAGE_phys);
#endif // ECUDB_USE_SIGFLOAT

  _d[0] |= (uint8_t) ( (_m->SOFTWARE_VERSION_ro & (0xFFU)) );
  _d[1] |= (uint8_t) ( ((_m->CHARGER_MAX_CURRENT_ro >> 8U) & (0xFFU)) );
  _d[2] |= (uint8_t) ( (_m->CHARGER_MAX_CURRENT_ro & (0xFFU)) );
  _d[3] |= (uint8_t) ( ((_m->CHARGER_MIN_CURRENT_ro >> 8U) & (0xFFU)) );
  _d[4] |= (uint8_t) ( (_m->CHARGER_MIN_CURRENT_ro & (0xFFU)) );
  _d[5] |= (uint8_t) ( ((_m->CHARGER_MAX_VOLTAGE_ro >> 8U) & (0xFFU)) );
  _d[6] |= (uint8_t) ( (_m->CHARGER_MAX_VOLTAGE_ro & (0xFFU)) );

  *_len = (uint8_t) EVCC_TX_3_DLC;
  *_ide = (uint8_t) EVCC_TX_3_IDE;
  return EVCC_TX_3_CANID;
}

#endif // ECUDB_USE_CANSTRUCT

uint32_t Unpack_EVCC_TX_4_ecudb(EVCC_TX_4_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->CHARGER_MIN_VOLTAGE_ro = (uint16_t) ( ((_d[0] & (0xFFU)) << 8U) | (_d[1] & (0xFFU)) );
#ifdef ECUDB_USE_SIGFLOAT
  _m->CHARGER_MIN_VOLTAGE_phys = (sigfloat_t)(ECUDB_CHARGER_MIN_VOLTAGE_ro_fromS(_m->CHARGER_MIN_VOLTAGE_ro));
#endif // ECUDB_USE_SIGFLOAT

  _m->CHARGER_MAX_POWER_ro = (uint16_t) ( ((_d[2] & (0xFFU)) << 8U) | (_d[3] & (0xFFU)) );
#ifdef ECUDB_USE_SIGFLOAT
  _m->CHARGER_MAX_POWER_phys = (uint32_t) ECUDB_CHARGER_MAX_POWER_ro_fromS(_m->CHARGER_MAX_POWER_ro);
#endif // ECUDB_USE_SIGFLOAT

  _m->CHARGER_PRESENT_VOLTAGE_ro = (uint16_t) ( ((_d[4] & (0xFFU)) << 8U) | (_d[5] & (0xFFU)) );
#ifdef ECUDB_USE_SIGFLOAT
  _m->CHARGER_PRESENT_VOLTAGE_phys = (sigfloat_t)(ECUDB_CHARGER_PRESENT_VOLTAGE_ro_fromS(_m->CHARGER_PRESENT_VOLTAGE_ro));
#endif // ECUDB_USE_SIGFLOAT

  _m->CHARGER_PRESENT_CURRENT_ro = (uint16_t) ( ((_d[6] & (0xFFU)) << 8U) | (_d[7] & (0xFFU)) );
#ifdef ECUDB_USE_SIGFLOAT
  _m->CHARGER_PRESENT_CURRENT_phys = (sigfloat_t)(ECUDB_CHARGER_PRESENT_CURRENT_ro_fromS(_m->CHARGER_PRESENT_CURRENT_ro));
#endif // ECUDB_USE_SIGFLOAT

#ifdef ECUDB_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < EVCC_TX_4_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_EVCC_TX_4_ecudb(&_m->mon1, EVCC_TX_4_CANID);
#endif // ECUDB_USE_DIAG_MONITORS

  return EVCC_TX_4_CANID;
}

#ifdef ECUDB_USE_CANSTRUCT

uint32_t Pack_EVCC_TX_4_ecudb(EVCC_TX_4_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < ECUDB_VALIDATE_DLC(EVCC_TX_4_DLC); cframe->Data[i++] = ECUDB_INITIAL_BYTE_VALUE);

#ifdef ECUDB_USE_SIGFLOAT
  _m->CHARGER_MIN_VOLTAGE_ro = (uint16_t) ECUDB_CHARGER_MIN_VOLTAGE_ro_toS(_m->CHARGER_MIN_VOLTAGE_phys);
  _m->CHARGER_MAX_POWER_ro = (uint16_t) ECUDB_CHARGER_MAX_POWER_ro_toS(_m->CHARGER_MAX_POWER_phys);
  _m->CHARGER_PRESENT_VOLTAGE_ro = (uint16_t) ECUDB_CHARGER_PRESENT_VOLTAGE_ro_toS(_m->CHARGER_PRESENT_VOLTAGE_phys);
  _m->CHARGER_PRESENT_CURRENT_ro = (uint16_t) ECUDB_CHARGER_PRESENT_CURRENT_ro_toS(_m->CHARGER_PRESENT_CURRENT_phys);
#endif // ECUDB_USE_SIGFLOAT

  cframe->Data[0] |= (uint8_t) ( ((_m->CHARGER_MIN_VOLTAGE_ro >> 8U) & (0xFFU)) );
  cframe->Data[1] |= (uint8_t) ( (_m->CHARGER_MIN_VOLTAGE_ro & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( ((_m->CHARGER_MAX_POWER_ro >> 8U) & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( (_m->CHARGER_MAX_POWER_ro & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( ((_m->CHARGER_PRESENT_VOLTAGE_ro >> 8U) & (0xFFU)) );
  cframe->Data[5] |= (uint8_t) ( (_m->CHARGER_PRESENT_VOLTAGE_ro & (0xFFU)) );
  cframe->Data[6] |= (uint8_t) ( ((_m->CHARGER_PRESENT_CURRENT_ro >> 8U) & (0xFFU)) );
  cframe->Data[7] |= (uint8_t) ( (_m->CHARGER_PRESENT_CURRENT_ro & (0xFFU)) );

  cframe->MsgId = (uint32_t) EVCC_TX_4_CANID;
  cframe->DLC = (uint8_t) EVCC_TX_4_DLC;
  cframe->IDE = (uint8_t) EVCC_TX_4_IDE;
  return EVCC_TX_4_CANID;
}

#else

uint32_t Pack_EVCC_TX_4_ecudb(EVCC_TX_4_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < ECUDB_VALIDATE_DLC(EVCC_TX_4_DLC); _d[i++] = ECUDB_INITIAL_BYTE_VALUE);

#ifdef ECUDB_USE_SIGFLOAT
  _m->CHARGER_MIN_VOLTAGE_ro = (uint16_t) ECUDB_CHARGER_MIN_VOLTAGE_ro_toS(_m->CHARGER_MIN_VOLTAGE_phys);
  _m->CHARGER_MAX_POWER_ro = (uint16_t) ECUDB_CHARGER_MAX_POWER_ro_toS(_m->CHARGER_MAX_POWER_phys);
  _m->CHARGER_PRESENT_VOLTAGE_ro = (uint16_t) ECUDB_CHARGER_PRESENT_VOLTAGE_ro_toS(_m->CHARGER_PRESENT_VOLTAGE_phys);
  _m->CHARGER_PRESENT_CURRENT_ro = (uint16_t) ECUDB_CHARGER_PRESENT_CURRENT_ro_toS(_m->CHARGER_PRESENT_CURRENT_phys);
#endif // ECUDB_USE_SIGFLOAT

  _d[0] |= (uint8_t) ( ((_m->CHARGER_MIN_VOLTAGE_ro >> 8U) & (0xFFU)) );
  _d[1] |= (uint8_t) ( (_m->CHARGER_MIN_VOLTAGE_ro & (0xFFU)) );
  _d[2] |= (uint8_t) ( ((_m->CHARGER_MAX_POWER_ro >> 8U) & (0xFFU)) );
  _d[3] |= (uint8_t) ( (_m->CHARGER_MAX_POWER_ro & (0xFFU)) );
  _d[4] |= (uint8_t) ( ((_m->CHARGER_PRESENT_VOLTAGE_ro >> 8U) & (0xFFU)) );
  _d[5] |= (uint8_t) ( (_m->CHARGER_PRESENT_VOLTAGE_ro & (0xFFU)) );
  _d[6] |= (uint8_t) ( ((_m->CHARGER_PRESENT_CURRENT_ro >> 8U) & (0xFFU)) );
  _d[7] |= (uint8_t) ( (_m->CHARGER_PRESENT_CURRENT_ro & (0xFFU)) );

  *_len = (uint8_t) EVCC_TX_4_DLC;
  *_ide = (uint8_t) EVCC_TX_4_IDE;
  return EVCC_TX_4_CANID;
}

#endif // ECUDB_USE_CANSTRUCT

uint32_t Unpack_EVCC_TX_2_ecudb(EVCC_TX_2_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->TEMPERATURE_1_VALUE_ro = (int16_t) __ext_sig__(( ((_d[0] & (0xFFU)) << 8U) | (_d[1] & (0xFFU)) ), 16);
#ifdef ECUDB_USE_SIGFLOAT
  _m->TEMPERATURE_1_VALUE_phys = (sigfloat_t)(ECUDB_TEMPERATURE_1_VALUE_ro_fromS(_m->TEMPERATURE_1_VALUE_ro));
#endif // ECUDB_USE_SIGFLOAT

  _m->TEMPERATURE_2_VALUE_ro = (int16_t) __ext_sig__(( ((_d[2] & (0xFFU)) << 8U) | (_d[3] & (0xFFU)) ), 16);
#ifdef ECUDB_USE_SIGFLOAT
  _m->TEMPERATURE_2_VALUE_phys = (sigfloat_t)(ECUDB_TEMPERATURE_2_VALUE_ro_fromS(_m->TEMPERATURE_2_VALUE_ro));
#endif // ECUDB_USE_SIGFLOAT

  _m->OBC_DERATING_FACTOR = (uint8_t) ( (_d[4] & (0xFFU)) );
  _m->TEMP_1_FAULT = (uint8_t) ( ((_d[5] >> 1U) & (0x01U)) );
  _m->TEMP_2_FAULT = (uint8_t) ( ((_d[5] >> 2U) & (0x01U)) );
  _m->GUN_LOCK_FAULT = (uint8_t) ( ((_d[5] >> 3U) & (0x01U)) );
  _m->VEHICLE_IMMOBILIZE = (uint8_t) ( ((_d[5] >> 4U) & (0x01U)) );
  _m->GUN_LOCK_FEEDBACK = (uint8_t) ( ((_d[5] >> 5U) & (0x01U)) );
  _m->EVCC_GUN_LOCK_REQUEST_STATUS = (uint8_t) ( ((_d[5] >> 6U) & (0x01U)) );
  _m->EVCC_GUN_UNLOCK_REQUEST_STATUS = (uint8_t) ( ((_d[5] >> 7U) & (0x01U)) );

#ifdef ECUDB_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < EVCC_TX_2_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_EVCC_TX_2_ecudb(&_m->mon1, EVCC_TX_2_CANID);
#endif // ECUDB_USE_DIAG_MONITORS

  return EVCC_TX_2_CANID;
}

#ifdef ECUDB_USE_CANSTRUCT

uint32_t Pack_EVCC_TX_2_ecudb(EVCC_TX_2_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < ECUDB_VALIDATE_DLC(EVCC_TX_2_DLC); cframe->Data[i++] = ECUDB_INITIAL_BYTE_VALUE);

#ifdef ECUDB_USE_SIGFLOAT
  _m->TEMPERATURE_1_VALUE_ro = (int16_t) ECUDB_TEMPERATURE_1_VALUE_ro_toS(_m->TEMPERATURE_1_VALUE_phys);
  _m->TEMPERATURE_2_VALUE_ro = (int16_t) ECUDB_TEMPERATURE_2_VALUE_ro_toS(_m->TEMPERATURE_2_VALUE_phys);
#endif // ECUDB_USE_SIGFLOAT

  cframe->Data[0] |= (uint8_t) ( ((_m->TEMPERATURE_1_VALUE_ro >> 8U) & (0xFFU)) );
  cframe->Data[1] |= (uint8_t) ( (_m->TEMPERATURE_1_VALUE_ro & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( ((_m->TEMPERATURE_2_VALUE_ro >> 8U) & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( (_m->TEMPERATURE_2_VALUE_ro & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( (_m->OBC_DERATING_FACTOR & (0xFFU)) );
  cframe->Data[5] |= (uint8_t) ( ((_m->TEMP_1_FAULT & (0x01U)) << 1U) | ((_m->TEMP_2_FAULT & (0x01U)) << 2U) | ((_m->GUN_LOCK_FAULT & (0x01U)) << 3U) | ((_m->VEHICLE_IMMOBILIZE & (0x01U)) << 4U) | ((_m->GUN_LOCK_FEEDBACK & (0x01U)) << 5U) | ((_m->EVCC_GUN_LOCK_REQUEST_STATUS & (0x01U)) << 6U) | ((_m->EVCC_GUN_UNLOCK_REQUEST_STATUS & (0x01U)) << 7U) );

  cframe->MsgId = (uint32_t) EVCC_TX_2_CANID;
  cframe->DLC = (uint8_t) EVCC_TX_2_DLC;
  cframe->IDE = (uint8_t) EVCC_TX_2_IDE;
  return EVCC_TX_2_CANID;
}

#else

uint32_t Pack_EVCC_TX_2_ecudb(EVCC_TX_2_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < ECUDB_VALIDATE_DLC(EVCC_TX_2_DLC); _d[i++] = ECUDB_INITIAL_BYTE_VALUE);

#ifdef ECUDB_USE_SIGFLOAT
  _m->TEMPERATURE_1_VALUE_ro = (int16_t) ECUDB_TEMPERATURE_1_VALUE_ro_toS(_m->TEMPERATURE_1_VALUE_phys);
  _m->TEMPERATURE_2_VALUE_ro = (int16_t) ECUDB_TEMPERATURE_2_VALUE_ro_toS(_m->TEMPERATURE_2_VALUE_phys);
#endif // ECUDB_USE_SIGFLOAT

  _d[0] |= (uint8_t) ( ((_m->TEMPERATURE_1_VALUE_ro >> 8U) & (0xFFU)) );
  _d[1] |= (uint8_t) ( (_m->TEMPERATURE_1_VALUE_ro & (0xFFU)) );
  _d[2] |= (uint8_t) ( ((_m->TEMPERATURE_2_VALUE_ro >> 8U) & (0xFFU)) );
  _d[3] |= (uint8_t) ( (_m->TEMPERATURE_2_VALUE_ro & (0xFFU)) );
  _d[4] |= (uint8_t) ( (_m->OBC_DERATING_FACTOR & (0xFFU)) );
  _d[5] |= (uint8_t) ( ((_m->TEMP_1_FAULT & (0x01U)) << 1U) | ((_m->TEMP_2_FAULT & (0x01U)) << 2U) | ((_m->GUN_LOCK_FAULT & (0x01U)) << 3U) | ((_m->VEHICLE_IMMOBILIZE & (0x01U)) << 4U) | ((_m->GUN_LOCK_FEEDBACK & (0x01U)) << 5U) | ((_m->EVCC_GUN_LOCK_REQUEST_STATUS & (0x01U)) << 6U) | ((_m->EVCC_GUN_UNLOCK_REQUEST_STATUS & (0x01U)) << 7U) );

  *_len = (uint8_t) EVCC_TX_2_DLC;
  *_ide = (uint8_t) EVCC_TX_2_IDE;
  return EVCC_TX_2_CANID;
}

#endif // ECUDB_USE_CANSTRUCT

uint32_t Unpack_EVCC_TX_5_ecudb(EVCC_TX_5_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->TERMINATION_DETAIL = (uint8_t) ( (_d[1] & (0xFFU)) );
  _m->EVCC_ERROR_CODES = (uint8_t) ( (_d[2] & (0xFFU)) );
  _m->EVSE_ERROR_CODE = (uint8_t) ( (_d[3] & (0xFFU)) );
  _m->CP_STATE = (uint8_t) ( (_d[4] & (0xFFU)) );
  _m->SELECTED_APP_PROTOCOL = (uint8_t) ( (_d[6] & (0xFFU)) );

#ifdef ECUDB_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < EVCC_TX_5_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_EVCC_TX_5_ecudb(&_m->mon1, EVCC_TX_5_CANID);
#endif // ECUDB_USE_DIAG_MONITORS

  return EVCC_TX_5_CANID;
}

#ifdef ECUDB_USE_CANSTRUCT

uint32_t Pack_EVCC_TX_5_ecudb(EVCC_TX_5_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < ECUDB_VALIDATE_DLC(EVCC_TX_5_DLC); cframe->Data[i++] = ECUDB_INITIAL_BYTE_VALUE);

  cframe->Data[1] |= (uint8_t) ( (_m->TERMINATION_DETAIL & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( (_m->EVCC_ERROR_CODES & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( (_m->EVSE_ERROR_CODE & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( (_m->CP_STATE & (0xFFU)) );
  cframe->Data[6] |= (uint8_t) ( (_m->SELECTED_APP_PROTOCOL & (0xFFU)) );

  cframe->MsgId = (uint32_t) EVCC_TX_5_CANID;
  cframe->DLC = (uint8_t) EVCC_TX_5_DLC;
  cframe->IDE = (uint8_t) EVCC_TX_5_IDE;
  return EVCC_TX_5_CANID;
}

#else

uint32_t Pack_EVCC_TX_5_ecudb(EVCC_TX_5_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < ECUDB_VALIDATE_DLC(EVCC_TX_5_DLC); _d[i++] = ECUDB_INITIAL_BYTE_VALUE);

  _d[1] |= (uint8_t) ( (_m->TERMINATION_DETAIL & (0xFFU)) );
  _d[2] |= (uint8_t) ( (_m->EVCC_ERROR_CODES & (0xFFU)) );
  _d[3] |= (uint8_t) ( (_m->EVSE_ERROR_CODE & (0xFFU)) );
  _d[4] |= (uint8_t) ( (_m->CP_STATE & (0xFFU)) );
  _d[6] |= (uint8_t) ( (_m->SELECTED_APP_PROTOCOL & (0xFFU)) );

  *_len = (uint8_t) EVCC_TX_5_DLC;
  *_ide = (uint8_t) EVCC_TX_5_IDE;
  return EVCC_TX_5_CANID;
}

#endif // ECUDB_USE_CANSTRUCT

