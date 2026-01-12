#include "config.h"
#include "MotionSystem.h"
#include "DisplaySystem.h"
#include "InputSystem.h"
#include "FeedbackSystem.h"

// Define the global state
DeviceState systemState = {0.0f, 0.0f, false};

void taskInput(void* pv) {
    bool lastButtonState = false;

    for(;;) {
        InputSystem::getInstance().update();

        // Edge Detection: Trigger only when button goes from HIGH to LOW
        if (systemState.buttonPressed && !lastButtonState) {
            FeedbackSystem::getInstance().playClick();
        }
        lastButtonState = systemState.buttonPressed;

        vTaskDelay(pdMS_TO_TICKS(20)); 
    }
}

void taskMotion(void* pv) {
    for(;;) {
        MotionSystem::getInstance().update();
        vTaskDelay(pdMS_TO_TICKS(20)); // 50Hz Update rate
    }
}

void taskDisplay(void* pv) {
    for(;;) {
        // Draw face based on current sensor state
        DisplaySystem::getInstance().drawFace(systemState.roll, systemState.pitch);
        vTaskDelay(pdMS_TO_TICKS(33)); // ~30 FPS
    }
}

void setup() {
    Serial.begin(115200);
    
    // Init Managers
    MotionSystem::getInstance().begin();
    DisplaySystem::getInstance().begin();
    InputSystem::getInstance().begin();

    // Create Tasks
    xTaskCreate(taskMotion,  "Motion", 2048, NULL, 2, NULL);
    xTaskCreate(taskInput,   "Input",  2048, NULL, 2, NULL);
    xTaskCreate(taskDisplay, "Display", 4096, NULL, 1, NULL); 
}

void loop() { vTaskDelete(NULL); } // Deletes the setup task to free RAM