#ifndef RN8209D_H
#define RN8209D_H

#include <Arduino.h>

class RN8209D {
public:
    // Constructor to initialize the serial port
    RN8209D(HardwareSerial &serial, uint32_t baudRate, int rxPin, int txPin);

    // Method to initialize the energy meter
    void begin();

    // Method to read a specific register (returns raw 8-32-bit data as uint32_t)
    uint32_t readRegister4byte(byte registerAddress);
    uint32_t readRegister3byte(byte registerAddress);
    uint16_t readRegister2byte(byte registerAddress);
    uint8_t readRegisterbyte(byte registerAddress);

    // Method to get the device ID (specific to register 0x7F)
    uint32_t getDeviceID();

    // Methods to read specific registers
    uint32_t getURMS();        // Voltage RMS
    uint32_t getUFreq();       // Voltage Frequency
    uint32_t getIARMS();       // Current A RMS
    uint32_t getIBRMS();       // Current B RMS
    uint32_t getPowerPA();     // Active Power A
    uint32_t getPowerPB();     // Active Power B
    uint32_t getPowerQ();      // Reactive Power
    uint32_t getEnergyP();     // Active Energy
    uint32_t getEnergyP2();    // Active Energy 2
    uint32_t getEnergyD();     // Reactive Energy
    uint32_t getEnergyD2();    // Reactive Energy 2
    uint32_t getEMUStatus();   // Energy Measurement Status
    uint32_t getSysStatus();   // System Status

    //Enable ans Disable write
    void EnableWrite();
    void DisableWrite();

    // Method to write a specific register
    uint32_t writeRegister(byte registerAddress, uint16_t data);

private:
    HardwareSerial &mySerial; // Reference to the serial object
    uint32_t baudRate;        // Baud rate for communication
    int rxPin, txPin;         // UART pins
};

#endif // RN8209D_H
