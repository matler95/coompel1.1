#include "DisplaySystem.h"

void DisplaySystem::begin() {
    display.begin(SCREEN_ADDRESS, true);
    display.clearDisplay();
    display.display();
}

void DisplaySystem::drawFace(float offsetX, float offsetY) {
    display.clearDisplay();

    // 1. Calculate Eye Movement
    int moveX = constrain(offsetX / 2, -15, 15);
    int moveY = constrain(offsetY / 2, -10, 10);

    // 2. Determine Eye Height (Blink logic)
    // If button is pressed, height is 2 (shut), otherwise use systemState.eyeSize
    int eyeH = systemState.buttonPressed ? 2 : systemState.eyeSize;

    // 3. Draw Left Eye
    display.fillRoundRect(30 + moveX, 30 + moveY - (eyeH/2), 20, eyeH, 4, SH110X_WHITE);
    
    // 4. Draw Right Eye
    display.fillRoundRect(78 + moveX, 30 + moveY - (eyeH/2), 20, eyeH, 4, SH110X_WHITE);

    display.display();
}