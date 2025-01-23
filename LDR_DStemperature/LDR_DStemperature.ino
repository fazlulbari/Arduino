#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h> 

// Pin Definitions
#define LDR_PIN 36
#define DS18B20_PIN 18
#define LIGHT_PIN 15
#define FAN_PIN 19

// Thresholds
const int ldrThreshold = 1000; // Adjust based on LDR calibration
const float tempThreshold = 28.0; // Temperature threshold in °C

// DS18B20 Setup
OneWire oneWire(DS18B20_PIN);
DallasTemperature sensors(&oneWire);

// Setup LCD (Assuming address 0x27 for 16x2 LCD)
LiquidCrystal_I2C lcd(0x27, 16, 2);


void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  // Pin Modes
  pinMode(LIGHT_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);
  pinMode(LDR_PIN, INPUT);

  // Initialize DS18B20
  sensors.begin();

  lcd.init();          // initialize the lcd 
  lcd.backlight();     // Turn on the backlight

}

void loop() {
  // Read LDR Value
  int ldrValue = analogRead(LDR_PIN);
  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

  // Read Temperature
  sensors.requestTemperatures();
  float temperature = sensors.getTempCByIndex(0);
  Serial.print("Temperature: ");
  Serial.println(temperature);
   Serial.print("C");

  // Display on LCD
  lcd.clear();
  lcd.setCursor(2, 0);  // Set cursor to first line
  lcd.print("Light= ");
  lcd.print(ldrValue);  // Print LDR value
  lcd.setCursor(2, 1);  // Set cursor to second line
  lcd.print("Temp= ");
  lcd.print(temperature, 1);  // Print temperature with 1 decimal place

  // Control Light
  if (ldrValue < ldrThreshold) {
    digitalWrite(LIGHT_PIN, HIGH); // Turn on Light
  } else {
    digitalWrite(LIGHT_PIN, LOW); // Turn off Light
  }

  // Control Fan
  if (temperature > tempThreshold) {
    digitalWrite(FAN_PIN, HIGH); // Turn on Fan
  } else {
    digitalWrite(FAN_PIN, LOW); // Turn off Fan
  }

  // Wait a bit before next loop
  delay(500);
}



