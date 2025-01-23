#include <Arduino.h>
#include "modbus_Master.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

// Wi-Fi credentials
const char* ssid = "SARBS";  // Replace with your Wi-Fi SSID
const char* password = "SARBS @12345";  // Replace with your Wi-Fi password

// Server URL for data upload
const char* serverURL = "https://pranto.dataloggerbd.com/EnergymeterYADA1.php";  // Replace with your server URL

// NTP client setup
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 3600, 60000); // Sync every 60 seconds


unsigned long previousSendTime = 0;
const unsigned long interval = 30;
unsigned long currentTime =0;

// Function to print parsed Modbus data
void printModbusData() {
    Serial.println("---- Modbus Data ----");
    Serial.print("Voltage Phase A: "); Serial.println(VoltagePhaseA);
    Serial.print("Voltage Phase B: "); Serial.println(VoltagePhaseB);
    Serial.print("Voltage Phase C: "); Serial.println(VoltagePhaseC);

    Serial.print("Current Phase A: "); Serial.println(String(CurrentPhaseA, 3));
    Serial.print("Current Phase B: "); Serial.println(String(CurrentPhaseB, 3));
    Serial.print("Current Phase C: "); Serial.println(String(CurrentPhaseC, 3));

    Serial.print("Frequency: "); Serial.println(Frequency);

    Serial.print("Active Power A: "); Serial.println(String(ActivePowerA, 3));
    Serial.print("Active Power B: "); Serial.println(String(ActivePowerB, 3));
    Serial.print("Active Power C: "); Serial.println(String(ActivePowerC, 3));
    Serial.print("Active Power Total: "); Serial.println(String(ActivePowerT, 3));

    Serial.print("Reactive Power A: "); Serial.println(String(ReactivePowerA, 3));
    Serial.print("Reactive Power B: "); Serial.println(String(ReactivePowerB, 3));
    Serial.print("Reactive Power C: "); Serial.println(String(ReactivePowerC, 3));
    Serial.print("Reactive Power Total: "); Serial.println(String(ReactivePowerT, 3));

    Serial.print("Power Factor A: "); Serial.println(String(PFA, 3));
    Serial.print("Power Factor B: "); Serial.println(String(PFB, 3));
    Serial.print("Power Factor C: "); Serial.println(String(PFC, 3));
    Serial.print("Power Factor Total: "); Serial.println(String(PFT, 3));

    Serial.print("Total Active Energy: "); Serial.println(String(TotalActiveEnergy,3));
    Serial.print("Timestamp: "); Serial.println(currentTime);
    Serial.println("---------------------");
}

// Function to send data to the server
void sendToServer(double voltageA, double voltageB, double voltageC,
                   double currentA, double currentB, double currentC,
                   double freq, double activePowerA, double activePowerB, double activePowerC, double activePowerT,
                   double reactivePowerA, double reactivePowerB, double reactivePowerC, double reactivePowerT,
                   double pfA, double pfB, double pfC, double pfT, double TotalActiveEnergy, unsigned long timestamp) {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(serverURL);

        // Set content type
        http.addHeader("Content-Type", "application/x-www-form-urlencoded");

        // Combine data into a properly formatted string
        String httpRequestData = "voltage_a=" + String(voltageA, 2) +
                                 "&voltage_b=" + String(voltageB, 2) +
                                 "&voltage_c=" + String(voltageC, 2) +
                                 "&current_a=" + String(currentA, 2) +
                                 "&current_b=" + String(currentB, 2) +
                                 "&current_c=" + String(currentC, 2) +
                                 "&frequency=" + String(freq, 2) +
                                 "&active_power_a=" + String(activePowerA, 2) +
                                 "&active_power_b=" + String(activePowerB, 2) +
                                 "&active_power_c=" + String(activePowerC, 2) +
                                 "&active_power_total=" + String(activePowerT, 2) +
                                 "&reactive_power_a=" + String(reactivePowerA, 2) +
                                 "&reactive_power_b=" + String(reactivePowerB, 2) +
                                 "&reactive_power_c=" + String(reactivePowerC, 2) +
                                 "&reactive_power_total=" + String(reactivePowerT, 2) +
                                 "&power_factor_a=" + String(pfA, 2) +
                                 "&power_factor_b=" + String(pfB, 2) +
                                 "&power_factor_c=" + String(pfC, 2) +
                                 "&power_factor_total=" + String(pfT, 2) +
                                 "&total_energyA=" + String(TotalActiveEnergy, 2) +
                                 "&timestamp=" + String(timestamp);  // Add timestamp to the data

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

void setup() {
    Serial.begin(115200); // Initialize Serial Monitor for debugging
    master_Init();        // Initialize the Modbus Master

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

void loop() {
  timeClient.update();
  currentTime = timeClient.getEpochTime();  // Get the current time from NTP server


    if (currentTime % interval == 0 && currentTime != previousSendTime) {
        previousSendTime = currentTime;
        int result = request_from_slave();
        if (result == 0) {
            sendToServer(VoltagePhaseA, VoltagePhaseB, VoltagePhaseC, CurrentPhaseA, CurrentPhaseB, CurrentPhaseC, Frequency,
                         ActivePowerA, ActivePowerB, ActivePowerC, ActivePowerT,
                         ReactivePowerA, ReactivePowerB, ReactivePowerC, ReactivePowerT,
                         PFA, PFB, PFC, PFT, TotalActiveEnergy, currentTime);  // Pass timestamp to sendToServer
            printModbusData();
        } else {
            Serial.print("Error reading Modbus registers. Error code: ");
            Serial.println(result);
        }
    }
}

