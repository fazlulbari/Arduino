#include "esp32-hal-gpio.h"

#include "fan_Controller.h"

unsigned long previousMillis = 0;
bool fanState = LOW;
bool fan_1_Faulty = false;
bool fan_2_Faulty = false;
bool fan_3_Faulty = false;
bool fan_4_Faulty = false;




int fan_Count = 0;
float average_consumption = 45;  // changeable with different fan


void fan_Init() {
  pinMode(FAN_1, OUTPUT);
  pinMode(FAN_2, OUTPUT);
  pinMode(FAN_3, OUTPUT);
  pinMode(FAN_4, OUTPUT);
  allfan_Off();
}

void fanAdc_Init() {
  pinMode(FAN_BUS_ADC, INPUT);
  pinMode(FAN_CH_1_ADC, INPUT);
  pinMode(FAN_CH_2_ADC, INPUT);
}

int runningFan_Count() {
  int total_FanRunning = fan_Status[0] + fan_Status[1] + fan_Status[2] + fan_Status[3];
  return total_FanRunning;
}


void fan_Control(uint8_t pin, bool val) {
  digitalWrite(pin, val);
  if (FAN_1 == pin) {
    if (val == 1) {
      fan_Status[0] = 1;
    } else {
      fan_Status[0] = 0;
    }
  }
  if (FAN_2 == pin) {
    if (val == 1) {
      fan_Status[1] = 1;
    } else {
      fan_Status[1] = 0;
    }
  }
  if (FAN_3 == pin) {
    if (val == 1) {
      fan_Status[2] = 1;
    } else {
      fan_Status[2] = 0;
    }
  }
  if (FAN_4 == pin) {
    if (val == 1) {
      fan_Status[3] = 1;
    } else {
      fan_Status[3] = 0;
    }
  }
  fan_Count = runningFan_Count();
}




void allfan_On() {
  fan_Control(FAN_1, ON);
  fan_Control(FAN_2, ON);
  fan_Control(FAN_3, ON);
  fan_Control(FAN_4, ON);
}
void allfan_Off() {
  fan_Control(FAN_1, OFF);
  fan_Control(FAN_2, OFF);
  fan_Control(FAN_3, OFF);
  fan_Control(FAN_4, OFF);
}



void toggle_Fan(bool fanState) {
  fan_Control(FAN_1, fanState);
  fan_Control(FAN_2, fanState);
  fan_Control(FAN_3, !fanState);
  fan_Control(FAN_4, !fanState);
}


void fanOperation_Loop() {
  if (smoke_Alarm == false) {
    if (env_Temp > lowerTemp_TH && env_Temp < higherTemp_TH) {
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
        toggle_Fan(fanState);
        highTemp_Alarm = false;
      }
    } else if (env_Temp > higherTemp_TH) {
      // all fan on
      highTemp_Alarm = true;
      Serial.println("All Fan ON!");
      allfan_On();
    } else {
      // all fan off
      highTemp_Alarm = false;
      Serial.println("All Fan OFF!");
      allfan_Off();
    }

  } else {
    // all fan off
    Serial.println("All Fan OFF!");
    allfan_Off();
  }
}


int fanConsumption() {

  int fan_Adc = 0;
  for (int i = 0; i < 1000; i++) {
    fan_Adc = fan_Adc + analogRead(FAN_BUS_ADC);
  }
  fan_Adc = fan_Adc / 1000;
  return fan_Adc;
}


boolean checkEvery(unsigned long interval) {
  static unsigned long previousMillis = 0;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    return true;
  }
  return false;
}

void fanController_Loop() {
  // if (checkEvery(30000)) {
  //   //// For Indevidual Fan fault alarm
  //   // fan_1_Faulty = false;
  //   // fan_2_Faulty = false;
  //   // fan_3_Faulty = false;
  //   // fan_4_Faulty = false;


  //   // For overall Fanfault alarm
  //   fanFault_Alarm = false;
  // }
  fanOperation_Loop();

  int fanLoad = fanConsumption();
  Serial.println(fanLoad);
  fan_Consumption = (fanLoad - 1980) * 4.02;
  if (fan_Consumption < 0) {
    fan_Consumption = 0;
  } else {
    fan_Consumption = fan_Consumption;
  }

  int expected_consumtion = fan_Count * average_consumption + 1980;


  Serial.println("expected_consumtion");
  Serial.println(expected_consumtion);
  int consumption_diff = fanLoad - expected_consumtion;

  Serial.println("consumption_diff");
  Serial.println(consumption_diff);

  if (consumption_diff > 30 || consumption_diff < -30) {  //|| (fanLoad - expected_consumtion) < 30) {  //&& fanFault_Alarm == false
    fanFault_Alarm = true;
  } else {
    fanFault_Alarm = false;
  }

  Serial.println("Fan Fault Alarm " + String(fanFault_Alarm));
}
