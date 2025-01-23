#include <Arduino.h>
#include <SPI.h>
#include "ATM90E36.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

// ATM90E36 instance
ATM90E36 energyMeter;

// Define SPI pins
#define SPI_MISO_PIN 5  // Connect to the MISO pin of ATM90E36
#define SPI_MOSI_PIN 6  // Connect to the MOSI pin of ATM90E36
#define SPI_SCK_PIN 7   // Connect to the SCK pin of ATM90E36
#define SPI_CS_PIN 8    // Connect to the CS pin of ATM90E36

// Define additional control pins
#define DMA_PIN 35
#define PM1_PIN 45  // Power Mode 1 pin
#define PM0_PIN 9   // Power Mode 0 pin
#define Warnout 12
#define CF1 47
#define CF2 21
#define CF3 14
#define CF4 13

// Wi-Fi credentials
const char* ssid = "SARBS";             // Replace with your Wi-Fi SSID
const char* password = "SARBS @12345";  // Replace with your Wi-Fi password

// Server URL for data upload
const char* serverURL = "https://pranto.dataloggerbd.com/Energymeter36.php";  // Replace with your server URL

// NTP client setup
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 3600, 60000);  // Sync every 60 seconds

// Time tracking variables
unsigned long previousSendTime = 0;
const unsigned long interval = 5;  // Send data every 30 seconds

// Declare global variables for energy
double TotalenergyA = 0;

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
  pinMode(DMA_PIN, OUTPUT);
  pinMode(Warnout, INPUT);
  pinMode(CF1, INPUT);

  // Set initial states for power mode
  digitalWrite(PM1_PIN, HIGH);
  digitalWrite(PM0_PIN, HIGH);
  digitalWrite(DMA_PIN, LOW);

  // Initialize SPI
  SPI.begin(SPI_SCK_PIN, SPI_MISO_PIN, SPI_MOSI_PIN, SPI_CS_PIN);

  // Initialize the ATM90E36 energy meter
  energyMeter.begin(SPI_CS_PIN, 0x287, 0x5555, 0x66A5, 0xA1A0, 0xA1A0, 0xA1A0, 0xA1A0);

  Serial.println(energyMeter.calibrationError());


  Serial.println("ATM90E36 Initialized");

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

  // Initialize NTP client
  timeClient.begin();
  Serial.println("NTP Time Initialized");
}

void sendToServer(double voltageA, double voltageB, double voltageC,
                  double currentA, double currentB, double currentC,
                  double freq, double activePowerA, double activePowerB, double activePowerC, double activePowerT,
                  double reactivePowerA, double reactivePowerB, double reactivePowerC, double reactivePowerT,
                  double pfA, double pfB, double pfC, double pfT, double TotalenergyA, unsigned long timestamp) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverURL);

    // Set content type
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // Prepare data to send
    String httpRequestData = "voltage_a=" + String(voltageA) + "&voltage_b=" + String(voltageB) + "&voltage_c=" + String(voltageC) + "&current_a=" + String(currentA) + "&current_b=" + String(currentB) + "&current_c=" + String(currentC) + "&frequency=" + String(freq) + "&active_power_a=" + String(activePowerA) + "&active_power_b=" + String(activePowerB) + "&active_power_c=" + String(activePowerC) + "&active_power_total=" + String(activePowerT) + "&reactive_power_a=" + String(reactivePowerA) + "&reactive_power_b=" + String(reactivePowerB) + "&reactive_power_c=" + String(reactivePowerC) + "&reactive_power_total=" + String(reactivePowerT) + "&power_factor_a=" + String(pfA) + "&power_factor_b=" + String(pfB) + "&power_factor_c=" + String(pfC) + "&power_factor_total=" + String(pfT) + "&total_energyA=" + String(TotalenergyA) + "&timestamp=" + String(timestamp);

    // Log data being sent
    Serial.println("Sending data: " + httpRequestData);

    // Send HTTP POST request
    int httpResponseCode = http.POST(httpRequestData);

    // Log response
    if (httpResponseCode > 0) {
      Serial.println("Data sent successfully. Response code: " + String(httpResponseCode));
    } else {
      Serial.println("Error sending data. HTTP response code: " + String(httpResponseCode));
    }
    http.end();
  } else {
    Serial.println("Wi-Fi not connected");
  }
}

