#pragma once
#include "game_controller.h"

class AtariJoystickController : public DigitalGameController {
public:
    AtariJoystickController();
    void init() override;
    void update() override;
    bool initDetection() override { return false; };
    float readAxis(uint8_t axisNumber) override;
    uint8_t readButton(uint8_t buttonNumber) override;
};
