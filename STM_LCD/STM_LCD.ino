// Include the LiquidCrystal library
#include <LiquidCrystal.h>

// Define pins for the LCD
#define RS A0 // Register Select pin connected to PA0
#define EN A1 // Enable pin connected to PA1
#define D4 A2 // Data pin 4 connected to PA2
#define D5 A3 // Data pin 5 connected to PA3
#define D6 A4 // Data pin 6 connected to PA4
#define D7 A5 // Data pin 7 connected to PA5

// Initialize the library with the numbers of the interface pins
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

void setup() {
  // Set up the LCD's number of columns and rows
  lcd.begin(16, 2); // 16 columns and 2 rows

  // Print a message to the LCD
  lcd.print("Hello, STM32!");
}

void loop() {
  // Move the cursor to the second row, first column
  lcd.setCursor(0, 1);

  // Print a scrolling counter on the second row
  static int counter = 0;
  lcd.print("Count: ");
  lcd.print(counter);
  counter++;

  // Delay for visibility
  delay(1000);
  
  // Clear the second row after a few iterations
  if (counter % 10 == 0) {
    lcd.setCursor(0, 1);
    lcd.print("                "); // Clear the second row
  }
}
