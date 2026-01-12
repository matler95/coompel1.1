#pragma once
#include <Adafruit_SH110X.h>
#include "config.h"

class DisplaySystem {
public:
    static DisplaySystem& getInstance() {
        static DisplaySystem instance;
        return instance;
    }
    void begin();
    void drawFace(float offsetX, float offsetY);
private:
    DisplaySystem() : display(SCREEN_HEIGHT, SCREEN_WIDTH, &Wire) {}
    Adafruit_SH1106G display;
};