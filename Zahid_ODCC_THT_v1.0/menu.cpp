#include "menu.h"

// create global CMBMenu instance
CMBMenu<100> g_Menu;

int value;
bool isModified;

const int UP_BUTTON = PB11;
const int DOWN_BUTTON = PB10;
const int ENTER_BUTTON = PB4;
const int ESC_BUTTON = PB5;

LiquidCrystal g_Lcd(PB2, PA15, PB12, PB13, PB14, PB15);
OneButton upButton(UP_BUTTON, true, true);
OneButton downButton(DOWN_BUTTON, true, true);
OneButton enterButton(ENTER_BUTTON, true, true);
OneButton escButton(ESC_BUTTON, true, true);

KeyType currentKey = KeyNone;

void handleUpClick() {
  currentKey = KeyLeft;
}

void handleDownClick() {
  currentKey = KeyRight;
}

void handleEnterClick() {
  currentKey = KeyEnter;
}

void handleEscClick() {
  currentKey = KeyExit;
}

void handleDoubleClick() {
  currentKey = DoubleClick;
}
void onLongPressUp1() {
  value= value + 1;
}

void onLongPressDown1() {
  value= value - 1;
}
void onLongPressUp100() {
  value= value + 100;
}

void onLongPressDown100() {
  value= value - 100;
}

void setupMenu() {
  g_Lcd.begin(16, 2);  // Initialize LCD
  Serial.begin(115200);

  pinMode(PB0, OUTPUT);
  digitalWrite(PB0, HIGH);
  g_Lcd.clear();
  g_Lcd.print("mblib example");
  delay(1000);

  Serial.println("===========================");
  Serial.println("mblib - example for CMBMenu");
  Serial.println("===========================");
  Serial.println("");


  // ** menu **
  // add nodes to menu (layer, string, function ID)
  g_Menu.addNode(0, Status, MenuStatus);
  g_Menu.addNode(1, Temperature, MenuTemperature);
  g_Menu.addNode(1, InputVoltage, MenuInputVoltage);

  g_Menu.addNode(0, Alarms, MenuAlarms);
  g_Menu.addNode(1, Smokealarm, MenuSmokeAlarm);
  g_Menu.addNode(1, Temperaturealarm, MenuTemperatureAlarm);
  g_Menu.addNode(1, FanFaultalarm, MenuFanFaultAlarm);
  g_Menu.addNode(1, Wateralarm, MenuWaterAlarm);
  g_Menu.addNode(1, Dooralarm, MenuDoorAlarm);

  g_Menu.addNode(0, Config, MenuConfig);
  g_Menu.addNode(1, TemperatureThresholdH, MenuTemperatureThresholdH);
  g_Menu.addNode(1, TemperatureThresholdL, MenuTemperatureThresholdL);
  g_Menu.addNode(1, VoltageThreshold, MenuVoltageThreshold);
  g_Menu.addNode(1, Baudrate, MenuBaudrate);
  g_Menu.addNode(1, SlaveID, MenuSlaveID);

  // ** menu **
  // build menu and print menu
  const char* info;
  g_Menu.buildMenu(info);
  g_Menu.printMenu();

  // ** menu **
  // print current menu entry
  printMenuEntry(info);
}

