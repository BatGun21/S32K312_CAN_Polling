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

// Define TEST_MODE to enable test code
#define TEST_MODE 01

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

// Define hexadecimal codes for the scenarios and tests
#define CODE_SCENARIO_NORMAL 0x01
#define CODE_SCENARIO_ISOLATION_BREACHED 0x02
#define CODE_SCENARIO_FORCED_UNLOCK_REQUESTED 0x03
#define CODE_SCENARIO_CHARGING_COMPLETE 0x04
#define CODE_SCENARIO_EVSE_ERROR 0x05
#define CODE_SCENARIO_EVCC_ERROR 0x06
#define CODE_SCENARIO_EV_ERROR 0x07
#define CODE_EV_READY_FOR_CHARGING 0x80
#define CODE_EV_NOT_READY_FOR_CHARGING 0x81
#define CODE_EV_NOT_READY_FOR_CHARGING_ERROR 0x82
#define CODE_TESTING_START 0x00
#define CODE_TESTING_END 0x99
#define CODE_TEST_MODE_EXITING 0x9A

//  Error codes
#define CODE_EV_ERROR_1 0x08
#define CODE_EV_ERROR_2 0x09
#define CODE_EV_ERROR_3 0x0A
#define CODE_EVSE_ERROR_1 0x0B
#define CODE_EVSE_ERROR_2 0x0C
#define CODE_EVSE_ERROR_3 0x0D
#define CODE_EVCC_ERROR_1 0x0E
#define CODE_EVCC_ERROR_2 0x0F
#define CODE_EVCC_ERROR_3 0x10
#define CODE_PP_RESISTANCE_ERROR 0xA0
#define CODE_CP_DUTY_CYCLE_ERROR 0xA1
#define CODE_GUN_NOT_DETECTED_ERROR 0xA2
#define CODE_GUN_LOCK_FAULT_ERROR 0xA3
#define CODE_VEHICLE_NOT_IMMOBILIZED_ERROR 0xA4
#define CODE_HV_ISOLATION_ERROR 0xA5
#define CODE_FORCE_ACTUATOR_UNLOCK_ERROR 0xA6
#define CODE_CHARGING_COMPLETE_ERROR 0xA7
#define CODE_GUN_LOCK_FEEDBACK_ERROR 0xA9
#define CODE_VEHICLE_STOP_CHARGING_ERROR 0xAA
#define CODE_EVCC_RX_1_PACK_UNPACK_TEST_PASSED 0xA8
#define CODE_EVCC_RX_1_PACK_UNPACK_TEST_FAILED 0xAB
#define CODE_EVCC_RX_2_PACK_UNPACK_TEST_PASSED 0xAC
#define CODE_EVCC_RX_2_PACK_UNPACK_TEST_FAILED 0xAD

// Define hexadecimal codes for each message
#define CODE_EVCC_TX_1 0x20
#define CODE_EVCC_TX_2 0x21
#define CODE_EVCC_TX_3 0x22
#define CODE_EVCC_TX_4 0x23
#define CODE_EVCC_TX_5 0x24

// Define hexadecimal codes for data points and messages
#define CODE_PP_GUN_RESISTANCE 0x40
#define CODE_CP_DUTY_CYCLE 0x41
#define CODE_EVCC_READY 0x42
#define CODE_GUN_DETECTED 0x43
#define CODE_POSITIVE_CONTACTOR_CONTROL 0x44
#define CODE_CHARGING_STATUS 0x45
#define CODE_NEGATIVE_CONTACTOR_CONTROL 0x46
#define CODE_SELECTED_ATTENUATION_IN_DB 0x47
#define CODE_EV_ERROR_CODE 0x48
#define CODE_DIFFERENTIAL_CURRENT_MEAS 0x49
#define CODE_TEMPERATURE_1_VALUE 0x50
#define CODE_TEMPERATURE_2_VALUE 0x51
#define CODE_OBC_DERATING_FACTOR 0x52
#define CODE_TEMP_1_FAULT 0x53
#define CODE_TEMP_2_FAULT 0x54
#define CODE_GUN_LOCK_FAULT 0x55
#define CODE_VEHICLE_IMMOBILIZE 0x56
#define CODE_GUN_LOCK_FEEDBACK 0x57
#define CODE_EVCC_GUN_LOCK_REQUEST_STATUS 0x58
#define CODE_EVCC_GUN_UNLOCK_REQUEST_STATUS 0x59
#define CODE_SOFTWARE_VERSION 0x60
#define CODE_CHARGER_MAX_CURRENT 0x61
#define CODE_CHARGER_MIN_CURRENT 0x62
#define CODE_CHARGER_MAX_VOLTAGE 0x63
#define CODE_CHARGER_MIN_VOLTAGE 0x64
#define CODE_CHARGER_MAX_POWER 0x65
#define CODE_CHARGER_PRESENT_VOLTAGE 0x66
#define CODE_CHARGER_PRESENT_CURRENT 0x67
#define CODE_TERMINATION_DETAIL 0x68
#define CODE_EVCC_ERROR_CODES 0x69
#define CODE_EVSE_ERROR_CODE 0x70
#define CODE_CP_STATE 0x71
#define CODE_SELECTED_APP_PROTOCOL 0x72
#define CODE_CAN_TIMEOUT 0x30
#define CODE_CAN_UNKNOWN 0x31

