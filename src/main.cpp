#include "config.h"
#include "MotionSystem.h"
#include "DisplaySystem.h"
#include "ClimateSystem.h"

DeviceState systemState = {0,0,0,0,0,false,AppMode::FACE};

void taskSensors(void* pv) {
    for(;;) {
        MotionSystem::getInstance().update();
        ClimateSystem::getInstance().update();
        
        int pot = analogRead(PIN_POTENTIOMETER);
        systemState.potValue = pot;
        AppMode newMode = (pot > 2048) ? AppMode::CLIMATE : AppMode::FACE;
        
        if(newMode != systemState.currentMode) {
            systemState.currentMode = newMode;
            DisplaySystem::getInstance().setAppMode(newMode);
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void taskUI(void* pv) {
    for(;;) {
        DisplaySystem::getInstance().updateFace(systemState.roll, systemState.pitch);
        DisplaySystem::getInstance().updateClimate(systemState.temp, systemState.hum);
        DisplaySystem::getInstance().updateUI();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void setup() {
    Serial.begin(115200);
    MotionSystem::getInstance().begin();
    ClimateSystem::getInstance().begin();
    DisplaySystem::getInstance().begin();

    xTaskCreate(taskSensors, "Sensors", 4096, NULL, 2, NULL);
    xTaskCreate(taskUI, "UI", 8192, NULL, 1, NULL);
}

void loop() { vTaskDelete(NULL); }