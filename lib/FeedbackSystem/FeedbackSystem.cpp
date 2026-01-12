#include "FeedbackSystem.h"

void FeedbackSystem::begin() {
    pinMode(PIN_BUZZER, OUTPUT);
}

void FeedbackSystem::playClick() {
    digitalWrite(PIN_BUZZER, HIGH);
    delay(5); // Non-blocking enough for a tiny click
    digitalWrite(PIN_BUZZER, LOW);
}