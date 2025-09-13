#include <Arduino.h>
#include "test_menu.h"
#include "display_manager.h"
#include "menu_controller.h"
#include "game_controllers.h"
#include "game_controller.h"

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

void TestMenu::onPrevious() {
    // nothing to do
}

void TestMenu::onNext() {
    // nothing to do
}

void TestMenu::onValidate() {
    MenuController::getInstance().setCurrentMenu(MenuController::MenuID::Action);
}
