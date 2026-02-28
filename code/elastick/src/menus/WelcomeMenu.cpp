#include <Arduino.h>
#include "WelcomeMenu.h"
#include "DisplayManager.h"
#include "MenuController.h"

WelcomeMenu::WelcomeMenu() {
    Serial.println("WelcomeMenu created");
}

void WelcomeMenu::show() {
    startTime = millis();
    DisplayManager::getInstance().showWelcome();
}

void WelcomeMenu::update() {
    unsigned long now = millis();
    if (now > startTime + 2000) {
        MenuController::getInstance().setCurrentMenu(MenuController::MenuID::Category);
    }
}

void WelcomeMenu::onPrevious() {
    // nothing to do
}

void WelcomeMenu::onNext() {
    // nothing to do
}

void WelcomeMenu::onValidate() {
    // nothing to do
}
