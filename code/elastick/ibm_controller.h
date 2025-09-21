#pragma once
#include "game_controller.h"

class IBMGameController : public GameController {
public:
    IBMGameController();
    void init() override;
    void update() override;
    bool isAnalog() const override { return true; };
    bool initDetection() override { return false; };
    virtual uint8_t getNbAxis() { return 2; };
    virtual uint8_t getNbButtons() { return 2; };
    float readAxis(uint8_t axisNumber) override;
    uint8_t readButton(uint8_t buttonNumber) override;
};
