///////////////// Fan Controller Loop ///////////////////////////////////

// void fan_Control(uint8_t pin, bool val) {

//   Serial.println("Fan Running:" + String(fan_Count));
//   if (val == true) {
//     if (pin == FAN_1 && fan_1_Faulty == false) {
//       digitalWrite(pin, val);
//       fan_Status[0] = 1;
//       fan_Count = runningFan_Count();
//       vTaskDelay(5000 / portTICK_PERIOD_MS);
//       int fanCurrent = fanConsumption();
//       Serial.println(fanCurrent);
//       if (fanCurrent > (2000 + fan_Count * 45)) {
//         fan_1_Faulty = true;
//         digitalWrite(pin, LOW);
//         fan_Status[0] = 0;
//         fan_Count = runningFan_Count();
//         Serial.println("Fan 1 Fault");
//       }
//     }

//     if (pin == FAN_2 && fan_2_Faulty == false) {
//       digitalWrite(pin, val);
//       fan_Status[1] = 1;
//       fan_Count = runningFan_Count();
//       vTaskDelay(5000 / portTICK_PERIOD_MS);
//       int fanCurrent = fanConsumption();
//       Serial.println(fanCurrent);
//       if (fanCurrent > (2000 + fan_Count * 45)) {
//         fan_2_Faulty = true;
//         digitalWrite(pin, LOW);
//         fan_Status[1] = 0;
//         fan_Count = runningFan_Count();
//         Serial.println("Fan 2 Fault");
//       }
//     }

//     if (pin == FAN_3 && fan_3_Faulty == false) {
//       digitalWrite(pin, val);
//       fan_Status[2] = 1;
//       fan_Count = runningFan_Count();
//       vTaskDelay(5000 / portTICK_PERIOD_MS);
//       int fanCurrent = fanConsumption();
//       Serial.println(fanCurrent);
//       if (fanCurrent > (2000 + fan_Count * 45)) {
//         fan_3_Faulty = true;
//         digitalWrite(pin, LOW);
//         fan_Status[2] = 0;
//         fan_Count = runningFan_Count();
//         Serial.println("Fan 3 Fault");
//       }
//     }

//     if (pin == FAN_4 && fan_4_Faulty == false) {
//       digitalWrite(pin, val);
//       fan_Status[3] = 1;
//       fan_Count = runningFan_Count();
//       vTaskDelay(5000 / portTICK_PERIOD_MS);
//       int fanCurrent = fanConsumption();
//       Serial.println(fanCurrent);
//       if (fanCurrent > (2000 + fan_Count * 45)) {
//         fan_4_Faulty = true;
//         digitalWrite(pin, LOW);
//         fan_Status[3] = 0;
//         fan_Count = runningFan_Count();
//         Serial.println("Fan 4 Fault");
//       }
//     }
//   } else {
//     digitalWrite(pin, OFF);
//     if (pin == FAN_1) {
//       fan_Status[0] = 0;
//       fan_Count = runningFan_Count();
//     } else if (pin == FAN_2) {
//       fan_Status[1] = 0;
//       fan_Count = runningFan_Count();
//     } else if (pin == FAN_3) {
//       fan_Status[2] = 0;
//       fan_Count = runningFan_Count();
//     } else if (pin == FAN_4) {
//       fan_Status[3] = 0;
//       fan_Count = runningFan_Count();
//     }
//   }
// }