# EVCC Integration with VCU

## Overview

This project involves integrating an Electric Vehicle Charging Controller (EVCC) with a Vehicle Control Unit (VCU) using NXP's S32K312 microcontroller and S32 Design Studio. The goal is to create a robust communication interface between the EVCC and VCU, enabling efficient management of vehicle charging operations.

## Project Structure

The repository is structured as follows:

- **`src/`**: Contains the source code files.
  - `main.c`: The main application code that handles the core functionalities.
  - `evcc_integration.c`: Functions for integrating EVCC communication with VCU.
  - `utils.c`: Utility functions for handling various operations.
- **`include/`**: Contains header files for the source code.
  - `main.h`: Header file for `main.c`.
  - `evcc_integration.h`: Header file for `evcc_integration.c`.
  - `utils.h`: Header file for `utils.c`.
- **`CMakeLists.txt`**: CMake configuration file for building the project.
- **`README.md`**: This documentation file.

## Features

- **CAN Communication**: Manages CAN message handling for EVCC and VCU communication.
- **UART Communication**: Facilitates serial communication for testing and debugging.
- **Flag Handling**: Implements functions to check and set various operational flags.
- **Testing Mode**: Includes a comprehensive testing suite to verify packing/unpacking functions and simulate different CAN message scenarios.

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

- **`void initSystem(void)`**: Initializes the system components, including CAN, UART, and LEDs.
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

## Testing

### Testing Mode

The `TEST_MODE` section in the code includes functions for:
- Packing and unpacking tests for different EVCC messages.
- Flag function tests to verify the correct operation of various system flags.
- Simulation of different CAN message scenarios to validate system responses.

To run the tests, enable `TEST_MODE` and build the project. The results will be sent over UART.

## Additional Information

- **NXP S32K312**: The microcontroller used for this project, which provides the necessary hardware for CAN and UART communication.
- **S32 Design Studio**: The development environment used to build and manage the project.

## Acknowledgements

- This project uses components and libraries from NXP Semiconductors.
- Special thanks to the development and support teams at Vayve Mobility Pvt. Ltd.

For more information, refer to the [official documentation](https://www.nxp.com/).
