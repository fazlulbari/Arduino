#ifndef MODULE1_H
#define MODULE1_H

#include <OneWire.h>
#include <DallasTemperature.h>

// Function declarations
float Returntemp(int gpioPin);  // Pass GPIO pin to get temperature from specific pin

#endif