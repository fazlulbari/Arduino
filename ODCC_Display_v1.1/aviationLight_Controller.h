#ifndef AVIATIONLIGHT_CONTROLLER_H
#define AVIATIONLIGHT_CONTROLLER_H
#include "config.h"


void lightSensor_Init();
void aviationLight_Init();
int readLight_Sensor();
void lightSensor_Check();
void aviationController();
void aviationController_Loop();






#endif