#include "InputSystem.h"

void InputSystem::begin() {
    pinMode(PIN_BUTTON_A, INPUT_PULLUP);
}

void InputSystem::update() {
    systemState.buttonPressed = (digitalRead(PIN_BUTTON_A) == LOW);
    systemState.potValue = analogRead(PIN_POTENTIOMETER);
}