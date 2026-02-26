#pragma once
#include "game_controller.h"

class Apple2GameController : public AnalogGameController {
public:
    Apple2GameController();
    void init() override;
    void update() override;
    bool initDetection() override;
    float readAxis(uint8_t axisNumber) override;
    uint8_t readButton(uint8_t buttonNumber) override;
};

