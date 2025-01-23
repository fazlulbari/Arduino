#include "Environment_Sensor.h"

#include "ClosedCube_HDC1080.h"

ClosedCube_HDC1080 Env_Sensor;

void environment_Sensor_Init() {
  if (!is_I2C_Initialized) I2C_Init();
  Env_Sensor.begin(0x40);
  // Serial.print("Environment Sensor Manufacturer ID = 0x");
  Serial.println(Env_Sensor.readManufacturerId(), HEX);  // 0x5449 ID of Texas Instruments
  // Serial.print("Environment Sensor Device ID = 0x");
  Serial.println(Env_Sensor.readDeviceId(), HEX);  // 0x1050 ID of the device
}

void get_Environment_Data() {
  Env_Sensor.setResolution(HDC1080_RESOLUTION_14BIT, HDC1080_RESOLUTION_14BIT);
  env_Temp = Env_Sensor.readTemperature();
  env_Hum = Env_Sensor.readHumidity();

  Serial.println("Env Temp: " + String(env_Temp) + " Hum: " + String(env_Hum));
}