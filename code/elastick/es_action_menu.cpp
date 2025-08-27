#include "es_action_menu.h"
#include "es_display_manager.h"
#include "es_game_controllers.h"
//#include "es_menu_controller.h"

ActionMenu::ActionMenu() {
}

void ActionMenu::show() {
    GameController* selected = GameControllers::getInstance().getSelectedController();
    DisplayManager::getInstance().showActions(selected, actionIndex);
}

void ActionMenu::update() {
    // nothing to do so far
}

void ActionMenu::onNext() {
    //selectedIndex = (selectedIndex + 1) % GameControllers::getInstance().getCount();
    //show();
}

void ActionMenu::onValidate() {
    //GameController* selected = GameControllers::getInstance().get(selectedIndex);
    //selected->init();
    //MenuController::get().setCurrentMenu(MenuController::MenuID::TestMenu); // or CalibrationMenu
}