void loop() {
  timeClient.update();
  unsigned long currentTime = timeClient.getEpochTime();
  if (currentTime % interval == 0 && currentTime != previousSendTime) {
    previousSendTime = currentTime;

    double importEnergyA = energyMeter.GetImportEnergy();
    double exportEnergyA = energyMeter.GetExportEnergy();
    double netEnergyA = importEnergyA - exportEnergyA;

    if (netEnergyA > 0) {
      TotalenergyA += netEnergyA;
    }

    // Fetch energy data
    double voltageA = energyMeter.GetLineVoltageA();
    double voltageB = energyMeter.GetLineVoltageB();
    double voltageC = energyMeter.GetLineVoltageC();
    double currentA = energyMeter.GetLineCurrentA();
    double currentB = energyMeter.GetLineCurrentB();
    double currentC = energyMeter.GetLineCurrentC();
    double freq = energyMeter.GetFrequency();
    double activePowerA = energyMeter.GetActivePowerA();
    double activePowerB = energyMeter.GetActivePowerB();
    double activePowerC = energyMeter.GetActivePowerC();
    double activePowerT = energyMeter.GetTotalActivePower();
    double reactivePowerA = energyMeter.GetReactivePowerA();
    double reactivePowerB = energyMeter.GetReactivePowerB();
    double reactivePowerC = energyMeter.GetReactivePowerC();
    double reactivePowerT = energyMeter.GetTotalReactivePower();
    double apperentPowerA = energyMeter.GetApparentPowerA();
    double apperentPowerB = energyMeter.GetApparentPowerB();
    double apperentPowerC = energyMeter.GetApparentPowerC();
    double apperentPowerT = energyMeter.GetTotalApparentPower();
    double pfA = energyMeter.GetPowerFactorA();
    double pfB = energyMeter.GetPowerFactorB();
    double pfC = energyMeter.GetPowerFactorC();
    double pfT = energyMeter.GetTotalPowerFactor();

    // Send data to server along with timestamp
    sendToServer(voltageA, voltageB, voltageC, currentA, currentB, currentC, freq, activePowerA, activePowerB, activePowerC, activePowerT,
                 reactivePowerA, reactivePowerB, reactivePowerC, reactivePowerT, pfT, pfT, pfT, pfT, TotalenergyA, currentTime);

    // Log data
    Serial.println("Voltage A: " + String(voltageA, 2));
    Serial.println("Voltage B: " + String(voltageB, 2));
    Serial.println("Voltage C: " + String(voltageC, 2));
    Serial.println("Current A: " + String(currentA, 2));
    Serial.println("Current B: " + String(currentB, 2));
    Serial.println("Current C: " + String(currentC, 2));
    Serial.println("Frequency: " + String(freq));
    Serial.println("Active Power A : " + String(activePowerA, 3));
    Serial.println("Active Power B : " + String(activePowerB, 3));
    Serial.println("Active Power C : " + String(activePowerC, 3));
    Serial.println("Total Active Power : " + String(activePowerT, 3));
    Serial.println("Reactive Power A : " + String(reactivePowerA, 3));
    Serial.println("Reactive Power B : " + String(reactivePowerB, 3));
    Serial.println("Reactive Power C : " + String(reactivePowerC, 3));
    Serial.println("Total Reactive Power : " + String(reactivePowerT, 3));
    Serial.println("Apperent Power A : " + String(apperentPowerA, 3));
    Serial.println("Apperent Power B : " + String(apperentPowerB, 3));
    Serial.println("Apperent Power C : " + String(apperentPowerC, 3));
    Serial.println("Total Apperent Power : " + String(apperentPowerT, 3));
    Serial.println("Power Factor A : " + String(pfT, 3));
    Serial.println("Power Factor B : " + String(pfT, 3));
    Serial.println("Power Factor C : " + String(pfT, 3));
    Serial.println("Total Power Factor: " + String(pfT, 3));
    Serial.println("Total Active Energy: " + String(TotalenergyA, 3));
    Serial.println("Timestamp: " + String(currentTime));
  }
}
