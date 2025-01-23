#include <Arduino.h>
#include <SPI.h>
#include "ATM90E36.h"

// ATM90E36 instance
ATM90E36 energyMeter;

// Define SPI pins
#define SPI_MISO_PIN 9  // Connect to the MISO pin of ATM90E36
#define SPI_MOSI_PIN 3  // Connect to the MOSI pin of ATM90E36
#define SPI_SCK_PIN 10   // Connect to the SCK pin of ATM90E36
#define SPI_CS_PIN 11     // Connect to the CS pin of ATM90E36

// Define additional control pins
#define DMA_PIN 12       // DMA control pin
#define PM1_PIN 13       // Power Mode 1 pin
#define PM0_PIN 14       // Power Mode 0 pin

void setup() {
    Serial.begin(115200);

    // Configure SPI pins
    pinMode(SPI_MISO_PIN, INPUT);
    pinMode(SPI_MOSI_PIN, OUTPUT);
    pinMode(SPI_SCK_PIN, OUTPUT);
    pinMode(SPI_CS_PIN, OUTPUT);

    // Configure control pins
    pinMode(DMA_PIN, OUTPUT);
    pinMode(PM1_PIN, OUTPUT);
    pinMode(PM0_PIN, OUTPUT);

    // Set initial states
    digitalWrite(DMA_PIN, LOW);   // Set DMA_PIN to LOW
    digitalWrite(PM1_PIN, HIGH); // Set PM1_PIN to HIGH
    digitalWrite(PM0_PIN, HIGH); // Set PM0_PIN to HIGH

    // Initialize SPI
    SPI.begin(SPI_SCK_PIN, SPI_MISO_PIN, SPI_MOSI_PIN, SPI_CS_PIN);

    // Initialize the ATM90E36 energy meter
    unsigned short lineFreq = 50; // Line frequency (50Hz or 60Hz)
    unsigned short pgagain = 0x0; // PGA gain configuration
    unsigned short ugain = 0xCDA0; // Voltage gain
    unsigned short igainA = 0x7530; // Current gain for phase A
    unsigned short igainB = 0x7530; // Current gain for phase B
    unsigned short igainC = 0x7530; // Current gain for phase C
    unsigned short igainN = 0x7530; // Current gain for neutral

    energyMeter.begin(SPI_CS_PIN, lineFreq, pgagain, ugain, igainA, igainB, igainC, igainN);

    Serial.println("ATM90E36 Initialized");
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
    double frequency= energyMeter.GetFrequency();
    double PowerFactorA = energyMeter.GetPowerFactorA();
		double PowerFactorB = energyMeter.GetPowerFactorB();
		double PowerFactorC = energyMeter.GetPowerFactorC();
    double ActivePowerA = energyMeter.GetActivePowerA();
		double ActivePowerB = energyMeter.GetActivePowerB();
		double ActivePowerC = energyMeter.GetActivePowerC();
		double ActivePowerT = energyMeter.GetTotalActivePower();
		double ImportEnergy = energyMeter.GetImportEnergy();
		double ExportEnergy = energyMeter.GetExportEnergy();

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

    Serial.print("Power FactorA: ");
    Serial.println(PowerFactorA);

    Serial.print("Power FactorB: ");
    Serial.println(PowerFactorB);

    Serial.print("Power FactorC: ");
    Serial.println(PowerFactorC);

    Serial.print("ImportEnergy: ");
    Serial.print(ImportEnergy);
    Serial.println(" kWh");

    Serial.print("ExportEnergy: ");
    Serial.print(ExportEnergy);
    Serial.println(" kWh");

    Serial.print("ActivePowerA: ");
    Serial.print(ActivePowerA);
    Serial.println(" kW");

    Serial.print("ActivePowerB: ");
    Serial.print(ActivePowerB);
    Serial.println(" kW");

    Serial.print("ActivePowerC: ");
    Serial.print(ActivePowerC);
    Serial.println(" kW");

    Serial.print("ActivePowerT: ");
    Serial.print(ActivePowerT);
    Serial.println(" kW");

    delay(1000); // Delay for readability
}
