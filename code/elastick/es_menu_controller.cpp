
#include "es_menu_controller.h"
#include "es_input_button.h"
#include "es_display_manager.h"
#include "es_welcome_menu.h"
#include "es_controller_list_menu.h"

MenuController& MenuController::getInstance() {
    static MenuController instance;
    return instance;
}

MenuController::MenuController() {
  welcomeMenu = new WelcomeMenu();
  controllerListMenu = new ControllerListMenu();
}

void MenuController::init() {
    setCurrentMenu(MenuID::ControllerList);
}

void MenuController::setCurrentMenu(MenuID id) {
    switch (id) {
        case MenuID::Welcome:
            currentMenu = welcomeMenu;
            currentMenu->show();
            break;
        case MenuID::ControllerList:
            currentMenu = controllerListMenu;
            currentMenu->show();
            break;
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
