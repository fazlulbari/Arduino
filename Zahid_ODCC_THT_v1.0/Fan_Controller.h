#ifndef FAN_CONTROLLER_H
#define FAN_CONTROLLER_H

#include "Arduino.h"
#include "ODCC_config.h"

class FanController {
public:
    FanController();
    void begin();
    void controlFan1(bool state);
    void controlFan2(bool state);
    int readFan1Current();
    int readFan2Current();
    void toggle_Fan(bool fanState);

private:
    void setupPins();
};

#endif // FAN_CONTROLLER_H
