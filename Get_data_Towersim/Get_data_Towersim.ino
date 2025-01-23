#include "modbus_Master.h"
#include "MQTT.h"


void setup() {
  Serial.begin(115200);
  master_Init();  // Initialize Modbus
  powerOnSIM800L();
  initializeGPRS();
  initializeMQTT();
}

void loop() {
  static unsigned long lastPublish = 0;

    // Periodically publish data to MQTT
    if (millis() - lastPublish >= 10000) { // Every 10 seconds
      String modbusData = request_from_slave();
      publishModbusData(modbusData);  // Passing modbusData as argument
      lastPublish = millis();
    }

  void mqttLoop();
  // mqttClient.loop(); // Process MQTT messages
}