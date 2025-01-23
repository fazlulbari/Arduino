#include <driver/ledc.h>  // Optional, not used here
#include <math.h>

// Sine wave generation parameters
const int sineFrequency = 50;  // Sine wave frequency (Hz)
const int sampleRate = 1000;   // Sampling rate (Hz)
const int tableSize = sampleRate / sineFrequency; // Number of samples per cycle
uint8_t sineTable[tableSize];  // Sine lookup table

hw_timer_t *timer = NULL;      // Timer object
volatile int sampleIndex = 0;  // Current index in sineTable

void IRAM_ATTR onTimer() {
  dacWrite(25, sineTable[sampleIndex]);  // Output sine wave value to GPIO 25 (DAC1)
  sampleIndex = (sampleIndex + 1) % tableSize;  // Increment and wrap index
}

void setup() {
  Serial.begin(115200);
  Serial.println("Starting Sine Wave Generator...");

  // Create sine lookup table
  for (int i = 0; i < tableSize; i++) {
    // Scale sine wave to fit within the 0-255 range of the DAC
    // The value is scaled to 0-255 range, corresponding to 0-3.3V
    sineTable[i] = (sin(2 * PI * i / tableSize) + 1) * 127.5; // Map to 0-255 (0 to 3.3V range)
  }

  // Initialize DAC on GPIO 25
  dacWrite(25, 0);

  // Configure hardware timer
  timer = timerBegin(0, 80, true);              // Timer 0, prescaler 80 (1 µs per tick)
  timerAttachInterrupt(timer, onTimer, true);   // Attach interrupt
  timerAlarm(timer, 1000000 / sampleRate, true, 0);  // Set the timer interval
  timerAlarmEnable(timer);                      // Enable timer
}

void loop() {
  // Nothing to do here; sine wave generation is handled by the timer interrupt
}

