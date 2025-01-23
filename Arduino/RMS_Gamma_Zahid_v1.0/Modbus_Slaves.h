#ifndef MODBUS_SLAVES_H
#define MODBUS_SLAVES_H

#include <ModbusMaster.h>
#include "config.h"


#ifdef SOFTWARE_SERIAL_FOR_MODBUS_1
  #include <SoftwareSerial.h>
  extern SoftwareSerial modbusSerial;
#else
  #define modbusSerial Serial1  // Use Serial1 or any other hardware serial port
#endif

// Enum to define register type
enum RegisterType {
  HOLDING_REGISTER,
  INPUT_REGISTER
};

// Define a struct for Modbus Parameters
struct ModbusParameter {
  const char* description;  // Description of the Parameter
  uint16_t address;         // Modbus register starting address
  uint8_t numRegisters;     // Number of registers to read (1 or 2)
  float scale;              // Scaling factor
  bool isSigned;            // Whether the value is signed or unsigned
  float value;              // Processed value
  RegisterType regType;     // Type of register: HOLDING or INPUT
};

// Define a struct for Modbus slaves
struct ModbusSlave {
  const char* name;             // Name of the Modbus slave
  uint8_t slaveID;              // Modbus slave ID
  ModbusParameter* registers;   // Pointer to an array of Modbus registers
  uint8_t numRegisters;         // Number of registers
  String* dataArray;            // Pointer to a string array to hold formatted data
};

// Function prototypes
void modbus_Init();
void modbus_Loop();
void modbus_Print();
void readModbusSlave(ModbusSlave &slave);
void readModbusParameter(ModbusParameter &reg);

// Global variables
extern ModbusMaster node;
extern ModbusSlave acem;
extern ModbusSlave dcem;
extern String acemData[];
extern String dcemData[];

#endif // MODBUS_SLAVES_H
