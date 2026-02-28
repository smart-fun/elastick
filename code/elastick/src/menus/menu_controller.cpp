
#include "menu_controller.h"
#include "input_button.h"
#include "input_rotary.h"
#include "display_manager.h"

MenuController& MenuController::getInstance() {
    static MenuController instance;
    return instance;
}

MenuController::MenuController(){
    Serial.println("MenuController created");
}

void MenuController::init() {
    setCurrentMenu(MenuID::Welcome);
}

void MenuController::setCurrentMenu(MenuID id) {
    currentMenu = nullptr;
    switch (id) {
        case MenuID::Welcome:
            currentMenu = &welcomeMenu;
            break;
        case MenuID::Action:
            currentMenu = &actionMenu;
            break;
        case MenuID::Test:
            currentMenu = &testMenu;
            break;
        case MenuID::Play:
            currentMenu = &playMenu;
            break;
        case MenuID::Category:
            currentMenu = &categoryMenu;
            break;
        case MenuID::JoystickList:
            currentMenu = &joystickMenu;
            break;
        case MenuID::MouseList:
            currentMenu = &mouseMenu;
            break;
        case MenuID::PaddleList:
            currentMenu = &paddleMenu;
            break;
    }
    if (currentMenu) {
        currentMenu->init();
        currentMenu->show();
    } else {
        Serial.println("Err MenuController::setCurrentMenu is null");
    }
}

void MenuController::update() {
    InputButtons::getInstance().update();
    currentMenu->update();
    int rotation = InputRotary::getInstance().getDeltaRotation();
    if (rotation < 0) {
        currentMenu->onPrevious();
        currentMenu->show();
    } else if (rotation > 0) {
        currentMenu->onNext();
        currentMenu->show();
    }
    if (InputButtons::getInstance().wasPressed(InputButtonName::Validate)) {
        currentMenu->onValidate();
        currentMenu->show();
    }

    
}
