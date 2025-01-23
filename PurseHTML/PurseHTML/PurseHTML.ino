#include <WiFi.h>
#include <HTTPClient.h>

// Replace with your network credentials
const char* ssid = "Virus";
const char* password = "Hellow there1";

// Server URL to fetch the data from
const String serverUrl = "http://pranto.dataloggerbd.com/Check.php";

void setup() {
  // Start the serial monitor and connect to Wi-Fi
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  // Wait until the ESP32 is connected to Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi!");
  // Fetch the data from the WaterBill.php page
  getData();
  
}

void loop() {
  // Keep the ESP32 running (optional, if you want to periodically get the data)
  delay(10000);  // Delay between requests
}

void getData() {
  HTTPClient http;

  // Start the HTTP request to the server URL
  http.begin(serverUrl);

  // Send GET request and get the HTTP response code
  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {
    // HTTP request was successful
    String response = http.getString();  // Get the response body

    Serial.println("Received data from WaterBill.php:");

    // Extract the MAC Address and Recharge Amount from the HTML response
    String macAddress = extractData(response, "MAC_Address:</strong> ");
    String rechargeAmount = extractData(response, "Recharge_Amount:</strong> ");

    Serial.println("MAC Address: " + macAddress);
    Serial.println("Recharge Amount: " + rechargeAmount);
  } else {
    // Handle error in getting the response
    Serial.println("Error on HTTP request");
    Serial.println("HTTP Response Code: " + String(httpResponseCode));
  }

  // End the HTTP request
  http.end();
}

// Function to extract data based on a marker
String extractData(String response, String marker) {
  int startIndex = response.indexOf(marker);
  if (startIndex == -1) return "";  // Marker not found

  startIndex += marker.length();  // Move past the marker
  int endIndex = response.indexOf("<", startIndex);  // Find the next HTML tag

  if (endIndex == -1) return "";  // No ending tag found

  return response.substring(startIndex, endIndex);  // Extract the data
}

