#ifndef MCU_CONFIG_H
#define MCU_CONFIG_H

#include "Arduino.h"

// Buttons Pin
#define BUTTON_ESC  PB5
#define BUTTON_OK   PB4
#define BUTTON_UP   PB11
#define BUTTON_DOWN PB10


#define DISPLAY_TYPE LCD
// Define the pins for the 16x2 LCD
#define LCD_RS PB2   // LCD Register select
#define LCD_EN PA15  // LCD EN pin
#define LCD_D4 PB12
#define LCD_D5 PB13
#define LCD_D6 PB14
#define LCD_D7 PB15
#define LCD_BL PB0   // LCD Backlight Control Pin

// For 2.42" 128x64 OLED
// #define DISPLAY_TYPE OLED
// #define DISPLAY_COMM I2C
// #define DISPLAY_COMM SPI
#define LCD_CS   PB15
#define LCD_SCK  PB14
#define LCD_MISO PB13
#define LCD_MOSI PB12


#define RELAY_1_Trigger  PA12  // Has LED indicator
#define RELAY_2_Trigger  PB3
#define RELAY_3_Trigger  PA11
#define RELAY_4_Trigger  PA1
#define RELAY_5_Trigger  PB6
#define RELAY_6_Trigger  PB7

#endif  // MCU_CONFIG_H
