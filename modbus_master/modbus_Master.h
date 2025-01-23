#ifndef MODBUS_MASTER_H
#define MODBUS_MASTER_H

#include <ModbusRTUMaster.h>

void master_Init();
void request_from_slave();

#endif // MODBUS_MASTER_H