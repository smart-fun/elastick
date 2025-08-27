#pragma once
#include <Arduino.h>

struct Detection {
    uint8_t db9Pin;
    uint8_t mode;   // INPUT_PULLUP, OUTPUT...
    uint8_t value;  // to set or attended
};

class GameController {
public:
    virtual void init() = 0;
    virtual void update() = 0;
    const char* getName() const;
    virtual bool isAnalog() const = 0;
    virtual void initDetection();
    bool isDetected();
protected:
    GameController(const char* controllerName);
    const char* name;
    std::vector<Detection> detectionRules;
};


