#include <OneWire.h>
#include <DallasTemperature.h>

// Pin where the DS18B20 is connected
#define ONE_WIRE_BUS 18

// Pin for PWM output
#define PWM_PIN 13

// Setup a OneWire instance to communicate with the sensor
OneWire oneWire(ONE_WIRE_BUS);

// Pass the OneWire reference to DallasTemperature
DallasTemperature sensors(&oneWire);

// Define the temperature range (in Celsius) you want to map to PWM values (0-255)
#define TEMP_MIN -55      // Minimum temperature for PWM mapping
#define TEMP_MAX 125      // Maximum temperature for PWM mapping

void setup() {
  // Start the serial communication
  Serial.begin(115200);
  
  // Start the temperature sensor library
  sensors.begin();
  
  // Set PWM_PIN as output
  pinMode(PWM_PIN, OUTPUT);

  #if defined(ESP32)
    // Set up the PWM with a frequency of 5000 Hz, resolution of 8 bits (0-255 range), on channel 0
    ledcSetup(0, 5000, 8); // Channel 0, 5000 Hz, 8-bit resolution
    ledcAttachPin(PWM_PIN, 0); // Attach PWM to pin 13 using channel 0
  #endif
  
  // Print a startup message
  Serial.println("DS18B20 Temperature Sensor with Custom PWM Range");
}

void loop() {
  // Request temperature reading from the sensor
  sensors.requestTemperatures();
  
  // Get the temperature in Celsius
  float tempC = sensors.getTempCByIndex(0);
  
  // Check if the temperature was successfully read
  if (tempC != DEVICE_DISCONNECTED_C) {
    // Print the temperature to the Serial Monitor
    Serial.print("Temperature: ");
    Serial.print(tempC);
    Serial.println(" °C");
    
    // Map the temperature to the PWM range (0-255)
    int pwmValue = map(tempC, TEMP_MIN, TEMP_MAX, 0, 255);

    // Ensure the PWM value is within the valid range
    pwmValue = constrain(pwmValue, 0, 255);
    
    // Output PWM signal on the PWM_PIN
    ledcWrite(0, pwmValue); // Write PWM value to channel 0 on pin 13
    
    // Print the PWM value for debugging
    Serial.print("PWM Value: ");
    Serial.println(pwmValue);
  } else {
    // If there's an error, print a message
    Serial.println("Error: Could not read temperature!");
    
    // Ensure the PWM signal is set to 0 in case of error
    ledcWrite(0, 0); // Set PWM value to 0 in case of error
  }

  // Wait for 1 second before reading again
  delay(1000);
}
