#pragma once
#include <Arduino.h>
#include "es_mapping.h"

class GameController {
public:
    virtual void init();
    virtual void deinit();
    virtual void update() = 0;
    const char* getName() const;
    virtual bool isAnalog() const = 0;
    virtual bool initDetection();
    bool isDetected();
    void logPinValues();
    virtual float readAxis(uint8_t axisNumber) = 0;
    virtual uint8_t readButton(uint8_t buttonNumber) = 0;
protected:
    GameController(const char* controllerName);
    uint8_t readPinValue(uint8_t plugPin);
    unsigned long readChargingDuration(uint8_t plugPin, unsigned long timeoutMicros);
    unsigned long readDischargingDuration(uint8_t plugPin, unsigned long timeoutMicros);
    const char* name;
    std::vector<PinConfig> detectionRules;
    std::vector<PinConfig> playRules;
};
