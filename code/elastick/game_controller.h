#pragma once
#include <vector>
#include <Arduino.h>
#include "mapping.h"

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
    virtual uint8_t getNbAxis() { return 2; };
    virtual uint8_t getNbButtons() { return 2; };
    virtual float readAxis(uint8_t axisNumber) = 0;
    virtual uint8_t readButton(uint8_t buttonNumber) = 0;
protected:
    GameController(const char* controllerName);
    uint8_t readPinValue(uint8_t plugPin);
    const char* name;
    std::vector<PinConfig> detectionRules;
    std::vector<PinConfig> playRules;
};

class AnalogGameController : public GameController {
public:
    bool isAnalog() const override { return true; }
    uint16_t getChargingDuration(uint8_t axisNumber) { return chargingDuration[axisNumber]; };
protected:
    AnalogGameController(const char* controllerName);
    unsigned long readChargingDuration(uint8_t plugPin, unsigned long timeoutMicros);
    unsigned long readDischargingDuration(uint8_t plugPin, unsigned long timeoutMicros);
    uint16_t chargingDuration[2] = {0, 0};
};

class DigitalGameController : public GameController {
public:
    bool isAnalog() const override { return false; }
protected:
    DigitalGameController(const char* controllerName);
};

