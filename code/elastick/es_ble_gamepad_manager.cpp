#include "es_ble_gamepad_manager.h"

const uint16_t MAX_PAD_VALUE = 10000;

BleGamepadManager::BleGamepadManager()
: bleGamepad("Elastick Joy", "Elastick", 100) {
  Serial.println("BleGamepadManager created");
}

void BleGamepadManager::start() {
  config.setAutoReport(true);
  config.setControllerType(CONTROLLER_TYPE_JOYSTICK); // or CONTROLLER_TYPE_GAMEPAD
  config.setButtonCount(2);
  config.setIncludeXAxis(true);
  config.setIncludeYAxis(true);
  config.setIncludeZAxis(false);
  config.setIncludeRxAxis(false);
  config.setIncludeRyAxis(false);
  config.setIncludeRzAxis(false);
  config.setIncludeSlider1(false);
  config.setIncludeSlider2(false);
  config.setHatSwitchCount(0);
  config.setAxesMin(-MAX_PAD_VALUE);
  config.setAxesMax(MAX_PAD_VALUE);
  bleGamepad.begin(&config);
}

void BleGamepadManager::stop() {
  bleGamepad.end();
}

bool BleGamepadManager::isConnected() {
  return bleGamepad.isConnected();
}