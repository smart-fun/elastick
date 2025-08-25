#pragma once
#include <U8g2lib.h>

// Handles all display-related operations, including rendering menus, messages, and controller feedback on the OLED screen.

class DisplayManager {
public:
    DisplayManager(uint8_t sclPin, uint8_t sdaPin);
    void init();
    void showWelcome();
    void showControllerList();
//    void showMenu(const char* options[], int selected);
//    void showMessage(const char* text);
//    void showTestScreen(const ControllerState& state);
//    void update();
private:
    U8G2_SSD1306_128X64_NONAME_F_HW_I2C lcd;
    uint8_t scl;
    uint8_t sda;
};
