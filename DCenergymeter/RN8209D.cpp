#include <Arduino.h> // Ensures standard Arduino types like uint32_t are defined
#include "RN8209D.h"

// Device ID for the energy meter (example address, 0x7F)
int DeviceID = 0x7F;  

// Register Addresses
int URMS = 0x24;          // Voltage RMS
int UFreq = 0x25;         // Voltage Frequency
int IARMS = 0x22;         // Current A RMS
int IBRMS = 0x23;         // Current B RMS
int PowerPA = 0x26;       // Active Power A
int PowerPB = 0x27;       // Active Power B
int PowerQ = 0x28;        // Reactive Power
int EnergyP = 0x29;       // Active Energy
int EnergyP2 = 0x2A;      // Active Energy 2
int EnergyD = 0x2B;       // Reactive Energy
int EnergyD2 = 0x2C;      // Reactive Energy 2
int EMUStatus = 0x2D;     // Energy Measurement Status
int SysStatus = 0x43;     // System status register 

// Constructor
RN8209D::RN8209D(HardwareSerial &serial, uint32_t baudRate, int rxPin, int txPin)
    : mySerial(serial), baudRate(baudRate), rxPin(rxPin), txPin(txPin) {}

// Initialize the energy meter
void RN8209D::begin() {
    mySerial.begin(baudRate, SERIAL_8E1, rxPin, txPin); // 8 data bits, even parity, 1 stop bit
}

// Read a specific register
uint32_t RN8209D::readRegister4byte(byte registerAddress) {
    // Send the register address
    mySerial.write(registerAddress);

    // Wait for a response (adjust based on meter specs)
    delay(100);

    // Check if at least 4 bytes are available
    if (mySerial.available() >= 5) {
        byte response[5];
        for (int i = 0; i < 5; i++) {
            response[i] = mySerial.read();
        }

        // Extract 24-bit data
        uint32_t dataOut = (response[0] << 24) | (response[1] << 16) | (response[2] << 8) | response[3];
        return dataOut; // Return raw 32-bit data
    }

    // Return an error value (all bits set to indicate failure)
    return 0xFFFFFFFF;
}

uint32_t RN8209D::readRegister3byte(byte registerAddress) {
    // Send the register address
    mySerial.write(registerAddress);

    // Wait for a response (adjust based on meter specs)
    delay(100);

    // Check if at least 4 bytes are available
    if (mySerial.available() >= 4) {
        byte response[4];
        for (int i = 0; i < 4; i++) {
            response[i] = mySerial.read();
        }

        // Extract 24-bit data
        uint32_t dataOut = (response[0] << 16) | (response[1] << 8) | response[2];
        return dataOut; // Return raw 24-bit data
    }

    // Return an error value (all bits set to indicate failure)
    return 0xFFFFFFFF;
}

uint16_t RN8209D::readRegister2byte(byte registerAddress) {
    // Send the register address
    mySerial.write(registerAddress);

    // Wait for a response (adjust based on meter specs)
    delay(100);

    // Check if at least 4 bytes are available
    if (mySerial.available() >= 3) {
        byte response[3];
        for (int i = 0; i < 3; i++) {
            response[i] = mySerial.read();
        }

        // Extract 24-bit data
        uint16_t dataOut = (response[0] << 8) | response[1];
        return dataOut; // Return raw 16-bit data
    }

    // Return an error value (all bits set to indicate failure)
    return 0xFFFFFFFF;
}

uint8_t RN8209D::readRegisterbyte(byte registerAddress) {
    // Send the register address
    mySerial.write(registerAddress);

    // Wait for a response (adjust based on meter specs)
    delay(100);

    // Check if at least 4 bytes are available
    if (mySerial.available() >= 2) {
        byte response[2];
        for (int i = 0; i < 2; i++) {
            response[i] = mySerial.read();
        }

        // Extract 24-bit data
        uint8_t dataOut = response[0];
        return dataOut; // Return raw 8-bit data
    }

    // Return an error value (all bits set to indicate failure)
    return 0xFFFFFFFF;
}

