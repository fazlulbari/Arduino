#include <SPI.h>

// Define the SPI pins for communication (change as needed)
#define PIN_SPI_CS   15  // Chip select pin
#define PIN_SPI_CLK  14  // SPI Clock pin
#define PIN_SPI_MISO 12  // Master In Slave Out
#define PIN_SPI_MOSI 13  // Master Out Slave In

static constexpr size_t BUFFER_SIZE = 8;
uint8_t tx_buf[BUFFER_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8};  // Data to send to slave
uint8_t rx_buf[BUFFER_SIZE] = {0, 0, 0, 0, 0, 0, 0, 0};  // Buffer to receive data from slave

void setup() {
    Serial.begin(115200);
    while (!Serial);

    // Initialize SPI as master
    SPI.begin(PIN_SPI_CLK, PIN_SPI_MISO, PIN_SPI_MOSI, PIN_SPI_CS);

    // Set SPI settings (SPI mode, speed, bit order)
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE2));  // 1 MHz, MSB first, SPI mode 2

    Serial.println("SPI Master initialized.");
}

void loop() {
    // Select the slave device (chip select low)
    digitalWrite(PIN_SPI_CS, LOW);

    // Transfer data byte by byte
    for (size_t i = 0; i < BUFFER_SIZE; ++i) {
        rx_buf[i] = SPI.transfer(tx_buf[i]);  // Send byte and receive byte
    }

    // Print the data received from the slave
    Serial.print("Received data from slave: ");
    for (size_t i = 0; i < BUFFER_SIZE; ++i) {
        Serial.print(rx_buf[i], HEX);
        Serial.print(" ");
    }
    Serial.println();

    // Modify tx_buf to send new data to the slave
    for (size_t i = 0; i < BUFFER_SIZE; ++i) {
        tx_buf[i] = i + 10;  // Modify tx_buf for the next transfer
    }

    // Deselect the slave device (chip select high)
    digitalWrite(PIN_SPI_CS, HIGH);

    delay(1000);  // Wait for a second before the next transfer
}