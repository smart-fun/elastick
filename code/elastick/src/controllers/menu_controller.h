#pragma once
#include "base_menu.h"
#include "welcome_menu.h"
#include "controller_list_menu.h"
#include "action_menu.h"
#include "test_menu.h"
#include "play_menu.h"
#include "ListMenu.h"
#include "JoystickMenu.h"

class MenuController {
public:
    enum class MenuID {
        Welcome,
        Category,
        ControllerList,
        JoystickList,
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
    CategoryMenu categoryMenu;
    ControllerListMenu controllerListMenu;
    ActionMenu actionMenu;
    TestMenu testMenu;
    PlayMenu playMenu;
    JoystickMenu joystickMenu;
};
