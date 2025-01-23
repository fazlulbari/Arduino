#include "display_Controller.h"

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library.
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET -1        // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C  ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void display_Init() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }
  display.clearDisplay();
}

void display_Println(int x, int y, String value) {
  display.setCursor(x, y);
  display.println(value);  // transfer internal memory to the display
  // display.display();
}


// Define global variables to store previous status
bool prevFanFault_Alarm = false;
bool prevHighTemp_Alarm = false;
bool prevSmoke_Alarm = false;
bool prevWater_Alarm = false;
bool prevDoor_Status = false;
bool prevAviation_Light = false;
bool prevLightSensor_Status = false;
float prevEnv_Temp = 0.0;
float prevEnv_Hum = 0.0;
bool prevFan_Status[4] = {false, false, false, false};
float prevFan_Consumption = 0.0;

void displayController_Loop() {
  // Check if any status has changed
  if (fanFault_Alarm != prevFanFault_Alarm || highTemp_Alarm != prevHighTemp_Alarm || smoke_Alarm != prevSmoke_Alarm || water_Alarm != prevWater_Alarm || door_Status != prevDoor_Status || aviation_Light != prevAviation_Light || lightSensor_Status != prevLightSensor_Status || env_Temp != prevEnv_Temp || env_Hum != prevEnv_Hum || fan_Status[0] != prevFan_Status[0] || fan_Status[1] != prevFan_Status[1] || fan_Status[2] != prevFan_Status[2] || fan_Status[3] != prevFan_Status[3] || fan_Consumption != prevFan_Consumption) {
    
    // Update previous status variables
    prevFanFault_Alarm = fanFault_Alarm;
    prevHighTemp_Alarm = highTemp_Alarm;
    prevSmoke_Alarm = smoke_Alarm;
    prevWater_Alarm = water_Alarm;
    prevDoor_Status = door_Status;
    prevAviation_Light = aviation_Light;
    prevLightSensor_Status = lightSensor_Status;
    prevEnv_Temp = env_Temp;
    prevEnv_Hum = env_Hum;
    prevFan_Status[0] = fan_Status[0];
    prevFan_Status[1] = fan_Status[1];
    prevFan_Status[2] = fan_Status[2];
    prevFan_Status[3] = fan_Status[3];
    prevFan_Consumption = fan_Consumption;

    // Clear the display
    display.clearDisplay();
    
    // Display the updated status
  display.setTextSize(1);               // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);  // Draw white text
  display_Println(32, 0, "ODC STATUS");


  display_Println(0, 8, "FanFault:" + String(fanFault_Alarm));
  display_Println(0, 16, "HighTemp:" + String(highTemp_Alarm));
  display_Println(0, 24, "SmokAlrm:" + String(smoke_Alarm));
  display_Println(0, 32, "WatrAlrm:" + String(water_Alarm));
  display_Println(0, 40, "DoorAlrm:" + String(door_Status));
  display_Println(0, 48, "AVLAlarm:" + String(aviation_Light));
  display_Println(0, 56, "LigtSnsr:" + String(lightSensor_Status));


  display_Println(67, 8, "Temp:" + String(env_Temp));
  display_Println(67, 16, "Hum:" + String(env_Hum));
  display_Println(67, 24, "Fan_1:" + String(fan_Status[0]));
  display_Println(67, 32, "Fan_2:" + String(fan_Status[1]));
  display_Println(67, 40, "Fan_3:" + String(fan_Status[2]));
  display_Println(67, 48, "Fan_4:" + String(fan_Status[3]));
  display_Println(67, 56, "Fan L:" + String(fan_Consumption));

   display.display();

  }

}