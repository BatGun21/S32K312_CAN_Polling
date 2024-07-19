// Generator version : v3.1
// DBC filename      : EVCC_CAN_DB_V2_4.dbc
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "dbccodeconf.h"

#include "ecudb.h"

typedef struct
{
  EVCC_RX_2_t EVCC_RX_2;
  EVCC_TX_1_t EVCC_TX_1;
  EVCC_TX_3_t EVCC_TX_3;
  EVCC_TX_4_t EVCC_TX_4;
  EVCC_TX_2_t EVCC_TX_2;
  EVCC_TX_5_t EVCC_TX_5;
} vector__xxx_ecudb_rx_t;

typedef struct
{
  EVCC_RX_1_t EVCC_RX_1;
  EVCC_RX_2_t EVCC_RX_2;
} vector__xxx_ecudb_tx_t;

uint32_t vector__xxx_ecudb_Receive(vector__xxx_ecudb_rx_t* m, const uint8_t* d, uint32_t msgid, uint8_t dlc);

#ifdef __DEF_VECTOR__XXX_ECUDB__

extern vector__xxx_ecudb_rx_t vector__xxx_ecudb_rx;

extern vector__xxx_ecudb_tx_t vector__xxx_ecudb_tx;

#endif // __DEF_VECTOR__XXX_ECUDB__

#ifdef __cplusplus
}
#endif
