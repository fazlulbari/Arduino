#include "Buttons.h"

Buttons::Buttons() {}

void Buttons::begin() {
    setupPins();
}

void Buttons::setupPins() {
    pinMode(BUTTON_ESC, INPUT_PULLUP);
    pinMode(BUTTON_OK, INPUT_PULLUP);
    pinMode(BUTTON_UP, INPUT_PULLUP);
    pinMode(BUTTON_DOWN, INPUT_PULLUP);
}

int Buttons::read() {
    if (digitalRead(BUTTON_ESC) == LOW) return BUTTON_ESC;
    if (digitalRead(BUTTON_OK) == LOW) return BUTTON_OK;
    if (digitalRead(BUTTON_UP) == LOW) return BUTTON_UP;
    if (digitalRead(BUTTON_DOWN) == LOW) return BUTTON_DOWN;
    return -1; // No button pressed
}
