#include "es_action_menu.h"
#include "es_display_manager.h"
#include "es_game_controllers.h"
#include "es_game_controller.h"
#include "es_menu_controller.h"
//#include "es_test_menu.h"

ActionMenu::ActionMenu() {
    actionItems.reserve(3);
    Serial.println("ActionMenu created");
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
        actionItems.push_back({Action::PLAY, "PLAY"});
        if (selected->isAnalog()) {
            actionItems.push_back({Action::CALIBRATE, "CALIBRATE"});
        }
        actionItems.push_back({Action::TEST, "TEST"});
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
        // case ActionState::Play:
        // {
        //     GameController* selected = GameControllers::getInstance().getSelectedController();
        //     Serial.println("**********");
        //     selected->logPinValues();
        //     delay(1000);
        // }
        // break;
        // case ActionState::Test:
        // {
        //     GameController* selected = GameControllers::getInstance().getSelectedController();
        //     DisplayManager::getInstance().showTest(selected);
            // Serial.println("**********");
            // float x = selected->readAxis(0);
            // float y = selected->readAxis(1);
            // uint8_t b1 = selected->readButton(0);
            // uint8_t b2 = selected->readButton(1);
            // Serial.print("X=");
            // Serial.print(x);
            // Serial.print(", Y=");
            // Serial.print(y);
            // Serial.print(", B1=");
            // Serial.print(b1);
            // Serial.print(", B2=");
            // Serial.println(b2);
            // delay(500);
        // }
        // break;
    }
}

void ActionMenu::onNext() {
    actionIndex = (actionIndex + 1) % GameControllers::getInstance().getCount();
    show();
}

void ActionMenu::onValidate() {
    ActionItem & item = actionItems[actionIndex];
    Action action = item.action;
    const char * name = item.displayName;
    Serial.print(name);
    Serial.println(" selected!");
    if (action == Action::PLAY) {
        GameController* selected = GameControllers::getInstance().getSelectedController();
        selected->init();
        MenuController::getInstance().setCurrentMenu(MenuController::MenuID::Play);
    } else if (action == Action::TEST) {
        GameController* selected = GameControllers::getInstance().getSelectedController();
        selected->init();
        MenuController::getInstance().setCurrentMenu(MenuController::MenuID::Test);
    }
}
