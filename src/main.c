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
} CAN_Msg;

CAN_Msg SendMsgInstances = {0x310, {0x01, 0x00, 0x00, 0x32, 0x00, 0xFF, 0x00, 0x10}, 8, "Test Case 1"};


extern ISR(PIT_0_ISR);
void PIT_Init(void);
void PitNotification(void);
void Clock_Init(void);
void LED_Init(void);
void LPUART_Init(void);
void UART_Error_Handler(Lpuart_Uart_Ip_StatusType Status);
void CAN_Init(void);
void sendCANMessage(CAN_Msg *SendMsg);
void processCANMessage(Flexcan_Ip_StatusType canStatus, Flexcan_Ip_MsgBuffType *rxData, const char *msgIdStr);
void receiveCANMessage(void);

void PitNotification(void)
{
    U8_counter++;
    if(U8_counter >= 100 && U8_counter <= 200)
    {
        toggleLed = 1U;
        Siul2_Dio_Ip_WritePin(LED_GREEN_PORT, LED_GREEN_PIN, 1);
    }
    else if (U8_counter >= 200)
    {
        toggleLed = 2U;
        U8_counter = 0;
        Siul2_Dio_Ip_WritePin(LED_GREEN_PORT, LED_GREEN_PIN, 0);
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

void processCANMessage(Flexcan_Ip_StatusType canStatus, Flexcan_Ip_MsgBuffType *rxData, const char *msgIdStr)
{
    if (canStatus == FLEXCAN_STATUS_SUCCESS)
    {
        snprintf((char *)uartString, BUFFER_SIZE, "Received CAN ID %s: 0x%08lX, Data: ", msgIdStr, rxData->msgId);
        for (uint8_t i = 0; i < rxData->dataLen; i++)
        {
            char byteStr[4];
            snprintf(byteStr, sizeof(byteStr), "%02X ", rxData->data[i]);
            strncat((char *)uartString, byteStr, BUFFER_SIZE - strlen((char *)uartString) - 1);
        }
        strncat((char *)uartString, "\r\n", BUFFER_SIZE - strlen((char *)uartString) - 1);
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


void sendCANMessage(CAN_Msg *SendMsg)
{
    Flexcan_Ip_DataInfoType tx_info = {
        .msg_id_type = FLEXCAN_MSG_ID_STD,
        .data_length = SendMsg->dataLen,
        .is_polling = TRUE,
        .is_remote = FALSE
    };

    FlexCAN_Ip_Send(INST_FLEXCAN_0, TX_MB_IDX, &tx_info, SendMsg->msgId, SendMsg->data);
    while (FlexCAN_Ip_GetTransferStatus(INST_FLEXCAN_0, TX_MB_IDX) != FLEXCAN_STATUS_SUCCESS)
    {
        FlexCAN_Ip_MainFunctionWrite(INST_FLEXCAN_0, TX_MB_IDX);
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

    while (1)
    {
    	receiveCANMessage();
    }    


    return 0;
}
