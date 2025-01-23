#include "Peripherals.h"

Peripherals::Peripherals() {}

void Peripherals::begin() {
    setupPins();
}

void Peripherals::setupPins() {
    pinMode(CA_LIGHT_Trigger, OUTPUT);
    pinMode(RELAY_1_Trigger, OUTPUT);
    pinMode(RELAY_2_Trigger, OUTPUT);
    pinMode(RELAY_3_Trigger, OUTPUT);
    pinMode(RELAY_4_Trigger, OUTPUT);
    pinMode(RELAY_5_Trigger, OUTPUT);
    pinMode(RELAY_6_Trigger, OUTPUT);
}

void Peripherals::triggerRelay(int relay, bool state) {
    digitalWrite(relay, state ? HIGH : LOW);
}

void Peripherals::controlLight(bool state) {
    digitalWrite(CA_LIGHT_Trigger, state ? HIGH : LOW);
}
