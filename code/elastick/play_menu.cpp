#include <Arduino.h>
#include "play_menu.h"
#include "display_manager.h"
#include "menu_controller.h"
#include "game_controllers.h"
#include "game_controller.h"
#include "ble_gamepad_manager.h"

PlayMenu::PlayMenu() {
  Serial.println("PlayMenu created");
}

void PlayMenu::init() {
  Serial.println("PlayMenu::init");
  GameController * controller = GameControllers::getInstance().getSelectedController();
  BleGamepadManager::getInstance().start(controller->getName());
}

void PlayMenu::deinit() {
  BleGamepadManager::getInstance().stop();
}

void PlayMenu::show() {
  DisplayManager::getInstance().showPlay(isConnected);
}

void PlayMenu::update() {
  bool connected = BleGamepadManager::getInstance().isConnected();
  if (isConnected != connected) {
    isConnected = connected;
    show();
  }
  if (connected) {
    GameController * controller = GameControllers::getInstance().getSelectedController();
    uint8_t b1 = controller->readButton(0);
    uint8_t b2 = controller->readButton(1);
    float x = controller->readAxis(0);
    float y = controller->readAxis(1);
    BleGamepadManager::getInstance().sendValues(b1, b2, x, -y);
  }
}

void PlayMenu::onNext() {
    // nothing to do
}

void PlayMenu::onValidate() {
  deinit();
  MenuController::getInstance().setCurrentMenu(MenuController::MenuID::Action);
}
