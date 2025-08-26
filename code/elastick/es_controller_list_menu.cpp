#include "es_controller_list_menu.h"
#include "es_display_manager.h"
#include "es_game_controllers.h"
//#include "es_menu_controller.h"

ControllerListMenu::ControllerListMenu() {
}

void ControllerListMenu::show() {
    DisplayManager::getInstance().showControllerList(selectedIndex);
}

void ControllerListMenu::onNext() {
    selectedIndex = (selectedIndex + 1) % GameControllers::getInstance().getCount();
    show();
}

void ControllerListMenu::onValidate() {
    GameController* selected = GameControllers::getInstance().get(selectedIndex);
    //selected->init();
    //MenuController::get().setCurrentMenu(MenuController::MenuID::TestMenu); // or CalibrationMenu
}
