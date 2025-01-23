#ifndef MODBUS_MASTER_H
#define MODBUS_MASTER_H

#include <Arduino.h>
#include "ModbusRTUMaster.h"

// Declare global variables to make them accessible across files
extern double VoltagePhaseA, VoltagePhaseB, VoltagePhaseC;
extern double CurrentPhaseA, CurrentPhaseB, CurrentPhaseC;
extern double Frequency;
extern double ActivePowerA, ActivePowerB, ActivePowerC, ActivePowerT;
extern double ReactivePowerA, ReactivePowerB, ReactivePowerC, ReactivePowerT;
extern double ApparentPowerA, ApparentPowerB, ApparentPowerC, ApparentPowerT;
extern double PFA, PFB, PFC, PFT;
extern double TotalActiveEnergy;
extern double TotalReactiveEnergy;


// Modbus Master Initialization
void master_Init();

// Request data from the slave and parse it
int request_from_slave();

// Combine two 16-bit values into a 32-bit integer
int32_t stackBinary(uint16_t num1, uint16_t num2);

#endif // MODBUS_MASTER_H