void loopMenu() {
  value =0;
  isModified = false;
  // Attach callbacks to button events
  upButton.attachClick(handleUpClick);
  downButton.attachClick(handleDownClick);
  enterButton.attachClick(handleEnterClick);
  escButton.attachClick(handleEscClick);

  upButton.tick();
  downButton.tick();
  enterButton.tick();
  escButton.tick();

  int fid = 0;
  const char* info;
  bool layerChanged = false;

  switch (currentKey) {
    case KeyExit:
      g_Menu.exit();
      // Serial.println("Exiting menu");
      break;
    case KeyEnter:
      g_Menu.enter(layerChanged);
      // Serial.println("Entering submenu");
      break;
    case KeyRight:
      g_Menu.right();
      // Serial.println("Navigating right");
      break;
    case KeyLeft:
      g_Menu.left();
      // Serial.println("Navigating left");
      break;
    default:
      break;
  }

  if (KeyNone != currentKey) {
    fid = g_Menu.getInfo(info);
    // Serial.print("Current Function ID: ");
    // Serial.println(fid);
    printMenuEntry(info);

    if ((0 != fid) && (KeyEnter == currentKey) && (!layerChanged)) {
      // Serial.print("Executing function for ID: ");
      // Serial.println(fid);
      while(KeyExit != currentKey)
      {
      upButton.tick();
      downButton.tick();
      enterButton.tick();
      escButton.tick();
      switch (fid) {
        case MenuTemperature:
          showTemperature();
          break;
        case MenuSmokeAlarm:
          showSmokeAlarm();
          break;
        case MenuTemperatureAlarm:
          showTemperatureAlarm();
          break;
        case MenuFanFaultAlarm:
          showFanFaultAlarm();
          break;
        case MenuWaterAlarm:
          showWaterAlarm();
          break;
        case MenuDoorAlarm:
          showDoorAlarm();
          break;
        case MenuConfig:
          showConfig();
          break;
        case MenuTemperatureThresholdH:
          upButton.attachClick(onLongPressUp1);
          downButton.attachClick(onLongPressDown1);
          upButton.attachDuringLongPress(onLongPressUp1);
          downButton.attachDuringLongPress(onLongPressDown1);
          enterButton.attachDoubleClick(handleDoubleClick);
          showTemperatureThresholdH();
          break;
        case MenuTemperatureThresholdL:
          upButton.attachClick(onLongPressUp1);
          downButton.attachClick(onLongPressDown1);
          upButton.attachDuringLongPress(onLongPressUp1);
          downButton.attachDuringLongPress(onLongPressDown1);
          enterButton.attachDoubleClick(handleDoubleClick);
          showTemperatureThresholdL();
          break;
        case MenuVoltageThreshold:
          upButton.attachClick(onLongPressUp1);
          downButton.attachClick(onLongPressDown1);
          upButton.attachDuringLongPress(onLongPressUp1);
          downButton.attachDuringLongPress(onLongPressDown1);
          enterButton.attachDoubleClick(handleDoubleClick);
          showVoltageThreshold();
          break;
        case MenuBaudrate:
          upButton.attachClick(onLongPressUp100);
          downButton.attachClick(onLongPressDown100);
          upButton.attachDuringLongPress(onLongPressUp100);
          downButton.attachDuringLongPress(onLongPressDown100);
          enterButton.attachDoubleClick(handleDoubleClick);
          showBaudrate();
          break;
        case MenuSlaveID:
          upButton.attachClick(onLongPressUp1);
          downButton.attachClick(onLongPressDown1);
          upButton.attachDuringLongPress(onLongPressUp1);
          downButton.attachDuringLongPress(onLongPressDown1);
          enterButton.attachDoubleClick(handleDoubleClick);
          showSlaveID();
          break;
        case MenuInputVoltage:
          showInputVoltage();
          break;
        default:
          //Serial.println("Unknown Function ID");
          break;
      }
      vTaskDelay(50 / portTICK_PERIOD_MS);
      }
    }
    currentKey = KeyNone;
  }
  // delay(50);
}

// ********************************************
// ** menu **
// printMenuEntry
// ********************************************
void printMenuEntry(const char* f_Info) {
  String info_s;
  MBHelper::stringFromPgm(f_Info, info_s);

  // print on LCD
  g_Lcd.clear();
  g_Lcd.setCursor(0, 0);
  g_Lcd.print(info_s);
}

// ********************************************
// showTemperature
// ********************************************
void showTemperature() {
  //Serial.println("Displaying Temperature.");
  g_Lcd.setCursor(0, 1);
  g_Lcd.print(temperature);
}

// ********************************************
// showSmokeAlarm
// ********************************************
void showSmokeAlarm() {
  //Serial.println("Smoke Alarm Triggered.");
  g_Lcd.setCursor(0, 1);
  g_Lcd.print(Smoke_alarm);
}

// ********************************************
// showTemperatureAlarm
// ********************************************
void showTemperatureAlarm() {
  //Serial.println("Temperature Alarm Triggered.");
  g_Lcd.setCursor(0, 1);
  g_Lcd.print(Temperature_alarm);
}

// ********************************************
// showFanFaultAlarm
// ********************************************
void showFanFaultAlarm() {
  //Serial.println("Fan Fault Alarm Triggered.");
  g_Lcd.setCursor(0, 1);
  g_Lcd.print(Fan_fault_alarm);
}

