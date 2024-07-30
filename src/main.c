#include "Mcal.h"
#include "Clock_Ip.h"
#include "Clock_Ip_Cfg.h"
#include "Siul2_Port_Ip.h"
#include "Siul2_Port_Ip_Cfg.h"
#include "Siul2_Dio_Ip.h"
#include "FlexCAN_Ip.h"
#include "IntCtrl_Ip.h"
#include "Pit_Ip.h"
#include "Lpuart_Uart_Ip.h"
#include "OsIf.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "ecudb.h"
#include "ecudb-fmon.h"
#include "ecudb-config.h"
#include "dbccodeconf.h"
#include "evcc_ecudb-binutil.h"
#include "vector__xxx_ecudb-binutil.h"
#include "canmonitorutil.h"

#define MSG_ID_RX_1 0x350U
#define MSG_ID_RX_2 0xECC01U
#define MSG_ID_RX_3 0x361U
#define MSG_ID_RX_4 0x360U
#define MSG_ID_RX_5 0xECC02U

#define RX_MB_IDX_1 1U
#define RX_MB_IDX_2 2U
#define RX_MB_IDX_3 3U
#define RX_MB_IDX_4 4U
#define RX_MB_IDX_5 5U

Flexcan_Ip_MsgBuffType rxData1, rxData2, rxData3, rxData4, rxData5;

#define TX_MB_IDX 0U
#define LPUART_UART_INSTANCE    0
#define BUFFER_SIZE            1000

#define RED_LED_PIN                 13u
#define GREEN_LED_PIN               14u
#define LED_PORT                PTA_H_HALF

#define FXOSC_CLOCK_FREQ   16000000U

#define LUT_SIZE 600

typedef struct {
    uint32_t timestamp;  // in 100 ms units
    uint16_t maxCurrentLimit;  // in Amps
    uint8_t soc;  // in %
    uint8_t evContinuousChargingCurrent;  // in Amps
    uint16_t batteryPackPresentVoltage;  // in Volts
    uint8_t remainingBattCapacity;  // in kWh
    uint16_t nominalBattCapacity;  // in Ah
} ChargingDataPoint;


/* PIT instance used - 0 */
#define PIT_INST_0 0U
#define CH_0 0U
#define PIT_PERIOD 300000

/* Global flag updated in interrupt */
// Define the CAN message buffer for EVCC_TX_1
ChargingDataPoint chargingLUT[LUT_SIZE];
EVCC_TX_1_t EVCC_TX_1_Msg;
EVCC_TX_2_t EVCC_TX_2_Msg;
EVCC_TX_3_t EVCC_TX_3_Msg;
EVCC_TX_4_t EVCC_TX_4_Msg;
EVCC_TX_5_t EVCC_TX_5_Msg;
EVCC_RX_1_t EVCC_RX_1_Msg;
EVCC_RX_2_t EVCC_RX_2_Msg;
volatile uint8 sendCanMsgFlag = 0U;
uint8 U8_counter = 0U;
volatile int exit_code = 0;
uint16_t currentLUTIndex;

/* Global Buffers */
Flexcan_Ip_DataInfoType rx_info; // For CAN RX configuration
Flexcan_Ip_DataInfoType tx_info; // For CAN TX configuration
uint8_t txBuffer[BUFFER_SIZE];
uint8_t rxBuffer[BUFFER_SIZE];
Flexcan_Ip_MsgBuffType rxData;
char uartString[BUFFER_SIZE]; // String to hold the formatted CAN data
ChargingDataPoint chargingLUT[LUT_SIZE];

/* Function Prototypes */
extern ISR(PIT_0_ISR);
void PIT_Init(void);
void PitNotification(void);
void Clock_Init(void);
void LED_Init(void);
void LPUART_Init(void);
void UART_Error_Handler(Lpuart_Uart_Ip_StatusType Status);
void CAN_Init(void);
void sendCANMessage(void);
void processCANMessage(Flexcan_Ip_StatusType canStatus, Flexcan_Ip_MsgBuffType *rxData, const char *msgIdStr);
void receiveCANMessage(void);
void setEVCC_RX_1_Values(void);
void setEVCC_RX_2_Values(void);
void generateLUT(void);
bool checkAndSetHVFlag(void);
bool checkAndSetVehicleStopChargingFlag(void);
bool checkAndSetForceActuatorFlag(void);
bool checkAndSetChargingCompleteFlag(void);
bool checkIsolation(void);
bool checkActuator(void);
uint8_t check_SOC(void);


