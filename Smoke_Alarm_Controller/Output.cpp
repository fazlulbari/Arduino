#include <Arduino.h>  // Include the Arduino API
#include "Output.h"

void initialize_Output() {
  pinMode(Smoke_Alarm, OUTPUT);
  pinMode(Smoke_Relay, OUTPUT);
}

void output_ON(bool St1, bool St2) {
  digitalWrite(Smoke_Alarm, St1);
  digitalWrite(Smoke_Relay, St2);
}

