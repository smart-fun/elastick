#include <Arduino.h>
#include "es_play_menu.h"
#include "es_display_manager.h"
#include "es_menu_controller.h"
#include "es_game_controllers.h"
#include "es_game_controller.h"
#include "es_ble_gamepad_manager.h"

PlayMenu::PlayMenu() {
  Serial.println("PlayMenu created");
}

void PlayMenu::init() {
  Serial.println("PlayMenu::init");
  Serial.printf("Free heap before begin: %u\n", ESP.getFreeHeap());
  BleGamepadManager::getInstance().start();
  Serial.println("begin done");
}

void PlayMenu::deinit() {
  BleGamepadManager::getInstance().stop();
}

void PlayMenu::show() {
  GameController * selected = GameControllers::getInstance().getSelectedController();
  //bleGamepad->deviceName = selected->getName();
  DisplayManager::getInstance().showPlay(isConnected);
}

void PlayMenu::update() {
  bool connected = BleGamepadManager::getInstance().isConnected();
  if (isConnected != connected) {
    isConnected = connected;
    show();
  }
}

void PlayMenu::onNext() {
    // nothing to do
}

void PlayMenu::onValidate() {
  // deinit();
  // MenuController::getInstance().setCurrentMenu(MenuController::MenuID::Action);
}
