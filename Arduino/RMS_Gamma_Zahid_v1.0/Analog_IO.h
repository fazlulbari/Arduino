#ifndef ANALOG_IO_H
#define ANALOG_IO_H

#include "config.h"

extern bool is_ANALOG_IN_IC_Initialized;
extern bool is_ANALOG_OUT_IC_Initialized;

void analogInputInit();
void analogOutputInit();

void analogInputLoop();
void analogOutputLoop();


#endif // ANALOG_IO_H