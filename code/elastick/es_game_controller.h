#pragma once
#include <Arduino.h>

class GameController {
public:
    virtual void init() = 0;
    virtual void update() = 0;
    const char* getName() const;
    virtual bool isAnalog() const = 0;
    virtual void initDetection() = 0;
    virtual bool isDetected() = 0;
protected:
    GameController(const char* controllerName);
    const char* name;
};

