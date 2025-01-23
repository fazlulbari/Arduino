#include "esp32-hal-gpio.h"
#include "mcp23017_defs.h"
#include "gpio_Extender.h"

MCP23017 mcp(0x20);

void extender_begin() {
  pinMode(35, OUTPUT);
  digitalWrite(35, LOW);
  delay(200);
  digitalWrite(35, HIGH);

  mcp.start();
  doorSensor_Init();
  waterSensor_Init();

  smokeSensor_TriggerInit();
  smokeSensor_DetectInit();


  alarmOut_Init();
}

void doorSensor_Init() {
  mcp.pinMode(GPA7, INPUT_PULLUP);
}

bool get_DoorSensorValue() {
  bool result = mcp.digitalRead(GPA7);
  return result;
}

void waterSensor_Init() {
  mcp.pinMode(GPA6, INPUT);
}

bool get_WaterSensorValue() {
  bool result = mcp.digitalRead(GPA6);
  return result;
}

void smokeSensor_TriggerInit() {
  mcp.pinMode(GPA4, OUTPUT);
}

void triggerSmoke_Sensor(bool value) {
  mcp.digitalWrite(GPA4, value);
}

void smokeSensor_DetectInit() {
  mcp.pinMode(GPA5, INPUT);
}

bool get_4WireSmokeSensorValue() {
  bool result = mcp.digitalRead(GPA5);
  return result;
}



void alarmOut_Init() {
  mcp.pinMode(FAN_FAULT_AL_PIN, OUTPUT);
  mcp.pinMode(SMOKE_AL_PIN, OUTPUT);
  mcp.pinMode(DOOR_AL_PIN, OUTPUT);
  mcp.pinMode(HIGH_TEMP_AL_PIN, OUTPUT);

  alarm_DryOut(FAN_FAULT_AL_PIN, OFF);
  alarm_DryOut(SMOKE_AL_PIN, OFF);
  alarm_DryOut(DOOR_AL_PIN, OFF);
  alarm_DryOut(HIGH_TEMP_AL_PIN, OFF);
}

void alarm_DryOut(uint8_t pin, bool value) {
  mcp.digitalWrite(pin, value);
}
