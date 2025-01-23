#ifndef LCD_H
#define LCD_H

#include "Arduino.h"
#include <LiquidCrystal.h>
#include "MCU_config.h"

class LCD {
public:
    LCD();
    void begin();
    void print(const String& message);
    void clear();
    void setCursor(uint8_t col, uint8_t row);
    void backlight(bool state);

private:
    LiquidCrystal lcd;
};

#endif // LCD_H
