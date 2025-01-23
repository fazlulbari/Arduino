#ifndef SENSORS_H
#define SENSORS_H

#include "Arduino.h"
#include "ODCC_config.h"
#include <OneWire.h>
#include <DallasTemperature.h>

class Sensors {
public:
    Sensors();
    void begin();
    bool isDoorOpen();
    bool isWaterPresent();
    bool isSmokeDetected();
    float readTemperature();
    float voltageSence();

private:
    void setupPins();
    // OneWire and DallasTemperature objects
    OneWire oneWire;
    DallasTemperature sensors;
};

#endif // SENSORS_H
