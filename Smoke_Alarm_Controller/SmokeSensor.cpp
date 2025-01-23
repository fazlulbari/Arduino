#include <Arduino.h>  // Include the Arduino API
#include "SmokeSensor.h"

bool Smoke1 = false;
bool Smoke2 = false;
bool Smoke3 = false;
bool Smoke4 = false;

void initiallize_Sensors() {
  pinMode(Smoke_Sensor1, INPUT_PULLUP);
  pinMode(Smoke_Sensor2, INPUT_PULLUP);
  pinMode(Smoke_Sensor3, INPUT_PULLUP);
  pinMode(Smoke_Sensor4, INPUT_PULLUP);
}

void read_Sensor_Values() {
  Smoke1 = !digitalRead(Smoke_Sensor1);
  Smoke2 = !digitalRead(Smoke_Sensor2);
  Smoke3 = !digitalRead(Smoke_Sensor3);
  Smoke4 = !digitalRead(Smoke_Sensor4);
}


