#include "module1.h"
#include <Arduino.h>

// Function to get temperature from a specific GPIO pin
float Returntemp(int gpioPin) {
    // Set up OneWire and DallasTemperature for the specific GPIO pin
    OneWire oneWire(gpioPin);
    DallasTemperature sensors(&oneWire);

    sensors.begin();  // Initialize the sensor

    // Request temperature measurement
    sensors.requestTemperatures();
    float temperatureC = sensors.getTempCByIndex(0); // Get the temperature from the first sensor

    if (temperatureC == DEVICE_DISCONNECTED_C) {
        Serial.println("Error: Could not read temperature data");
        return NAN; // Return Not-a-Number to indicate an error
    }

    return temperatureC;
}