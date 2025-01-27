#include "menu.h"

// create global CMBMenu instance
CMBMenu<100> g_Menu;

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

  // Attach callbacks to button events
  upButton.attachClick(handleUpClick);
  downButton.attachClick(handleDownClick);
  enterButton.attachClick(handleEnterClick);
  escButton.attachClick(handleEscClick);

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
  g_Menu.addNode(1, TemperatureThreshold, MenuTemperatureThreshold);
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
      Serial.println("Exiting menu");
      break;
    case KeyEnter:
      g_Menu.enter(layerChanged);
      Serial.println("Entering submenu");
      break;
    case KeyRight:
      g_Menu.right();
      Serial.println("Navigating right");
      break;
    case KeyLeft:
      g_Menu.left();
      Serial.println("Navigating left");
      break;
    default:
      break;
  }

  if (KeyNone != currentKey) {
    fid = g_Menu.getInfo(info);
    Serial.print("Current Function ID: ");
    Serial.println(fid);
    printMenuEntry(info);

    if ((0 != fid) && (KeyEnter == currentKey) && (!layerChanged)) {
      Serial.print("Executing function for ID: ");
      Serial.println(fid);
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
        case MenuTemperatureThreshold:
          showTemperatureThreshold();
          break;
        case MenuVoltageThreshold:
          showVoltageThreshold();
          break;
        case MenuBaudrate:
          showBaudrate();
          break;
        case MenuSlaveID:
          showSlaveID();
          break;
        case MenuInputVoltage:
          showInputVoltage();
          break;
        default:
          Serial.println("Unknown Function ID");
          break;
      }
    }
    currentKey = KeyNone;
  }
  delay(50);
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
  Serial.println("Displaying Temperature.");
  g_Lcd.setCursor(0, 1);
  g_Lcd.print("Temp: 25C    ");
}

// ********************************************
// showSmokeAlarm
// ********************************************
void showSmokeAlarm() {
  Serial.println("Smoke Alarm Triggered.");
  g_Lcd.setCursor(0, 1);
  g_Lcd.print("Smoke Alarm ");
}

// ********************************************
// showTemperatureAlarm
// ********************************************
void showTemperatureAlarm() {
  Serial.println("Temperature Alarm Triggered.");
  g_Lcd.setCursor(0, 1);
  g_Lcd.print("Temp Alarm  ");
}

// ********************************************
// showFanFaultAlarm
// ********************************************
void showFanFaultAlarm() {
  Serial.println("Fan Fault Alarm Triggered.");
  g_Lcd.setCursor(0, 1);
  g_Lcd.print("Fan Fault   ");
}

// ********************************************
// showWaterAlarm
// ********************************************
void showWaterAlarm() {
  Serial.println("Water Level Alarm Triggered.");
  g_Lcd.setCursor(0, 1);
  g_Lcd.print("Water Alarm ");
}

// ********************************************
// showDoorAlarm
// ********************************************
void showDoorAlarm() {
  Serial.println("Door Alarm Triggered.");
  g_Lcd.setCursor(0, 1);
  g_Lcd.print("Door Alarm  ");
}

// ********************************************
// showInputVoltage
// ********************************************
void showInputVoltage() {
  float voltage = 12.5;  // Example value
  Serial.print("Displaying Input Voltage: ");
  Serial.println(voltage);

  g_Lcd.setCursor(0, 1);
  g_Lcd.print("Input Voltage: ");
  g_Lcd.print(voltage);
  g_Lcd.print(" V");
}

// ********************************************
// showConfig
// ********************************************
void showConfig() {
  Serial.println("Config Menu");
  g_Lcd.setCursor(0, 1);
  g_Lcd.print("Config Menu ");
}

// ********************************************
// showTemperatureThreshold
// ********************************************
void showTemperatureThreshold() {
  Serial.println("Temperature Threshold");
  g_Lcd.setCursor(0, 1);
  g_Lcd.print("Temp Threshold");
}

// ********************************************
// showVoltageThreshold
// ********************************************
void showVoltageThreshold() {
  Serial.println("Voltage Threshold");
  g_Lcd.setCursor(0, 1);
  g_Lcd.print("Voltage Threshold");
}

// ********************************************
// showBaudrate
// ********************************************
void showBaudrate() {
  Serial.println("Baudrate Menu");
  g_Lcd.setCursor(0, 1);
  g_Lcd.print("Baudrate Menu ");
}

// ********************************************
// showSlaveID
// ********************************************
void showSlaveID() {
  Serial.println("Slave ID Menu");
  g_Lcd.setCursor(0, 1);
  g_Lcd.print("Slave ID Menu");
}