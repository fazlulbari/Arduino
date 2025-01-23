#ifndef SMOKE_SENSOR_H
#define SMOKE_SENSOR_H

#include "config.h"

void initiallize_Sensors();
void read_Sensor_Values();

extern bool Smoke1;
extern bool Smoke2;
extern bool Smoke3;
extern bool Smoke4;

#endif // SMOKE_SENSOR_H
