#include "System_Parameters.h"

LTC4151 sensor;

void system_Parameter_Init() {
  if (!is_I2C_Initialized) I2C_Init();
  sensor.init(LTC4151::L, LTC4151::L);
}

void get_System_Parameters(){
  double system_Voltage = sensor.getInputVoltage();
  double system_Current = sensor.getLoadCurrent(0.01);   
  // system_Current *= 0.001;   // to get in milliAmp
  double system_Power = system_Voltage * system_Current;
  system_Power *= 0.001;
  Serial.println("System Voltage: " + String(system_Voltage) + " V");
  Serial.println("System Current: " + String(system_Current) + " mA");
  Serial.println("System Power  : " + String(system_Power)   + " W");
}