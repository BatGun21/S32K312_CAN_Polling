// Generator version : v3.1
// DBC filename      : EVCC_CAN_DB_V2_4.dbc
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// DBC file version
#define VER_ECUDB_MAJ_FMON (0U)
#define VER_ECUDB_MIN_FMON (0U)

#include "ecudb-config.h"

#ifdef ECUDB_USE_DIAG_MONITORS

#include "canmonitorutil.h"
/*
This file contains the prototypes of all the functions that will be called
from each Unpack_*name* function to detect DBC related errors
It is the user responsibility to defined these functions in the
separated .c file. If it won't be done the linkage error will happen
*/

#ifdef ECUDB_USE_MONO_FMON

void _FMon_MONO_ecudb(FrameMonitor_t* _mon, uint32_t msgid);

#define FMon_EVCC_RX_1_ecudb(x, y) _FMon_MONO_ecudb((x), (y))
#define FMon_EVCC_RX_2_ecudb(x, y) _FMon_MONO_ecudb((x), (y))
#define FMon_EVCC_TX_1_ecudb(x, y) _FMon_MONO_ecudb((x), (y))
#define FMon_EVCC_TX_3_ecudb(x, y) _FMon_MONO_ecudb((x), (y))
#define FMon_EVCC_TX_4_ecudb(x, y) _FMon_MONO_ecudb((x), (y))
#define FMon_EVCC_TX_2_ecudb(x, y) _FMon_MONO_ecudb((x), (y))
#define FMon_EVCC_TX_5_ecudb(x, y) _FMon_MONO_ecudb((x), (y))

#else

void _FMon_EVCC_RX_1_ecudb(FrameMonitor_t* _mon, uint32_t msgid);
void _FMon_EVCC_RX_2_ecudb(FrameMonitor_t* _mon, uint32_t msgid);
void _FMon_EVCC_TX_1_ecudb(FrameMonitor_t* _mon, uint32_t msgid);
void _FMon_EVCC_TX_3_ecudb(FrameMonitor_t* _mon, uint32_t msgid);
void _FMon_EVCC_TX_4_ecudb(FrameMonitor_t* _mon, uint32_t msgid);
void _FMon_EVCC_TX_2_ecudb(FrameMonitor_t* _mon, uint32_t msgid);
void _FMon_EVCC_TX_5_ecudb(FrameMonitor_t* _mon, uint32_t msgid);

#define FMon_EVCC_RX_1_ecudb(x, y) _FMon_EVCC_RX_1_ecudb((x), (y))
#define FMon_EVCC_RX_2_ecudb(x, y) _FMon_EVCC_RX_2_ecudb((x), (y))
#define FMon_EVCC_TX_1_ecudb(x, y) _FMon_EVCC_TX_1_ecudb((x), (y))
#define FMon_EVCC_TX_3_ecudb(x, y) _FMon_EVCC_TX_3_ecudb((x), (y))
#define FMon_EVCC_TX_4_ecudb(x, y) _FMon_EVCC_TX_4_ecudb((x), (y))
#define FMon_EVCC_TX_2_ecudb(x, y) _FMon_EVCC_TX_2_ecudb((x), (y))
#define FMon_EVCC_TX_5_ecudb(x, y) _FMon_EVCC_TX_5_ecudb((x), (y))

#endif

#endif // ECUDB_USE_DIAG_MONITORS

#ifdef __cplusplus
}
#endif
