#pragma once
#include <Adafruit_SH110X.h>
#include <lvgl.h>
#include "config.h"

class DisplaySystem {
public:
    static DisplaySystem& getInstance() {
        static DisplaySystem instance;
        return instance;
    }

    void begin();
    void updateUI();
    void setAppMode(AppMode mode);
    void updateFace(float x, float y);
    void updateClimate(float t, float h);
    
    // Public getter for the flush callback
    Adafruit_SH1106G& getRawDisplay() { return display; }

private:
    DisplaySystem() : display(SCREEN_HEIGHT, SCREEN_WIDTH, &Wire) {}
    Adafruit_SH1106G display;
    
    // Screens
    lv_obj_t* screen_face;
    lv_obj_t* screen_climate;
    
    // Widgets
    lv_obj_t* left_eye;
    lv_obj_t* right_eye;
    lv_obj_t* label_temp;
    lv_obj_t* label_hum;

    void createFaceApp();
    void createClimateApp();
};