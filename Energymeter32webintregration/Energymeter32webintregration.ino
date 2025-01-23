#include <Arduino.h>
#include <SPI.h>
#include "ATM90E32.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

// ATM90E32 instance
ATM90E32 energyMeter;

// Define SPI pins
#define SPI_MISO_PIN 5  // Connect to the MISO pin of ATM90E32
#define SPI_MOSI_PIN 6  // Connect to the MOSI pin of ATM90E32
#define SPI_SCK_PIN 7   // Connect to the SCK pin of ATM90E32
#define SPI_CS_PIN 8    // Connect to the CS pin of ATM90E32

// Define additional control pins
#define PM1_PIN 45      // Power Mode 1 pin
#define PM0_PIN 9       // Power Mode 0 pin

// Wi-Fi credentials
const char* ssid = "SARBS";
const char* password = "SARBS @12345";

// Create a web server object on port 80
WebServer server(80);

void writeRegister(uint8_t reg, uint16_t value) {
    digitalWrite(SPI_CS_PIN, LOW);   // Pull CS low to start communication
    SPI.transfer((reg & 0x7F) | 0x80); // Register address with write bit set
    SPI.transfer16(value);           // Write the 16-bit value
    digitalWrite(SPI_CS_PIN, HIGH);  // Pull CS high to end communication
}

void resetEnergyMeter() {
    const uint16_t RESET_VALUE = 0x789A;
    const uint8_t RESET_REGISTER = 0x70;

    Serial.println("Resetting Energy Meter...");
    writeRegister(RESET_REGISTER, RESET_VALUE);
    delay(100);
    Serial.println("Energy Meter Reset Complete.");
}

void setup() {
    Serial.begin(115200);

    // Configure SPI pins
    pinMode(SPI_MISO_PIN, INPUT);
    pinMode(SPI_MOSI_PIN, OUTPUT);
    pinMode(SPI_SCK_PIN, OUTPUT);
    pinMode(SPI_CS_PIN, OUTPUT);

    // Configure control pins
    pinMode(PM1_PIN, OUTPUT);
    pinMode(PM0_PIN, OUTPUT);

    // Set initial states for power mode
    digitalWrite(PM1_PIN, HIGH); // Set PM1_PIN to HIGH
    digitalWrite(PM0_PIN, HIGH); // Set PM0_PIN to HIGH

    // Initialize SPI
    SPI.begin(SPI_SCK_PIN, SPI_MISO_PIN, SPI_MOSI_PIN, SPI_CS_PIN);

    // Initialize the ATM90E32 energy meter
    unsigned int lineFreq = 50;  // Line frequency (50Hz or 60Hz)
    unsigned int pgagain = 0x0;  // PGA gain configuration
    unsigned int ugain = 0x8000;    // Voltage gain
    unsigned int igainA = 0x8000;   // Current gain for phase A
    unsigned int igainB = 0x8000;   // Current gain for phase B
    unsigned int igainC = 0x8000;   // Current gain for phase C

    energyMeter.begin(SPI_CS_PIN, lineFreq, pgagain, ugain, igainA, igainB, igainC);

    Serial.println("ATM90E32 Initialized");

    resetEnergyMeter();

    // Connect to Wi-Fi
    Serial.print("Connecting to Wi-Fi");
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }

    Serial.println("\nConnected to Wi-Fi");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    // Define the root route
    server.on("/", []() {
        String data = "<html>\n";
        data += "<head><meta http-equiv='refresh' content='2'></head>\n"; // Auto-refresh every 2 seconds
        data += "<body>\n";
        data += "<h1>Welcome to the Energy Meter</h1>\n";
        data += "<p>Visit <a href='/data'>/data</a> for detailed energy meter data.</p>\n";
        data += "</body>\n";
        data += "</html>";
        server.send(200, "text/html", data);
    });

    // Define a route to send detailed data with auto-refresh
    server.on("/data", []() {
        String data = "<html>\n";
        data += "<head><meta http-equiv='refresh' content='1'></head>\n"; // Auto-refresh every 1 seconds
        data += "<body>\n";
        data += "<h1>Energy Meter Data</h1>\n";
        data += "<p>Voltage A: " + String(energyMeter.GetLineVoltageA()/0.65) + "V</p>\n";
        data += "<p>Voltage B: " + String(energyMeter.GetLineVoltageB()/0.65) + "V</p>\n";
        data += "<p>Voltage C: " + String(energyMeter.GetLineVoltageC()/0.65) + "V</p>\n";
        data += "<p>Current A: " + String(energyMeter.GetLineCurrentA()) + "A</p>\n";
        data += "<p>Current B: " + String(energyMeter.GetLineCurrentB()) + "A</p>\n";
        data += "<p>Current C: " + String(energyMeter.GetLineCurrentC()) + "A</p>\n";
        data += "<p>Current N: " + String(energyMeter.GetLineCurrentN()) + "A</p>\n";
        data += "<p>Phase angle A: " + String(energyMeter.GetPhaseA()) + "degree</p>\n";
        data += "<p>Phase angle B: " + String(energyMeter.GetPhaseB()) + "degree</p>\n";
        data += "<p>Phase angle C: " + String(energyMeter.GetPhaseC()) + "degree</p>\n";
        data += "<p>Frequency: " + String(energyMeter.GetFrequency()) + "Hz</p>\n";
        data += "<p>Temperature: " + String(energyMeter.GetTemperature()) + "C</p>\n";
        data += "<p>Power Factor A: " + String(energyMeter.GetPowerFactorA()) + "</p>\n";
        data += "<p>Power Factor B: " + String(energyMeter.GetPowerFactorB()) + "</p>\n";
        data += "<p>Power Factor C: " + String(energyMeter.GetPowerFactorC()) + "</p>\n";
        data += "<p>Active Power A: " + String(energyMeter.GetActivePowerA()) + "kW</p>\n";
        data += "<p>Active Power B: " + String(energyMeter.GetActivePowerB()) + "kW</p>\n";
        data += "<p>Active Power C: " + String(energyMeter.GetActivePowerC()) + "kW</p>\n";
        data += "<p>Total Active Power: " + String(energyMeter.GetTotalActivePower()) + "kW</p>\n";
        data += "<p>Import Energy: " + String(energyMeter.GetImportEnergy()) + "kWh</p>\n";
        data += "<p>Export Energy: " + String(energyMeter.GetExportEnergy()) + "kWh</p>\n";
        data += "</body>\n";
        data += "</html>";
        server.send(200, "text/html", data);
    });

    // Start the server
    server.begin();
    Serial.println("HTTP server started");
}

void loop() {
    // Handle client requests
    server.handleClient();
}



