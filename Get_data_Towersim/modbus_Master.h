#ifndef MODBUS_MASTER_H
#define MODBUS_MASTER_H

#include <ModbusRTUMaster.h>
#include <bitset>
#include <ArduinoJson.h>

void master_Init();
String request_from_slave();

#endif