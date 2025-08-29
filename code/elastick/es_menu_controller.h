#pragma once
#include "es_base_menu.h"
#include "es_welcome_menu.h"
#include "es_controller_list_menu.h"
#include "es_action_menu.h"
#include "es_test_menu.h"
#include "es_play_menu.h"

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
