#pragma once
#include "game_controller.h"

class AtariPaddleGameController : public AnalogGameController {
public:
    AtariPaddleGameController();
    void init() override;
    void update() override;
    bool initDetection() override { return false; };
    virtual uint8_t getNbAxis() { return 2; };
    virtual uint8_t getNbButtons() { return 2; };
    float readAxis(uint8_t axisNumber) override;
    uint8_t readButton(uint8_t buttonNumber) override;

};

