#include <Arduino.h>
#include "welcome_menu.h"
#include "display_manager.h"
#include "menu_controller.h"

WelcomeMenu::WelcomeMenu() {
    Serial.println("WelcomeMenu created");
}

void WelcomeMenu::show() {
    startTime = millis();
    DisplayManager::getInstance().showWelcome();
}

void WelcomeMenu::update() {
    unsigned long now = millis();
    if (now > startTime + 1000) {
        MenuController::getInstance().setCurrentMenu(MenuController::MenuID::ControllerList);
    }
}

void WelcomeMenu::onNext() {
    // nothing to do
}

void WelcomeMenu::onValidate() {
    // nothing to do
}