int main(void)
{
    Clock_Init();

    /* Initialize the Osif driver */
    OsIf_Init(NULL_PTR);

    /* Init Pins */
    Siul2_Port_Ip_Init(NUM_OF_CONFIGURED_PINS0, g_pin_mux_InitConfigArr0);

    Siul2_Dio_Ip_WritePin(CAN0_STB_PORT, CAN0_STB_PIN, 0U);   // CAN0_STB  : PTC-20

    /* Initialize interrupts */
    IntCtrl_Ip_Init(&IntCtrlConfig_0);

    PIT_Init();
    CAN_Init();
    LPUART_Init();
    LED_Init();
    generateLUT();

    Siul2_Dio_Ip_WritePin(CAN0_STB_PORT, CAN0_STB_PIN, 1U);   //CAN0_STB

    while (1)
    {
    	receiveCANMessage();
    	if(sendCanMsgFlag)
    	{
    		sendCANMessage();
    		Siul2_Dio_Ip_WritePin(LED_PORT, LED_GREEN_PIN, 0); // Turn off GREEN LED
    		sendCanMsgFlag = 0;
    	}
    }

    return 0;
}

/* Function Definitions */
void PIT_Init(void)
{
    /* Initialize PIT instance 0 - Channel 0 */
    IntCtrl_Ip_EnableIrq(PIT0_IRQn);
    Pit_Ip_Init(PIT_INST_0, &PIT_0_InitConfig_PB);
    Pit_Ip_InitChannel(PIT_INST_0, PIT_0_CH_0);
    Pit_Ip_EnableChannelInterrupt(PIT_INST_0, CH_0);
    Pit_Ip_StartChannel(PIT_INST_0, CH_0, PIT_PERIOD);
}

void PitNotification(void)
{
    U8_counter++;
    if(U8_counter >= 100)
    {
    	sendCanMsgFlag = 1U;
    	Siul2_Dio_Ip_WritePin(LED_PORT, LED_GREEN_PIN, 1); // Turn on GREEN LED
    }
    if (U8_counter>=110)
    {
    	U8_counter = 0;
    }
}

void Clock_Init(void)
{
    /* Initialize the clock */
    Clock_Ip_StatusType clockStatus;
    clockStatus = Clock_Ip_Init(&Clock_Ip_aClockConfig[0]);
    if (clockStatus != CLOCK_IP_SUCCESS || Clock_Ip_GetClockFrequency(FXOSC_CLK) != FXOSC_CLOCK_FREQ)
    {
        exit_code = -1;
    }

#if (CLOCK_IP_HAS_PLL_CLK)
    while (CLOCK_IP_PLL_LOCKED != Clock_Ip_GetPllStatus())
    {
        /* Busy wait until the System PLL is locked */
    }
    Clock_Ip_DistributePll();
#endif
}

void LED_Init(void)
{
    Siul2_Port_Ip_SetOutputBuffer(PORTA_H_HALF, 29, TRUE, PORT_MUX_AS_GPIO); //PTA29 as Output LED_RED
    Siul2_Port_Ip_SetOutputBuffer(PORTA_H_HALF, 30, TRUE, PORT_MUX_AS_GPIO); //PTA30 as Output LED_GREEN
    Siul2_Port_Ip_SetOutputBuffer(PORTA_H_HALF, 31, TRUE, PORT_MUX_AS_GPIO); //PTA31 as Output LED_BLUE
}

void LPUART_Init(void)
{
    Clock_Ip_EnableModuleClock(LPUART0_CLK);
    Lpuart_Uart_Ip_Init(LPUART_UART_INSTANCE, &Lpuart_Uart_Ip_xHwConfigPB_0);
}

void UART_Error_Handler(Lpuart_Uart_Ip_StatusType Status)
{
    if (Status == LPUART_UART_IP_STATUS_ERROR)
    {
        Siul2_Dio_Ip_WritePin(LED_PORT, LED_RED_PIN, 1); // Turn on RED LED
    }
    else if(Status == LPUART_UART_IP_STATUS_BUSY)
    {
        Siul2_Dio_Ip_WritePin(LED_PORT, LED_BLUE_PIN, 1); // Turn on GREEN LED
    }
    else if (Status == LPUART_UART_IP_STATUS_TIMEOUT)
    {
        Siul2_Dio_Ip_WritePin(LED_PORT, LED_BLUE_PIN, 1); // Turn on BLUE LED
    }
    else if (Status == LPUART_UART_IP_STATUS_SUCCESS)
    {
        Siul2_Dio_Ip_WritePin(LED_PORT, LED_RED_PIN, 0); // Turn off RED LED
        Siul2_Dio_Ip_WritePin(LED_PORT, LED_BLUE_PIN, 0); // Turn off BLUE LED
        Siul2_Dio_Ip_WritePin(LED_PORT, LED_GREEN_PIN, 0); // Turn off GREEN LED
    }
}

