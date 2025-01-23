////////////////////////////////////////////////////////////////////////////////////
// @File          : blueSerial.cpp                                                //
// @Module        : Bluetooth Serial                                              //
// @Version       : v1.2.5                                                        //
// @Standerd      : Moduler C/C++                                                 //
// @OS            : freeRTOS                                                      //
// @Platform      : Arduino                                                       //
// @MCU           : Esp32 Wrover -B                                               //
// @Project       : Portable Generator Monitoring System                          //
// @Creation Date : 13/09/2023                                                    //
// @Modified Date : 13/09/2023                                                    //
// @Auther        : Shamim Hasan                                                  //
// @Modified by   : Shamim Hasan                                                  //
// @Company       : SARBS Communication LTD                                       //
// @Copyright     : 2023@SARBS Communication LTD                                  //
////////////////////////////////////////////////////////////////////////////////////


#include "blueSerial.h"

//#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
//#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
//#endif
//
//BluetoothSerial SerialBT;
void blue_SerialInit() {
//  SerialBT.begin(DEVICE_ID);
  Serial.begin(115200);
  Serial.println("Serial Debugging Start!");
}

void serialPrint(String str) {
  Serial.print(str);
//  SerialBT.print(str);
}
void serialPrint(int str) {
  Serial.print(str);
//  SerialBT.print(str);
}
void serialPrint(boolean str) {
  Serial.print(str);
//  SerialBT.print(str);
}
void serialPrint(String str, int integer) {
  Serial.print(str);
  Serial.print(" : ");
  Serial.print(String(integer));

//  SerialBT.print(str);
//  SerialBT.print(" : ");
//  SerialBT.print(String(integer));
}

void serialPrint(String str, String strng) {
  Serial.print(str);
  Serial.print(" : ");
  Serial.print(strng);

//  SerialBT.print(str);
//  SerialBT.print(" : ");
//  SerialBT.print(strng);
}

void serialPrintln(String str) {
  Serial.println(str);
//  SerialBT.println(str);
}
void serialPrintln(String str, int integer) {
  Serial.print(str);
  Serial.print(" : ");
  Serial.println(String(integer));

//  SerialBT.print(str);
//  SerialBT.print(" : ");
//  SerialBT.println(String(integer));
}

void serialPrintln(String text_1, String text_2) {
  Serial.print(text_1);
  Serial.print(" : ");
  Serial.println(text_2);

//  SerialBT.print(text_1);
//  SerialBT.print(" : ");
//  SerialBT.println(text_2);
}
