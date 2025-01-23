#ifndef MQTT_H
#define MQTT_H

#include <Arduino.h>

bool initializeGPRS();
void initializeMQTT();
void publishModbusData(String modbusData);  // Updated to accept the modbusData argument
void powerOnSIM800L();
void mqttLoop();

#endif // MQTT_H