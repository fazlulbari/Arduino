#include "modbus_Master.h"

void setup() {
  Serial.begin(9600); // Start serial communication for debugging
  master_Init();      // Initialize the Modbus master
}

void loop() {
  request_from_slave(); // Request data from the slave
  delay(2000);          // Add a delay between requests
}
