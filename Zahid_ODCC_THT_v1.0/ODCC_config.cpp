#include "ODCC_config.h"
// Data
float temperature = 0;
float Input_voltage =0;
//Set Values
int temperature_thresholdHigh = 28;
int temperature_thresholdLow = 24;
uint32_t fanToggle_Interval = 2000;
int VoltageThres = 30;
int Baud_Rate = 9600;
int Slave_id = 20;
// Flags
bool Smoke_alarm = 0;
bool Temperature_alarm = 0;
bool Water_level_alarm =0;
bool Door_alarm = 0;
bool Fan_fault_alarm = 0;
