#include "es_controller_list_menu.h"
#include "es_display_manager.h"
#include "es_game_controllers.h"
#include "es_menu_controller.h"

ControllerListMenu::ControllerListMenu() {
    Serial.println("ControllerListMenu created");
}

void ControllerListMenu::show() {
    DisplayManager::getInstance().showControllerList(selectedIndex);
}

void ControllerListMenu::update() {
    // nothing to do so far
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