void CAN_Init(void)
{
    FlexCAN_Ip_Init(INST_FLEXCAN_0, &FlexCAN_State0, &FlexCAN_Config0);

    FlexCAN_Ip_EnterFreezeMode(INST_FLEXCAN_0);

    rx_info.msg_id_type = FLEXCAN_MSG_ID_EXT;  // Set to extended ID type
    rx_info.data_length = 8;
    rx_info.is_polling = TRUE;
    rx_info.is_remote = FALSE;

    // Configure RX message buffers for each ID
    FlexCAN_Ip_ConfigRxMb(INST_FLEXCAN_0, RX_MB_IDX_1, &rx_info, MSG_ID_RX_1);
    FlexCAN_Ip_ConfigRxMb(INST_FLEXCAN_0, RX_MB_IDX_2, &rx_info, MSG_ID_RX_2);
    FlexCAN_Ip_ConfigRxMb(INST_FLEXCAN_0, RX_MB_IDX_3, &rx_info, MSG_ID_RX_3);
    FlexCAN_Ip_ConfigRxMb(INST_FLEXCAN_0, RX_MB_IDX_4, &rx_info, MSG_ID_RX_4);
    FlexCAN_Ip_ConfigRxMb(INST_FLEXCAN_0, RX_MB_IDX_5, &rx_info, MSG_ID_RX_5);

    FlexCAN_Ip_ExitFreezeMode(INST_FLEXCAN_0);
}

void generateLUT(void) {
    uint32_t timestamp = 0;
    float soc = 1.0;  // Start from 1% SOC
    float maxCurrentLimit = 100.0;  // in Amps
    float batteryPackPresentVoltage = 288.0;  // in Volts
    float remainingBattCapacity = 1.0;  // in kWh, just an example
    float nominalBattCapacity = 100.0;  // in Ah

    for (int i = 0; i < LUT_SIZE; i++) {
        chargingLUT[i].timestamp = timestamp;
        chargingLUT[i].maxCurrentLimit = (uint16_t)maxCurrentLimit;
        chargingLUT[i].soc = (uint8_t)soc;
        chargingLUT[i].evContinuousChargingCurrent = 50;  // assuming a constant value, can be updated
        chargingLUT[i].batteryPackPresentVoltage = (uint16_t)batteryPackPresentVoltage;
        chargingLUT[i].remainingBattCapacity = (uint8_t)remainingBattCapacity;
        chargingLUT[i].nominalBattCapacity = (uint16_t)nominalBattCapacity;

        timestamp += 100;  // Increment time stamp by 100 ms
        soc += 0.165f;  // Increment SOC to reach 100% in 1 minute (60/600)
        remainingBattCapacity += 0.165f / 100.0f * 75.0f / 100.0f;  // Example value increment
    }
}

