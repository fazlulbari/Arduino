#ifndef MENU_H
#define MENU_H

#include <LiquidCrystal.h>
#include <OneButton.h>
#include "ODCC_config.h"
#include "CMBMenu.hpp"
#include <STM32FreeRTOS.h>

// define text to display
const char Status[] PROGMEM = { "1. Status" };
const char Temperature[] PROGMEM = { "Temperature" };
const char InputVoltage[] PROGMEM = { "Input Voltage" };
const char Alarms[] PROGMEM = { "2. Alarms" };
const char Smokealarm[] PROGMEM = { "Smoke Alarm" };
const char Temperaturealarm[] PROGMEM = { "Temperature" };
const char FanFaultalarm[] PROGMEM = { "Fan Fault" };
const char Wateralarm[] PROGMEM = { "Water Level" };
const char Dooralarm[] PROGMEM = { "Door Open" };
const char Config[] PROGMEM = { "3. Config" };
const char TemperatureThresholdH[] PROGMEM = { "Temp Threshold H" };
const char TemperatureThresholdL[] PROGMEM = { "Temp Threshold L" };
const char VoltageThreshold[] PROGMEM = { "Volt Threshold" };
const char Baudrate[] PROGMEM = { "Baud Rate" };
const char SlaveID[] PROGMEM = { "Slave ID" };

extern const int UP_BUTTON;
extern const int DOWN_BUTTON;
extern const int ENTER_BUTTON;
extern const int ESC_BUTTON;

extern LiquidCrystal g_Lcd;
extern OneButton upButton;
extern OneButton downButton;
extern OneButton enterButton;
extern OneButton escButton;

// define function IDs
enum MenuFID {
  MenuDummy,
  MenuStatus,
  MenuTemperature,
  MenuInputVoltage,
  MenuAlarms,
  MenuSmokeAlarm,
  MenuTemperatureAlarm,
  MenuFanFaultAlarm,
  MenuWaterAlarm,
  MenuDoorAlarm,
  MenuConfig,
  MenuTemperatureThresholdH,
  MenuTemperatureThresholdL,
  MenuVoltageThreshold,
  MenuBaudrate,
  MenuSlaveID
};

enum KeyType {
  KeyNone,
  KeyLeft,
  KeyRight,
  KeyEnter,
  KeyExit,
  DoubleClick // Add this if not already defined
};

extern KeyType currentKey;

// Function declarations
void setupMenu();
void loopMenu();
void printMenuEntry(const char* f_Info);
void showTemperature();
void showSmokeAlarm();
void showTemperatureAlarm();
void showFanFaultAlarm();
void showWaterAlarm();
void showDoorAlarm();
void showInputVoltage();
void showConfig();
void showTemperatureThresholdH();
void showTemperatureThresholdL();
void showVoltageThreshold();
void showBaudrate();
void showSlaveID();

#endif