uint32_t RN8209D::writeRegister(byte registerAddress, uint16_t data) {
    // CMD[7] = 1 (write command)
    byte CMD = 0x80 | (registerAddress & 0x7F);  // CMD[6:0] = register address
    
    // Prepare the data (2 bytes for a 16-bit register)
    byte DATA[2];
    DATA[0] = (data >> 8) & 0xFF;  // High byte
    DATA[1] = data & 0xFF;         // Low byte

    // Calculate checksum
    byte checksum = 0;
    checksum = ~(CMD + DATA[0] + DATA[1]) & 0xFF; // Sum CMD and DATA bytes and invert all bits

    // Send CMD, DATA, and checksum
    mySerial.write(CMD);      // Send command byte
    mySerial.write(DATA[0]);  // Send high byte of data
    mySerial.write(DATA[1]);  // Send low byte of data
    mySerial.write(checksum); // Send checksum byte
    Serial.print("Sent: 0x");
    Serial.print(CMD,HEX);
    Serial.print(",0x");
    Serial.print(DATA[0],HEX);
    Serial.print(",0x");
    Serial.print(DATA[1],HEX);
    Serial.print(",0x");
    Serial.println(checksum,HEX);


    // Wait for a small time to ensure the data is processed
    delay(100);

    // Return a success code (for example, return 0 for success)
    return 0;  // You can modify this to return an appropriate status code or value
}

void RN8209D::EnableWrite() {

    byte CMD = 0xEA;
    byte data = 0xE5;

    // Calculate checksum
    byte checksum = 0;
    checksum = ~(CMD + data) & 0xFF; // Sum CMD and DATA bytes and invert all bits

    // Send CMD, DATA, and checksum
    mySerial.write(CMD);      // Send command byte
    mySerial.write(data);  // Send data
    mySerial.write(checksum); // Send checksum byte
    Serial.print("Sent: 0x");
    Serial.print(CMD,HEX);
    Serial.print(",0x");
    Serial.print(data,HEX);
    Serial.print(",0x");
    Serial.println(checksum,HEX);


    // Wait for a small time to ensure the data is processed
    delay(100);
}

void RN8209D::DisableWrite() {

    byte CMD = 0xEA;
    byte data = 0xDC;

    // Calculate checksum
    byte checksum = 0;
    checksum = ~(CMD + data) & 0xFF; // Sum CMD and DATA bytes and invert all bits

    // Send CMD, DATA, and checksum
    mySerial.write(CMD);      // Send command byte
    mySerial.write(data);  // Send data
    mySerial.write(checksum); // Send checksum byte
    Serial.print("Sent: 0x");
    Serial.print(CMD,HEX);
    Serial.print(",0x");
    Serial.print(data,HEX);
    Serial.print(",0x");
    Serial.println(checksum,HEX);


    // Wait for a small time to ensure the data is processed
    delay(100);
}

// Get device ID by reading register 0x7F
uint32_t RN8209D::getDeviceID() {
    return readRegister3byte(DeviceID); // Device ID is located in register 0x7F
}

// Read Voltage RMS (URMS)
uint32_t RN8209D::getURMS() {
    int32_t signedData = readRegister3byte(URMS);

    // Check the sign bit (most significant bit of 24-bit data)
    if (signedData & 0x800000) { // If the 24th bit is set (negative value)
        return 0; // Return 0 for negative values
    }
        return signedData & 0xFFFFFF; // Return raw 24-bit unsigned data for positive values
}

// Read Voltage Frequency (UFreq)
uint32_t RN8209D::getUFreq() {
    return readRegister2byte(UFreq);
}

// Read Current A RMS (IARMS)
uint32_t RN8209D::getIARMS() {
    return readRegister3byte(IARMS);
}

// Read Current B RMS (IBRMS)
uint32_t RN8209D::getIBRMS() {
    return readRegister3byte(IBRMS);
}

// Read Active Power A (PowerPA)
uint32_t RN8209D::getPowerPA() {
    return readRegister4byte(PowerPA);
}

// Read Active Power B (PowerPB)
uint32_t RN8209D::getPowerPB() {
    return readRegister4byte(PowerPB);
}

// Read Reactive Power (PowerQ)
uint32_t RN8209D::getPowerQ() {
    return readRegister4byte(PowerQ);
}

// Read Active Energy (EnergyP)
uint32_t RN8209D::getEnergyP() {
    return readRegister3byte(EnergyP);
}

// Read Active Energy 2 (EnergyP2)
uint32_t RN8209D::getEnergyP2() {
    return readRegister3byte(EnergyP2);
}

// Read Reactive Energy (EnergyD)
uint32_t RN8209D::getEnergyD() {
    return readRegister3byte(EnergyD);
}

// Read Reactive Energy 2 (EnergyD2)
uint32_t RN8209D::getEnergyD2() {
    return readRegister3byte(EnergyD2);
}

// Read Energy Measurement Status (EMUStatus)
uint32_t RN8209D::getEMUStatus() {
    return readRegister2byte(EMUStatus);
}

// Read System Status (SysStatus)
uint32_t RN8209D::getSysStatus() {
    return readRegisterbyte(SysStatus);
}
