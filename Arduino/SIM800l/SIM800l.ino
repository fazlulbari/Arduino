#include <HardwareSerial.h>

// Define SIM800L TX and RX pins for ESP32
#define SIM800L_TX_PIN 27 // ESP32 TX pin connected to SIM800L RX
#define SIM800L_RX_PIN 26 // ESP32 RX pin connected to SIM800L TX
#define MODEM_RST            5
#define MODEM_PWKEY          4
#define MODEM_POWER_ON       23

HardwareSerial sim800l(1); // Use UART1 for SIM800L

void setup() {
  // Start Serial for debugging
  Serial.begin(115200);

  // Start HardwareSerial for SIM800L
  sim800l.begin(115200, SERIAL_8N1, SIM800L_RX_PIN, SIM800L_TX_PIN);

  Serial.println("Initializing SIM800L...");
  
    // Set modem reset, enable, power pins
  pinMode(MODEM_PWKEY, OUTPUT);
  pinMode(MODEM_RST, OUTPUT);

  digitalWrite(MODEM_PWKEY, LOW);
  digitalWrite(MODEM_RST, HIGH);

  
  // Test SIM800L module
  if (sendATCommand("AT", "OK", 5000)) {
    Serial.println("SIM800L is ready.");
  } else {
    Serial.println("Failed to communicate with SIM800L.");
    return;
  }

  // Set SMS text mode
  if (sendATCommand("AT+CMGF=1", "OK", 5000)) {
    Serial.println("Set SMS mode to text.");
  } else {
    Serial.println("Failed to set SMS mode.");
    return;
  }

  // Send SMS
  sendSMS("+8801716863729", "Hello from ESP32 and SIM800L!");
}

void loop() {
  // Nothing to do here
}

// Function to send AT command
bool sendATCommand(const char* command, const char* expectedResponse, int timeout) {
  sim800l.println(command); // Send the command
  long int time = millis();
  while ((time + timeout) > millis()) {
    while (sim800l.available()) {
      String response = sim800l.readString();
      Serial.println("SIM800L Response: " + response);
      if (response.indexOf(expectedResponse) != -1) {
        return true; // Found the expected response
      }
    }
  }
  return false; // Timed out
}

// Function to send an SMS
void sendSMS(const char* phoneNumber, const char* message) {
  // Set the recipient phone number
  String command = "AT+CMGS=\"";
  command += phoneNumber;
  command += "\"";
  
  if (sendATCommand(command.c_str(), ">", 5000)) {
    // Send the message body
    sim800l.print(message);
    sim800l.write(26); // ASCII code for Ctrl+Z to send the message
    Serial.println("Message sent.");
  } else {
    Serial.println("Failed to send SMS.");
  }
}
