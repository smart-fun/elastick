#include <Arduino.h>
#include "es_welcome_menu.h"
#include "es_display_manager.h"
#include "es_menu_controller.h"

WelcomeMenu::WelcomeMenu() {
}

void WelcomeMenu::show() {
    startTime = millis();
    DisplayManager::getInstance().showWelcome();
}

void WelcomeMenu::update() {
    unsigned long now = millis();
    if (now > startTime + 2000) {
      onNext();
    }
}

void WelcomeMenu::onNext() {
    MenuController::getInstance().setCurrentMenu(MenuController::MenuID::ControllerList);
}

void WelcomeMenu::onValidate() {
    // nothing to do
}
