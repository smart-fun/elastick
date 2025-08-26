#pragma once
#include "es_base_menu.h"

class ControllerListMenu;

class MenuController {
public:
    enum class MenuID {
        Welcome,
        ControllerList,
    };

    static MenuController& getInstance();

    void init();
    void update();
    void setCurrentMenu(MenuID id);

private:
    MenuController();
    BaseMenu* currentMenu = nullptr;

    // Menu Instances
    // WelcomeMenu * welcomeMenu = nullptr;
    ControllerListMenu * controllerListMenu = nullptr;
};
