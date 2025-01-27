#include "modbus.h"

// Define HardwareSerial and ModbusRTUSlave globally
HardwareSerial mySerial(USART2);
ModbusRTUSlave slave(mySerial);

// Define global Modbus registers
uint16_t inputRegisters[20];
bool discreteInputs[20];

// Previous settings for checking changes
static int previousBaudRate = -1;  // Set an invalid initial value
static int previousSlaveId = -1;  // Set an invalid initial value

void modbus_init() {
    // Initialize serial communication for RS485
    mySerial.begin(Baud_Rate, SERIAL_8N1);

    // Initialize Modbus slave
    slave.begin(Slave_id, Baud_Rate, SERIAL_8N1);

    // Configure discrete inputs and input registers
    slave.configureDiscreteInputs(discreteInputs, 20);
    slave.configureInputRegisters(inputRegisters, 20);

    // Update previous settings
    previousBaudRate = Baud_Rate;
    previousSlaveId = Slave_id;
}

void modbus_loop() {
    // Check if Baud_Rate or Slave_id has changed
    if (Baud_Rate != previousBaudRate || Slave_id != previousSlaveId) {
        modbus_init();  // Reinitialize Modbus settings
    }

    // Status
    inputRegisters[1] = temperature;
    inputRegisters[2] = Input_voltage;
    // Set values
    inputRegisters[3] = temperature_thresholdHigh;
    inputRegisters[4] = temperature_thresholdLow;
    inputRegisters[5] = VoltageThres;
    inputRegisters[6] = Baud_Rate;
    inputRegisters[7] = Slave_id;
    // Flags
    discreteInputs[1] = Smoke_alarm;
    discreteInputs[2] = Temperature_alarm;
    discreteInputs[3] = Water_level_alarm;
    discreteInputs[4] = Door_alarm;
    discreteInputs[5] = Fan_fault_alarm;

    // Poll Modbus slave
    slave.poll();
}