// Define codes for tests
#define CODE_TESTING_HV_FLAG 0x90
#define CODE_HV_FLAG_TEST_RESULT 0x91
#define CODE_TESTING_VEHICLE_STOP_CHARGING_FLAG 0x92
#define CODE_VEHICLE_STOP_CHARGING_FLAG_TEST_RESULT 0x93
#define CODE_TESTING_FORCE_ACTUATOR_FLAG 0x94
#define CODE_FORCE_ACTUATOR_FLAG_TEST_RESULT 0x95
#define CODE_TESTING_CHARGING_COMPLETE_FLAG 0x96
#define CODE_CHARGING_COMPLETE_FLAG_TEST_RESULT 0x97


/* Define the CAN message buffer for EVCC_TX*/
ChargingDataPoint chargingLUT[LUT_SIZE];
EVCC_TX_1_t EVCC_TX_1_Msg;
EVCC_TX_2_t EVCC_TX_2_Msg;
EVCC_TX_3_t EVCC_TX_3_Msg;
EVCC_TX_4_t EVCC_TX_4_Msg;
EVCC_TX_5_t EVCC_TX_5_Msg;
EVCC_RX_1_t EVCC_RX_1_Msg;
EVCC_RX_2_t EVCC_RX_2_Msg;
volatile uint8 sendCanMsgFlag = 0U;
volatile uint8 sendSOCMsgFlag = 1U;
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
void processCANMessage(Flexcan_Ip_StatusType canStatus, Flexcan_Ip_MsgBuffType *rxData);
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
void sendUARTCode(uint8_t code);
void sendUARTDataCode(uint8_t code, int32_t data);

/* Test Function Prototypes */
void runTests(void);
void testPackUnpack(void);
void testFlagFunctions(void);
void simulateCANMessages(void);


