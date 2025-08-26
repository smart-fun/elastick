#pragma once
#include <U8g2lib.h>
#include "es_gpio.h"

// Handles all display-related operations, including rendering menus, messages, and controller feedback on the OLED screen.

class DisplayManager {
public:
    static DisplayManager& getInstance();
    void init();
    void showWelcome();
    void showControllerList(int currentIndex);
private:
    DisplayManager();
    U8G2_SSD1306_128X64_NONAME_F_HW_I2C lcd = U8G2_SSD1306_128X64_NONAME_F_HW_I2C(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ ES_GPIO_SCL, /* data=*/ ES_GPIO_SDA);
};
