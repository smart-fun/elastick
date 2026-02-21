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
  BleGamepadManager::getInstance().start(controller->getName(), controller->getNbAxis(), controller->getNbButtons());
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
    controller->update();
    // send Buttons
    for(uint8_t button = 0; button < controller->getNbButtons(); ++button) {
      uint8_t value = controller->readButton(button);
      BleGamepadManager::getInstance().sendButtonValue(button, value);
    }
    // send Axis
    for(uint8_t axis = 0; axis < controller->getNbAxis(); ++axis) {
      float value = controller->readAxis(axis);
      bool isVerticalAxis = (axis & 1);
      BleGamepadManager::getInstance().sendAxisValue(axis, isVerticalAxis ? -value : value);
    }
  }
}
void PlayMenu::onPrevious() {
    // nothing to do
}

void PlayMenu::onNext() {
    // nothing to do
}

void PlayMenu::onValidate() {
  deinit();
  MenuController::getInstance().setCurrentMenu(MenuController::MenuID::Action);
}
