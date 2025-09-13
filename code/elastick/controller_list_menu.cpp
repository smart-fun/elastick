#include "controller_list_menu.h"
#include "display_manager.h"
#include "game_controllers.h"
#include "menu_controller.h"

ControllerListMenu::ControllerListMenu() {
    Serial.println("ControllerListMenu created");
}

void ControllerListMenu::show() {
    DisplayManager::getInstance().showControllerList(selectedIndex);
}

void ControllerListMenu::update() {
    // nothing to do so far
}

void ControllerListMenu::onPrevious() {
    if (selectedIndex > 0) {
        --selectedIndex;
    } else {
        selectedIndex = GameControllers::getInstance().getCount() - 1;
    }
    show();
}

void ControllerListMenu::onNext() {
    selectedIndex = (selectedIndex + 1) % GameControllers::getInstance().getCount();
    show();
}

void ControllerListMenu::onValidate() {
    GameController* selected = GameControllers::getInstance().get(selectedIndex);
    GameControllers::getInstance().setSelectedController(selected);
    //selected->init();
    MenuController::getInstance().setCurrentMenu(MenuController::MenuID::Action);
}
