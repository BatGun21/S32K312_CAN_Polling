# VCU EVCC Integration Project

This project integrates an Electric Vehicle Communication Controller (EVCC) with a Vehicle Control Unit (VCU) using NXP's S32K312 microcontroller. It includes CAN communication, data packing/unpacking, and EVCC functionality.

## Features

- **CAN Communication**
  - **Transmission**: Sends CAN messages based on the EVCC requirements.
  - **Reception**: Receives and processes CAN messages from the EVCC.
- **Data Packing/Unpacking**
  - Utilizes predefined structures for packing data into CAN messages and unpacking received data.
- **EVCC Functionality**
  - Ensures seamless communication between the EVCC and VCU, facilitating electric vehicle operations.

## Functional Overview

### CAN Communication

- **Sending CAN Messages**
  - The system sends CAN messages with specific IDs and data payloads necessary for EVCC operation.
- **Receiving CAN Messages**
  - CAN messages are received from the EVCC, processed, and appropriate actions are taken based on the data.

### Data Packing/Unpacking

- **Packing Data**
  - Data to be sent via CAN is packed into a specific format using predefined structures.
- **Unpacking Data**
  - Received CAN data is unpacked into readable formats for processing and logging.

### EVCC Functionality

- **Integration with VCU**
  - Facilitates communication between the EVCC and VCU, ensuring proper vehicle control.
- **Handling EVCC Commands**
  - Executes commands received from the EVCC, enabling various electric vehicle functionalities.

## How It Works

1. **Initialization**: Initializes the S32K312 microcontroller, CAN module, and data structures.
2. **Data Packing**: Packs data into CAN messages based on the EVCC communication protocol.
3. **Sending Messages**: Transmits packed CAN messages to the EVCC.
4. **Receiving Messages**: Receives CAN messages from the EVCC and unpacks the data.
5. **Processing Data**: Processes the unpacked data and performs necessary actions.

## Dependencies

- NXP S32K312 microcontroller
- EVCC and VCU hardware
- Peripheral drivers for CAN communication

## Getting Started

1. **Setup**: Connect the S32K312 microcontroller to the EVCC and VCU.
2. **Compile and Upload**: Compile the code and upload it to the S32K312 microcontroller.
3. **Run the System**: Power on the system to start CAN communication between the EVCC and VCU.

---

This project demonstrates the integration of an EVCC with a VCU using the S32K312 microcontroller, showcasing essential functionalities for electric vehicle control systems.
