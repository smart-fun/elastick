#include "action_menu.h"
#include "display_manager.h"
#include "game_controllers.h"
#include "game_controller.h"
#include "menu_controller.h"

ActionMenu::ActionMenu() {
    actionItems.reserve(4);
    Serial.println("ActionMenu created");
}

void ActionMenu::init() {

}

void ActionMenu::deinit() {
    GameController* controller = GameControllers::getInstance().getSelectedController();
    controller->deinit();
}

void ActionMenu::show() {
    GameController* selected = GameControllers::getInstance().getSelectedController();
    if (actionState == ActionState::DetectController) {
        if (selected->initDetection()) {
            DisplayManager::getInstance().showDetecting(selected);
            delay(500);
        } else {
            actionState = ActionState::DisplayMenu;
            show();
        }
    } else {
        actionItems.clear();
        actionItems.push_back(&actionBack);
        actionItems.push_back(&actionPlay);
        if (selected->isAnalog()) {
            actionItems.push_back(&actionCalibrate);
        }
        actionItems.push_back(&actionTest);
        DisplayManager::getInstance().showActions(selected->getName(), actionItems, actionIndex);
    }
}

void ActionMenu::update() {

    switch(actionState) {
        case ActionState::DetectController:
        {
            GameController* selected = GameControllers::getInstance().getSelectedController();
            if (selected->isDetected()) {
                actionState = ActionState::DisplayMenu;
                show();
            } else {
                delay(1000);
            }
        }
        break;
        case ActionState::DisplayMenu:
        {

        }
        break;
    }
}

void ActionMenu::onPrevious() {
    if (actionIndex > 0) {
        --actionIndex;
    } else {
        actionIndex = actionItems.size() - 1;
    }
    show();
}

void ActionMenu::onNext() {
    actionIndex = (actionIndex + 1) % actionItems.size();
    show();
}

void ActionMenu::onValidate() {
    ActionItem * item = actionItems[actionIndex];
    Action action = item->action;
    const char * name = item->displayName;
    Serial.print(name);
    Serial.println(" selected!");
    if (action == Action::PLAY) {
        GameController* controller = GameControllers::getInstance().getSelectedController();
        controller->init();
        MenuController::getInstance().setCurrentMenu(MenuController::MenuID::Play);
    } else if (action == Action::TEST) {
        GameController* controller = GameControllers::getInstance().getSelectedController();
        controller->init();
        MenuController::getInstance().setCurrentMenu(MenuController::MenuID::Test);
    } else if (action == Action::BACK) {
        deinit();
        MenuController::getInstance().setCurrentMenu(MenuController::MenuID::ControllerList);
    }
}
