#ifndef CONFIG_H
#define CONFIG_H

#include <Wire.h>

extern bool is_I2C_Initialized;


extern float system_Voltage;

extern float env_Temp;
extern float env_Hum;


// I2C configuration
#define I2C_SCL   41
#define I2C_SDA   42

// I2C Addresses
#define EXTENDER_1_ADDR     0x20
#define EXTENDER_2_ADDR     0x24
#define ANALOG_IN_IC_ADDR   0x48
#define ANALOG_OUT_IC_ADDR  0x40

// #define SOFTWARE_SERIAL_FOR_MODBUS_1
// #define SOFTWARE_SERIAL_FOR_MODBUS_2

// Modbus configuration
#define MODBUS_1_TX_PIN     17
#define MODBUS_1_RX_PIN     18
#define MODBUS_1_BAUDRATE   9600

#define MODBUS_2_TX_PIN     43
#define MODBUS_2_RX_PIN     44
#define MODBUS_2_BAUDRATE   9600


// Ethernet SPI configuration
#define ETH_MOSI_PIN    12
#define ETH_MISO_PIN    11
#define ETH_SCLK_PIN    10
#define ETH_RST_PIN     9
#define ETH_CS_PIN      48

void I2C_Init();


#endif // CONFIG_H
