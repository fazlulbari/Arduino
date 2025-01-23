#include <OneWire.h>
#include <DallasTemperature.h>

// Define the pin where the data wire is connected to the ESP32 (or other Arduino board)
#define ONE_WIRE_BUS 18  // Change this to the GPIO pin you're using

// Setup a OneWire instance
OneWire oneWire(ONE_WIRE_BUS);

// Pass the OneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

void setup() {
  // Start serial communication
  Serial.begin(115200);

  // Start the DallasTemperature library
  sensors.begin();
  
  // Give some time for the serial monitor to open
  delay(2000);
}

void loop() {
  // Request temperature readings from all sensors on the bus
  sensors.requestTemperatures();

  // Print the temperature from the first sensor
  Serial.print("Temperature for sensor 1: ");
  Serial.print(sensors.getTempCByIndex(0));  // Get temperature in Celsius
  Serial.println(" °C");

  // Delay between readings
  delay(2000);  // 2 seconds delay
}