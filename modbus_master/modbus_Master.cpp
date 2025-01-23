#include "modbus_Master.h"

// Define HardwareSerial and ModbusRTUMaster instances
HardwareSerial mySerial(1); // Use UART1
ModbusRTUMaster master(mySerial);

// Define Modbus data arrays
bool coils[10];
bool discreteInputs[10];
uint16_t holdingRegisters[100];
uint16_t inputRegisters[100];

// Initialize the master
void master_Init() {
  // Initialize hardware serial for Modbus communication
  mySerial.begin(9600, SERIAL_8N1, 33, 32); // GPIO33 as RX, GPIO32 as TX
  
  // Set timeout for Modbus communication
  master.setTimeout(1000); // 1000ms timeout
  
  // Start the master
  master.begin(9600);
}

// Request data from the slave
void request_from_slave() {
  // Read 10 input registers starting from address 0 from slave with ID 1
  ModbusRTUMasterError result = master.readInputRegisters(23, 0, inputRegisters, 100);

  if (result == 0) {
    Serial.println("Registers read successfully!");
    for (int i = 0; i < 30; i++) {
      Serial.print("Register ");
      Serial.print(i);
      Serial.print(": ");
      Serial.println(inputRegisters[i]); // Use inputRegisters instead of inputBuffer
    }
  } else {
    Serial.print("Failed to read registers. Error: ");
    Serial.println(result);
  }
}