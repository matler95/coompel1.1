#pragma once
#include <Arduino.h>

// I2C Bus Settings
#define I2C_SDA             6
#define I2C_SCL             7

// Peripherals
#define PIN_BUTTON_A        9
#define PIN_POTENTIOMETER   0 // ADC1_CH0 is GPIO 0 on C3
#define PIN_BUZZER          2
#define PIN_DHT             1
// Display Settings
#define SCREEN_WIDTH        128
#define SCREEN_HEIGHT       64 // Adjust to 128 if your SH1106 is the square version
#define SCREEN_ADDRESS      0x3C

// App States
enum class AppMode {
    FACE,
    CLIMATE,
    TIMER
};

struct DeviceState {
    float roll, pitch;
    float temp, hum;
    int potValue;
    bool buttonPressed;
    AppMode currentMode;
};

extern DeviceState systemState;