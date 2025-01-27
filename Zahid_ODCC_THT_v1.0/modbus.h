#ifndef MODBUS_H
#define MODBUS_H

#include <ModbusRTUSlave.h>
#include <Arduino.h>
#include "ODCC_config.h"

// Function declarations
void modbus_init();
void modbus_loop();

#endif  // MODBUS_H

