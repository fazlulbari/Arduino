#include "config.h"
#include "SmokeSensor.h"
#include "Output.h"

void setup() {
  initiallize_Sensors();    // Initialize sensor pins
  initialize_Output();      // Initialize output pins
}

void loop() {
  read_Sensor_Values();     // Read sensor values

  if (Smoke1 || Smoke2 || Smoke3 || Smoke4) {
    output_ON(HIGH, HIGH);  // Turn on alarm and relay
  } else {
    output_ON(LOW, LOW);    // Turn off alarm and relay
  }
}

