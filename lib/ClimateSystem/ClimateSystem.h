#pragma once
#include <DHT.h>
#include "config.h"

class ClimateSystem {
public:
    static ClimateSystem& getInstance() {
        static ClimateSystem instance;
        return instance;
    }
    void begin();
    void update();
private:
    ClimateSystem() : dht(PIN_DHT, DHT11) {}
    DHT dht;
};