#include <Arduino.h>
#include "stm32f1xx_hal.h"  // Adjust for your STM32 series

#define FLASH_PAGE_SIZE 1024  // STM32F1 Flash page size is 1KB
#define FLASH_PAGE_NUMBER 100  // Page number for storing the data
#define FLASH_BASE_ADDRESS(page) (0x08000000 + (page) * FLASH_PAGE_SIZE)

#define DATA_COUNT 20  // Storing 10 integers (each 4 bytes)

void writeFlashArray(int FLASH_PAGE, int32_t *data, size_t length) {
    HAL_FLASH_Unlock();  // Unlock Flash for writing

    uint32_t flashAddress = FLASH_BASE_ADDRESS(FLASH_PAGE);

    // Erase the Flash page before writing
    FLASH_EraseInitTypeDef eraseInit;
    uint32_t pageError;
    eraseInit.TypeErase = FLASH_TYPEERASE_PAGES;
    eraseInit.PageAddress = flashAddress;
    eraseInit.NbPages = 1;

    if (HAL_FLASHEx_Erase(&eraseInit, &pageError) != HAL_OK) {
        Serial.println("Flash erase failed!");
        HAL_FLASH_Lock();
        return;
    }

    // Write data array to Flash
    for (size_t i = 0; i < length; i++) {
        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, flashAddress, data[i]) != HAL_OK) {
            Serial.println("Flash write failed!");
        }
        flashAddress += 4;  // Move to next 32-bit address
    }

    HAL_FLASH_Lock();  // Lock Flash after writing
}

void readFlashArray(int FLASH_PAGE, int32_t *buffer, size_t length) {
    uint32_t flashAddress = FLASH_BASE_ADDRESS(FLASH_PAGE);
    memcpy(buffer, (uint32_t*)flashAddress, length * sizeof(int32_t));
}

void setup() {
    Serial.begin(115200);

    // Data to store (10 integers)
    int32_t valuesToStore[DATA_COUNT] = {100, -200, 300, 400, 500, 600, 700, 800, 900, -1000, 100, 200, 300, -400, 500, 600, 700, 800, 900, 1000};

    Serial.println("Writing 10 integers to Flash...");
    writeFlashArray(FLASH_PAGE_NUMBER, valuesToStore, DATA_COUNT);

    // Read data back
    int32_t storedValues[DATA_COUNT] = {0};
    readFlashArray(FLASH_PAGE_NUMBER, storedValues, DATA_COUNT);

    Serial.println("Stored Integers:");
    for (size_t i = 0; i < DATA_COUNT; i++) {
        Serial.print("Value "); Serial.print(i); Serial.print(": ");
        Serial.println(storedValues[i]);  // Should print the same values as written
    }
}

void loop() {
}







