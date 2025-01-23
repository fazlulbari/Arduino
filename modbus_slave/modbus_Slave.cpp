#include "modbus_Slave.h"

// SoftwareSerial mySerial(rxPin, txPin);
HardwareSerial mySerial(1);
ModbusRTUSlave slave(mySerial);

bool coils[10];
bool discreteInputs[10];
uint16_t holdingRegisters[10];
uint16_t inputRegisters[10];

void slave_Init() {
  mySerial.begin(9600, SERIAL_8N1, 18, 17);
  slave.configureCoils(coils, 20);                       // bool array of coil values, number of coils
  slave.configureDiscreteInputs(discreteInputs, 20);     // bool array of discrete input values, number of discrete inputs
  slave.configureHoldingRegisters(holdingRegisters, 20); // unsigned 16 bit integer array of holding register values, number of holding registers
  slave.configureInputRegisters(inputRegisters, 20);     // unsigned 16 bit integer array of input register values, number of input registers
  slave.begin(20, 9600);
}

void sendTo_Master() {
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
  const int arrLen = sizeof(holdingRegisters) / sizeof(holdingRegisters[0]);
  Serial.println("");
  for (int i = 0; i < arrLen; i++) {
    Serial.print(holdingRegisters[i]);
    Serial.print(" | ");
  }
  Serial.println("");
}

void modbus_Loop() {
  sendTo_Master();

  slave.poll();
}