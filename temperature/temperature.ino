#include "module1.h"

void setup() {
    Serial.begin(9600); // Start serial communication
}

void loop() {
    // Get temperature from GPIO 18 and print it
    float temp18 = Returntemp(18);  
    Serial.print("Temperature from GPIO 18: ");
    Serial.println(temp18);

    // Get temperature from GPIO 23 and print it
    float temp23 = Returntemp(23);  
    Serial.print("Temperature from GPIO 23: ");
    Serial.println(temp23);

    delay(1000); // Wait for 1 second before reading again
}