void processCANMessage(Flexcan_Ip_StatusType canStatus, Flexcan_Ip_MsgBuffType *rxData, const char *msgIdStr)
{
    if (canStatus == FLEXCAN_STATUS_SUCCESS)
    {
        if (rxData->msgId == MSG_ID_RX_1)
        {
            Unpack_EVCC_TX_1_ecudb(&EVCC_TX_1_Msg, rxData->data, rxData->dataLen);
//            snprintf((char *)uartString, BUFFER_SIZE,
//                     "Received CAN ID %s: 0x%08lX, EVCC_STATUS_CODE: %d, PP_GUN_RESISTANCE: %d, CP_DUTY_CYCLE: %d%%, EVCC_READY: %d, GUN_DETECTED: %d, POSITIVE_CONTACTOR_CONTROL: %d, CHARGING_STATUS: %d, NEGATIVE_CONTACTOR_CONTROL: %d, SELECTED_ATTENUATION_IN_DB: %d, EV_Error_Code: %d, DIFFERENTIAL_CURRENT_MEAS: %d\r\n",
//                     msgIdStr, rxData->msgId,
//                     EVCC_TX_1_Msg.EVCC_STATUS_CODE, EVCC_TX_1_Msg.PP_GUN_RESISTANCE, EVCC_TX_1_Msg.CP_DUTY_CYCLE,
//                     EVCC_TX_1_Msg.EVCC_READY, EVCC_TX_1_Msg.GUN_DETECTED, EVCC_TX_1_Msg.POSITIVE_CONTACTOR_CONTROL,
//                     EVCC_TX_1_Msg.CHARGING_STATUS, EVCC_TX_1_Msg.NEGATIVE_CONTACTOR_CONTROL, EVCC_TX_1_Msg.SELECTED_ATTENUATION_IN_DB,
//                     EVCC_TX_1_Msg.EV_Error_Code, EVCC_TX_1_Msg.DIFFERENTIAL_CURRENT_MEAS);
        }
        else if (rxData->msgId == MSG_ID_RX_2)
        {
            Unpack_EVCC_TX_2_ecudb(&EVCC_TX_2_Msg, rxData->data, rxData->dataLen);
//            snprintf((char *)uartString, BUFFER_SIZE,
//                     "Received CAN ID %s: 0x%08lX, TEMPERATURE_1_VALUE: %d, TEMPERATURE_2_VALUE: %d, OBC_DERATING_FACTOR: %d%%, TEMP_1_FAULT: %d, TEMP_2_FAULT: %d, GUN_LOCK_FAULT: %d, VEHICLE_IMMOBILIZE: %d, GUN_LOCK_FEEDBACK: %d, EVCC_GUN_LOCK_REQUEST_STATUS: %d, EVCC_GUN_UNLOCK_REQUEST_STATUS: %d\r\n",
//                     msgIdStr, rxData->msgId,
//                     EVCC_TX_2_Msg.TEMPERATURE_1_VALUE_ro, EVCC_TX_2_Msg.TEMPERATURE_2_VALUE_ro,
//                     EVCC_TX_2_Msg.OBC_DERATING_FACTOR, EVCC_TX_2_Msg.TEMP_1_FAULT, EVCC_TX_2_Msg.TEMP_2_FAULT,
//                     EVCC_TX_2_Msg.GUN_LOCK_FAULT, EVCC_TX_2_Msg.VEHICLE_IMMOBILIZE, EVCC_TX_2_Msg.GUN_LOCK_FEEDBACK,
//                     EVCC_TX_2_Msg.EVCC_GUN_LOCK_REQUEST_STATUS, EVCC_TX_2_Msg.EVCC_GUN_UNLOCK_REQUEST_STATUS);
        }
        else if (rxData->msgId == MSG_ID_RX_3)
        {
            Unpack_EVCC_TX_3_ecudb(&EVCC_TX_3_Msg, rxData->data, rxData->dataLen);
//            snprintf((char *)uartString, BUFFER_SIZE,
//                     "Received CAN ID %s: 0x%08lX, SOFTWARE_VERSION: %d, CHARGER_MAX_CURRENT: %d, CHARGER_MIN_CURRENT: %d, CHARGER_MAX_VOLTAGE: %d\r\n",
//                     msgIdStr, rxData->msgId,
//                     EVCC_TX_3_Msg.SOFTWARE_VERSION_ro, EVCC_TX_3_Msg.CHARGER_MAX_CURRENT_ro,
//                     EVCC_TX_3_Msg.CHARGER_MIN_CURRENT_ro, EVCC_TX_3_Msg.CHARGER_MAX_VOLTAGE_ro);
        }
        else if (rxData->msgId == MSG_ID_RX_4)
        {
            Unpack_EVCC_TX_4_ecudb(&EVCC_TX_4_Msg, rxData->data, rxData->dataLen);
//            snprintf((char *)uartString, BUFFER_SIZE,
//                     "Received CAN ID %s: 0x%08lX, CHARGER_MIN_VOLTAGE: %d, CHARGER_MAX_POWER: %d, CHARGER_PRESENT_VOLTAGE: %d, CHARGER_PRESENT_CURRENT: %d\r\n",
//                     msgIdStr, rxData->msgId,
//                     EVCC_TX_4_Msg.CHARGER_MIN_VOLTAGE_ro, EVCC_TX_4_Msg.CHARGER_MAX_POWER_ro,
//                     EVCC_TX_4_Msg.CHARGER_PRESENT_VOLTAGE_ro, EVCC_TX_4_Msg.CHARGER_PRESENT_CURRENT_ro);
        }
        else if (rxData->msgId == MSG_ID_RX_5)
        {
            Unpack_EVCC_TX_5_ecudb(&EVCC_TX_5_Msg, rxData->data, rxData->dataLen);
//            snprintf((char *)uartString, BUFFER_SIZE,
//                     "Received CAN ID %s: 0x%08lX, TERMINATION_DETAIL: %d, EVCC_ERROR_CODES: %d, EVSE_ERROR_CODE: %d, CP_STATE: %d, SELECTED_APP_PROTOCOL: %d\r\n",
//                     msgIdStr, rxData->msgId,
//                     EVCC_TX_5_Msg.TERMINATION_DETAIL, EVCC_TX_5_Msg.EVCC_ERROR_CODES,
//                     EVCC_TX_5_Msg.EVSE_ERROR_CODE, EVCC_TX_5_Msg.CP_STATE, EVCC_TX_5_Msg.SELECTED_APP_PROTOCOL);
        }
        else
        {
            snprintf((char *)uartString, BUFFER_SIZE, "Received CAN ID %s: 0x%08lX, Data: ", msgIdStr, rxData->msgId);
            for (uint8_t i = 0; i < rxData->dataLen; i++)
            {
                char byteStr[4];
                snprintf(byteStr, sizeof(byteStr), "%02X ", rxData->data[i]);
                strncat((char *)uartString, byteStr, BUFFER_SIZE - strlen((char *)uartString) - 1);
            }
            strncat((char *)uartString, "\r\n", BUFFER_SIZE - strlen((char *)uartString) - 1);
        }

        Lpuart_Uart_Ip_StatusType Uart_status = Lpuart_Uart_Ip_SyncSend(LPUART_UART_INSTANCE, (const uint8 *)uartString, strlen((char *)uartString), 50000000);
        UART_Error_Handler(Uart_status);
    }
    else if (canStatus == FLEXCAN_STATUS_TIMEOUT)
    {
        snprintf((char *)uartString, BUFFER_SIZE, "CAN receive timeout for ID %s: %d\r\n", msgIdStr, canStatus);
        Lpuart_Uart_Ip_SyncSend(LPUART_UART_INSTANCE, (const uint8 *)uartString, strlen((char *)uartString), 50000000);
        UART_Error_Handler(LPUART_UART_IP_STATUS_ERROR);
    }
}

