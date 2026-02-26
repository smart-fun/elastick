#pragma once
#include "game_controller.h"

class AtariJoystickController : public DigitalGameController {
public:
    AtariJoystickController();
    AtariJoystickController(const char * name); // for derivated controllers
    void init() override;
    void update() override;
    bool initDetection() override { return false; };
    float readAxis(uint8_t axisNumber) override;
    uint8_t readButton(uint8_t buttonNumber) override;
};

class AmigaJoystickController : public AtariJoystickController {
public:
    AmigaJoystickController();
};

class C64JoystickController : public AtariJoystickController {
public:
    C64JoystickController();
};

class AmstradJoystickController : public AtariJoystickController {
public:
    AmstradJoystickController();
};