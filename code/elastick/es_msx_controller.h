#pragma once
#include "es_game_controller.h"

class MSXGameController : public GameController {
public:
    MSXGameController();
    void init() override;
    void update() override;
    bool isAnalog() const override { return true; };
    bool initDetection() override { return false; };
    float readAxis(uint8_t axisNumber) override;
    uint8_t readButton(uint8_t buttonNumber) override;
};
