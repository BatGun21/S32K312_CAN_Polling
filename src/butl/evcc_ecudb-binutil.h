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
  EVCC_RX_1_t EVCC_RX_1;
  EVCC_RX_2_t EVCC_RX_2;
} evcc_ecudb_rx_t;

typedef struct
{
  EVCC_TX_1_t EVCC_TX_1;
  EVCC_TX_3_t EVCC_TX_3;
  EVCC_TX_4_t EVCC_TX_4;
  EVCC_TX_2_t EVCC_TX_2;
  EVCC_TX_5_t EVCC_TX_5;
} evcc_ecudb_tx_t;

uint32_t evcc_ecudb_Receive(evcc_ecudb_rx_t* m, const uint8_t* d, uint32_t msgid, uint8_t dlc);

#ifdef __DEF_EVCC_ECUDB__

extern evcc_ecudb_rx_t evcc_ecudb_rx;

extern evcc_ecudb_tx_t evcc_ecudb_tx;

#endif // __DEF_EVCC_ECUDB__

#ifdef __cplusplus
}
#endif
