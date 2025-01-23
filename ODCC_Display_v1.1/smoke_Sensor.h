#ifndef SMOKE_SENSOR_H
#define SMOKE_SENSOR_H
#include "config.h"
#include "gpio_Extender.h"


void smokeSensorAdc_Init();
int smokeSensorConsumption();
void smokeSensor_Loop();



#endif