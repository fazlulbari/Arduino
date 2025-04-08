#ifndef ODCC_CONFIG_H
#define ODCC_CONFIG_H

#include "MCU_config.h"

extern float temperature;
extern float Input_voltage;
extern float current1;
extern float current2;

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
#define FAN1_PWM_PIN PA7
#define FAN1_SHUNT_PIN   PA5  // Analog pin ADC for Current sensing

#define FAN2_PWM_PIN PA6
#define FAN2_SHUNT_PIN   PA4  // Analog pin ADC for Current sensing

#define CA_LIGHT_PIN PA8  // Cabinet light, Turn ON when Door opens

// Relay Alarm pins
#define DOOR_ALARM       RELAY_1_Trigger
#define WATER_ALARM      RELAY_2_Trigger
#define SMOKE_ALARM      RELAY_3_Trigger
#define FAN_FAULT_ALARM  RELAY_4_Trigger
#define HIGH_TEMP_ALARM  RELAY_5_Trigger
#define BUZZER_Trigger   RELAY_6_Trigger

// Cabinet Power voltage sense
#define VOLTAGE_ADC_PIN    PA0 // Analog pin ADC for Volatge sensing

// Digital Sensors
#define Door_Sensor      PB9  //  Use Input PullUp, 0 when Opens
#define Water_Sensor     PB1  //  Use Input PullUp, 0 when Water enters
#define Smoke_Sensor     PB8  //  Use Input PullUp, 0 when smoke detected, also pulses every 5-6 seconds

// Temperature sensor
#define Temp_Sensor      PC13 // DS18B20 Temperature Sensor, Onewire protocol

// Temperature threshold



#endif  // ODCC_CONFIG_H
