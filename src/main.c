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

#define MSG_ID 0x55
#define MSG_ID_RX 0x11
#define RX_MB_IDX 1U
#define TX_MB_IDX 0U
#define LPUART_UART_INSTANCE    0
#define BUFFER_SIZE            100

/*Defines for user pin and port configurations */
#define RED_LED_PIN                 13u
#define GREEN_LED_PIN               14u
#define LED_PORT                PTA_H_HALF

#define FXOSC_CLOCK_FREQ   16000000U

/* PIT instance used - 0 */
#define PIT_INST_0 0U
#define CH_0 0U
#define PIT_PERIOD 300000

/* Global flag updated in interrupt */
volatile uint8 toggleLed = 0U;
uint8 U8_counter = 0U;
volatile int exit_code = 0;

/* Global Buffers */
Flexcan_Ip_DataInfoType rx_info; // For CAN RX configuration
Flexcan_Ip_DataInfoType tx_info; // For CAN TX configuration
uint8_t txBuffer[BUFFER_SIZE];
uint8_t rxBuffer[BUFFER_SIZE];
Flexcan_Ip_MsgBuffType rxData;
char uartString[BUFFER_SIZE]; // String to hold the formatted CAN data

typedef struct {
    uint32 msgId;
    uint8 data[8];
    uint8 dataLen;
    const char *description;
} CAN_TestCase;

CAN_TestCase txTestCases[] = {
    {0x350, {0x01, 0x00, 0x00, 0x32, 0x00, 0xFF, 0x00, 0x10}, 8, "Test EVCC Status and CP Duty Cycle"},
    {0x351, {0x02, 0x01, 0x00, 0x33, 0x00, 0xFE, 0x00, 0x11}, 8, "Test Case 2"},
    {0x352, {0x03, 0x02, 0x00, 0x34, 0x00, 0xFD, 0x00, 0x12}, 8, "Test Case 3"},
    {0x353, {0x04, 0x03, 0x00, 0x35, 0x00, 0xFC, 0x00, 0x13}, 8, "Test Case 4"},
    {0x354, {0x05, 0x04, 0x00, 0x36, 0x00, 0xFB, 0x00, 0x14}, 8, "Test Case 5"},
    {0x355, {0x06, 0x05, 0x00, 0x37, 0x00, 0xFA, 0x00, 0x15}, 8, "Test Case 6"},
    {0x356, {0x07, 0x06, 0x00, 0x38, 0x00, 0xF9, 0x00, 0x16}, 8, "Test Case 7"},
    {0x357, {0x08, 0x07, 0x00, 0x39, 0x00, 0xF8, 0x00, 0x17}, 8, "Test Case 8"},
};


CAN_TestCase rxTestCases[] = {
    {0x310, {0x00, 0x00, 0x50, 0x00, 0xFA, 0x03, 0x00, 0x00}, 8, "Test EV Maximum Charging Current Limit and SOC"},
    {0x311, {0x00, 0x01, 0x51, 0x00, 0xFB, 0x04, 0x00, 0x01}, 8, "Test Case 2"},
    {0x312, {0x00, 0x02, 0x52, 0x00, 0xFC, 0x05, 0x00, 0x02}, 8, "Test Case 3"},
    {0x313, {0x00, 0x03, 0x53, 0x00, 0xFD, 0x06, 0x00, 0x03}, 8, "Test Case 4"},
    {0x314, {0x00, 0x04, 0x54, 0x00, 0xFE, 0x07, 0x00, 0x04}, 8, "Test Case 5"},
    {0x315, {0x00, 0x05, 0x55, 0x00, 0xFF, 0x08, 0x00, 0x05}, 8, "Test Case 6"},
    {0x316, {0x00, 0x06, 0x56, 0x00, 0xF0, 0x09, 0x00, 0x06}, 8, "Test Case 7"},
    {0x317, {0x00, 0x07, 0x57, 0x00, 0xF1, 0x0A, 0x00, 0x07}, 8, "Test Case 8"},
};



extern ISR(PIT_0_ISR);

