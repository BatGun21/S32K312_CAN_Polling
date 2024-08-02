import serial
import io;
import time;
import os;

# Open the serial port
ser = serial.Serial('COM4', 115200)

# Define the codes
CODES = {
    0x01: "Normal Operation",
    0x02: "Isolation Breached",
    0x03: "Forced Unlock Requested",
    0x04: "Charging Complete",
    0x05: "EVSE Error",
    0x06: "EVCC Error",
    0x07: "EV Error",
    0x80: "EV Ready for Charging",
    0x81: "EV Not Ready for Charging",
    0x10: "EVCC_TX_1 Status Code",
    0x11: "PP Gun Resistance",
    0x12: "CP Duty Cycle",
    0x13: "EVCC Ready",
    0x14: "Gun Detected",
    0x15: "Positive Contactor Control",
    0x16: "Charging Status",
    0x17: "Negative Contactor Control",
    0x18: "Selected Attenuation in dB",
    0x19: "EV Error Code",
    0x1A: "Differential Current Measure",
    0x20: "Temperature 1 Value",
    0x21: "Temperature 2 Value",
    0x22: "OBC Derating Factor",
    0x23: "Temp 1 Fault",
    0x24: "Temp 2 Fault",
    0x25: "Gun Lock Fault",
    0x26: "Vehicle Immobilize",
    0x27: "Gun Lock Feedback",
    0x28: "EVCC Gun Lock Request Status",
    0x29: "EVCC Gun Unlock Request Status",
    0x30: "Software Version",
    0x31: "Charger Max Current",
    0x32: "Charger Min Current",
    0x33: "Charger Max Voltage",
    0x40: "Charger Min Voltage",
    0x41: "Charger Max Power",
    0x42: "Charger Present Voltage",
    0x43: "Charger Present Current",
    0x50: "Termination Detail",
    0x51: "EVCC Error Codes",
    0x52: "EVSE Error Code",
    0x53: "CP State",
    0x54: "Selected App Protocol",
    0x60: "CAN Receive Timeout"
}

def read_uart(serial_port):
    with serial.Serial(serial_port, 9600, timeout=1) as ser:
        while True:
            line = ser.readline().decode('utf-8').strip()
            if line:
                code = int(line[:2], 16)
                data = int(line[2:], 16)
                description = CODES.get(code, "Unknown Code")
                print(f"{description}: {data}")

if __name__ == "__main__":
    read_uart('/dev/ttyUSB0')  # Update the serial port as per your setup
