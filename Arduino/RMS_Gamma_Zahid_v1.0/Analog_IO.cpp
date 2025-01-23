#include "Analog_IO.h"


#include <ADS7828.h>

bool is_ANALOG_IN_IC_Initialized = false;
bool is_ANALOG_OUT_IC_Initialized = false;

ADS7828 adc;

void analog_In_IC_Init() {
  if (!is_I2C_Initialized) I2C_Init();
  adc.begin(ANALOG_IN_IC_ADDR);
  is_ANALOG_IN_IC_Initialized = true;
}

void analog_Out_IC_Init() {
  if (!is_I2C_Initialized) I2C_Init();
  adc.begin(ANALOG_OUT_IC_ADDR);
  is_ANALOG_OUT_IC_Initialized = true;
}

void analogInputInit() {
  if (!is_ANALOG_IN_IC_Initialized) analog_In_IC_Init();
}

void analogOutputInit() {
  if (!is_ANALOG_OUT_IC_Initialized) analog_Out_IC_Init();
}



void analogInputLoop() {
  //
}

void analogOutputLoop() {
  //
}