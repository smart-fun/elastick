#pragma once
#include "WelcomeMenu.h"
#include "ActionMenu.h"
#include "TestMenu.h"
#include "PlayMenu.h"
#include "CategoryMenu.h"
#include "JoystickMenu.h"
#include "MouseMenu.h"
#include "PaddleMenu.h"

class MenuController {
public:
    enum class MenuID {
        Welcome,
        Category,
        JoystickList,
        MouseList,
        PaddleList,
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
    JoystickMenu joystickMenu;
    MouseMenu mouseMenu;
    PaddleMenu paddleMenu;
    ActionMenu actionMenu;
    TestMenu testMenu;
    PlayMenu playMenu;
};
