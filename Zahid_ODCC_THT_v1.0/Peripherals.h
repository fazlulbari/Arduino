#ifndef PERIPHERALS_H
#define PERIPHERALS_H

#include "Arduino.h"
#include "ODCC_config.h"

class Peripherals {
public:
    Peripherals();
    void begin();
    void triggerRelay(int relay, bool state);
    void controlLight(bool state);

private:
    void setupPins();
};

#endif // PERIPHERALS_H
