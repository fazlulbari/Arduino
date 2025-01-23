#ifndef CABINETLIGHT_CONTROLLER_H
#define CABINETLIGHT_CONTROLLER_H

#include "config.h"
#include "gpio_Extender.h"

void cabinetLight_Init();
int CALight_Consumption();
void cabinetLight_Operator(uint8_t pin, bool val);
void cabinetLight_Control();


#endif