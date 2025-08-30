#include <Arduino.h>
#include "es_welcome_menu.h"
#include "es_display_manager.h"

WelcomeMenu::WelcomeMenu() {
    Serial.println("WelcomeMenu created");
}

void WelcomeMenu::show() {
    startTime = millis();
    DisplayManager::getInstance().showWelcome();
}

void WelcomeMenu::update() {
    // nothing to do
}

void WelcomeMenu::onNext() {
    // nothing to do
}

void WelcomeMenu::onValidate() {
    // nothing to do
}
