////////////////////////////////////////////////////////////////////////////////////
// @File          : config.h                                                      //
// @Module        : Configuration                                                 //
// @Version       : v1.0.0                                                        //
// @Standerd      : Moduler C/C++                                                 //
// @OS            : freeRTOS                                                      //
// @Platform      : Arduino                                                       //
// @MCU           : Esp32 Wrover -B                                               //
// @Project       : Remote Monitoring System                                      //
// @Creation Date : 03/10/2023                                                    //
// @Modified Date : 03/10/2023                                                    //
// @Auther        : Shamim Hasan                                                  //
// @Modified by   : Shamim Hasan                                                  //
// @Company       : SARBS Communication LTD                                       //
// @Copyright     : 2023@SARBS Communication LTD                                  //
////////////////////////////////////////////////////////////////////////////////////

#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include "esp_task_wdt.h"
#include <WiFi.h>
#include <Wire.h>
#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include <SPIFFS.h>
#include "esp32-hal-gpio.h"
#include "WString.h"

void i2cBus_Begin();

extern int base_ADC;

extern bool lightSensor_Status;
//////////////////////// Alarm Data ///////////////////////////////////////////////
extern bool fanFault_Alarm;
extern bool caFault_Alarm;
extern bool water_Alarm;
extern bool smoke_Alarm;
extern bool highTemp_Alarm;
extern bool aviation_Light;

//////////////////////// Environmental Data ///////////////////////////////////////////////
extern int fan_Status[4];
extern int fan_Consumption;
extern float env_Temp;
extern float env_Hum;
extern uint8_t lowerTemp_TH;
extern uint8_t higherTemp_TH;
extern uint32_t fanToggle_Interval;

extern bool fan_Ch1_Fault;
extern bool fan_Ch2_Fault;

extern bool door_Status;



//////////////////////// Alarm Out PINS ///////////////////////////////////////////////
#define FAN_FAULT_AL_PIN GPB0
#define SMOKE_AL_PIN GPB1
#define DOOR_AL_PIN GPB2
#define HIGH_TEMP_AL_PIN GPB3



//////////////////////// Exhaust Fan Config ///////////////////////////////////////////////
#define FAN_1 2  //  Fan OUTPUT Pin
#define FAN_2 4  //  Fan OUTPUT Pin
#define FAN_3 6  //  Fan OUTPUT Pin
#define FAN_4 8  //  Fan OUTPUT Pin

#define FAN_BUS_ADC 1   // Fan Bus Input Pin
#define FAN_CH_1_ADC 3  // Fan ADC Input Pin
#define FAN_CH_2_ADC 5  // Fan ADC Input Pin

#define ON true
#define OFF false

#define LIGHT_SENSOR 14
#define AVIATION_LIGHT_PIN 42
#define CABINET_LIGHT_PIN 10
#define CABINET_LIGHT_ADC 9

#define SMOKE_SENSOR_ADC 11

//////////////////////  Modbus ////////////////////////////////////
#define MODBUS_RX_PIN 18
#define MODBUS_TX_PIN 17






#endif