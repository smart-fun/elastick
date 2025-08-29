#include <Arduino.h>
#include "es_test_menu.h"
#include "es_display_manager.h"
#include "es_menu_controller.h"
#include "es_game_controllers.h"
#include "es_game_controller.h"

TestMenu::TestMenu() {
  Serial.println("TestMenu created");
}

void TestMenu::show() {
  GameController * selected = GameControllers::getInstance().getSelectedController();
  DisplayManager::getInstance().showTest(selected);
}

void TestMenu::update() {
  show();
}

void TestMenu::onNext() {
    // nothing to do
}

void TestMenu::onValidate() {
    MenuController::getInstance().setCurrentMenu(MenuController::MenuID::Action);
}
