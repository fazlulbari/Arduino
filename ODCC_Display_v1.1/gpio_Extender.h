#include "config.h"
#include <mcp23017.h>

void extender_begin();

void doorSensor_Init();
bool get_DoorSensorValue();

void waterSensor_Init();
bool get_WaterSensorValue();

void smokeSensor_TriggerInit();
void smokeSensor_DetectInit();
void triggerSmoke_Sensor(bool value);
bool get_4WireSmokeSensorValue() ;




void alarmOut_Init();
void alarm_DryOut(uint8_t pin, bool value);
