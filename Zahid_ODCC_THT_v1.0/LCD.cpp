#include "LCD.h"

LCD::LCD() : lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7) {}

void LCD::begin() {
    lcd.begin(16, 2);
    backlight(true);
}

void LCD::print(const String& message) {
    lcd.print(message);
}

void LCD::clear() {
    lcd.clear();
}

void LCD::setCursor(uint8_t col, uint8_t row) {
    lcd.setCursor(col, row);
}

void LCD::backlight(bool state) {
    pinMode(LCD_BL, OUTPUT);
    digitalWrite(LCD_BL, state ? HIGH : LOW);
}
