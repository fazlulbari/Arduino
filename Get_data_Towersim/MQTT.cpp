#define TINY_GSM_MODEM_SIM800  // Define the GSM modem model
#include <TinyGsmClient.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

// Control Pins
#define PWKEY 4
#define RST 5
#define PWON 23

// SIM800L configuration
#define SIM800L_TX_PIN 27
#define SIM800L_RX_PIN 26
#define SIM800L_BAUD_RATE 115200
HardwareSerial sim800l(1);  // Use Serial1 for SIM800L

// MQTT configuration
const char* mqttServer = "broker.hivemq.com";
const int mqttPort = 1883;
const char* mqttUser = "Fazlulbari";
const char* mqttPassword = "Hellowthere1";
const char* publishTopic = "device/payload";

// APN Configuration
const char* apn = "gpinternet";  // Replace with your carrier's APN
const char* apnUser = "";        // APN username (if required)
const char* apnPass = "";        // APN password (if required)

// Declare TinyGsm modem and client
TinyGsm modem(sim800l);
TinyGsmClient gsmClient(modem);
PubSubClient mqttClient(gsmClient);  // Declare globally

// Power on SIM800L
void powerOnSIM800L() {
  pinMode(PWKEY, OUTPUT);
  pinMode(RST, OUTPUT);
  pinMode(PWON, OUTPUT);
  digitalWrite(PWKEY, LOW);
  digitalWrite(RST, HIGH);
  digitalWrite(PWON, HIGH);
  Serial.println("SIM800L powered on");
}

// Initialize GPRS
bool initializeGPRS() {
  Serial.println("Initializing modem...");
  sim800l.begin(SIM800L_BAUD_RATE, SERIAL_8N1, SIM800L_RX_PIN, SIM800L_TX_PIN);
  if (!modem.restart()) {
    Serial.println("Failed to restart modem");
    return false;
  }
  Serial.println("Modem restarted");

  int signalStrength = modem.getSignalQuality();
  Serial.print("Network Signal Strength: ");
  if (signalStrength == -1) {
    Serial.println("Error: Unable to get signal strength.");
  } else {
    Serial.print(signalStrength);
    Serial.println(" dBm");
  }

  Serial.println("Setting up GPRS...");
  if (!modem.gprsConnect(apn, apnUser, apnPass)) {
    Serial.println("Failed to connect to GPRS");
    return false;
  }

  Serial.println("Checking GPRS connection...");
  if (!modem.isGprsConnected()) {
    Serial.println("GPRS is not connected!");
    return false;
  }

  Serial.println("GPRS connected");
  return true;
}

// Initialize MQTT
void initializeMQTT() {
  mqttClient.setServer(mqttServer, mqttPort);
  mqttClient.setBufferSize(4096);
  while (!mqttClient.connected()) {
    if (mqttClient.connect("ESP32_Client", mqttUser, mqttPassword)) {
      Serial.println("Connected to MQTT broker");
    } else {
      Serial.println("Failed to connect to MQTT. Retrying...");
      delay(2000);
    }
  }
}

// Publish Modbus data to MQTT
void publishModbusData(String modbusData) {
  if (mqttClient.publish(publishTopic, modbusData.c_str())) {
    Serial.println("Published Modbus data to MQTT");
  } else {
    Serial.println("Failed to publish Modbus data");
  }
}

void mqttLoop() {
  mqttClient.loop();  // Process MQTT messages
}