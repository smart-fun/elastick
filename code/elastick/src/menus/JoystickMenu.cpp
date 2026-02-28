#include <Arduino.h>
#include "JoystickMenu.h"
#include "game_controllers.h"

JoystickMenu::JoystickMenu()
    :ListMenu() {
    Serial.println("JoystickMenu created");
    list.clear();
    list.reserve(16);

    list.push_back(new MenuItem(MenuAction::START_CATEGORY_MENU, ".."));    // Back

    GameControllers & gc = GameControllers::getInstance();
    int nbControllers = gc.getCount();
    for(int i=0; i<nbControllers; ++i) {
        GameController * controller = gc.get(i);
        if (controller->getCategory() == ControllerCategory::JOY) {
            list.push_back(new MenuItem(ControllerCategory::JOY, controller->getName()));
        }
    }
}

const char * JoystickMenu::getTitle() {
    return "STICKS & PADS";
}
