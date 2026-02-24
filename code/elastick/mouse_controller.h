#pragma once

#include "game_controller.h"

class MouseController : public DigitalGameController {
  public:
    void init() override;
    void deinit() override;
    bool initDetection() override { return false; };
    uint8_t getNbButtons() override { return 3; };
    float readAxis(uint8_t axisNumber) override;
    uint8_t readButton(uint8_t buttonNumber) override;

  protected:
    MouseController(const char* controllerName);
    virtual void getMouseDirectionPins(uint8_t &x1Pin, uint8_t &x2Pin, uint8_t &y1Pin, uint8_t &y2Pin) = 0;
    virtual void getMouseButtonPins(uint8_t &button1Pin, uint8_t &button2Pin, uint8_t &button3Pin) = 0;
  private:
    uint8_t button1Pin;
    uint8_t button2Pin;
    uint8_t button3Pin;
};
