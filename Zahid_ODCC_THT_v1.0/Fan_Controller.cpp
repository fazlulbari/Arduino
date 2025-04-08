#include "Fan_Controller.h"

FanController::FanController() {}

void FanController::begin() {
    setupPins();
}

void FanController::setupPins() {
    pinMode(FAN1_PWM_PIN, OUTPUT);
    pinMode(FAN2_PWM_PIN, OUTPUT);
}

void FanController::controlFan1(bool state) {
    digitalWrite(FAN1_PWM_PIN, state ? HIGH : LOW);
}

void FanController::controlFan2(bool state) {
    digitalWrite(FAN2_PWM_PIN, state ? HIGH : LOW);
}

int FanController::readFan1Current() {
    return analogRead(FAN1_SHUNT_PIN);
}

int FanController::readFan2Current() {
    return analogRead(FAN2_SHUNT_PIN);
}

void FanController::toggle_Fan(bool fanState) {
  controlFan1(fanState);
  controlFan2(!fanState);
}
