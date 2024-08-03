import serial
import struct
import colorama
from colorama import Fore

# Initialize colorama
colorama.init(autoreset=True)

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
    0x82: "EV Not Ready for Charging Error",

    # Error codes
    0x08: "EV Error 1",
    0x09: "EV Error 2",
    0x0A: "EV Error 3",
    0x0B: "EVSE Error 1",
    0x0C: "EVSE Error 2",
    0x0D: "EVSE Error 3",
    0x0E: "EVCC Error 1",
    0x0F: "EVCC Error 2",
    0x10: "EVCC Error 3",
    0xA0: "PP Resistance Error",
    0xA1: "CP Duty Cycle Error",
    0xA2: "Gun Not Detected Error",
    0xA3: "Gun Lock Fault Error",
    0xA4: "Vehicle Not Immobilized Error",
    0xA5: "HV Isolation Error",
    0xA6: "Force Actuator Unlock Error",
    0xA7: "Charging Complete Error",
    0xA9: "Gun Lock Feedback Error",
    0xAA: "Vehicle Stop Charging Error",
    0xA8: "EVCC RX 1 Pack Unpack Test Passed",
    0xAB: "EVCC RX 1 Pack Unpack Test Failed",
    0xAC: "EVCC RX 2 Pack Unpack Test Passed",
    0xAD: "EVCC RX 2 Pack Unpack Test Failed",

    # Message codes
    0x20: "EVCC TX 1",
    0x21: "EVCC TX 2",
    0x22: "EVCC TX 3",
    0x23: "EVCC TX 4",
    0x24: "EVCC TX 5",

    # Data points and messages
    0x40: "PP Gun Resistance",
    0x41: "CP Duty Cycle",
    0x42: "EVCC Ready",
    0x43: "Gun Detected",
    0x44: "Positive Contactor Control",
    0x45: "Charging Status",
    0x46: "Negative Contactor Control",
    0x47: "Selected Attenuation in dB",
    0x48: "EV Error Code",
    0x49: "Differential Current Measure",
    0x50: "Temperature 1 Value",
    0x51: "Temperature 2 Value",
    0x52: "OBC Derating Factor",
    0x53: "Temp 1 Fault",
    0x54: "Temp 2 Fault",
    0x55: "Gun Lock Fault",
    0x56: "Vehicle Immobilize",
    0x57: "Gun Lock Feedback",
    0x58: "EVCC Gun Lock Request Status",
    0x59: "EVCC Gun Unlock Request Status",
    0x60: "Software Version",
    0x61: "Charger Max Current",
    0x62: "Charger Min Current",
    0x63: "Charger Max Voltage",
    0x64: "Charger Min Voltage",
    0x65: "Charger Max Power",
    0x66: "Charger Present Voltage",
    0x67: "Charger Present Current",
    0x68: "Termination Detail",
    0x69: "EVCC Error Codes",
    0x70: "EVSE Error Code",
    0x71: "CP State",
    0x72: "Selected App Protocol",
    0x30: "CAN Timeout",
    0x31: "CAN Unknown",

    # Test codes
    0x90: "Testing HV Flag",
    0x91: "HV Flag Test Result",
    0x92: "Testing Vehicle Stop Charging Flag",
    0x93: "Vehicle Stop Charging Flag Test Result",
    0x94: "Testing Force Actuator Flag",
    0x95: "Force Actuator Flag Test Result",
    0x96: "Testing Charging Complete Flag",
    0x97: "Charging Complete Flag Test Result"
}

def interpret_message(data):
    code = data[0]
    if len(data) == 1:
        message = CODES.get(code, "Unknown Code")
    elif len(data) == 5:
        data_value = struct.unpack(">I", data[1:])[0]
        message = f"{CODES.get(code, 'Unknown Code')}: {data_value}"
    else:
        message = "Invalid data length"

    if code in [0x01, 0x04, 0x80]:
        return Fore.GREEN + f"INFO: {message}"
    elif code in [0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA9, 0xAA]:
        return Fore.RED + f"ERROR: {message}"
    elif code in [0x10, 0x11, 0x12, 0x13, 0x20, 0x21, 0x22, 0x23, 0x24, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x70, 0x71, 0x72]:
        return Fore.YELLOW + f"STATUS: {message}"
    else:
        return Fore.BLUE + f"OTHER: {message}"

def read_uart(serial_port):
    try:
        with serial.Serial(serial_port, 115200) as ser:
            print(Fore.CYAN + "Starting UART reader...\n")
            while True:
                line = ser.readline().decode('utf-8').strip()  # Read a full line of data
                if line:
                    print(interpret_message([ord(c) for c in line]))
    except serial.SerialException as e:
        print(Fore.RED + f"Serial Error: {e}")
    except KeyboardInterrupt:
        print(Fore.CYAN + "\nExiting UART reader.")

if __name__ == "__main__":
    read_uart('COM4')
