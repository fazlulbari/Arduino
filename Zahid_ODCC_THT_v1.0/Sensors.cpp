#include "Sensors.h"


Sensors::Sensors() {}

void Sensors::begin() {
    
    setupPins();
}

void Sensors::setupPins() {
    pinMode(Door_Sensor, INPUT_PULLUP);
    pinMode(Water_Sensor, INPUT_PULLUP);
    pinMode(Smoke_Sensor, INPUT_PULLUP);
}

bool Sensors::isDoorOpen() {
    return digitalRead(Door_Sensor) == LOW;
}

bool Sensors::isWaterPresent() {
    return digitalRead(Water_Sensor) == LOW;
}

bool Sensors::isSmokeDetected() {
    return digitalRead(Smoke_Sensor) == LOW;
}

float Sensors::readTemperature() {
    // Request temperature measurement
    OneWire oneWire(Temp_Sensor);
    DallasTemperature sensors(&oneWire);
    sensors.begin();  // Initialize the temperature sensor
    sensors.requestTemperatures();
    float temperatureC = sensors.getTempCByIndex(0); // Get the temperature from 
    // Placeholder for actual temperature sensor reading
    return temperatureC; // Example value
}

float Sensors::voltageSence(){
    analogReadResolution(12);
    // Read ADC value from the input pin
    int adcValue = analogRead(VOLTAGE_ADC_PIN);
    float voltage = (adcValue * 3.3* 100) / 4095.0; // 12-bit ADC resolution (0-4095)
    return voltage; // Example value
}

float Sensors::CurrentSence1(){
    analogReadResolution(12);
    // Read ADC value from the input pin
    int adcValue = analogRead(FAN1_SHUNT_PIN);
    float current = (adcValue * 3.3* 100) / 4095.0; // 12-bit ADC resolution (0-4095)
    return current; // Example value
}

float Sensors::CurrentSence2(){
    analogReadResolution(12);
    // Read ADC value from the input pin
    int adcValue = analogRead(FAN2_SHUNT_PIN);
    float current = (adcValue * 3.3* 100) / 4095.0; // 12-bit ADC resolution (0-4095)
    return current; // Example value
}