void receiveCANMessage(void)
{
    Flexcan_Ip_StatusType canStatus1 = FlexCAN_Ip_ReceiveBlocking(INST_FLEXCAN_0, RX_MB_IDX_1, &rxData1, TRUE, 100000);
    Flexcan_Ip_StatusType canStatus2 = FlexCAN_Ip_ReceiveBlocking(INST_FLEXCAN_0, RX_MB_IDX_2, &rxData2, TRUE, 100000);
    Flexcan_Ip_StatusType canStatus3 = FlexCAN_Ip_ReceiveBlocking(INST_FLEXCAN_0, RX_MB_IDX_3, &rxData3, TRUE, 100000);
    Flexcan_Ip_StatusType canStatus4 = FlexCAN_Ip_ReceiveBlocking(INST_FLEXCAN_0, RX_MB_IDX_4, &rxData4, TRUE, 100000);
    Flexcan_Ip_StatusType canStatus5 = FlexCAN_Ip_ReceiveBlocking(INST_FLEXCAN_0, RX_MB_IDX_5, &rxData5, TRUE, 100000);

    processCANMessage(canStatus1, &rxData1, "0x350");
    processCANMessage(canStatus2, &rxData2, "0xECC01");
    processCANMessage(canStatus3, &rxData3, "0x361");
    processCANMessage(canStatus4, &rxData4, "0x360");
    processCANMessage(canStatus5, &rxData5, "0xECC02");
}

uint8_t check_SOC(void) {
    if (currentLUTIndex < LUT_SIZE) {
        return chargingLUT[currentLUTIndex].soc;
    }
    return 0;  // Default value if the index is out of range
}

bool checkIsolation(void) {
    // Check for isolation issue via UART
    char isolationMsg[] = "isolation gone";
    Lpuart_Uart_Ip_StatusType status = Lpuart_Uart_Ip_SyncReceive(LPUART_UART_INSTANCE, (uint8_t *)uartString, strlen(isolationMsg), 50000000);

    if (status == LPUART_UART_IP_STATUS_SUCCESS && strncmp((char *)uartString, isolationMsg, strlen(isolationMsg)) == 0) {
        return true;
    }
    return false;  // Assume no isolation issue
}

