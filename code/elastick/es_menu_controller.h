#pragma once
#include "es_base_menu.h"

class WelcomeMenu;
class ControllerListMenu;
class ActionMenu;
class TestMenu;

class MenuController {
public:
    enum class MenuID {
        Welcome,
        ControllerList,
        Action,
        Test
    };

    static MenuController& getInstance();

    void init();
    void update();
    void setCurrentMenu(MenuID id);

private:
    MenuController();
    BaseMenu* currentMenu = nullptr;

    // Menu Instances
    WelcomeMenu * welcomeMenu = nullptr;
    ControllerListMenu * controllerListMenu = nullptr;
    ActionMenu * actionMenu = nullptr;
    TestMenu * testMenu = nullptr;
};
