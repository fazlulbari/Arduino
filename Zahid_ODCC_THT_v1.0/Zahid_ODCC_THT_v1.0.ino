#include "ODCC_config.h"
#include "menu.h"
#include "Fan_Controller.h"
#include "Sensors.h"
#include "Peripherals.h"
#include <STM32FreeRTOS.h>
#include "modbus.h"

FanController fans;
Sensors sensors;
Peripherals peripherals;

bool fanState = LOW;
unsigned long previousMillis = 0;

void loopMenuTask(void *pvParameters) {
    // Infinite loop for menu tasks
    while (true) {
        loopMenu();
        vTaskDelay(10 / portTICK_PERIOD_MS); // Add a small delay to prevent watchdog reset and allow other tasks to run
    }
}

void sensorAndFanControlTask(void *pvParameters) {
    // Infinite loop for sensor monitoring and fan control
    while (true) {
        // Sensing Voltage
        Input_voltage = sensors.voltageSence();
        Serial.println(Input_voltage);
        // Sensing Temperature
        temperature = sensors.readTemperature();
        Serial.println(temperature);

        // Monitor sensors
        if (sensors.isDoorOpen()) {
            peripherals.controlLight(true);
            peripherals.triggerRelay(DOOR_ALARM, true);
            Serial.println("DOOR OPEN");
            Door_alarm = 1;

        } else {
            peripherals.controlLight(false);
            peripherals.triggerRelay(DOOR_ALARM, false);
            Door_alarm = 0;
        }

        if (sensors.isWaterPresent()) {
            peripherals.triggerRelay(WATER_ALARM, true);
            Serial.println("HIGH WATER");
            Water_level_alarm = 1;
        } else {
            peripherals.triggerRelay(WATER_ALARM, false);
            Water_level_alarm = 0;
        }

        if (sensors.isSmokeDetected()) {
            peripherals.triggerRelay(SMOKE_ALARM, true);
            Serial.println("FIRE");
            Smoke_alarm = 1;
        } else {
            peripherals.triggerRelay(SMOKE_ALARM, false);
            Smoke_alarm = 0;
        }

        if (temperature > temperature_thresholdHigh) {
            peripherals.triggerRelay(HIGH_TEMP_ALARM, true);
            Serial.println("HIGH TEMP");
            Temperature_alarm = 1 ;
        } else {
            peripherals.triggerRelay(HIGH_TEMP_ALARM, false);
            Temperature_alarm = 0 ;
        }

        // Fan Control
        if (!sensors.isSmokeDetected()) {
            if (Input_voltage > VoltageThres) {
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
            } else {
                // All fan off
                Serial.println("All Fan OFF!");
                fans.controlFan1(LOW);
                fans.controlFan2(LOW);
            }
        } else {
            // All fan off
            Serial.println("All Fan OFF!");
            fans.controlFan1(LOW);
            fans.controlFan2(LOW);
        }
        modbus_loop();
        vTaskDelay(100 / portTICK_PERIOD_MS); // Small delay to yield to other tasks
    }
}

void setup() {
    Serial.begin(115200);  // Initialize Serial for debugging
    setupMenu();
    fans.begin();
    sensors.begin();
    peripherals.begin();
    modbus_init();
    delay(2000);  // Initial delay for hardware to settle

    // Create FreeRTOS tasks
    xTaskCreate(sensorAndFanControlTask, "Sensor & Fan Control Task", 2048, NULL, 1, NULL);
    xTaskCreate(loopMenuTask, "Loop Menu Task", 1024, NULL, 2, NULL);

    // Start the scheduler
    vTaskStartScheduler();
}

void loop() {
    // No longer needed as tasks are now running independently
}



