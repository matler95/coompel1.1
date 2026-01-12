#include "InputSystem.h"

void InputSystem::begin() {
    pinMode(PIN_BUTTON_A, INPUT_PULLUP);
    // Pin 0 (Potentiometer) is analog by default on C3
}

void InputSystem::update() {
    systemState.buttonPressed = (digitalRead(PIN_BUTTON_A) == LOW);

    // Read Pot (0-4095) and map to reasonable eye height (5 to 30 pixels)
    int rawPot = analogRead(PIN_POTENTIOMETER);
    systemState.eyeSize = map(rawPot, 0, 4095, 5, 30);
}