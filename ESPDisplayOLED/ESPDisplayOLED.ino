#include <Wire.h>
#include <U8g2lib.h>
#include "images.h"

// Define custom pins for I2C and display control
#define SDA_PIN 12    // Custom SDA pin for ESP32-S3
#define SCL_PIN 13    // Custom SCL pin for ESP32-S3
#define RESET_PIN 42  // Display RESET pin (optional)

#include <Wire.h>

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(10);
  }
  Serial.println("\nI2C Scanner");

  Wire.begin(12,13);
}

void loop() {
  byte error, address;
  int nDevices = 0;

  Serial.println("\nScanning...");

  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println(" !");

      nDevices++;
    } else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  delay(5000);
}



