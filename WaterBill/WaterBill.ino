#include <WiFi.h>
#include <WiFiManager.h>
#include <HTTPClient.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <NTPClient.h>

// Server URLs
const String serverUrl = "http://pranto.dataloggerbd.com/updateRechargeAmount.php";
const String serverFeedbackUrl = "http://pranto.dataloggerbd.com/updatePumpFeedback.php";

#define PUMP_GPIO 32

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 21600, 60000);

unsigned long pumpStartTime = 0;
unsigned long pumpRunTime = 0;
bool pumpIsRunning = false;
unsigned long pumpDuration = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

String getMacAddress() {
  return WiFi.macAddress();
}

void setup() {
  pinMode(PUMP_GPIO, OUTPUT);
  digitalWrite(PUMP_GPIO, LOW);

  Serial.begin(115200);

  WiFiManager wm;

  if (!wm.autoConnect("PrepaidPump_AP")) {
    Serial.println("Failed to connect, restarting...");
    ESP.restart();
  }

  Serial.println("Connected to WiFi!");
  Serial.println("MAC Address: " + getMacAddress());
  Serial.println("IP Address: " + WiFi.localIP().toString());

  timeClient.begin();
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Prepaid Pumping");
  lcd.setCursor(5, 1);
  lcd.print("System");
  delay(100);

  updateBalance(getMacAddress());
}

void loop() {
  updateBalance(getMacAddress());

  if (pumpIsRunning && pumpRunTime >= pumpDuration) {
    digitalWrite(PUMP_GPIO, LOW);
    pumpIsRunning = false;
    resetPumpDuration(getMacAddress());
  }

  int pumpState = digitalRead(PUMP_GPIO);

  if (pumpState == HIGH && !pumpIsRunning) {
    pumpStartTime = millis();
    pumpIsRunning = true;
  }

  pumpRunTime = (pumpState == HIGH) ? (millis() - pumpStartTime) / 1000 : 0;
  sendPumpFeedback(pumpState, pumpRunTime);
  displayInfo();
}

void updateBalance(String macAddress) {
  HTTPClient http;
  String url = serverUrl + "?macAddress=" + macAddress;
  http.begin(url);
  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {
    String response = http.getString();
    if (response.indexOf("Pump Duration:") != -1) {
      pumpDuration = response.substring(response.indexOf("Pump Duration:") + 14).toInt();
    }
    controlPump(response);
  }
  http.end();
}

void controlPump(String response) {
  if (response.indexOf("Pump State: ON") != -1) {
    digitalWrite(PUMP_GPIO, HIGH);
  } else if (response.indexOf("Pump State: OFF") != -1) {
    digitalWrite(PUMP_GPIO, LOW);
  }
}

void sendPumpFeedback(int pumpState, int pumpRunTime) {
  HTTPClient http;
  String url = serverFeedbackUrl + "?macAddress=" + WiFi.macAddress() +
               "&pumpState=" + (pumpState == HIGH ? "ON" : "OFF") +
               "&pumpRunTime=" + String(pumpRunTime);
  http.begin(url);
  http.GET();
  http.end();
}

void resetPumpDuration(String macAddress) {
  HTTPClient http;
  String url = "http://pranto.dataloggerbd.com/resetPumpDuration.php?macAddress=" + macAddress;
  http.begin(url);
  http.GET();
  http.end();
}

void displayInfo() {
  timeClient.update();
  String currentTime = timeClient.getFormattedTime();
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print(currentTime);
  lcd.setCursor(0, 1);
  lcd.print(String(pumpIsRunning ? "ON " : "OFF") + " Runtime:" + String(pumpRunTime) + "s");
}
