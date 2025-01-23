#include <Arduino.h>
#include <SPI.h>
#include "ATM90E36.h"
#include <ModbusRTUSlave.h>
#include <FS.h>
#include <SPIFFS.h>

// ATM90E36 instance
ATM90E36 energyMeter;

// ModbusRTUSlave instance
HardwareSerial mySerial(1);
ModbusRTUSlave modbus(mySerial);

// Declare global variables for energy
uint64_t TotalenergyA = 0;

// Define SPI pins
#define SPI_MISO_PIN 5
#define SPI_MOSI_PIN 6
#define SPI_SCK_PIN 7
#define SPI_CS_PIN 8

// RS485 control pins
#define RS485_TX_PIN 17
#define RS485_RX_PIN 18

// Define additional control pins
#define DMA_PIN 35
#define PM1_PIN 45
#define PM0_PIN 9
#define Warnout 12
#define CF1 47
#define CF2 21
#define CF3 14
#define CF4 13

// SPIFFS file path
#define ENERGY_FILE "/energy.dat"

// Time tracking variables
unsigned long previousSendTime = 0;
const unsigned long interval = 5;

// Global energy variables
uint16_t holdingRegisters[0x1200];

void loadTotalEnergy() {
  if (SPIFFS.exists(ENERGY_FILE)) {
    File file = SPIFFS.open(ENERGY_FILE, FILE_READ);
    if (file) {
      file.readBytes((char*)&TotalenergyA, sizeof(TotalenergyA));
      file.close();
      Serial.println("TotalenergyA loaded from SPIFFS");
    }
  }
}

void saveTotalEnergy() {
  File file = SPIFFS.open(ENERGY_FILE, FILE_WRITE);
  if (file) {
    file.write((uint8_t*)&TotalenergyA, sizeof(TotalenergyA));
    file.close();
    Serial.println("TotalenergyA saved to SPIFFS");
  }
}

void setup() {
  Serial.begin(115200);

  // Initialize SPIFFS
  if (!SPIFFS.begin(true)) {
    Serial.println("SPIFFS Mount Failed");
    return;
  }
  loadTotalEnergy();

  // Configure SPI pins
  pinMode(SPI_MISO_PIN, INPUT);
  pinMode(SPI_MOSI_PIN, OUTPUT);
  pinMode(SPI_SCK_PIN, OUTPUT);
  pinMode(SPI_CS_PIN, OUTPUT);

  // Configure control pins
  pinMode(PM1_PIN, OUTPUT);
  pinMode(PM0_PIN, OUTPUT);
  pinMode(DMA_PIN, OUTPUT);
  pinMode(Warnout, INPUT);
  pinMode(CF1, INPUT);

  // Set initial states for power mode
  digitalWrite(PM1_PIN, HIGH);
  digitalWrite(PM0_PIN, HIGH);
  digitalWrite(DMA_PIN, LOW);

  modbus.configureHoldingRegisters(holdingRegisters, 0x1200);

  // Initialize RS485
  mySerial.begin(9600, SERIAL_8N1, RS485_RX_PIN, RS485_TX_PIN);
  modbus.begin(23, 9600, SERIAL_8N1);

  // Initialize SPI
  SPI.begin(SPI_SCK_PIN, SPI_MISO_PIN, SPI_MOSI_PIN, SPI_CS_PIN);

  // Initialize ATM90E36
  energyMeter.begin(SPI_CS_PIN, 0x287, 0x5555, 0x66A5, 0xA1A0, 0xA1A0, 0xA1A0, 0xA1A0);
  Serial.println(energyMeter.calibrationError());
  Serial.println("ATM90E36 Initialized");
}

void writeUint32ToModbus(uint32_t index, uint32_t value) {
  holdingRegisters[index] = (value >> 16) & 0xFFFF;  // High 16 bits
  holdingRegisters[index + 1] = value & 0xFFFF;      // Low 16 bits
}

void updateModbusData() {
  uint32_t importEnergyA = energyMeter.GetImportEnergy();
  uint32_t exportEnergyA = energyMeter.GetExportEnergy();
  uint32_t netEnergyA = importEnergyA - exportEnergyA;

  if (netEnergyA >= 0) {
    TotalenergyA += netEnergyA;
    saveTotalEnergy();
    writeUint32ToModbus(0x1000, (uint32_t)(TotalenergyA) / 3200);
    Serial.println(TotalenergyA);
  }

  writeUint32ToModbus(0x1090, (uint32_t)(energyMeter.GetLineVoltageA() / 0.0001));
  writeUint32ToModbus(0x1092, (uint32_t)(energyMeter.GetLineVoltageB() / 0.0001));
  writeUint32ToModbus(0x1094, (uint32_t)(energyMeter.GetLineVoltageC() / 0.0001));
  writeUint32ToModbus(0x10c0, (uint32_t)(energyMeter.GetLineCurrentA() / 0.0001));
  writeUint32ToModbus(0x10c2, (uint32_t)(energyMeter.GetLineCurrentB() / 0.0001));
  writeUint32ToModbus(0x10c4, (uint32_t)(energyMeter.GetLineCurrentC() / 0.0001));
  holdingRegisters[0x11b0] = (uint16_t)(energyMeter.GetFrequency() / 0.01);
  writeUint32ToModbus(14, (uint32_t)(energyMeter.GetActivePowerA()));
  writeUint32ToModbus(16, (uint32_t)(energyMeter.GetActivePowerB()));
  writeUint32ToModbus(18, (uint32_t)(energyMeter.GetActivePowerC()));
  writeUint32ToModbus(0x1100, (uint32_t)(energyMeter.GetTotalActivePower()));
  writeUint32ToModbus(22, (uint32_t)(energyMeter.GetReactivePowerA()));
  writeUint32ToModbus(24, (uint32_t)(energyMeter.GetReactivePowerB()));
  writeUint32ToModbus(26, (uint32_t)(energyMeter.GetReactivePowerC()));
  writeUint32ToModbus(28, (uint32_t)(energyMeter.GetTotalReactivePower()));
  writeUint32ToModbus(30, (uint32_t)(energyMeter.GetApparentPowerA()));
  writeUint32ToModbus(32, (uint32_t)(energyMeter.GetApparentPowerB()));
  writeUint32ToModbus(34, (uint32_t)(energyMeter.GetApparentPowerC()));
  writeUint32ToModbus(36, (uint32_t)(energyMeter.GetTotalApparentPower()));
  writeUint32ToModbus(38, (uint32_t)(energyMeter.GetPowerFactorA()));
  writeUint32ToModbus(40, (uint32_t)(energyMeter.GetPowerFactorB()));
  writeUint32ToModbus(42, (uint32_t)(energyMeter.GetPowerFactorC()));
  holdingRegisters[0x1190] = (uint16_t)(energyMeter.GetTotalPowerFactor() / 0.001);
}


void loop() {
  unsigned long currentTime = millis() / 1000;
  if (currentTime % interval == 0 && currentTime != previousSendTime) {
    previousSendTime = currentTime;
    updateModbusData();
  }
  modbus.poll();
}

