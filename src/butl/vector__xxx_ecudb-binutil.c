// Generator version : v3.1
// DBC filename      : EVCC_CAN_DB_V2_4.dbc
#include "vector__xxx_ecudb-binutil.h"

// DBC file version
#if (VER_ECUDB_MAJ != (0U)) || (VER_ECUDB_MIN != (0U))
#error The VECTOR__XXX_ECUDB binutil source file has inconsistency with core dbc lib!
#endif

#ifdef __DEF_VECTOR__XXX_ECUDB__

vector__xxx_ecudb_rx_t vector__xxx_ecudb_rx;

vector__xxx_ecudb_tx_t vector__xxx_ecudb_tx;

#endif // __DEF_VECTOR__XXX_ECUDB__

uint32_t vector__xxx_ecudb_Receive(vector__xxx_ecudb_rx_t* _m, const uint8_t* _d, uint32_t _id, uint8_t dlc_)
{
 uint32_t recid = 0;
 if ((_id >= 0x340U) && (_id < 0x361U)) {
  if (_id == 0x340U) {
   recid = Unpack_EVCC_RX_2_ecudb(&(_m->EVCC_RX_2), _d, dlc_);
  } else {
   if (_id == 0x350U) {
    recid = Unpack_EVCC_TX_1_ecudb(&(_m->EVCC_TX_1), _d, dlc_);
   } else if (_id == 0x360U) {
    recid = Unpack_EVCC_TX_3_ecudb(&(_m->EVCC_TX_3), _d, dlc_);
   }
  }
 } else {
  if (_id == 0x361U) {
   recid = Unpack_EVCC_TX_4_ecudb(&(_m->EVCC_TX_4), _d, dlc_);
  } else {
   if (_id == 0xECC01U) {
    recid = Unpack_EVCC_TX_2_ecudb(&(_m->EVCC_TX_2), _d, dlc_);
   } else if (_id == 0xECC02U) {
    recid = Unpack_EVCC_TX_5_ecudb(&(_m->EVCC_TX_5), _d, dlc_);
   }
  }
 }

 return recid;
}