bool checkActuator(void) {
    // Check for actuator unlock via UART
    char actuatorMsg[] = "force unlock actuator";
    Lpuart_Uart_Ip_StatusType status = Lpuart_Uart_Ip_SyncReceive(LPUART_UART_INSTANCE, (uint8_t *)uartString, strlen(actuatorMsg), 50000000);

    if (status == LPUART_UART_IP_STATUS_SUCCESS && strncmp((char *)uartString, actuatorMsg, strlen(actuatorMsg)) == 0) {
        return true;
    }
    return false;  // Assume actuator unlock is not pressed
}


bool checkAndSetHVFlag(void) {
    bool hvIsolationOk = true;
    bool IsolationGone = checkIsolation();
    if (IsolationGone)
    {
    	 EVCC_RX_2_Msg.HV_READY = 0;
    	 hvIsolationOk = false;
    }else
    {
    	 EVCC_RX_2_Msg.HV_READY = 1;
    }
    return hvIsolationOk;
}

bool checkAndSetVehicleStopChargingFlag(void) {
    bool vehicleStopCharging = false;

    // Monitor EV error codes from transmit frame 1 byte 6
    uint8_t evErrorCode = EVCC_TX_1_Msg.EV_Error_Code;

    // Monitor EVCC and EVSE error codes
    uint8_t evccErrorCode = EVCC_TX_5_Msg.EVCC_ERROR_CODES;
    uint8_t evseErrorCode = EVCC_TX_5_Msg.EVSE_ERROR_CODE;

    if (evErrorCode != 0 || evccErrorCode != 0 || evseErrorCode != 0) {
        // Set the vehicle stop charging flag
    	EVCC_RX_2_Msg.VEH_STOP_CHARGING_FLAG = 1;
        vehicleStopCharging = true;

        // Send appropriate error message over UART
        if (evErrorCode != 0) {
            snprintf((char *)uartString, BUFFER_SIZE, "Error: EV Error Code: %d\r\n", evErrorCode);
        } else if (evccErrorCode != 0) {
            snprintf((char *)uartString, BUFFER_SIZE, "Error: EVCC Error Code: %d\r\n", evccErrorCode);
        } else if (evseErrorCode != 0) {
            snprintf((char *)uartString, BUFFER_SIZE, "Error: EVSE Error Code: %d\r\n", evccErrorCode);
        }

        Lpuart_Uart_Ip_StatusType Uart_status = Lpuart_Uart_Ip_SyncSend(LPUART_UART_INSTANCE, (const uint8 *)uartString, strlen((char *)uartString), 50000000);
        UART_Error_Handler(Uart_status);
    }

    return vehicleStopCharging;
}


bool checkAndSetForceActuatorFlag(void) {
    bool forceActuatorUnlock = false;
    bool ActuatorUnlockPressed = checkActuator();
    if (ActuatorUnlockPressed)
    {
    	 EVCC_RX_2_Msg.FORCE_ACTUATOR_UNLOCK = 1;
    	 forceActuatorUnlock = true;
    }else
    {
    	 EVCC_RX_2_Msg.FORCE_ACTUATOR_UNLOCK = 0;
    }

    return forceActuatorUnlock;
}

bool checkAndSetChargingCompleteFlag(void) {
	bool chargingComplete = false;
	uint8_t SOC = check_SOC();
    if (SOC == 100)
    {
    	EVCC_RX_2_Msg.CHARGING_COMPLETE_FLAG = 1;
    	chargingComplete = true;
    }else
    {
    	EVCC_RX_2_Msg.CHARGING_COMPLETE_FLAG = 0;
    }
    return chargingComplete;
}

