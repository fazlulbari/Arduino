#include <Arduino.h>
#include <SPI.h>
#include "ATM90E32.h"

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
    unsigned int ugain = 0x0;    // Voltage gain
    unsigned int igainA = 0x8000;   // Current gain for phase A
    unsigned int igainB = 0x8000;   // Current gain for phase B
    unsigned int igainC = 0x8000;   // Current gain for phase C

    energyMeter.begin(SPI_CS_PIN, lineFreq, pgagain, ugain, igainA, igainB, igainC);

    Serial.println("ATM90E32 Initialized");
}

void loop() {
    // Read and print voltage data
    double voltageA = energyMeter.GetLineVoltageA();
    double voltageB = energyMeter.GetLineVoltageB();
    double voltageC = energyMeter.GetLineVoltageC();

    double linecurrentA = energyMeter.GetLineCurrentA();
    double linecurrentB = energyMeter.GetLineCurrentB();
    double linecurrentC = energyMeter.GetLineCurrentC();
    double linecurrentN = energyMeter.GetLineCurrentN();

    double frequency = energyMeter.GetFrequency();
    double powerFactorA = energyMeter.GetPowerFactorA();
    double powerFactorB = energyMeter.GetPowerFactorB();
    double powerFactorC = energyMeter.GetPowerFactorC();

    double activePowerA = energyMeter.GetActivePowerA();
    double activePowerB = energyMeter.GetActivePowerB();
    double activePowerC = energyMeter.GetActivePowerC();
    double totalActivePower = energyMeter.GetTotalActivePower();

    double importEnergy = energyMeter.GetImportEnergy();
    double exportEnergy = energyMeter.GetExportEnergy();

    // Print readings
    Serial.print("Voltage A: ");
    Serial.print(voltageA);
    Serial.println(" V");

    Serial.print("Voltage B: ");
    Serial.print(voltageB);
    Serial.println(" V");

    Serial.print("Voltage C: ");
    Serial.print(voltageC);
    Serial.println(" V");

    Serial.print("Current A: ");
    Serial.print(linecurrentA);
    Serial.println(" A");

    Serial.print("Current B: ");
    Serial.print(linecurrentB);
    Serial.println(" A");

    Serial.print("Current C: ");
    Serial.print(linecurrentC);
    Serial.println(" A");

    Serial.print("Current N: ");
    Serial.print(linecurrentN);
    Serial.println(" A");

    Serial.print("Frequency: ");
    Serial.print(frequency);
    Serial.println(" Hz");

    Serial.print("Power Factor A: ");
    Serial.println(powerFactorA);

    Serial.print("Power Factor B: ");
    Serial.println(powerFactorB);

    Serial.print("Power Factor C: ");
    Serial.println(powerFactorC);

    Serial.print("Active Power A: ");
    Serial.print(activePowerA);
    Serial.println(" kW");

    Serial.print("Active Power B: ");
    Serial.print(activePowerB);
    Serial.println(" kW");

    Serial.print("Active Power C: ");
    Serial.print(activePowerC);
    Serial.println(" kW");

    Serial.print("Total Active Power: ");
    Serial.print(totalActivePower);
    Serial.println(" kW");

    Serial.print("Import Energy: ");
    Serial.print(importEnergy);
    Serial.println(" kWh");

    Serial.print("Export Energy: ");
    Serial.print(exportEnergy);
    Serial.println(" kWh");

    delay(1000); // Delay for readability
}
