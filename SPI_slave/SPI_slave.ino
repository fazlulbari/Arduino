#include <ESP32SPISlave.h>

ESP32SPISlave slave;

static constexpr size_t BUFFER_SIZE = 8;
static constexpr size_t QUEUE_SIZE = 1;

uint8_t tx_buf[BUFFER_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8};  // Data to send to master
uint8_t rx_buf[BUFFER_SIZE] = {0, 0, 0, 0, 0, 0, 0, 0};  // Buffer to receive data from master

void setup() {
    Serial.begin(115200);
    while (!Serial);

    // Set SPI mode and queue size
    slave.setDataMode(SPI_MODE2);  // SPI_MODE2 (CPOL=1, CPHA=0)
    slave.setQueueSize(QUEUE_SIZE);  // Set queue size

    // Initialize SPI in slave mode (default is HSPI)
    if (!slave.begin(HSPI, 14, 12, 13, 15)) {
        Serial.println("Failed to initialize SPI Slave!");
        while (1);  // Halt if initialization fails
    }

    Serial.println("SPI Slave initialized.");

    // Set the post-setup callback (called after transaction setup)
    slave.setPostSetupCb([](spi_slave_transaction_t* transaction) {
        Serial.println("Post-Setup Callback Triggered.");
        // You can inspect the transaction here if needed
    });

    // Set the post-transaction callback (called after the transaction is completed)
    slave.setPostTransCb([](spi_slave_transaction_t* transaction) {
        Serial.println("Post-Transaction Callback Triggered.");
        size_t received_bytes = transaction->length;  // Use length instead of rxlength
        if (received_bytes > 0) {
            // Copy received data into rx_buf
            memcpy(rx_buf, transaction->rx_buffer, received_bytes);
            Serial.print("Received data from master: ");
            for (size_t i = 0; i < received_bytes; ++i) {
                Serial.print(rx_buf[i], HEX);
                Serial.print(" ");
            }
            Serial.println();
        }
        
        // Send response back to master (modify tx_buf if needed)
        Serial.println("Sending response to master.");
        for (size_t i = 0; i < BUFFER_SIZE; ++i) {
            tx_buf[i] = i + 10;  // Modify tx_buf for the next transfer
        }
    });
}

void loop() {
    // Transfer data between the master and slave
    size_t received_bytes = slave.transfer(tx_buf, rx_buf, BUFFER_SIZE, 1000);

    if (received_bytes > 0) {
        // Print the received data from the master
        Serial.print("Received data from master: ");
        for (size_t i = 0; i < received_bytes; ++i) {
            Serial.print(rx_buf[i], HEX);
            Serial.print(" ");
        }
        Serial.println();

        // Respond to the master with new data
        Serial.println("Sending response to master.");
        for (size_t i = 0; i < BUFFER_SIZE; ++i) {
            tx_buf[i] = i + 10;  // Modify tx_buf to send different data (example)
        }
    }
    delay(100);  // Small delay to avoid blocking the loop
}