// ********************************************
// showWaterAlarm
// ********************************************
void showWaterAlarm() {
  //Serial.println("Water Level Alarm Triggered.");
  g_Lcd.setCursor(0, 1);
  g_Lcd.print(Water_level_alarm);
}

// ********************************************
// showDoorAlarm
// ********************************************
void showDoorAlarm() {
  //Serial.println("Door Alarm Triggered.");
  g_Lcd.setCursor(0, 1);
  g_Lcd.print(Door_alarm);
}

// ********************************************
// showInputVoltage
// ********************************************
void showInputVoltage() {
  //Serial.println("Input Voltage");
  g_Lcd.setCursor(0, 1);
  g_Lcd.print(Input_voltage);
}

// ********************************************
// showConfig
// ********************************************
void showConfig() {
}

// ********************************************
// showTemperatureThreshold
// ********************************************
void showTemperatureThresholdH() {
  if (!isModified) {
    value = temperature_thresholdHigh;
    isModified = true;
  }
  
  if (DoubleClick == currentKey) {
    temperature_thresholdHigh = value;
    
    g_Lcd.setCursor(0, 1);
    g_Lcd.print("Saved  ");
    delay(1000);
    g_Lcd.setCursor(0, 1);
    g_Lcd.print("         "); // Clear the row
    currentKey = KeyNone;
  }
  
  g_Lcd.setCursor(0, 1);
  g_Lcd.print("         "); // Clear the row before printing
  g_Lcd.setCursor(0, 1);
  g_Lcd.print(value);
}

void showTemperatureThresholdL() {
  if (!isModified) {
    value = temperature_thresholdLow;
    isModified = true;
  }
  
  if (DoubleClick == currentKey) {
    temperature_thresholdLow = value;
    
    g_Lcd.setCursor(0, 1);
    g_Lcd.print("Saved  ");
    delay(1000);
    g_Lcd.setCursor(0, 1);
    g_Lcd.print("         "); // Clear the row
    currentKey = KeyNone;
  }
  
  g_Lcd.setCursor(0, 1);
  g_Lcd.print("         "); // Clear the row before printing
  g_Lcd.setCursor(0, 1);
  g_Lcd.print(value);
}


// ********************************************
// showVoltageThreshold
// ********************************************
void showVoltageThreshold() {
  if (!isModified) {
    value = VoltageThres;
    isModified = true;
  }
  
  if (DoubleClick == currentKey) {
    VoltageThres = value;
    
    g_Lcd.setCursor(0, 1);
    g_Lcd.print("Saved  ");
    delay(1000);
    g_Lcd.setCursor(0, 1);
    g_Lcd.print("         "); // Clear the row
    currentKey = KeyNone;
  }
  
  g_Lcd.setCursor(0, 1);
  g_Lcd.print("         "); // Clear the row before printing
  g_Lcd.setCursor(0, 1);
  g_Lcd.print(value);
}


// ********************************************
// showBaudrate
// ********************************************
void showBaudrate() {
  if (!isModified) {
    value = Baud_Rate;
    isModified = true;
  }
  
  if (DoubleClick == currentKey) {
    Baud_Rate = value;
    
    g_Lcd.setCursor(0, 1);
    g_Lcd.print("Saved  ");
    delay(1000);
    g_Lcd.setCursor(0, 1);
    g_Lcd.print("         "); // Clear the row
    currentKey = KeyNone;
  }
  
  g_Lcd.setCursor(0, 1);
  g_Lcd.print("         "); // Clear the row before printing
  g_Lcd.setCursor(0, 1);
  g_Lcd.print(value);
}

// ********************************************
// showSlaveID
// ********************************************
void showSlaveID() {
  if (!isModified) {
    value = Slave_id;
    isModified = true;
  }
  
  if (DoubleClick == currentKey) {
    Slave_id = value;
    
    g_Lcd.setCursor(0, 1);
    g_Lcd.print("Saved  ");
    delay(1000);
    g_Lcd.setCursor(0, 1);
    g_Lcd.print("         "); // Clear the row
    currentKey = KeyNone;
  }
  
  g_Lcd.setCursor(0, 1);
  g_Lcd.print("         "); // Clear the row before printing
  g_Lcd.setCursor(0, 1);
  g_Lcd.print(value);
}