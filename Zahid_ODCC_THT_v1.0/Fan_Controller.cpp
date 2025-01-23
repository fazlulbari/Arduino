#include "Fan_Controller.h"

FanController::FanController() {}

void FanController::begin() {
    setupPins();
}

void FanController::setupPins() {
    pinMode(FAN_1_Trigger, OUTPUT);
    pinMode(FAN_2_Trigger, OUTPUT);
}

void FanController::controlFan1(bool state) {
    digitalWrite(FAN_1_Trigger, state ? HIGH : LOW);
}

void FanController::controlFan2(bool state) {
    digitalWrite(FAN_2_Trigger, state ? HIGH : LOW);
}

int FanController::readFan1Current() {
    return analogRead(FAN_1_Sense);
}

int FanController::readFan2Current() {
    return analogRead(FAN_2_Sense);
}

void FanController::toggle_Fan(bool fanState) {
  controlFan1(fanState);
  controlFan2(!fanState);
}
