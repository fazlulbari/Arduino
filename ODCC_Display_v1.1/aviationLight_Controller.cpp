#include "Arduino.h"
#include "esp32-hal-gpio.h"
#include "aviationLight_Controller.h"


void lightSensor_Init() {
  pinMode(LIGHT_SENSOR, INPUT);
}

void aviationLight_Init() {
  pinMode(AVIATION_LIGHT_PIN, OUTPUT);
}

void aviationLight_Operation(uint8_t pin, bool val) {
  digitalWrite(pin, val);
}


int readLight_Sensor() {
  int Light_Adc = 0;
  for (int i = 0; i < 500; i++) {
    Light_Adc = Light_Adc + analogRead(LIGHT_SENSOR);
  }
  Light_Adc = Light_Adc / 500;
  return Light_Adc;
}

void lightSensor_Check() {
  int sensorValue = readLight_Sensor();
  if (sensorValue > 4000) {
    lightSensor_Status = false;
    Serial.println("Light Sensor Disnnected!");
  } else {
    lightSensor_Status = true;
    Serial.println("Light Sensor Connected!");
  }
}


void aviationController() {
  if (lightSensor_Status) {
    int sensorValue = readLight_Sensor();
    if (sensorValue < 2500) {
      Serial.println("Day Time! Light OFF!");
      aviationLight_Operation(AVIATION_LIGHT_PIN, OFF);
      aviation_Light = false;
    } else {
      Serial.println("NIGHT Time! Light ON!");
      aviationLight_Operation(AVIATION_LIGHT_PIN, ON);
      aviation_Light = true;
    }
  }
}



void aviationController_Loop() {
  lightSensor_Check();
  aviationController();
}