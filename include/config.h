#pragma once
#include <Arduino.h>

// I2C Bus Settings
#define I2C_SDA             6
#define I2C_SCL             7

// Peripherals
#define PIN_BUTTON_A        9
#define PIN_LED_STATUS      8
#define PIN_POTENTIOMETER   0 // ADC1_CH0 is GPIO 0 on C3
#define PIN_BUZZER          2

// Display Settings
#define SCREEN_WIDTH        128
#define SCREEN_HEIGHT       64 // Adjust to 128 if your SH1106 is the square version
#define SCREEN_ADDRESS      0x3C

// System Settings
#define TASK_STACK_SIZE     4096

// Thread-safe data structure for movement
struct DeviceState {
    float roll;          // Tilt left/right
    float pitch;         // Tilt up/down
    bool buttonPressed;  // For blinking
    int eyeSize;         // From Potentiometer
};
// Global instance (simplified for now, later we use Queues)
extern DeviceState systemState;