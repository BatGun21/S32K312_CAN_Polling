# S32K312 CAN Polling Project

This project demonstrates CAN communication, UART integration, and periodic interrupt handling on the NXP S32K312 microcontroller. It includes sending and receiving CAN messages, logging via UART, and using LEDs to indicate various statuses.

## Features

- **CAN Communication**
  - **Transmission**: The system sends predefined CAN messages with specific IDs and data payloads.
  - **Reception**: The system receives CAN messages, processes them, and logs the information via UART.
- **UART Logging**
  - Logs CAN messages and system status updates in real-time.
  - Uses LEDs to indicate different UART status conditions such as errors or busy states.
- **Periodic Interrupts**
  - Utilizes the PIT (Periodic Interrupt Timer) module to create regular interrupts for executing periodic tasks.
- **LED Indicators**
  - LEDs connected to GPIO pins indicate system states and UART communication status.

## Functional Overview

### CAN Communication

- **Sending CAN Messages**
  - The code contains a list of CAN test cases, each with a unique CAN ID and data payload.
  - These messages are sent through the CAN module and are used for testing and demonstration purposes.

- **Receiving CAN Messages**
  - The system is configured to receive CAN messages.
  - Upon reception, the CAN data is formatted into a string and logged via UART for easy monitoring.

### UART Logging

- **Logging Mechanism**
  - UART is used to output received CAN messages and other important information.
  - If any UART errors occur, the system uses LEDs to indicate the specific error condition.

### Periodic Interrupts

- **PIT Configuration**
  - The PIT module is set up to generate interrupts at regular intervals.
  - These interrupts are used to perform periodic tasks, such as toggling LEDs and checking the system status.

### LED Indicators

- **Status Indication**
  - Different LEDs are used to indicate the status of UART communication and other system states.
  - For example, LEDs may turn on or off based on error conditions or the state of CAN communication.

## How It Works

1. **Initialization**: The system initializes the clock, CAN, UART, and GPIO for LEDs.
2. **Sending Messages**: Predefined CAN messages are sent in a loop. Each message is logged via UART.
3. **Receiving Messages**: CAN messages are received and logged in a formatted string over UART.
4. **Handling Interrupts**: Periodic interrupts are generated to handle tasks such as checking the state of the system and updating LEDs.
5. **Error Handling**: Any UART errors are indicated through LEDs to alert the user to communication issues.

## Dependencies

- NXP S32K312 microcontroller
- Necessary peripheral drivers and configurations for CAN, UART, PIT, and GPIO.

## Getting Started

1. **Setup**: Connect the NXP S32K312 microcontroller to your development environment.
2. **Compile and Upload**: Compile the code using your preferred IDE and upload it to the microcontroller.
3. **Run the System**: Power on the system to start CAN communication, UART logging, and LED status indication.

---

This project is a practical demonstration of CAN communication and UART logging using the S32K312 microcontroller, providing a foundational example for automotive and embedded applications.
