
#include "es_menu_controller.h"
#include "es_input_button.h"
#include "es_display_manager.h"

MenuController& MenuController::getInstance() {
    static MenuController instance;
    return instance;
}

MenuController::MenuController(){
    Serial.println("MenuController created");
}

void MenuController::init() {
    setCurrentMenu(MenuID::ControllerList);
}

void MenuController::setCurrentMenu(MenuID id) {
    switch (id) {
        case MenuID::Welcome:
            currentMenu = &welcomeMenu;
            break;
        case MenuID::ControllerList:
            currentMenu = &controllerListMenu;
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
    }
    if (currentMenu) {
        currentMenu->init();
        currentMenu->show();
    }
}

void MenuController::update() {
    InputButtons::getInstance().update();
    currentMenu->update();
    if (InputButtons::getInstance().wasPressed(InputButtonName::Next)) {
        currentMenu->onNext();
        currentMenu->show();
    }
    if (InputButtons::getInstance().wasPressed(InputButtonName::Validate)) {
        currentMenu->onValidate();
        currentMenu->show();
    }

    
}
