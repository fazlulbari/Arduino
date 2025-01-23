#include "config.h"


bool is_I2C_Initialized = false;


float system_Voltage = 0;

float env_Temp = 0;
float env_Hum = 0;


void I2C_Init() {
  Wire.setPins(I2C_SDA, I2C_SCL);
  Wire.begin();
  is_I2C_Initialized = true;
}
