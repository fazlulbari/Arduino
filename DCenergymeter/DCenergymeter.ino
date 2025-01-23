#include <Arduino.h>
#include "RN8209D.h"

// Define RX and TX pins for UART
#define RX_PIN 32
#define TX_PIN 33

// Scaling factors
#define VOLTAGE_SCALING_FACTOR 3.068e-5  // V/unit
#define CURRENT_SCALING_FACTOR 3.597e-5  // A/unit
#define POWER_SCALING_FACTOR 3.598e-5    // W/unit

// Create an instance of the RN8209D class
RN8209D energyMeter(Serial1, 4800, RX_PIN, TX_PIN);

void setup() {
    // Initialize the Serial Monitor
    Serial.begin(115200);
    Serial.println("RN8209D Energy Meter Example");

    // Initialize the energy meter
    energyMeter.begin();

    energyMeter.EnableWrite(); //Enable WRITE operations
    energyMeter.writeRegister(0x00, 0x40);  // PGAU gain PGA=2
    energyMeter.writeRegister(0x01, 0x4063);  // Disable High-Pass filter
    energyMeter.writeRegister(0x15, 0x0000);  // Voltage Offset
    energyMeter.writeRegister(0x16, 0x0000);  // DCL Offset
}

void loop() {
    // Read the device ID and RMS values
    uint32_t id = energyMeter.getDeviceID();
    int32_t voltageRaw = energyMeter.getURMS();
    uint32_t currentRaw = energyMeter.getIARMS();
    uint32_t powerRaw = energyMeter.getPowerPA();

    // Check and handle MSB (if MSB is 1, set the value to 0)
    if (voltageRaw & 0x80000000) voltageRaw = 0; // MSB check for voltage
    if (currentRaw & 0x80000000) currentRaw = 0; // MSB check for current
    if (powerRaw & 0x80000000) powerRaw = 0;     // MSB check for power

    if (voltageRaw != 0xFFFFFFFF && currentRaw != 0xFFFFFFFF && powerRaw != 0xFFFFFFFF) {
        // Apply the scaling factors
        double voltage = (voltageRaw - 400) * VOLTAGE_SCALING_FACTOR;
        double current = (currentRaw - 46920) * CURRENT_SCALING_FACTOR;
        double power = powerRaw * POWER_SCALING_FACTOR;

        // Print the results
        Serial.print("Device ID: 0x");
        Serial.println(id, HEX);
        Serial.print("Voltage (V): ");
        Serial.println(voltage, BIN);  // Display with 2 decimal places
        Serial.print("Current (A): ");
        Serial.println(currentRaw);    // Display with 2 decimal places
        Serial.print("Power (W): ");
        Serial.println(power, 3);   // Display with 3 decimal places
    } else {
        // Print error message
        Serial.println("Failed to read register.");
    }

    // Delay before the next read
    delay(2000);
}

