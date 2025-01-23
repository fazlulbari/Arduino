#ifndef DIGITAL_IO_H
#define DIGITAL_IO_H

#include "config.h"

extern bool is_Extender_1_Initialized;
extern bool is_Extender_2_Initialized;

void digitalInputInit();
void digitalOutputInit();

void digitalInputLoop();
void digitalOutputLoop();


#endif // DIGITAL_IO_H