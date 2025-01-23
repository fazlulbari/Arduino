#include "HardwareSerial.h"
#include "WString.h"
#include "esp32-hal-gpio.h"

#include "cabinetLight_Controller.h"

bool caLight_Status = false;

void cabinetLight_Init() {
  pinMode(CABINET_LIGHT_PIN, OUTPUT);
  pinMode(CABINET_LIGHT_ADC, INPUT);
}

int CALight_Consumption() {

  int caLight_Adc = 0;
  for (int i = 0; i < 1000; i++) {
    caLight_Adc = caLight_Adc + analogRead(CABINET_LIGHT_ADC);
  }
  caLight_Adc = caLight_Adc / 1000;
  return caLight_Adc;
}

void cabinetLight_Operator(uint8_t pin, bool val) {
  digitalWrite(pin, val);
  int caLight_Adc = CALight_Consumption();
  Serial.println("Cabinet Light Power Consumptions " + String(caLight_Adc));

  if (caLight_Status) {
    if (caLight_Adc > 2000 && caLight_Adc < 2200) {
      caFault_Alarm = false;
      Serial.println("Cabinet Light Ok!");
    } else {
      caFault_Alarm = true;
      Serial.println("Cabinet Light Fault!");
    }
  }
}

void cabinetLight_Control() {
  door_Status = get_DoorSensorValue();
  Serial.println("Door Status: " + String(door_Status));

  if (door_Status) {
    // Cabinet Light On
    cabinetLight_Operator(CABINET_LIGHT_PIN, ON);
    caLight_Status = true;
  } else {
    // Cabinet Light Off
    cabinetLight_Operator(CABINET_LIGHT_PIN, OFF);
    caLight_Status = false;
  }
}