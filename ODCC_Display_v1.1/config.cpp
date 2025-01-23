////////////////////////////////////////////////////////////////////////////////////
// @File          : config.cpp                                                    //
// @Module        : Configuration                                                 //
// @Version       : v1.0.0                                                        //
// @Standerd      : Moduler C/C++                                                 //
// @OS            : freeRTOS                                                      //
// @Platform      : Arduino                                                       //
// @MCU           : Esp32 Wrover -B                                               //
// @Project       : Remote Monitoring System                                      //
// @Creation Date : 03/10/2023                                                    //
// @Modified Date : 08/11/2023                                                    //
// @Auther        : Shamim Hasan                                                  //
// @Modified by   : Shamim Hasan                                                  //
// @Company       : SARBS Communication LTD                                       //
// @Copyright     : 2023@SARBS Communication LTD                                  //
////////////////////////////////////////////////////////////////////////////////////


#include "config.h"

void i2cBus_Begin() {
  Wire.setPins(12, 13);
  Wire.begin();
}

int base_ADC = 1983;

bool lightSensor_Status = false;
//////////////////////// Alarm Data ///////////////////////////////////////////////
bool fanFault_Alarm = false;
bool caFault_Alarm = false;
bool door_Status = false;
bool water_Alarm = false;
bool smoke_Alarm = false;
bool highTemp_Alarm = false;
bool aviation_Light = false;


//////////////////////// Environmental Data ///////////////////////////////////////////////
int fan_Status[4] = { 0, 0, 0, 0 };
int fan_Consumption = 0;
float env_Temp = 0;
float env_Hum = 0;
uint8_t lowerTemp_TH = 27;
uint8_t higherTemp_TH = 30;
uint32_t fanToggle_Interval = 30000;

bool fan_Ch1_Fault = false;
bool fan_Ch2_Fault = false;