void checkAndSetEVFlag(void) {
    bool ppResistanceOk = (EVCC_TX_1_Msg.PP_GUN_RESISTANCE >= 900 && EVCC_TX_1_Msg.PP_GUN_RESISTANCE <= 1100);
    bool cpDutyCycleOk = (EVCC_TX_1_Msg.CP_DUTY_CYCLE > 0 && EVCC_TX_1_Msg.CP_DUTY_CYCLE <= 10); // Typical value is 4%, so within 10%
    bool gunDetected = (EVCC_TX_1_Msg.GUN_DETECTED == 1);
    bool gunLockOk = (EVCC_TX_2_Msg.GUN_LOCK_FAULT == 0);
    bool vehicleImmobilized = (EVCC_TX_2_Msg.VEHICLE_IMMOBILIZE == 1);
    bool gunLockFeedbackOk = (EVCC_TX_2_Msg.GUN_LOCK_FEEDBACK == 1);

    bool hvFlag = checkAndSetHVFlag();
    bool vehicleStopChargingFlag = checkAndSetVehicleStopChargingFlag();
    bool forceActuatorFlag = checkAndSetForceActuatorFlag();
    bool chargingCompleteFlag = checkAndSetChargingCompleteFlag();

    if (ppResistanceOk && cpDutyCycleOk && gunDetected && gunLockOk && vehicleImmobilized && gunLockFeedbackOk &&
        hvFlag && !vehicleStopChargingFlag && !forceActuatorFlag && !chargingCompleteFlag) {
        EVCC_RX_2_Msg.EV_READY_FLAG = 1;  // Set EV Ready flag high
        snprintf((char *)uartString, BUFFER_SIZE, "EV ready for Charging\r\n");
    } else {
        // Send appropriate error message over UART
        if (!ppResistanceOk) {
            snprintf((char *)uartString, BUFFER_SIZE, "Error: PP Resistance out of range: %d ohms\r\n", EVCC_TX_1_Msg.PP_GUN_RESISTANCE);
        } else if (!cpDutyCycleOk) {
            snprintf((char *)uartString, BUFFER_SIZE, "Error: CP Duty Cycle out of range: %d%%\r\n", EVCC_TX_1_Msg.CP_DUTY_CYCLE);
        } else if (!gunDetected) {
            snprintf((char *)uartString, BUFFER_SIZE, "Error: Gun not detected\r\n");
        } else if (!gunLockOk) {
            snprintf((char *)uartString, BUFFER_SIZE, "Error: Gun lock fault\r\n");
        } else if (!vehicleImmobilized) {
            snprintf((char *)uartString, BUFFER_SIZE, "Error: Vehicle not immobilized\r\n");
        } else if (!gunLockFeedbackOk) {
            snprintf((char *)uartString, BUFFER_SIZE, "Error: Gun lock feedback not OK\r\n");
        } else if (!hvFlag) {
            snprintf((char *)uartString, BUFFER_SIZE, "Error: HV Isolation not OK\r\n");
        } else if (vehicleStopChargingFlag) {
            snprintf((char *)uartString, BUFFER_SIZE, "Error: Vehicle Stop Charging requested\r\n");
        } else if (forceActuatorFlag) {
            snprintf((char *)uartString, BUFFER_SIZE, "Error: Force Actuator Unlock requested\r\n");
        } else if (chargingCompleteFlag) {
            snprintf((char *)uartString, BUFFER_SIZE, "Charging complete\r\n");
        }
        EVCC_RX_2_Msg.EV_READY_FLAG = 0;  // Reset EV Ready flag
    }
    Lpuart_Uart_Ip_StatusType Uart_status = Lpuart_Uart_Ip_SyncSend(LPUART_UART_INSTANCE, (const uint8 *)uartString, strlen((char *)uartString), 5000000);
    UART_Error_Handler(Uart_status);
}

void setEVCC_RX_1_Values(void) {
    if (currentLUTIndex < LUT_SIZE) {
    	EVCC_RX_1_Msg.EV_MAX_CHRG_CURR_LIMIT_ro = (uint16_t)((chargingLUT[currentLUTIndex].maxCurrentLimit - 0.0) / 0.25);
    	EVCC_RX_1_Msg.SOC_ro = (uint8_t)((chargingLUT[currentLUTIndex].soc - 0.0) / 0.5);
        EVCC_RX_1_Msg.EV_CONTINEOUS_CHRG_CURR_LIMIT = chargingLUT[currentLUTIndex].evContinuousChargingCurrent;
        EVCC_RX_1_Msg.BATT_PACK_PRESENT_VOLTAGE_ro = (uint16_t)((chargingLUT[currentLUTIndex].batteryPackPresentVoltage - 0.0) / 0.25);
        EVCC_RX_1_Msg.EVSE_Protocol_Priority_Selection = 1;
    }
}

void setEVCC_RX_2_Values(void) {
    if (currentLUTIndex < LUT_SIZE) {
        EVCC_RX_2_Msg.REMAINING_BATT_CAPACITY = chargingLUT[currentLUTIndex].remainingBattCapacity;
        EVCC_RX_2_Msg.NOMINAL_BATT_CAPACITY = chargingLUT[currentLUTIndex].nominalBattCapacity;
    }
}

