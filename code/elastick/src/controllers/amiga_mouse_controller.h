#pragma once
#include "mouse_controller.h"

class AmigaMouseController : public MouseController {
public:
    AmigaMouseController();
    AmigaMouseController(const char * name); // for derivated controllers
    void init() override;
    void deinit() override;
    void update() override;
protected:
    void getMouseDirectionPins(uint8_t &x1Pin, uint8_t &x2Pin, uint8_t &y1Pin, uint8_t &y2Pin) override;
    void getMouseButtonPins(uint8_t &button1Pin, uint8_t &button2Pin, uint8_t &button3Pin) override;
};
