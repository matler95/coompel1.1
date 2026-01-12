#include "ClimateSystem.h"

void ClimateSystem::begin() {
    dht.begin();
}

void ClimateSystem::update() {
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    
    if (!isnan(h) && !isnan(t)) {
        systemState.hum = h;
        systemState.temp = t;
    }
}