void PitNotification(void)
{
    U8_counter++;
    if(U8_counter >= 100 && U8_counter <= 200)
    {
        toggleLed = 1U;
    }
    else if (U8_counter >= 200)
    {
        toggleLed = 2U;
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
        Siul2_Dio_Ip_WritePin(LED_PORT, LED_GREEN_PIN, 1); // Turn on GREEN LED
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

void sendCANMessage(CAN_TestCase *testCase)
{
    Flexcan_Ip_DataInfoType tx_info = {
        .msg_id_type = FLEXCAN_MSG_ID_STD,
        .data_length = testCase->dataLen,
        .is_polling = TRUE,
        .is_remote = FALSE
    };

    FlexCAN_Ip_Send(INST_FLEXCAN_0, TX_MB_IDX, &tx_info, testCase->msgId, testCase->data);
    while (FlexCAN_Ip_GetTransferStatus(INST_FLEXCAN_0, TX_MB_IDX) != FLEXCAN_STATUS_SUCCESS)
    {
        FlexCAN_Ip_MainFunctionWrite(INST_FLEXCAN_0, TX_MB_IDX);
    }
}


void receiveCANMessage(void)
{
    Flexcan_Ip_StatusType canStatus = FlexCAN_Ip_ReceiveBlocking(INST_FLEXCAN_0, RX_MB_IDX, &rxData, TRUE, 100000);

    if (canStatus == FLEXCAN_STATUS_SUCCESS)
    {
        snprintf((char *)uartString, BUFFER_SIZE, "Received CAN ID: 0x%08lX, Data: ", rxData.msgId);
        for (uint8_t i = 0; i < rxData.dataLen; i++)
        {
            char byteStr[4]; // Space for two hex digits and a space or null terminator
            snprintf(byteStr, sizeof(byteStr), "%02X ", rxData.data[i]);
            strncat((char *)uartString, byteStr, BUFFER_SIZE - strlen((char *)uartString) - 1);
        }
        strncat((char *)uartString, "\r\n", BUFFER_SIZE - strlen((char *)uartString) - 1); // Add a new line at the end

        Lpuart_Uart_Ip_StatusType Uart_status = Lpuart_Uart_Ip_SyncSend(LPUART_UART_INSTANCE, (const uint8 *)uartString, strlen((char *)uartString), 50000000);

        UART_Error_Handler(Uart_status);
    }
}


void CAN_Init(void)
{
    FlexCAN_Ip_Init(INST_FLEXCAN_0, &FlexCAN_State0, &FlexCAN_Config0);

    FlexCAN_Ip_EnterFreezeMode(INST_FLEXCAN_0);
    rx_info.msg_id_type = FLEXCAN_MSG_ID_STD;
    rx_info.data_length = 8;
    rx_info.is_polling = TRUE;
    rx_info.is_remote = FALSE;
    FlexCAN_Ip_ConfigRxMb(INST_FLEXCAN_0, RX_MB_IDX, &rx_info, MSG_ID_RX);
    FlexCAN_Ip_ExitFreezeMode(INST_FLEXCAN_0);
}

void testEVCC(void)
{
    char logMessage[BUFFER_SIZE];
    Lpuart_Uart_Ip_StatusType Uart_status;

    for (size_t i = 0; i < sizeof(txTestCases) / sizeof(txTestCases[0]); i++)
    {
    	snprintf(logMessage, sizeof(logMessage), "Sending Test Case %zu: %s\n", i + 1, txTestCases[i].description);

        Uart_status = Lpuart_Uart_Ip_SyncSend(LPUART_UART_INSTANCE, (const uint8 *)logMessage, strlen(logMessage), 50000000);
        UART_Error_Handler(Uart_status);

        sendCANMessage(&txTestCases[i]);

        receiveCANMessage();
    }
}


void PIT_Init(void)
{
    /* Initialize PIT instance 0 - Channel 0 */
    IntCtrl_Ip_EnableIrq(PIT0_IRQn);
    Pit_Ip_Init(PIT_INST_0, &PIT_0_InitConfig_PB);
    Pit_Ip_InitChannel(PIT_INST_0, PIT_0_CH_0);
    Pit_Ip_EnableChannelInterrupt(PIT_INST_0, CH_0);
    Pit_Ip_StartChannel(PIT_INST_0, CH_0, PIT_PERIOD);
}

int main(void)
{
    /* Initialize the Osif driver */
    OsIf_Init(NULL_PTR);

    Clock_Init();

    /* Init Pins */
    Siul2_Port_Ip_Init(NUM_OF_CONFIGURED_PINS0, g_pin_mux_InitConfigArr0);

    Siul2_Dio_Ip_WritePin(CAN0_STB_PORT, CAN0_STB_PIN, 0U);   // CAN0_STB  : PTC-20

    /* Initialize interrupts */
    IntCtrl_Ip_Init(&IntCtrlConfig_0);

    PIT_Init();
    CAN_Init();
    LPUART_Init();
    LED_Init();

    Siul2_Dio_Ip_WritePin(CAN0_STB_PORT, CAN0_STB_PIN, 1U);   //CAN0_STB

    /* Send welcome message */
    Lpuart_Uart_Ip_StatusType Uart_status;
    Uart_status = Lpuart_Uart_Ip_SyncSend(LPUART_UART_INSTANCE, (uint8_t *)"Lets read some CAN messages here:", strlen("Lets read some CAN messages here:"), 50000000);
    UART_Error_Handler(Uart_status);

    testEVCC();

    while (1)
    {
        receiveCANMessage();
        if (toggleLed == 1){
        	testEVCC();
        }
    }

    return 0;
}
