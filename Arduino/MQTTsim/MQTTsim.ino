#define TINY_GSM_MODEM_SIM800
#include <TinyGsmClient.h>
#include <PubSubClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <ArduinoJson.h>

// SIM800L Configuration
#define SIM800L_TX_PIN 27
#define SIM800L_RX_PIN 26
#define SIM800L_BAUD_RATE 115200

// Define the pin where the data wire is connected to the ESP32 (or other Arduino board)
#define ONE_WIRE_BUS 18  // Change this to the GPIO pin you're using

HardwareSerial sim800l(1); // Use Serial1 for SIM800L

// Setup a OneWire instance
OneWire oneWire(ONE_WIRE_BUS);

// Pass the OneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

StaticJsonDocument<200> tem;
StaticJsonDocument<200> alar;
StaticJsonDocument<200> Set;
StaticJsonDocument<200> Rec;

// Control Pins
#define PWKEY 4
#define RST 5
#define PWON 23

// GPIO for controlling output
#define OUTPUT_PIN 15    // GPIO 15 for temperature control
#define RECTIFIER_PIN 19 // GPIO 19 for rectifier control

// APN Configuration
const char* apn = "gpinternet"; // Replace with your carrier's APN
const char* apnUser = "";       // APN username (if required)
const char* apnPass = "";       // APN password (if required)

// MQTT Configuration
const char* mqttServer = "broker.hivemq.com"; // HiveMQ broker
const int mqttPort = 1883; // Non-secure MQTT port
const char* mqttUser = "Fazlulbari";
const char* mqttPassword = "Hellowthere1";

// Topics
const char* publishTopic = "device/payload";  // Topic to publish temperature
const char* alarmTopic = "device/alarm";      // Topic to publish alarm or safe status
const char* subscribeTopic = "server/setting"; // Topic to subscribe for threshold settings
const char* rectifierTopic = "device/Rectifier"; // Topic to control GPIO 19 (rectifier)

// TinyGSM and MQTT Clients
TinyGsm modem(sim800l);
TinyGsmClient gsmClient(modem); // Use non-secure client
PubSubClient mqttClient(gsmClient);

// Variable to store threshold temperature
float thresholdTemp = 35.0; // Default value if no data is received from the server
unsigned long timeb = 0;

// MQTT Callback function
void mqttCallback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived on topic: ");
    Serial.println(topic);
    Serial.print("Message: ");

    // Convert the payload to a String
    String message = "";
    for (unsigned int i = 0; i < length; i++) {
        message += (char)payload[i];
    }

    Serial.println(message);
    deserializeJson(Set, message);

    // Process data from the "server/setting" topic
    if (strcmp(topic, subscribeTopic) == 0) {
        Serial.println("Received settings from the server:");
        String thresholdStr = Set["Threshold Temp"];
        thresholdTemp = thresholdStr.toFloat(); // Convert to float
        Serial.print("Updated threshold temperature: ");
        Serial.println(thresholdTemp);
        
    }
    deserializeJson(Rec, message);
    // Process commands for GPIO 19 (Rectifier)
    if (strcmp(topic, rectifierTopic) == 0) {
      String stat = Rec["Rectifier"];
        if (stat.equalsIgnoreCase("ON")) {
            digitalWrite(RECTIFIER_PIN, HIGH);
            Serial.println("Rectifier turned ON (GPIO 19 HIGH).");
        } else if (stat.equalsIgnoreCase("OFF")) {
            digitalWrite(RECTIFIER_PIN, LOW);
            Serial.println("Rectifier turned OFF (GPIO 19 LOW).");
        } else {
            Serial.println("Invalid command for Rectifier.");
        }
    }
}

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

// Initialize GPRS connection
bool initializeGPRS() {
    Serial.println("Initializing modem...");
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

// Initialize MQTT connection
void initializeMQTT() {
    mqttClient.setServer(mqttServer, mqttPort);
    mqttClient.setCallback(mqttCallback);

    while (!mqttClient.connected()) {
        Serial.println("Connecting to MQTT...");
        if (mqttClient.connect("ESP32_Client1", mqttUser, mqttPassword)) {
            Serial.println("Connected to MQTT broker");
            mqttClient.subscribe(subscribeTopic);  // Subscribe to the threshold topic
            mqttClient.subscribe(rectifierTopic); // Subscribe to the rectifier control topic
            Serial.println("Subscribed to topics: server/setting, device/Rectifier");
        } else {
            Serial.print("MQTT connection failed, rc=");
            Serial.println(mqttClient.state());
            delay(2000);
        }
    }
}

// Publish MQTT message
void publishMQTTMessage(float temperature) {
  unsigned long timea= millis();

  if((timea-timeb) >= 10000)
  {
    tem["Temperature"]= temperature; 
    if (mqttClient.connected()) {
        String payload;
        serializeJson(tem, payload);
        if (mqttClient.publish(publishTopic, payload.c_str())) {
            Serial.println("Message published to device/payload");
            timeb = millis(); 
        } else {
            Serial.println("Failed to publish message");
        }   
    }
  }
}

// Publish alarm or safe message
void publishAlarm(bool isAlarm) {
    if (mqttClient.connected()) {
        alar["Alarm"] = isAlarm ? "Temperature is above threshold value!" : "Safe to operate";
        String message;
        serializeJson(alar, message);
        if (mqttClient.publish(alarmTopic, message.c_str())) {
            Serial.print("Message published to device/alarm: ");
            Serial.println(message);
        } else {
            Serial.println("Failed to publish alarm/safe message");
        }
    }
}

// Control GPIO and trigger alarm or safe status based on temperature
void controlGPIO(float temperature) {
    static bool lastState = false; // Track last state to avoid duplicate messages

    if (temperature > thresholdTemp) {
        digitalWrite(OUTPUT_PIN, HIGH);
        if (!lastState) { // Only publish if the state changes
            publishAlarm(true);
            lastState = true;
        }
    } else {
        digitalWrite(OUTPUT_PIN, LOW);
        if (lastState) { // Only publish if the state changes
            publishAlarm(false);
            lastState = false;
        }
    }
}

void setup() {
    Serial.begin(115200);

    // Start the DallasTemperature library
    sensors.begin();

    // Set GPIO pins as outputs
    pinMode(OUTPUT_PIN, OUTPUT);
    pinMode(RECTIFIER_PIN, OUTPUT);
    digitalWrite(OUTPUT_PIN, LOW);       // Initialize GPIO 15 to LOW
    digitalWrite(RECTIFIER_PIN, LOW);    // Initialize GPIO 19 to LOW

    powerOnSIM800L();
    sim800l.begin(SIM800L_BAUD_RATE, SERIAL_8N1, SIM800L_RX_PIN, SIM800L_TX_PIN);

    if (!initializeGPRS()) {
        Serial.println("Failed to initialize GPRS");
        while (true); // Halt on error
    }

    initializeMQTT();
}

void loop() {
    mqttClient.loop(); // Process MQTT messages

    // Request temperature readings from all sensors on the bus
    sensors.requestTemperatures();

    // Get the temperature from the first sensor (index 0)
    float temperature = sensors.getTempCByIndex(0);
    // Publish the temperature
    
    publishMQTTMessage(temperature);


    // Control GPIO and check for alarms
    controlGPIO(temperature);
}