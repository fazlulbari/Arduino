#include "config.h"
#include "blueSerial.h"
#include "gpio_Extender.h"
#include "environment_Sensor.h"
#include "fan_Controller.h"
#include "aviationLight_Controller.h"
#include "cabinetLight_Controller.h"
#include "water_Sensor.h"
#include "smoke_Sensor.h"
#include "alarm_Out.h"
#include "display_Controller.h"

void setup() {
  blue_SerialInit();
  i2cBus_Begin();
  extender_begin();
  environment_SensorInit();

  fan_Init();
  fanAdc_Init();

  lightSensor_Init();
  aviationLight_Init();

  doorSensor_Init();
  cabinetLight_Init();

  display_Init();
}

void loop() {
  get_EnvironmentData();
  fanController_Loop();
  fanConsumption();
  aviationController_Loop();
  cabinetLight_Control();

  waterSensor_Loop();

  smokeSensor_Loop();

  // dryAlarmOut_Loop();
  displayController_Loop();
}
