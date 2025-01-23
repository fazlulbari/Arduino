#include "modbus_Slave.h"

void setup() {
  // Start the serial communication for debugging
  Serial.begin(9600);
  slave_Init();
}

void loop() {
  modbus_Loop();

}
