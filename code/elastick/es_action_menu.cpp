#include "es_action_menu.h"
#include "es_display_manager.h"
#include "es_game_controllers.h"
#include "es_game_controller.h"
//#include "es_menu_controller.h"

ActionMenu::ActionMenu() {
}

void ActionMenu::show() {
    GameController* selected = GameControllers::getInstance().getSelectedController();
    if (actionState == ActionState::DetectController) {
        DisplayManager::getInstance().showDetecting(selected);
        selected->initDetection();
        delay(500);
    } else {
        DisplayManager::getInstance().showActions(selected, actionIndex);
    }
}

void ActionMenu::update() {
    if (actionState == ActionState::DetectController) {
        GameController* selected = GameControllers::getInstance().getSelectedController();
        if (selected->isDetected()) {
            actionState = ActionState::DisplayMenu;
            show();
        }
    }
}

void ActionMenu::onNext() {
    //selectedIndex = (selectedIndex + 1) % GameControllers::getInstance().getCount();
    //show();
}

void ActionMenu::onValidate() {
    //MenuController::getInstance().setCurrentMenu(MenuController::MenuID::TestMenu); // or CalibrationMenu
}
