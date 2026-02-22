#pragma once
#include "game_controller.h"

class AmigaMouseController : public DigitalGameController {
public:
    AmigaMouseController();
    AmigaMouseController(const char * name); // for derivated controllers
    void init() override;
    void deinit() override;
    void update() override;
    bool initDetection() override { return false; };
    uint8_t getNbButtons() override { return 3; };
    float readAxis(uint8_t axisNumber) override;
    uint8_t readButton(uint8_t buttonNumber) override;
};
