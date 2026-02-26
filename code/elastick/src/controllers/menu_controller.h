#pragma once
#include "base_menu.h"
#include "welcome_menu.h"
#include "controller_list_menu.h"
#include "action_menu.h"
#include "test_menu.h"
#include "play_menu.h"

class MenuController {
public:
    enum class MenuID {
        Welcome,
        ControllerList,
        Action,
        Test,
        Play
    };

    static MenuController& getInstance();

    void init();
    void update();
    void setCurrentMenu(MenuID id);

private:
    MenuController();
    BaseMenu* currentMenu = nullptr;

    // Menu Instances
    WelcomeMenu welcomeMenu;
    ControllerListMenu controllerListMenu;
    ActionMenu actionMenu;
    TestMenu testMenu;
    PlayMenu playMenu;
};
