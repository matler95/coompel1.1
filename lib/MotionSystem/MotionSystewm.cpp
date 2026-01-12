#include "MotionSystem.h"

void MotionSystem::begin() {
    Wire.begin(I2C_SDA, I2C_SCL);
    mpu.initialize();
    if (!mpu.testConnection()) {
        Serial.println("MPU6050 connection failed");
    }
}

void MotionSystem::update() {
    int16_t ax, ay, az, gx, gy, gz;
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    
    // Invert all axes
    ax = -ax;
    ay = -ay;
    az = -az;

    // Calculate Target Angles
    float targetRoll = atan2(ay, az) * 180.0 / PI;
    float targetPitch = atan2(-ax, sqrt(ay * ay + az * az)) * 180.0 / PI;

    // --- The Pro Filter (EMA: Exponential Moving Average) ---
    // Formula: Current = (Target * Alpha) + (Previous * (1 - Alpha))
    float alpha = 0.15f; // Adjustment: 0.01 (very slow) to 1.0 (no filter)

    systemState.roll  = (targetRoll * alpha) + (systemState.roll * (1.0f - alpha));
    systemState.pitch = (targetPitch * alpha) + (systemState.pitch * (1.0f - alpha));
}