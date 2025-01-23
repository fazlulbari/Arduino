#include "Digital_IO.h"

#include <mcp23017.h>

bool is_Extender_1_Initialized = false;
bool is_Extender_2_Initialized = false;

MCP23017 Extender_1(EXTENDER_1_ADDR);
MCP23017 Extender_2(EXTENDER_2_ADDR);

void extender1Init() {
  if (!is_I2C_Initialized) I2C_Init();
  Extender_1.start();
  is_Extender_1_Initialized = true;
}

void digitalInputInit() {
  if (!is_Extender_1_Initialized) extender1Init();
  for (uint8_t i = 8; i < 16; i++) {
    Extender_1.pinMode(i, INPUT);  // + 8 for PortB (8 - 15)
  }
}

void digitalOutputInit() {
  if (!is_Extender_1_Initialized) extender1Init();
  for (uint8_t i = 0; i < 8; i++) {
    Extender_1.pinMode(i, OUTPUT);  // PortA (0 - 7)
  }
}

void digitalInputLoop() {
  for (uint8_t i = 15; i > 7; i--) {
    bool val = Extender_1.digitalRead(i);  // + 8 for PortB (8 - 15)
    Serial.print(String(val));
    Serial.print("   ");
  }
  Serial.println("");
}

void digitalOutputLoop() {
  //
}