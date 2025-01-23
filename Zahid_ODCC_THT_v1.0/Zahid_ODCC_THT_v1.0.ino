#include "ODCC_config.h"
#include "LCD.h"
#include "Buttons.h"
#include "Fan_Controller.h"
#include "Sensors.h"
#include "Peripherals.h"

LCD lcd;
Buttons buttons;
FanController fans;
Sensors sensors;
Peripherals peripherals;

bool fanState = LOW;

unsigned long previousMillis = 0;

// float temperature_thresholdHigh = 28;
// float temperature_thresholdLow = 24;
// uint32_t fanToggle_Interval = 2000;

void setup() {
    Serial.begin(115200);
    lcd.begin();
    buttons.begin();
    fans.begin();
    sensors.begin();
    peripherals.begin();

    lcd.print("System Ready");
    delay(2000);
    lcd.clear();
}

void loop() {
    // Check buttons
    int buttonPressed = buttons.read();
    if (buttonPressed != -1) {
        // peripherals.triggerRelay(BUZZER_Trigger, true); // Buzzer feedback
        delay(100);
        // peripherals.triggerRelay(BUZZER_Trigger, false);
    }

    // Monitor sensors
    if (sensors.isDoorOpen()) {
        peripherals.controlLight(true);
        peripherals.triggerRelay(DOOR_ALARM, true);
        Serial.println("DOOR OPEN");
    } else {
        peripherals.controlLight(false);
        peripherals.triggerRelay(DOOR_ALARM, false);
    }

    if (sensors.isWaterPresent()) {
        peripherals.triggerRelay(WATER_ALARM, true);
        Serial.println("HIGH WATER");
    } else {
        peripherals.triggerRelay(WATER_ALARM, false);
    }

    if (sensors.isSmokeDetected()) {
        peripherals.triggerRelay(SMOKE_ALARM, true);
        Serial.println("FIRE");
    } else {
        peripherals.triggerRelay(SMOKE_ALARM, false);
    }

    float temperature = sensors.readTemperature();
    Serial.println(temperature);

    if (temperature > temperature_thresholdHigh)
    {
      peripherals.triggerRelay(HIGH_TEMP_ALARM, true);
      Serial.println("HIGH TEMP");
    }else {
      peripherals.triggerRelay(HIGH_TEMP_ALARM, false);
    }

    //Sensing Voltage
    float voltage = sensors.voltageSence();
    Serial.println(voltage);

    //Fan Control

    if (!sensors.isSmokeDetected()) {
      if(voltage > VoltageThreshold)
      {
        if (temperature > temperature_thresholdLow && temperature < temperature_thresholdHigh) {
          // Fan Toggle
          Serial.println("Fan Toggling");
          unsigned long currentMillis = millis();  // Get the current time

          // Check if it's time to toggle the fans
          if (currentMillis - previousMillis >= fanToggle_Interval) {
            // Save the last time the fans were toggled
            previousMillis = currentMillis;

            // Toggle the fan states
            if (fanState == LOW) {
              fanState = HIGH;
            } else {
              fanState = LOW;
            }
            // Update the fan states
            fans.toggle_Fan(fanState);
          }

        } else if (temperature >= temperature_thresholdHigh) {
          Serial.println("All Fan ON!");
          fans.controlFan1(HIGH);
          fans.controlFan2(HIGH);
        } else if (temperature <= temperature_thresholdLow) {

          Serial.println("All Fan OFF!");
          fans.controlFan1(LOW);
          fans.controlFan2(LOW);
        }
    }
    else {
        // all fan off
        Serial.println("All Fan OFF!");
        fans.controlFan1(LOW);
        fans.controlFan2(LOW);
      }
  } 
  else {
    // all fan off
    Serial.println("All Fan OFF!");
    fans.controlFan1(LOW);
    fans.controlFan2(LOW);
  }
  delay(500); // Main loop delay
}

