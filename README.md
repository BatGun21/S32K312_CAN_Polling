# EVCC Integration with VCU

## Overview

This project involves integrating an Electric Vehicle Charging Controller (EVCC) with a Vehicle Control Unit (VCU) using NXP's S32K312 microcontroller. The primary objective is to create a reliable communication interface that efficiently manages vehicle charging operations through CAN and UART communication.

## Project Structure

The repository is structured as follows:

- **`src/`**: Contains the source code files.
  - `main.c`: The main application code handling core functionalities.
  - `evcc_integration.c`: Functions for integrating EVCC communication with VCU.
  - `utils.c`: Utility functions for various operations.
- **`include/`**: Contains header files for the source code.
  - `main.h`: Header file for `main.c`.
  - `evcc_integration.h`: Header file for `evcc_integration.c`.
  - `utils.h`: Header file for `utils.c`.
- **`CMakeLists.txt`**: CMake configuration file for building the project.
- **`README.md`**: This documentation file.

## Features

- **CAN Communication**: Manages CAN message handling between the EVCC and VCU.
- **UART Communication**: Facilitates serial communication for debugging and testing.
- **Flag Handling**: Implements functions to check and manage operational flags.
- **Testing Mode**: Includes a comprehensive suite for testing message packing/unpacking and CAN message scenarios.

## Detailed Explanation

### CAN Communication

The project relies heavily on CAN (Controller Area Network) for robust and real-time communication between the EVCC and VCU. 

- **Receiving CAN Messages**: The system listens for incoming CAN messages, processes them, and updates the system state based on the message content. The `processCANMessage` function in `main.c` is responsible for handling these messages. It takes the status and message details as inputs, updates internal states, and triggers necessary actions.

- **Sending CAN Messages**: The project sends CAN messages to communicate various states and commands. The `sendCANMessage` function encapsulates this functionality. Messages are packed into a specific format and transmitted over the CAN bus to ensure accurate data exchange between components.

### Packing and Unpacking

Packing and unpacking messages are crucial for converting data between its raw format and a structured format suitable for CAN communication.

- **Packing**: Packing functions convert structured data (e.g., EVCC message structures) into a byte array that can be sent over CAN. For instance, the `Pack_EVCC_RX_1_ecudb` function in `evcc_integration.c` takes an EVCC message structure and converts it into a format suitable for transmission. This includes setting appropriate lengths and identifiers.

- **Unpacking**: Unpacking functions reverse the process, converting raw CAN message data back into structured formats. For example, `Unpack_EVCC_RX_1_ecudb` takes a byte array received over CAN and reconstructs it into the EVCC message structure. This ensures that the data can be processed and understood by the system.

### Testing Mode

The testing mode is designed to validate the system's functionality by simulating various scenarios and verifying the correctness of packing/unpacking operations and flag handling.

- **Pack/Unpack Tests**: The `testPackUnpack` function tests whether the packing and unpacking processes correctly preserve message integrity. It checks the consistency between packed and unpacked data for different EVCC message types and sends the result over UART.

- **Flag Functions Tests**: The `testFlagFunctions` function verifies that flag-related operations work correctly. It checks the status of various operational flags, such as HV flag and Vehicle Stop Charging flag, ensuring the system behaves as expected.

- **Simulation of CAN Messages**: The `simulateCANMessages` function creates and sends various simulated CAN messages to test the system's response to different scenarios, including normal operation, isolation breaches, and error conditions. This helps in validating the robustness of the CAN message handling.

## Build Instructions

1. **Clone the repository**:
    ```bash
    git clone https://github.com/your-repository/evcc_integration.git
    ```
2. **Navigate to the project directory**:
    ```bash
    cd evcc_integration
    ```
3. **Create a build directory**:
    ```bash
    mkdir build
    cd build
    ```
4. **Configure the project using CMake**:
    ```bash
    cmake ..
    ```
5. **Build the project**:
    ```bash
    cmake --build . --config Release
    ```

## Usage

1. **Compile and Flash**: Build the project and flash it onto the target microcontroller.
2. **Run**: The software will automatically start handling CAN and UART communication based on the provided implementation.
3. **Testing Mode**: To run tests, ensure `TEST_MODE` is enabled in the code. The system will perform various tests and send results over UART.

## Functions

### `main.c`

- **`void initSystem(void)`**: Initializes system components, including CAN, UART, and LEDs.
- **`void processCANMessage(FLEXCAN_StatusType status, CAN_MessageType *message)`**: Processes incoming CAN messages and updates system states accordingly.
- **`void sendUARTCode(uint8_t code)`**: Sends a specific code over UART for communication and debugging.
- **`void handleErrors(void)`**: Manages error conditions and performs necessary actions.

### `evcc_integration.c`

- **`void Pack_EVCC_RX_1_ecudb(EVCC_RX_1_t *msg, uint8_t *data, uint8_t *length, uint8_t *ide)`**: Packs EVCC RX 1 message for transmission.
- **`void Unpack_EVCC_RX_1_ecudb(EVCC_RX_1_t *msg, const uint8_t *data, uint8_t length)`**: Unpacks received EVCC RX 1 message.
- **`bool checkAndSetHVFlag(void)`**: Checks and sets the HV flag based on conditions.

### `utils.c`

- **`void initializeFlags(void)`**: Initializes system flags for various operations.
- **`bool checkAndSetVehicleStopChargingFlag(void)`**: Checks and sets the Vehicle Stop Charging flag.

## Additional Information

This project leverages CAN communication to ensure reliable and efficient data exchange between the EVCC and VCU, crucial for managing electric vehicle charging operations. The packing and unpacking processes are vital for ensuring accurate and consistent data transmission.
