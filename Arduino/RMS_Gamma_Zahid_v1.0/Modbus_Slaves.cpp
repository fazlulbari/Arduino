#include "Modbus_Slaves.h"

#ifdef SOFTWARE_SERIAL_FOR_MODBUS_1
  SoftwareSerial modbusSerial(MODBUS_1_RX_PIN, MODBUS_1_TX_PIN);
#endif

// Function to read all registers of a Modbus slave
void readModbusSlave(ModbusSlave &slave) {
  node.begin(slave.slaveID, modbusSerial);
  
  for (uint8_t i = 0; i < slave.numRegisters; i++) {
    readModbusParameter(slave.registers[i]);

    // Format the description and value into a string and store it in the data array
    // slave.dataArray[i] = String(slave.registers[i].value, 2);
    slave.dataArray[i] = String(slave.registers[i].description) + String(slave.registers[i].value, 2);
  }
}

void readModbusParameter(ModbusParameter &reg) {
  uint8_t result;
  if (reg.regType == HOLDING_REGISTER) {
    result = node.readHoldingRegisters(reg.address, reg.numRegisters);
  } else {
    result = node.readInputRegisters(reg.address, reg.numRegisters);
  }
  
  if (result == node.ku8MBSuccess) {
    uint32_t rawValue = 0;
    
    if (reg.numRegisters == 2) {
      rawValue = (uint32_t(node.getResponseBuffer(0)) << 16) | node.getResponseBuffer(1);
    } else {
      rawValue = node.getResponseBuffer(0);
    }

    if (reg.isSigned) {
      reg.value = int32_t(rawValue) * reg.scale;  // Treat the value as signed
    } else {
      reg.value = rawValue * reg.scale;  // Treat the value as unsigned
    }
  } else {
    Serial.println("Modbus Read error");
  }
}

// Define registers for ACEM slave with descriptions and scaling factors
ModbusParameter acemParameters[] = {
  {"Voltage phase A:",            0x1090, 2, 0.0001, false, 0.0, HOLDING_REGISTER},
  {"Voltage phase B:",            0x1092, 2, 0.0001, false, 0.0, HOLDING_REGISTER},
  {"Voltage phase C:",            0x1094, 2, 0.0001, false, 0.0, HOLDING_REGISTER},
  {"Current phase A:",            0x10C0, 2, 0.0001, false, 0.0, HOLDING_REGISTER},
  {"Current phase B:",            0x10C2, 2, 0.0001, false, 0.0, HOLDING_REGISTER},
  {"Current phase C:",            0x10C4, 2, 0.0001, false, 0.0, HOLDING_REGISTER},
  {"Frequency:",                  0x11B0, 1, 0.01,   false, 0.0, HOLDING_REGISTER},
  {"Power Factor:",               0x1190, 1, 0.001,  false, 0.0, HOLDING_REGISTER},
  {"Cumulative Energy (kWh):",    0x1000, 2, 0.01,   false, 0.0, HOLDING_REGISTER},
  {"Power (kW):",                 0x1100, 2, 0.0001, false, 0.0, HOLDING_REGISTER}
};

// Define registers for DCEM slave with descriptions and scaling factors
ModbusParameter dcemParameters[] = {
  {"DC Voltage (V):",             0x0000, 2, 0.001,  false, 0.0, HOLDING_REGISTER},
  {"Tenant load (A):",            0x000C, 2, 0.0001, false, 0.0, HOLDING_REGISTER},
  {"Cumulative DC Energy (kWh):", 0x0028, 2, 0.01,   false, 0.0, HOLDING_REGISTER},
  {"Power DC (kW):",              0x001A, 2, 0.0001, false, 0.0, HOLDING_REGISTER}
};

// Define arrays to hold the formatted data strings
String acemData[sizeof(acemParameters) / sizeof(acemParameters[0])];
String dcemData[sizeof(dcemParameters) / sizeof(dcemParameters[0])];

// Define the ACEM and DCEM slaves
ModbusSlave acem = {"ACEM", 23, acemParameters, sizeof(acemParameters) / sizeof(acemParameters[0]), acemData};
ModbusSlave dcem = {"DCEM", 22, dcemParameters, sizeof(dcemParameters) / sizeof(dcemParameters[0]), dcemData};

ModbusMaster node;


void modbus_Init() {
  
  #ifdef SOFTWARE_SERIAL_FOR_MODBUS_1
    modbusSerial.begin(MODBUS_1_BAUDRATE); // Initialize software serial for Modbus
  #else
    modbusSerial.begin(MODBUS_1_BAUDRATE, SERIAL_8N1, MODBUS_1_RX_PIN, MODBUS_1_TX_PIN); // Initialize hardware serial for Modbus
  #endif
  
  node.begin(1, modbusSerial);  // Initialize ModbusMaster with the serial instance

}

void modbus_Loop() {
  
  readModbusSlave(acem);  // Read data from the ACEM slave
  readModbusSlave(dcem);  // Read data from the DCEM slave

}

void modbus_Print() {

  // Print the formatted data for ACEM
  for (int i = 0; i < acem.numRegisters; i++) {
    Serial.println(acemData[i]);
  }
  delay(10);

  // Print the formatted data for DCEM
  for (int i = 0; i < dcem.numRegisters; i++) {
    Serial.println(dcemData[i]);
  }
}

