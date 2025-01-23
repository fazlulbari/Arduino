#include <SPI.h>
#include <max6675.h>

// Define SPI pins
#define SCK   18   // Serial Clock
#define MISO  19   // Master In Slave Out
#define CS_PIN 32  // Chip Select

// Create MAX6675 object
MAX6675 thermocouple(SCK, CS_PIN, MISO);

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  delay(500);
  Serial.println("MAX6675 Thermocouple Test");

  // Optional: Ensure the SPI pins are initialized correctly
  pinMode(SCK, OUTPUT);
  pinMode(MISO, INPUT);
  pinMode(CS_PIN, OUTPUT);
}

void loop() {
  // Read temperature from the MAX6675 sensor
  double temperature = thermocouple.readCelsius();

  if (temperature != NAN) {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");
  } else {
    Serial.println("Error reading temperature!");
  }

  // Wait 1 second before the next reading
  delay(1000);
}
