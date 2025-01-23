#include "modbus_Master.h"
#include <math.h>

// Define HardwareSerial and ModbusRTUMaster instances
HardwareSerial mySerial(2); // Use UART1
ModbusRTUMaster master(mySerial);

// DC energy meter registers
uint16_t HoldingRegisters1[6];
uint16_t HoldingRegisters2[6];
uint16_t HoldingRegisters3[2];
uint16_t HoldingRegisters4[2];
uint16_t HoldingRegisters5[2];
uint16_t HoldingRegisters6[2];
uint16_t HoldingRegisters7[2];
uint16_t HoldingRegisters8[2];
uint16_t HoldingRegisters9[2];
uint16_t HoldingRegisters10[2];

// Initialize the master
void master_Init() {
  // Initialize hardware serial for Modbus communication
  mySerial.begin(9600, SERIAL_8N1, 33, 32); // GPIO33 as RX, GPIO32 as TX
  
  // Set timeout for Modbus communication
  master.setTimeout(1000); // 1000ms timeout
  
  // Start the master
  master.begin(9600);
}

int32_t stackBinary(uint16_t num1, uint16_t num2) {
  int bits1 = 16;
  int bits2 = 16;

  // Combine by shifting num1 and adding num2
  int32_t combined = ((long)num1 << bits2) | num2;
  return combined;
}

// Request data from the slave
String request_from_slave() {
  StaticJsonDocument<4096> jsonData;

  master.readHoldingRegisters(23, 4240, HoldingRegisters1, 6);
  master.readHoldingRegisters(23, 4288, HoldingRegisters2, 6);
  master.readHoldingRegisters(23, 4528, HoldingRegisters3, 2);
  master.readHoldingRegisters(23, 4496, HoldingRegisters4, 2);
  master.readHoldingRegisters(23, 4096, HoldingRegisters5, 2);
  master.readHoldingRegisters(23, 4352, HoldingRegisters6, 2);
  master.readHoldingRegisters(22, 0, HoldingRegisters7, 2);
  master.readHoldingRegisters(22, 12, HoldingRegisters8, 2);
  master.readHoldingRegisters(22, 40, HoldingRegisters9, 2);
  ModbusRTUMasterError result1 = master.readHoldingRegisters(22, 26, HoldingRegisters10, 2);
  Serial.println("Data taken ");

  if (result1 == 0) {
      
    jsonData["VoltagePhaseA"] = round(stackBinary(HoldingRegisters1[0], HoldingRegisters1[1]) * 0.0001 * 100) / 100.0;
    jsonData["VoltagePhaseB"] = round(stackBinary(HoldingRegisters1[2], HoldingRegisters1[3]) * 0.0001 * 100) / 100.0;
    jsonData["VoltagePhaseC"] = round(stackBinary(HoldingRegisters1[4], HoldingRegisters1[5]) * 0.0001 * 100) / 100.0;
    jsonData["CurrentPhaseA"] = round(stackBinary(HoldingRegisters2[0], HoldingRegisters2[1]) * 0.0001 * 100) / 100.0;
    jsonData["CurrentPhaseB"] = round(stackBinary(HoldingRegisters2[2], HoldingRegisters2[3]) * 0.0001 * 100) / 100.0;
    jsonData["CurrentPhaseC"] = round(stackBinary(HoldingRegisters2[4], HoldingRegisters2[5]) * 0.0001 * 100) / 100.0;
    jsonData["Frequency"] = round(HoldingRegisters3[0] * 0.01 * 100) / 100.0;
    jsonData["PowerFactor"] = round(HoldingRegisters4[0] * 0.001 * 100) / 100.0;
    jsonData["CumulativeEnergy"] = round(stackBinary(HoldingRegisters5[0], HoldingRegisters5[1]) * 0.01 * 100) / 100.0;
    jsonData["Power"] = round(stackBinary(HoldingRegisters6[0], HoldingRegisters6[1]) * 0.0001 * 100) / 100.0;
    jsonData["DCVoltage"] = round(stackBinary(HoldingRegisters7[0], HoldingRegisters7[1]) * 0.001 * 100) / 100.0;
    jsonData["TenantLoad"] = round(stackBinary(HoldingRegisters8[0], HoldingRegisters8[1]) * 0.0001 * 100) / 100.0;
    jsonData["CumulativeDCEnergy"] = round(stackBinary(HoldingRegisters9[0], HoldingRegisters9[1]) * 0.001 * 100) / 100.0;
    jsonData["PowerDC"] = round(stackBinary(HoldingRegisters10[0], HoldingRegisters10[1]) * 0.001 * 100) / 100.0;

      String jsonString;
      serializeJson(jsonData, jsonString);
      return jsonString;
  } else {
      Serial.print("Error reading registers: ");
      Serial.println(result1);
      return "{}";
  }
}