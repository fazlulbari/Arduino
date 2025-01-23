#include "modbus_Master.h"
#include <math.h>

// HardwareSerial and ModbusRTUMaster instances
HardwareSerial mySerial(2); // Use UART1
ModbusRTUMaster master(mySerial);

// Modbus registers
uint16_t HoldingRegisters1[6];
uint16_t HoldingRegisters2[6];
uint16_t HoldingRegisters3[2];
uint16_t HoldingRegisters4[8];
uint16_t HoldingRegisters5[8];
uint16_t HoldingRegisters6[8];
uint16_t HoldingRegisters7[8];
uint16_t HoldingRegisters8[2];
uint16_t HoldingRegisters9[2];

// Data variables
double VoltagePhaseA, VoltagePhaseB, VoltagePhaseC;
double CurrentPhaseA, CurrentPhaseB, CurrentPhaseC;
double Frequency;
double ActivePowerA, ActivePowerB, ActivePowerC, ActivePowerT;
double ReactivePowerA, ReactivePowerB, ReactivePowerC, ReactivePowerT;
double ApparentPowerA, ApparentPowerB, ApparentPowerC, ApparentPowerT;
double PFA, PFB, PFC, PFT;
double TotalActiveEnergy;
double TotalReactiveEnergy;
// Combine two 16-bit values into a 32-bit integer
int32_t stackBinary(uint16_t num1, uint16_t num2) {
    return ((int32_t)num1 << 16) | num2;
}

// Initialize the Modbus master
void master_Init() {
    mySerial.begin(9600, SERIAL_8N1, 33, 32); // GPIO33 as RX, GPIO32 as TX
    master.setTimeout(1000); // 1000ms timeout
    master.begin(9600);
    Serial.println("Modbus Master Initialized");
}

// Request data from the slave and parse the response
int request_from_slave() {
  master.readHoldingRegisters(23, 0x1090, HoldingRegisters1, 6); //Voltage
  master.readHoldingRegisters(23, 0x10c0, HoldingRegisters2, 6); //Current
  master.readHoldingRegisters(23, 0x11b0, HoldingRegisters3, 2); //Freq
  master.readHoldingRegisters(23, 0x1100, HoldingRegisters4, 8); //Active Power
  master.readHoldingRegisters(23, 0x1140, HoldingRegisters5, 8); //Reactive Power
  master.readHoldingRegisters(23, 0x1100, HoldingRegisters6, 8); //Apperent Power
  master.readHoldingRegisters(23, 0x1190, HoldingRegisters7, 4); //PF
  master.readHoldingRegisters(23, 0x1000, HoldingRegisters8, 2); //Total Active Energy
  ModbusRTUMasterError result =master.readHoldingRegisters(23, 0x13e0, HoldingRegisters9, 2); //Total Reactive Energy
  int Sign= result;

  if (result == 0) {
  // Parse data into variables
    VoltagePhaseA = stackBinary(HoldingRegisters1[0], HoldingRegisters1[1]) * 0.0001;
    VoltagePhaseB = stackBinary(HoldingRegisters1[2], HoldingRegisters1[3]) * 0.0001;
    VoltagePhaseC = stackBinary(HoldingRegisters1[4], HoldingRegisters1[5]) * 0.0001;

    CurrentPhaseA = stackBinary(HoldingRegisters2[0], HoldingRegisters2[1])* 0.0001;
    CurrentPhaseB = stackBinary(HoldingRegisters2[2], HoldingRegisters2[3]) * 0.0001;
    CurrentPhaseC = stackBinary(HoldingRegisters2[4], HoldingRegisters2[5]) * 0.0001;

    Frequency = round(HoldingRegisters3[0] * 0.01 * 100) / 100.0;

    ActivePowerA = stackBinary(HoldingRegisters4[2], HoldingRegisters4[3]) * 0.0001;
    ActivePowerB = stackBinary(HoldingRegisters4[4], HoldingRegisters4[5]) * 0.0001;
    ActivePowerC = stackBinary(HoldingRegisters4[6], HoldingRegisters4[7]) * 0.0001;
    ActivePowerT = stackBinary(HoldingRegisters4[0], HoldingRegisters4[1]) * 0.0001;

    ReactivePowerA = stackBinary(HoldingRegisters5[2], HoldingRegisters5[3]) * 0.0001;
    ReactivePowerB = stackBinary(HoldingRegisters5[4], HoldingRegisters5[5]) * 0.0001;
    ReactivePowerC = stackBinary(HoldingRegisters5[6], HoldingRegisters5[7]) * 0.0001;
    ReactivePowerT = stackBinary(HoldingRegisters5[0], HoldingRegisters5[1]) * 0.0001;

    PFA = round(HoldingRegisters7[1] * 0.001);
    PFB = round(HoldingRegisters7[2] * 0.001);
    PFC = round(HoldingRegisters7[3] * 0.001);
    PFT = round(HoldingRegisters7[0] * 0.001);

    TotalActiveEnergy = round(stackBinary(HoldingRegisters8[0], HoldingRegisters8[1]) * 0.01 * 100) / 100.0;
    TotalReactiveEnergy = round(stackBinary(HoldingRegisters9[0], HoldingRegisters9[1]) * 0.01 * 100) / 100.0;

  
  return Sign;
  }
  else
  {
  return Sign;
  }
}
