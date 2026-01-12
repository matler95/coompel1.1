#pragma once
#include "config.h"

class InputSystem {
public:
    static InputSystem& getInstance() {
        static InputSystem instance;
        return instance;
    }
    void begin();
    void update(); // Reads Button and Potentiometer
private:
    InputSystem() {}
};