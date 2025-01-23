#include "config.h"
#include "Modbus_Slaves.h"
#include "Digital_IO.h"
#include "Analog_IO.h"
#include "System_Parameters.h"
#include "Environment_Sensor.h"

void setup() {
  Serial.begin(115200);

  digitalInputInit();
  digitalOutputInit();
  analogInputInit();
  analogOutputInit();

  system_Parameter_Init();
  environment_Sensor_Init();

  modbus_Init();
}

void loop() {

  digitalInputLoop();
  digitalOutputLoop();
  analogInputLoop();
  analogOutputLoop();

  get_System_Parameters();
  get_Environment_Data();

  // modbus_Loop();
  // modbus_Print();

  delay(100);

  delay(1000);
}
