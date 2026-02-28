#pragma once
#include <vector>
#include <U8g2lib.h>
#include "gpio.h"

// Handles all display-related operations, including rendering menus, messages, and controller feedback on the OLED screen.

class GameController;
class ActionItem;
class MenuItem;

class DisplayManager {
public:
    static DisplayManager& getInstance();
    void init();
    void clear();
    void showWelcome();
    void showList(const char * title, const std::vector<MenuItem*> &list, int currentIndex);
    //void showDetecting(GameController * controller);
    // void showActions(const char * menuName, std::vector<ActionItem*> & actionItems, int actionIndex);
    void showTest(GameController * controller);
    void showPlay(GameController * controller, bool connected);
private:
    DisplayManager();
    U8G2_SSD1306_128X64_NONAME_F_HW_I2C lcd = U8G2_SSD1306_128X64_NONAME_F_HW_I2C(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ ES_GPIO_SCL, /* data=*/ ES_GPIO_SDA);
    void printTitle(const char * title);
    void printCenterX(const char * text, int y);
    void printCenterXY(const char * text);
};
