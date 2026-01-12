#pragma once
#include "config.h"

class FeedbackSystem {
public:
    static FeedbackSystem& getInstance() {
        static FeedbackSystem instance;
        return instance;
    }
    void begin();
    void playClick();
private:
    FeedbackSystem() {}
};