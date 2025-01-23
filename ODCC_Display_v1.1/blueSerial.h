////////////////////////////////////////////////////////////////////////////////////
// @File          : blueSerial.h                                                  //
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

#ifndef BLUESERIAL_H
#define BLUESERIAL_H

#include "config.h"
#include "BluetoothSerial.h"

void blue_SerialInit();

void serialPrint(String str);
void serialPrint(int str) ;
void serialPrint(boolean str) ;
void serialPrint(String str, int integer);
void serialPrint(String str, String strng);

void serialPrintln(String str);
void serialPrintln(String str, int integer);
void serialPrintln(String text_1, String text_2);

#endif
