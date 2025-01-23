
#include "environment_Sensor.h"

ClosedCube_HDC1080 hdc1080;

void environment_SensorInit() {
  hdc1080.begin(0x40);
  Serial.print("Manufacturer ID=0x");
  Serial.println(hdc1080.readManufacturerId(), HEX);  // 0x5449 ID of Texas Instruments
  Serial.print("Device ID=0x");
  Serial.println(hdc1080.readDeviceId(), HEX);  // 0x1050 ID of the device
}

void get_EnvironmentData() {
  hdc1080.setResolution(HDC1080_RESOLUTION_14BIT, HDC1080_RESOLUTION_14BIT);
  env_Temp = hdc1080.readTemperature();
  env_Hum = hdc1080.readHumidity();

  Serial.println("Env Temp: " + String(env_Temp) + " Hum: " + String(env_Hum));
}