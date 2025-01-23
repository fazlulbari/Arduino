
#include "water_Sensor.h"

void waterSensor_Loop() {
  bool water_Sensor= get_WaterSensorValue();
  if(water_Sensor){
    water_Alarm = false;
  }
  else{
    water_Alarm = true;
  }
  Serial.println("Water Detected " + String(water_Alarm));
}