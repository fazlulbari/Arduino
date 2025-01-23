// Include the LiquidCrystal library
#include <LiquidCrystal.h>

// Define the pins used for the LCD
#define RS PB2  // Register Select pin
#define EN PA12  // Enable pin
#define D4 PB15  // Data pin 4
#define D5 PB14  // Data pin 5
#define D6 PB13  // Data pin 6
#define D7 PB12  // Data pin 7

#define BRIGHTNESS_PIN PB0  // PWM pin for controlling brightness
#define CONTRAST_PIN PB1    // PWM pin for controlling contrast

// Initialize the library with the numbers of the interface pins
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

void setup() {
  // Set up the LCD's number of columns and rows
  lcd.begin(16, 2);

  // Add a small delay to ensure LCD initialization
  delay(200);

  // Set up PWM pins
  pinMode(BRIGHTNESS_PIN, OUTPUT);
  pinMode(CONTRAST_PIN, OUTPUT);

  // Initialize brightness and contrast
  analogWrite(BRIGHTNESS_PIN, 128); // Set brightness to 50%
  analogWrite(CONTRAST_PIN, 100);    // Increase contrast to 50%

  // Print a message to the LCD
  lcd.print("Hello, STM32!");

  // Move the cursor to the second row
  lcd.setCursor(0, 1);
  lcd.print("1602A Display");
  delay(3000);  // Wait for 3 seconds

  // Clear only the second row
  lcd.setCursor(0, 1);  // Move cursor to the second row
  lcd.print("                ");  // Write 16 spaces to clear the second row
}

void loop() {
  // Optional: Add animations or dynamic updates
  lcd.setCursor(0, 1);  // Move cursor to the second row
  lcd.print("Time: ");
  lcd.print(millis() / 1000); // Display uptime in seconds
  delay(500);
}