int main(void)
{
    Clock_Init();

    // Initialize the Osif driver
    OsIf_Init(NULL_PTR);

    // Init Pins
    Siul2_Port_Ip_Init(NUM_OF_CONFIGURED_PINS0, g_pin_mux_InitConfigArr0);

    Siul2_Dio_Ip_WritePin(CAN0_STB_PORT, CAN0_STB_PIN, 0U);   // CAN0_STB  : PTC-20

    // Initialize interrupts
    IntCtrl_Ip_Init(&IntCtrlConfig_0);

    PIT_Init();
    CAN_Init();
    LPUART_Init();
    LED_Init();
    generateLUT();

    Siul2_Dio_Ip_WritePin(CAN0_STB_PORT, CAN0_STB_PIN, 1U);   //CAN0_STB

    #ifdef TEST_MODE
        runTests();
    #else
        while (1)
        {
            receiveCANMessage();

            if(sendCanMsgFlag)
            {
            	Siul2_Dio_Ip_WritePin(LED_PORT, LED_GREEN_PIN, 0); // Turn off GREEN LED
                sendCANMessage();
                sendCanMsgFlag = 0;

            }
            else if (sendSOCMsgFlag)
            {
                // Send the current SOC level over UART
                snprintf((char *)uartString, BUFFER_SIZE, "Current SOC: %d%%\r\n", EVCC_RX_1_Msg.SOC_ro);
                Lpuart_Uart_Ip_StatusType Uart_status = Lpuart_Uart_Ip_SyncSend(LPUART_UART_INSTANCE, (const uint8 *)uartString, strlen((char *)uartString), 50000000);
                UART_Error_Handler(Uart_status);
                sendSOCMsgFlag = 0;
                Siul2_Dio_Ip_WritePin(LED_PORT, LED_GREEN_PIN, 0); // Turn off GREEN LED
            }
        }
    #endif

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
    if((U8_counter > 100) & (U8_counter <200) )
    {
    	sendCanMsgFlag = 1U;
    	Siul2_Dio_Ip_WritePin(LED_PORT, LED_GREEN_PIN, 1); // Turn on GREEN LED
    }
    if (U8_counter>=200)
    {
    	sendSOCMsgFlag = 1;
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

void sendUARTCode(uint8_t code)
{
    char codeStr[4];
    snprintf(codeStr, sizeof(codeStr), "%02X\n", code);
    Lpuart_Uart_Ip_StatusType uartStatus = Lpuart_Uart_Ip_SyncSend(LPUART_UART_INSTANCE, (const uint8 *)codeStr, strlen(codeStr), 50000000);
    UART_Error_Handler(uartStatus);
}

void sendUARTDataCode(uint8_t code, int32_t data) {
    char codeDataStr[14];
    snprintf(codeDataStr, sizeof(codeDataStr), "%02X%08lu\n", code, data);
    Lpuart_Uart_Ip_StatusType uartStatus = Lpuart_Uart_Ip_SyncSend(LPUART_UART_INSTANCE, (const uint8 *)codeDataStr, strlen(codeDataStr), 50000000);
    UART_Error_Handler(uartStatus);
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

void generateLUT(void)
{
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

void processCANMessage(Flexcan_Ip_StatusType canStatus, Flexcan_Ip_MsgBuffType *rxData)
{
    if (canStatus == FLEXCAN_STATUS_SUCCESS) {
        if (rxData->msgId == MSG_ID_RX_1) {
            Unpack_EVCC_TX_1_ecudb(&EVCC_TX_1_Msg, rxData->data, rxData->dataLen);
            sendUARTDataCode(CODE_PP_GUN_RESISTANCE, EVCC_TX_1_Msg.PP_GUN_RESISTANCE);
            sendUARTDataCode(CODE_CP_DUTY_CYCLE, EVCC_TX_1_Msg.CP_DUTY_CYCLE);
            sendUARTDataCode(CODE_EVCC_READY, EVCC_TX_1_Msg.EVCC_READY);
            sendUARTDataCode(CODE_GUN_DETECTED, EVCC_TX_1_Msg.GUN_DETECTED);
            sendUARTDataCode(CODE_POSITIVE_CONTACTOR_CONTROL, EVCC_TX_1_Msg.POSITIVE_CONTACTOR_CONTROL);
            sendUARTDataCode(CODE_CHARGING_STATUS, EVCC_TX_1_Msg.CHARGING_STATUS);
            sendUARTDataCode(CODE_NEGATIVE_CONTACTOR_CONTROL, EVCC_TX_1_Msg.NEGATIVE_CONTACTOR_CONTROL);
            sendUARTDataCode(CODE_SELECTED_ATTENUATION_IN_DB, EVCC_TX_1_Msg.SELECTED_ATTENUATION_IN_DB);
            sendUARTDataCode(CODE_EV_ERROR_CODE, EVCC_TX_1_Msg.EV_Error_Code);
            sendUARTDataCode(CODE_DIFFERENTIAL_CURRENT_MEAS, EVCC_TX_1_Msg.DIFFERENTIAL_CURRENT_MEAS);
        } else if (rxData->msgId == MSG_ID_RX_2) {
            Unpack_EVCC_TX_2_ecudb(&EVCC_TX_2_Msg, rxData->data, rxData->dataLen);
            sendUARTDataCode(CODE_TEMPERATURE_1_VALUE, EVCC_TX_2_Msg.TEMPERATURE_1_VALUE_ro);
            sendUARTDataCode(CODE_TEMPERATURE_2_VALUE, EVCC_TX_2_Msg.TEMPERATURE_2_VALUE_ro);
            sendUARTDataCode(CODE_OBC_DERATING_FACTOR, EVCC_TX_2_Msg.OBC_DERATING_FACTOR);
            sendUARTDataCode(CODE_TEMP_1_FAULT, EVCC_TX_2_Msg.TEMP_1_FAULT);
            sendUARTDataCode(CODE_TEMP_2_FAULT, EVCC_TX_2_Msg.TEMP_2_FAULT);
            sendUARTDataCode(CODE_GUN_LOCK_FAULT, EVCC_TX_2_Msg.GUN_LOCK_FAULT);
            sendUARTDataCode(CODE_VEHICLE_IMMOBILIZE, EVCC_TX_2_Msg.VEHICLE_IMMOBILIZE);
            sendUARTDataCode(CODE_GUN_LOCK_FEEDBACK, EVCC_TX_2_Msg.GUN_LOCK_FEEDBACK);
            sendUARTDataCode(CODE_EVCC_GUN_LOCK_REQUEST_STATUS, EVCC_TX_2_Msg.EVCC_GUN_LOCK_REQUEST_STATUS);
            sendUARTDataCode(CODE_EVCC_GUN_UNLOCK_REQUEST_STATUS, EVCC_TX_2_Msg.EVCC_GUN_UNLOCK_REQUEST_STATUS);
        } else if (rxData->msgId == MSG_ID_RX_3) {
            Unpack_EVCC_TX_3_ecudb(&EVCC_TX_3_Msg, rxData->data, rxData->dataLen);
            sendUARTDataCode(CODE_SOFTWARE_VERSION, EVCC_TX_3_Msg.SOFTWARE_VERSION_ro);
            sendUARTDataCode(CODE_CHARGER_MAX_CURRENT, EVCC_TX_3_Msg.CHARGER_MAX_CURRENT_ro);
            sendUARTDataCode(CODE_CHARGER_MIN_CURRENT, EVCC_TX_3_Msg.CHARGER_MIN_CURRENT_ro);
            sendUARTDataCode(CODE_CHARGER_MAX_VOLTAGE, EVCC_TX_3_Msg.CHARGER_MAX_VOLTAGE_ro);
        } else if (rxData->msgId == MSG_ID_RX_4) {
            Unpack_EVCC_TX_4_ecudb(&EVCC_TX_4_Msg, rxData->data, rxData->dataLen);
            sendUARTDataCode(CODE_CHARGER_MIN_VOLTAGE, EVCC_TX_4_Msg.CHARGER_MIN_VOLTAGE_ro);
            sendUARTDataCode(CODE_CHARGER_MAX_POWER, EVCC_TX_4_Msg.CHARGER_MAX_POWER_ro);
            sendUARTDataCode(CODE_CHARGER_PRESENT_VOLTAGE, EVCC_TX_4_Msg.CHARGER_PRESENT_VOLTAGE_ro);
            sendUARTDataCode(CODE_CHARGER_PRESENT_CURRENT, EVCC_TX_4_Msg.CHARGER_PRESENT_CURRENT_ro);
        } else if (rxData->msgId == MSG_ID_RX_5) {
            Unpack_EVCC_TX_5_ecudb(&EVCC_TX_5_Msg, rxData->data, rxData->dataLen);
            sendUARTDataCode(CODE_TERMINATION_DETAIL, EVCC_TX_5_Msg.TERMINATION_DETAIL);
            sendUARTDataCode(CODE_EVCC_ERROR_CODES, EVCC_TX_5_Msg.EVCC_ERROR_CODES);
            sendUARTDataCode(CODE_EVSE_ERROR_CODE, EVCC_TX_5_Msg.EVSE_ERROR_CODE);
            sendUARTDataCode(CODE_CP_STATE, EVCC_TX_5_Msg.CP_STATE);
            sendUARTDataCode(CODE_SELECTED_APP_PROTOCOL, EVCC_TX_5_Msg.SELECTED_APP_PROTOCOL);
        } else {
            sendUARTCode(CODE_CAN_UNKNOWN);
        }
    } else if (canStatus == FLEXCAN_STATUS_TIMEOUT) {
        sendUARTCode(CODE_CAN_TIMEOUT);
    }
}

void receiveCANMessage(void)
{
    Flexcan_Ip_StatusType canStatus1 = FlexCAN_Ip_ReceiveBlocking(INST_FLEXCAN_0, RX_MB_IDX_1, &rxData1, TRUE, 100000);
    Flexcan_Ip_StatusType canStatus2 = FlexCAN_Ip_ReceiveBlocking(INST_FLEXCAN_0, RX_MB_IDX_2, &rxData2, TRUE, 100000);
    Flexcan_Ip_StatusType canStatus3 = FlexCAN_Ip_ReceiveBlocking(INST_FLEXCAN_0, RX_MB_IDX_3, &rxData3, TRUE, 100000);
    Flexcan_Ip_StatusType canStatus4 = FlexCAN_Ip_ReceiveBlocking(INST_FLEXCAN_0, RX_MB_IDX_4, &rxData4, TRUE, 100000);
    Flexcan_Ip_StatusType canStatus5 = FlexCAN_Ip_ReceiveBlocking(INST_FLEXCAN_0, RX_MB_IDX_5, &rxData5, TRUE, 100000);

    processCANMessage(canStatus1, &rxData1);
    processCANMessage(canStatus2, &rxData2);
    processCANMessage(canStatus3, &rxData3);
    processCANMessage(canStatus4, &rxData4);
    processCANMessage(canStatus5, &rxData5);
}

uint8_t check_SOC(void)
{
    if (currentLUTIndex < LUT_SIZE) {
        return chargingLUT[currentLUTIndex].soc;
    }
    return 0;  // Default value if the index is out of range
}

bool checkIsolation(void)
{
    // Check for isolation issue via UART
    char isolationMsg[] = "Isolation Gone";
    Lpuart_Uart_Ip_StatusType status = Lpuart_Uart_Ip_SyncReceive(LPUART_UART_INSTANCE, (uint8_t *)uartString, strlen(isolationMsg), 50000000);

    if (status == LPUART_UART_IP_STATUS_SUCCESS && strncmp((char *)uartString, isolationMsg, strlen(isolationMsg)) == 0) {
        return true;
    }
    return false;  // Assume no isolation issue
}

bool checkActuator(void)
{
    // Check for actuator unlock via UART
    char actuatorMsg[] = "Force Unlock Actuator";
    Lpuart_Uart_Ip_StatusType status = Lpuart_Uart_Ip_SyncReceive(LPUART_UART_INSTANCE, (uint8_t *)uartString, strlen(actuatorMsg), 50000000);

    if (status == LPUART_UART_IP_STATUS_SUCCESS && strncmp((char *)uartString, actuatorMsg, strlen(actuatorMsg)) == 0) {
        return true;
    }
    return false;  // Assume actuator unlock is not pressed
}

bool checkAndSetHVFlag(void)
{
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
            sendUARTDataCode(CODE_EV_ERROR_1, evErrorCode);
        } else if (evccErrorCode != 0) {
            sendUARTDataCode(CODE_EVCC_ERROR_2, evccErrorCode);
        } else if (evseErrorCode != 0) {
            sendUARTDataCode(CODE_EVSE_ERROR_1, evseErrorCode);
        }
    }

    return vehicleStopCharging;
}

bool checkAndSetForceActuatorFlag(void)
{
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

bool checkAndSetChargingCompleteFlag(void)
{
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
        sendUARTCode(CODE_EV_READY_FOR_CHARGING);
    } else {
        // Send appropriate error message over UART
        if (!ppResistanceOk) {
            sendUARTDataCode(CODE_PP_RESISTANCE_ERROR, EVCC_TX_1_Msg.PP_GUN_RESISTANCE);
        } else if (!cpDutyCycleOk) {
            sendUARTDataCode(CODE_CP_DUTY_CYCLE_ERROR, EVCC_TX_1_Msg.CP_DUTY_CYCLE);
        } else if (!gunDetected) {
            sendUARTCode(CODE_GUN_NOT_DETECTED_ERROR);
        } else if (!gunLockOk) {
            sendUARTCode(CODE_GUN_LOCK_FAULT_ERROR);
        } else if (!vehicleImmobilized) {
            sendUARTCode(CODE_VEHICLE_NOT_IMMOBILIZED_ERROR);
        } else if (!gunLockFeedbackOk) {
            sendUARTCode(CODE_GUN_LOCK_FEEDBACK_ERROR);
        } else if (!hvFlag) {
            sendUARTCode(CODE_HV_ISOLATION_ERROR);
        } else if (vehicleStopChargingFlag) {
            sendUARTCode(CODE_VEHICLE_STOP_CHARGING_ERROR);
        } else if (forceActuatorFlag) {
            sendUARTCode(CODE_FORCE_ACTUATOR_UNLOCK_ERROR);
        } else if (chargingCompleteFlag) {
            sendUARTCode(CODE_CHARGING_COMPLETE_ERROR);
        } else {
            sendUARTCode(CODE_EV_NOT_READY_FOR_CHARGING_ERROR);
        }
        EVCC_RX_2_Msg.EV_READY_FLAG = 0;  // Reset EV Ready flag
    }
}

void setEVCC_RX_1_Values(void)
{
    if (currentLUTIndex < LUT_SIZE) {
    	EVCC_RX_1_Msg.EV_MAX_CHRG_CURR_LIMIT_ro = (uint16_t)((chargingLUT[currentLUTIndex].maxCurrentLimit - 0.0) / 0.25);
    	EVCC_RX_1_Msg.SOC_ro = (uint8_t)((chargingLUT[currentLUTIndex].soc - 0.0) / 0.5);
        EVCC_RX_1_Msg.EV_CONTINEOUS_CHRG_CURR_LIMIT = chargingLUT[currentLUTIndex].evContinuousChargingCurrent;
        EVCC_RX_1_Msg.BATT_PACK_PRESENT_VOLTAGE_ro = (uint16_t)((chargingLUT[currentLUTIndex].batteryPackPresentVoltage - 0.0) / 0.25);
        EVCC_RX_1_Msg.EVSE_Protocol_Priority_Selection = 1;
    }
}

void setEVCC_RX_2_Values(void)
{
    if (currentLUTIndex < LUT_SIZE) {
        EVCC_RX_2_Msg.REMAINING_BATT_CAPACITY = chargingLUT[currentLUTIndex].remainingBattCapacity;
        EVCC_RX_2_Msg.NOMINAL_BATT_CAPACITY = chargingLUT[currentLUTIndex].nominalBattCapacity;
    }
}

void sendCANMessage(void)
{
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

#ifdef TEST_MODE

void runTests(void) {
    testPackUnpack();
    testFlagFunctions();
    simulateCANMessages();
    sendUARTCode(CODE_TEST_MODE_EXITING);
}

void testPackUnpack(void) {
    // Test scenarios for packing and unpacking CAN messages
    EVCC_RX_1_t unpackedMsg1;
    uint8_t evcc_rx_1_data[EVCC_RX_1_DLC];
    uint8_t evcc_rx_1_len;
    uint8_t evcc_rx_1_ide;
    Pack_EVCC_RX_1_ecudb(&EVCC_RX_1_Msg, evcc_rx_1_data, &evcc_rx_1_len, &evcc_rx_1_ide);
    Unpack_EVCC_RX_1_ecudb(&unpackedMsg1, evcc_rx_1_data, evcc_rx_1_len);

    if (memcmp(&EVCC_RX_1_Msg, &unpackedMsg1, sizeof(EVCC_RX_1_Msg)) == 0) {
        sendUARTCode(CODE_EVCC_RX_1_PACK_UNPACK_TEST_PASSED);
    } else {
        sendUARTCode(CODE_EVCC_RX_1_PACK_UNPACK_TEST_FAILED);
    }

    EVCC_RX_2_t unpackedMsg2;
    uint8_t evcc_rx_2_data[EVCC_RX_2_DLC];
    uint8_t evcc_rx_2_len;
    uint8_t evcc_rx_2_ide;
    Pack_EVCC_RX_2_ecudb(&EVCC_RX_2_Msg, evcc_rx_2_data, &evcc_rx_2_len, &evcc_rx_2_ide);
    Unpack_EVCC_RX_2_ecudb(&unpackedMsg2, evcc_rx_2_data, evcc_rx_2_len);

    if (memcmp(&EVCC_RX_2_Msg, &unpackedMsg2, sizeof(EVCC_RX_2_Msg)) == 0) {
        sendUARTCode(CODE_EVCC_RX_2_PACK_UNPACK_TEST_PASSED);
    } else {
        sendUARTCode(CODE_EVCC_RX_2_PACK_UNPACK_TEST_FAILED);
    }
}

void testFlagFunctions(void) {
    // Test HV flag function
    sendUARTCode(CODE_TESTING_HV_FLAG);
    bool hvFlag = checkAndSetHVFlag();
    sendUARTDataCode(CODE_HV_FLAG_TEST_RESULT, hvFlag);

    // Test Vehicle Stop Charging flag function
    sendUARTCode(CODE_TESTING_VEHICLE_STOP_CHARGING_FLAG);
    bool vehicleStopChargingFlag = checkAndSetVehicleStopChargingFlag();
    sendUARTDataCode(CODE_VEHICLE_STOP_CHARGING_FLAG_TEST_RESULT, vehicleStopChargingFlag);

    // Test Force Actuator flag function
    sendUARTCode(CODE_TESTING_FORCE_ACTUATOR_FLAG);
    bool forceActuatorFlag = checkAndSetForceActuatorFlag();
    sendUARTDataCode(CODE_FORCE_ACTUATOR_FLAG_TEST_RESULT, forceActuatorFlag);

    // Test Charging Complete flag function
    sendUARTCode(CODE_TESTING_CHARGING_COMPLETE_FLAG);
    bool chargingCompleteFlag = checkAndSetChargingCompleteFlag();
    sendUARTDataCode(CODE_CHARGING_COMPLETE_FLAG_TEST_RESULT, chargingCompleteFlag);
}

void simulateCANMessages(void) {
    // Normal Operation
    sendUARTCode(CODE_TESTING_START);
    sendUARTCode(CODE_SCENARIO_NORMAL);
    uint8_t evcc_tx_1_data_normal[EVCC_TX_1_DLC] = {0x00, 0x00, 0x04, 0x00, 0x02, 0x00, 0x00, 0x00};  // Example normal data
    rxData1.msgId = MSG_ID_RX_1;
    rxData1.dataLen = EVCC_TX_1_DLC;
    memcpy(rxData1.data, evcc_tx_1_data_normal, EVCC_TX_1_DLC);
    processCANMessage(FLEXCAN_STATUS_SUCCESS, &rxData1);

    uint8_t evcc_tx_2_data_normal[EVCC_TX_2_DLC] = {0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00};  // Example normal data
    rxData2.msgId = MSG_ID_RX_2;
    rxData2.dataLen = EVCC_TX_2_DLC;
    memcpy(rxData2.data, evcc_tx_2_data_normal, EVCC_TX_2_DLC);
    processCANMessage(FLEXCAN_STATUS_SUCCESS, &rxData2);
    sendUARTCode(CODE_TESTING_END);

    // Isolation Breached
    sendUARTCode(CODE_TESTING_START);
    sendUARTCode(CODE_SCENARIO_ISOLATION_BREACHED);
    uint8_t evcc_tx_1_data_isolation[EVCC_TX_1_DLC] = {0x00, 0x00, 0x04, 0x00, 0x02, 0x00, 0x00, 0x00};  // Same as normal for this example
    rxData1.dataLen = EVCC_TX_1_DLC;
    memcpy(rxData1.data, evcc_tx_1_data_isolation, EVCC_TX_1_DLC);
    processCANMessage(FLEXCAN_STATUS_SUCCESS, &rxData1);

    uint8_t evcc_tx_2_data_isolation[EVCC_TX_2_DLC] = {0x00, 0x00, 0x00, 0x08, 0x10, 0x00, 0x00, 0x00};  // HV Isolation fault (bit 3)
    rxData2.dataLen = EVCC_TX_2_DLC;
    memcpy(rxData2.data, evcc_tx_2_data_isolation, EVCC_TX_2_DLC);
    processCANMessage(FLEXCAN_STATUS_SUCCESS, &rxData2);
    sendUARTCode(CODE_TESTING_END);

    // Forced Unlock Requested
    sendUARTCode(CODE_TESTING_START);
    sendUARTCode(CODE_SCENARIO_FORCED_UNLOCK_REQUESTED);
    uint8_t evcc_tx_1_data_unlock[EVCC_TX_1_DLC] = {0x00, 0x00, 0x04, 0x00, 0x02, 0x00, 0x00, 0x00};  // Same as normal for this example
    rxData1.dataLen = EVCC_TX_1_DLC;
    memcpy(rxData1.data, evcc_tx_1_data_unlock, EVCC_TX_1_DLC);
    processCANMessage(FLEXCAN_STATUS_SUCCESS, &rxData1);

    uint8_t evcc_tx_2_data_unlock[EVCC_TX_2_DLC] = {0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00};  // Force unlock request (bit 4)
    rxData2.dataLen = EVCC_TX_2_DLC;
    memcpy(rxData2.data, evcc_tx_2_data_unlock, EVCC_TX_2_DLC);
    processCANMessage(FLEXCAN_STATUS_SUCCESS, &rxData2);
    sendUARTCode(CODE_TESTING_END);

    // Charging Complete
    sendUARTCode(CODE_TESTING_START);
    sendUARTCode(CODE_SCENARIO_CHARGING_COMPLETE);
    uint8_t evcc_tx_1_data_complete[EVCC_TX_1_DLC] = {0x00, 0x00, 0x04, 0x00, 0x02, 0x00, 0x00, 0x00};  // Same as normal for this example
    rxData1.dataLen = EVCC_TX_1_DLC;
    memcpy(rxData1.data, evcc_tx_1_data_complete, EVCC_TX_1_DLC);
    processCANMessage(FLEXCAN_STATUS_SUCCESS, &rxData1);

    uint8_t evcc_tx_2_data_complete[EVCC_TX_2_DLC] = {0x00, 0x00, 0x00, 0x00, 0x10, 0x01, 0x00, 0x00};  // Charging complete (bit 0)
    rxData2.dataLen = EVCC_TX_2_DLC;
    memcpy(rxData2.data, evcc_tx_2_data_complete, EVCC_TX_2_DLC);
    processCANMessage(FLEXCAN_STATUS_SUCCESS, &rxData2);
    sendUARTCode(CODE_TESTING_END);

    // Charging Stopped due to EVSE Error
    sendUARTCode(CODE_TESTING_START);
    sendUARTCode(CODE_SCENARIO_EVSE_ERROR);
    uint8_t evcc_tx_1_data_evse_error[EVCC_TX_1_DLC] = {0x00, 0x00, 0x04, 0x00, 0x02, 0x00, 0x00, 0x00};  // Same as normal for this example
    rxData1.dataLen = EVCC_TX_1_DLC;
    memcpy(rxData1.data, evcc_tx_1_data_evse_error, EVCC_TX_1_DLC);
    processCANMessage(FLEXCAN_STATUS_SUCCESS, &rxData1);

    uint8_t evcc_tx_2_data_evse_error[EVCC_TX_2_DLC] = {0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x06, 0x00};  // EVSE error code 6
    rxData2.dataLen = EVCC_TX_2_DLC;
    memcpy(rxData2.data, evcc_tx_2_data_evse_error, EVCC_TX_2_DLC);
    processCANMessage(FLEXCAN_STATUS_SUCCESS, &rxData2);
    sendUARTCode(CODE_TESTING_END);

    // Charging Stopped due to EVCC Error
    sendUARTCode(CODE_TESTING_START);
    sendUARTCode(CODE_SCENARIO_EVCC_ERROR);
    uint8_t evcc_tx_1_data_evcc_error[EVCC_TX_1_DLC] = {0x00, 0x00, 0x04, 0x00, 0x02, 0x00, 0x00, 0x00};  // Same as normal for this example
    rxData1.dataLen = EVCC_TX_1_DLC;
    memcpy(rxData1.data, evcc_tx_1_data_evcc_error, EVCC_TX_1_DLC);
    processCANMessage(FLEXCAN_STATUS_SUCCESS, &rxData1);

    uint8_t evcc_tx_2_data_evcc_error[EVCC_TX_2_DLC] = {0x00, 0x00, 0x00, 0x00, 0x10, 0x03, 0x00, 0x00};  // EVCC error code 3
    rxData2.dataLen = EVCC_TX_2_DLC;
    memcpy(rxData2.data, evcc_tx_2_data_evcc_error, EVCC_TX_2_DLC);
    processCANMessage(FLEXCAN_STATUS_SUCCESS, &rxData2);
    sendUARTCode(CODE_TESTING_END);

    // Charging Stopped due to EV Error
    sendUARTCode(CODE_TESTING_START);
    sendUARTCode(CODE_SCENARIO_EV_ERROR);
    uint8_t evcc_tx_1_data_ev_error[EVCC_TX_1_DLC] = {0x00, 0x00, 0x04, 0x00, 0x02, 0x00, 0x00, 0x00};  // Same as normal for this example
    rxData1.dataLen = EVCC_TX_1_DLC;
    memcpy(rxData1.data, evcc_tx_1_data_ev_error, EVCC_TX_1_DLC);
    processCANMessage(FLEXCAN_STATUS_SUCCESS, &rxData1);

    uint8_t evcc_tx_2_data_ev_error[EVCC_TX_2_DLC] = {0x00, 0x00, 0x00, 0x00, 0x10, 0x09, 0x00, 0x00};  // EV error code 9
    rxData2.dataLen = EVCC_TX_2_DLC;
    memcpy(rxData2.data, evcc_tx_2_data_ev_error, EVCC_TX_2_DLC);
    processCANMessage(FLEXCAN_STATUS_SUCCESS, &rxData2);
    sendUARTCode(CODE_TESTING_END);
}
#endif



