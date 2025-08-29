#pragma once
#include "es_game_controller.h"

class Apple2GameController : public GameController {
public:
    Apple2GameController();
    void init() override;
    void update() override;
    bool isAnalog() const override { return true; };
    bool initDetection() override;
    float readAxis(uint8_t axisNumber) override { return 0.f;};
    uint8_t readButton(uint8_t buttonNumber) override {return 0;};
};

