// Generator version : v3.1
// DBC filename      : EVCC_CAN_DB_V2_4.dbc
#include "evcc_ecudb-binutil.h"

// DBC file version
#if (VER_ECUDB_MAJ != (0U)) || (VER_ECUDB_MIN != (0U))
#error The EVCC_ECUDB binutil source file has inconsistency with core dbc lib!
#endif

#ifdef __DEF_EVCC_ECUDB__

evcc_ecudb_rx_t evcc_ecudb_rx;

evcc_ecudb_tx_t evcc_ecudb_tx;

#endif // __DEF_EVCC_ECUDB__

uint32_t evcc_ecudb_Receive(evcc_ecudb_rx_t* _m, const uint8_t* _d, uint32_t _id, uint8_t dlc_)
{
 uint32_t recid = 0;
 if (_id == 0x310U) {
  recid = Unpack_EVCC_RX_1_ecudb(&(_m->EVCC_RX_1), _d, dlc_);
 } else if (_id == 0x340U) {
  recid = Unpack_EVCC_RX_2_ecudb(&(_m->EVCC_RX_2), _d, dlc_);
 }

 return recid;
}

