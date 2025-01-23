#include <Wire.h>

#define MPU6050_ADDR 0x68 // MPU6050 I2C address
#define ACCEL_CONFIG 0x1C // Accelerometer configuration register
#define GYRO_CONFIG 0x1B  // Gyroscope configuration register

const float accelSensitivity = 16384.0; // LSB/g for ±2g range
const float gyroSensitivity = 131.0;   // LSB/(°/s) for ±250°/s range
const float g = 9.81;                  // Gravitational acceleration (m/s²)

int16_t accelX, accelY, accelZ;
int16_t gyroX, gyroY, gyroZ;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22); // SDA = GPIO 21, SCL = GPIO 22

  // Initialize MPU6050
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x6B); // Power management register
  Wire.write(0);    // Wake up the MPU6050
  Wire.endTransmission();

  // Optionally configure accelerometer and gyroscope ranges here
  configureMPU6050();
}

void loop() {
  readMPU6050(); // Read raw data from MPU6050
  calculateAndPrintValues(); // Convert and display the data
  delay(500); // Update every 500ms
}

void configureMPU6050() {
  // Set accelerometer to ±2g range
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(ACCEL_CONFIG);
  Wire.write(0x00); // ±2g range
  Wire.endTransmission();

  // Set gyroscope to ±250°/s range
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(GYRO_CONFIG);
  Wire.write(0x01); // ±250°/s range
  Wire.endTransmission();
}

void readMPU6050() {
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x3B); // Starting register for accelerometer data
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_ADDR, 14, true); // Request 14 bytes

  accelX = (Wire.read() << 8 | Wire.read());
  accelY = (Wire.read() << 8 | Wire.read());
  accelZ = (Wire.read() << 8 | Wire.read());
  Wire.read(); Wire.read(); // Skip temperature data
  gyroX = (Wire.read() << 8 | Wire.read());
  gyroY = (Wire.read() << 8 | Wire.read());
  gyroZ = (Wire.read() << 8 | Wire.read());
}

void calculateAndPrintValues() {
  // Convert accelerometer data to m/s²
  float ax = (accelX / accelSensitivity) * g;
  float ay = (accelY / accelSensitivity) * g;
  float az = (accelZ / accelSensitivity) * g;

  // Convert gyroscope data to °/s
  float gx = gyroX / gyroSensitivity;
  float gy = gyroY / gyroSensitivity;
  float gz = gyroZ / gyroSensitivity;

  // Calculate Roll and Pitch (in degrees)
  float roll = atan2(ay, sqrt(ax * ax + az * az)) * 180 / PI;
  float pitch = atan2(-ax, sqrt(ay * ay + az * az)) * 180 / PI;

  // Print the converted values to the Serial Monitor
  Serial.print("Accel (m/s²): ");
  Serial.print("Ax: "); Serial.print(ax, 2);
  Serial.print(", Ay: "); Serial.print(ay, 2);
  Serial.print(", Az: "); Serial.print(az, 2);

  Serial.print(" || Gyro (°/s): ");
  Serial.print("Gx: "); Serial.print(gx, 2);
  Serial.print(", Gy: "); Serial.print(gy, 2);
  Serial.print(", Gz: "); Serial.print(gz, 2);

  Serial.print(" || Angles (°): ");
  Serial.print("Roll: "); Serial.print(roll, 2);
  Serial.print(", Pitch: "); Serial.println(pitch, 2);
}