void sendCANMessage(void) {
    // Check and set the EV Ready flag
    checkAndSetEVFlag();
    uint8_t evcc_rx_1_data[EVCC_RX_1_DLC];
    uint8_t evcc_rx_1_len;
    uint8_t evcc_rx_1_ide;
    uint32_t evcc_rx_1_id;
    uint8_t evcc_rx_2_data[EVCC_RX_2_DLC];
    uint8_t evcc_rx_2_len;
    uint8_t evcc_rx_2_ide;
    uint32_t evcc_rx_2_id;

    // Define FlexCAN data info structure for sending
    Flexcan_Ip_DataInfoType tx_info = {
        .msg_id_type = FLEXCAN_MSG_ID_EXT,
        .data_length = EVCC_RX_1_DLC,
        .is_polling = TRUE,
        .is_remote = FALSE
    };

    // Only send CAN messages if EV Ready flag is set
    if (EVCC_RX_2_Msg.EV_READY_FLAG == 1) {
        // Set the values for EVCC_RX_1 and EVCC_RX_2
        setEVCC_RX_1_Values();
        setEVCC_RX_2_Values();

        // Pack the EVCC_RX_1 message
        evcc_rx_1_id = Pack_EVCC_RX_1_ecudb(&EVCC_RX_1_Msg, evcc_rx_1_data, &evcc_rx_1_len, &evcc_rx_1_ide);

        // Pack the EVCC_RX_2 message
        evcc_rx_2_id = Pack_EVCC_RX_2_ecudb(&EVCC_RX_2_Msg, evcc_rx_2_data, &evcc_rx_2_len, &evcc_rx_2_ide);


        // Send EVCC_RX_1 message
        FlexCAN_Ip_Send(INST_FLEXCAN_0, TX_MB_IDX, &tx_info, evcc_rx_1_id, evcc_rx_1_data);
        while (FlexCAN_Ip_GetTransferStatus(INST_FLEXCAN_0, TX_MB_IDX) != FLEXCAN_STATUS_SUCCESS) {
            FlexCAN_Ip_MainFunctionWrite(INST_FLEXCAN_0, TX_MB_IDX);
        }

        // Update the data length for EVCC_RX_2 message
        tx_info.data_length = EVCC_RX_2_DLC;

        // Send EVCC_RX_2 message
        FlexCAN_Ip_Send(INST_FLEXCAN_0, TX_MB_IDX, &tx_info, evcc_rx_2_id, evcc_rx_2_data);
        while (FlexCAN_Ip_GetTransferStatus(INST_FLEXCAN_0, TX_MB_IDX) != FLEXCAN_STATUS_SUCCESS) {
            FlexCAN_Ip_MainFunctionWrite(INST_FLEXCAN_0, TX_MB_IDX);
        }

        // Increment the LUT index
        currentLUTIndex++;
        if (currentLUTIndex >= LUT_SIZE) {
            currentLUTIndex = 0;  // Reset to loop over the LUT again
        }
    }else
    {
        // Set the values for EVCC_RX_1 and EVCC_RX_2
        setEVCC_RX_2_Values();

        // Pack the EVCC_RX_2 message
        evcc_rx_2_id = Pack_EVCC_RX_2_ecudb(&EVCC_RX_2_Msg, evcc_rx_2_data, &evcc_rx_2_len, &evcc_rx_2_ide);

        // Update the data length for EVCC_RX_2 message
        tx_info.data_length = EVCC_RX_2_DLC;

        // Send EVCC_RX_2 message
        FlexCAN_Ip_Send(INST_FLEXCAN_0, TX_MB_IDX, &tx_info, evcc_rx_2_id, evcc_rx_2_data);
        while (FlexCAN_Ip_GetTransferStatus(INST_FLEXCAN_0, TX_MB_IDX) != FLEXCAN_STATUS_SUCCESS) {
            FlexCAN_Ip_MainFunctionWrite(INST_FLEXCAN_0, TX_MB_IDX);
        }
    	snprintf((char *)uartString, BUFFER_SIZE, "Error: EV not ready for Charging\r\n");
    	Lpuart_Uart_Ip_StatusType Uart_status = Lpuart_Uart_Ip_SyncSend(LPUART_UART_INSTANCE, (const uint8 *)uartString, strlen((char *)uartString), 50000000);
    	UART_Error_Handler(Uart_status);
    }
}







