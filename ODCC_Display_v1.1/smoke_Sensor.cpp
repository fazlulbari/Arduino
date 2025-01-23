#include "smoke_Sensor.h"

void smokeSensorAdc_Init() {
  pinMode(SMOKE_SENSOR_ADC, INPUT);
}




int smokeSensorConsumption() {
  int smoke_Adc = 0;
  for (int i = 0; i < 1000; i++) {
    smoke_Adc = smoke_Adc + analogRead(SMOKE_SENSOR_ADC);
  }
  smoke_Adc = smoke_Adc / 1000;
  return smoke_Adc;
}




void smokeSensor_Loop() {
  triggerSmoke_Sensor(ON);
  int smoke_Status = get_4WireSmokeSensorValue();
  int smoke_Adc = smokeSensorConsumption();

  int smokeAdc_Diff = smoke_Adc - base_ADC;
  Serial.println("Smoke Sensor ADC " + String(smoke_Adc) + "4 Wire Smoke Status" + String(smoke_Status) + "Smoke Difference" + String(smokeAdc_Diff));

  if (smoke_Status == true || smokeAdc_Diff > 25) {
    smoke_Alarm = true;
  } else {
    smoke_Alarm = false;
  }
}