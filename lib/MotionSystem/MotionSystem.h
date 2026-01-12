#pragma once
#include <MPU6050.h>
#include "config.h"

class MotionSystem {
public:
    static MotionSystem& getInstance() {
        static MotionSystem instance;
        return instance;
    }
    void begin();
    void update(); // Reads raw data and converts to degrees
private:
    MotionSystem() {}
    MPU6050 mpu;
};