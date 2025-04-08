#define LED_PIN 2  // ESP-01 onboard LED (GPIO2)

void setup() {
    pinMode(LED_PIN, OUTPUT);  // Set GPIO2 as an output
}

void loop() {
    digitalWrite(LED_PIN, LOW);  // Turn LED ON (active LOW)
    delay(1000);  // Wait 1 second
    digitalWrite(LED_PIN, HIGH); // Turn LED OFF
    delay(1000);  // Wait 1 second
}






