#ifndef FAN_CONTROLLER_H
#define FAN_CONTROLLER_H

#include "config.h"


void fan_Init();
void fanAdc_Init();
void fan_Control(uint8_t pin, bool val);
void fanGroup_1_On();
void fanGroup_1_Off();
void fanGroup_2_On();
void fanGroup_2_Off();
void allfan_On();
void allfan_Off();
void fanOperation_Loop();
int fanConsumption();
void fanController_Loop();



#endif