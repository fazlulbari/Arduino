#ifndef BUTTONS_H
#define BUTTONS_H

#include "Arduino.h"
#include "MCU_config.h"

class Buttons {
public:
    Buttons();
    void begin();
    int read();

private:
    void setupPins();
};

#endif // BUTTONS_H
