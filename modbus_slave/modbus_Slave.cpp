#include "modbus_Slave.h"

// STM32 UART2 pins are predefined (PA2: TX, PA3: RX)
HardwareSerial mySerial(PA2, PA3); // Rename to avoid conflict with Serial1

ModbusRTUSlave slave(mySerial);

// Define Modbus memory arrays
bool coils[10];
bool discreteInputs[10];
uint16_t holdingRegisters[10];
uint16_t inputRegisters[10];

void slave_Init() {
  // Initialize UART
  mySerial.begin(9600, SERIAL_8N1);

  // Configure Modbus memory
  slave.configureCoils(coils, 20);                       // bool array for coil values
  slave.configureDiscreteInputs(discreteInputs, 20);     // bool array for discrete input values
  slave.configureHoldingRegisters(holdingRegisters, 20); // unsigned 16-bit array for holding registers
  slave.configureInputRegisters(inputRegisters, 20);     // unsigned 16-bit array for input registers

  // Start Modbus slave with ID 20 and baud rate 9600
  slave.begin(20, 9600);
}

void sendTo_Master() {
  // Populate input registers with test data
  inputRegisters[0] = 1;
  inputRegisters[1] = 2;
  inputRegisters[2] = 4;
  inputRegisters[3] = 4;
  inputRegisters[4] = 5;
  inputRegisters[5] = 6;
  inputRegisters[6] = 9;
  inputRegisters[7] = 9;
  inputRegisters[8] = 9;
}

void modbus_Callback() {
  // Print holding register values for debugging
  const int arrLen = sizeof(holdingRegisters) / sizeof(holdingRegisters[0]);
  Serial.println("");
  for (int i = 0; i < arrLen; i++) {
    Serial.print(holdingRegisters[i]);
    Serial.print(" | ");
  }
  Serial.println("");
}

void modbus_Loop() {
  // Update input registers with new data
  sendTo_Master();

  // Poll Modbus requests
  slave.poll();
}

