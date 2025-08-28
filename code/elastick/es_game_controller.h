#pragma once
#include <Arduino.h>
#include "es_mapping.h"

class GameController {
public:
    virtual void init();
    virtual void update() = 0;
    const char* getName() const;
    virtual bool isAnalog() const = 0;
    virtual bool initDetection();
    bool isDetected();
    void logPinValues();
protected:
    GameController(const char* controllerName);
    const char* name;
    std::vector<PinConfig> detectionRules;
    std::vector<PinConfig> playRules;
};
