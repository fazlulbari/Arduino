#include <Wire.h>
#include <U8g2lib.h>
#include "images.h"

// Define custom pins for I2C and display control
#define SDA_PIN 12    // Custom SDA pin for ESP32-S3
#define SCL_PIN 13    // Custom SCL pin for ESP32-S3
#define RESET_PIN 42  // Display RESET pin (optional)

// Initialize the U8g2 library for SSD1306 OLED
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, 0x3C);

// Bitmap of a simple logo (128x64 pixels)

void Animateframe(const uint8_t bitmap_logo[]){
  // Clear the display buffer
  u8g2.clearBuffer();

  // Draw the bitmap at (x, y) position
  u8g2.drawBitmap(0, 0, 16, 64, bitmap_logo); // Width in bytes, Height in pixels

  // Send the buffer to the display
  u8g2.sendBuffer();

  // Pause for .1 seconds
  delay(50);
}

void setup() {
  Serial.begin(115200);
  Serial.println("Starting OLED test...");

  pinMode(RESET_PIN, OUTPUT);

  // Reset the display
  digitalWrite(RESET_PIN, HIGH);  // Hold RESET low
  delay(100);                    // Wait for 100ms
  digitalWrite(RESET_PIN, LOW); // Release RESET

  // Initialize I2C with custom SDA and SCL pins
  Wire.begin(SDA_PIN, SCL_PIN);

  // Initialize the OLED display
  if (!u8g2.begin()) {
    Serial.println("OLED initialization failed!");
    while (1); // Halt execution if initialization fails
  }
  Serial.println("OLED initialized successfully!");
}


void loop() {
    Animateframe(bitmap_logo1); // Pass the array name, which is a pointer to the data
    Animateframe(bitmap_logo2);
    Animateframe(bitmap_logo3);
    Animateframe(bitmap_logo4);
}


