#include "es_ble_gamepad_manager.h"

const uint16_t MAX_PAD_VALUE = 10000;

BleGamepadManager::BleGamepadManager()
: bleGamepad("Elastick Joy", "Elastick", 100) {
  Serial.println("BleGamepadManager created");
}

void BleGamepadManager::start(const char * deviceName) {
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
  bleGamepad.deviceName = deviceName;
  bleGamepad.begin(&config);
}

void BleGamepadManager::stop() {
  bleGamepad.end();
}

bool BleGamepadManager::isConnected() {
  return bleGamepad.isConnected();
}

void BleGamepadManager::sendValues(uint8_t button1, uint8_t button2, float x, float y) {
  if (button1) {
    bleGamepad.press(BUTTON_1);
  } else {
    bleGamepad.release(BUTTON_1);
  }
  if (button2) {
    bleGamepad.press(BUTTON_2);
  } else {
    bleGamepad.release(BUTTON_2);
  }
  bleGamepad.setX((int16_t)(x * MAX_PAD_VALUE));
  bleGamepad.setY((int16_t)(y * MAX_PAD_VALUE));
}