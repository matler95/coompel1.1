#include "MotionSystem.h"

void MotionSystem::begin() {
    Wire.begin(I2C_SDA, I2C_SCL);
    mpu.initialize();
}

void MotionSystem::update() {
    int16_t ax, ay, az, gx, gy, gz;
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    float targetRoll = atan2(ay, az) * 180.0 / PI;
    float targetPitch = atan2(-ax, sqrt(ay * ay + az * az)) * 180.0 / PI;

    float alpha = 0.15f;
    systemState.roll = (targetRoll * alpha) + (systemState.roll * (1.0f - alpha));
    systemState.pitch = (targetPitch * alpha) + (systemState.pitch * (1.0f - alpha));
}