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
        if (selected->initDetection()) {
            DisplayManager::getInstance().showDetecting(selected);
            delay(500);
        } else {
            actionState = ActionState::DisplayMenu;
            show();
        }
    } else {
        actionItems.reserve(3);
        actionItems.clear();
        actionItems.push_back(new ActionItem{Action::PLAY, "PLAY"});
        if (selected->isAnalog()) {
            actionItems.push_back(new ActionItem{Action::CALIBRATE, "CALIBRATE"});
        }
        actionItems.push_back(new ActionItem{Action::TEST, "TEST"});
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
        case ActionState::Play:
        {
            GameController* selected = GameControllers::getInstance().getSelectedController();
            Serial.println("**********");
            selected->logPinValues();
            delay(1000);
        }
        break;
    }
}

void ActionMenu::onNext() {
    actionIndex = (actionIndex + 1) % GameControllers::getInstance().getCount();
    show();
}

void ActionMenu::onValidate() {
    ActionItem * item = actionItems[actionIndex];
    Action action = item->action;
    const char * name = item->displayName;
    Serial.print(name);
    Serial.println(" selected!");
    if (action == Action::PLAY) {
        GameController* selected = GameControllers::getInstance().getSelectedController();
        selected->init();
        actionState = ActionState::Play;
    }
    //MenuController::getInstance().setCurrentMenu(MenuController::MenuID::TestMenu);
}
