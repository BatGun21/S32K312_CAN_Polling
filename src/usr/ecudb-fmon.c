// Generator version : v3.1
// DBC filename      : EVCC_CAN_DB_V2_4.dbc
#include "ecudb-fmon.h"

#ifdef ECUDB_USE_DIAG_MONITORS

/*
Put the monitor function content here, keep in mind -
next generation will completely clear all manually added code (!)
*/

#ifdef ECUDB_USE_MONO_FMON

void _FMon_MONO_ecudb(FrameMonitor_t* _mon, uint32_t msgid)
{
  (void)_mon;
  (void)msgid;
}

#else

void _FMon_EVCC_RX_1_ecudb(FrameMonitor_t* _mon, uint32_t msgid)
{
  (void)_mon;
  (void)msgid;
}

void _FMon_EVCC_RX_2_ecudb(FrameMonitor_t* _mon, uint32_t msgid)
{
  (void)_mon;
  (void)msgid;
}

void _FMon_EVCC_TX_1_ecudb(FrameMonitor_t* _mon, uint32_t msgid)
{
  (void)_mon;
  (void)msgid;
}

void _FMon_EVCC_TX_3_ecudb(FrameMonitor_t* _mon, uint32_t msgid)
{
  (void)_mon;
  (void)msgid;
}

void _FMon_EVCC_TX_4_ecudb(FrameMonitor_t* _mon, uint32_t msgid)
{
  (void)_mon;
  (void)msgid;
}

void _FMon_EVCC_TX_2_ecudb(FrameMonitor_t* _mon, uint32_t msgid)
{
  (void)_mon;
  (void)msgid;
}

void _FMon_EVCC_TX_5_ecudb(FrameMonitor_t* _mon, uint32_t msgid)
{
  (void)_mon;
  (void)msgid;
}

#endif // ECUDB_USE_MONO_FMON

#endif // ECUDB_USE_DIAG_MONITORS
