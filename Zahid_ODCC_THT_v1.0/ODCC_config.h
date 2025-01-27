#ifndef ODCC_CONFIG_H
#define ODCC_CONFIG_H

#include "MCU_config.h"

extern float temperature;
extern float Input_voltage;

extern int temperature_thresholdHigh;
extern int temperature_thresholdLow;
extern uint32_t fanToggle_Interval;
extern int VoltageThres;
extern int Baud_Rate;
extern int Slave_id;


extern bool Smoke_alarm;
extern bool Temperature_alarm;
extern bool Water_level_alarm;
extern bool Door_alarm;
extern bool Fan_fault_alarm;

// Main control pins
#define FAN_1_Trigger PA7
#define FAN_1_Sense   PA6  // Analog pin ADC for Current sensing

#define FAN_2_Trigger PA5
#define FAN_2_Sense   PA4  // Analog pin ADC for Current sensing

#define CA_LIGHT_Trigger PA8  // Cabinet light, Turn ON when Door opens

// Relay Alarm pins
#define DOOR_ALARM       RELAY_1_Trigger
#define WATER_ALARM      RELAY_2_Trigger
#define SMOKE_ALARM      RELAY_3_Trigger
#define FAN_FAULT_ALARM  RELAY_4_Trigger
#define HIGH_TEMP_ALARM  RELAY_5_Trigger
#define BUZZER_Trigger   RELAY_6_Trigger

// Cabinet Power voltage sense
#define Voltage_Sense    PA0 // Analog pin ADC for Volatge sensing

// Digital Sensors
#define Door_Sensor      PB9  //  Use Input PullUp, 0 when Opens
#define Water_Sensor     PB1  //  Use Input PullUp, 0 when Water enters
#define Smoke_Sensor     PB8  //  Use Input PullUp, 0 when smoke detected, also pulses every 5-6 seconds

// Temperature sensor
#define Temp_Sensor      PC13 // DS18B20 Temperature Sensor, Onewire protocol

// Temperature threshold



#endif  // ODCC_CONFIG_H
