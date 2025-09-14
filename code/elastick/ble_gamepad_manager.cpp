#include "ble_gamepad_manager.h"

const uint16_t MAX_PAD_VALUE = 10000;

BleGamepadManager::BleGamepadManager()
: bleGamepad("Elastick Joy", "Elastick", 100) {
  Serial.println("BleGamepadManager created");
}

void BleGamepadManager::start(const char * deviceName, uint8_t nbAxis, uint8_t nbButtons) {
  config.setAutoReport(true);
  config.setControllerType(CONTROLLER_TYPE_JOYSTICK); // or CONTROLLER_TYPE_GAMEPAD
  config.setButtonCount(nbButtons);
  config.setIncludeXAxis(nbAxis >= 1);
  config.setIncludeYAxis(nbAxis >= 2);
  config.setIncludeZAxis(false);
  config.setIncludeRxAxis(nbAxis >= 3);
  config.setIncludeRyAxis(nbAxis >= 4);
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

void BleGamepadManager::sendButtonValue(uint8_t button, bool pressed) {
  uint8_t padButton;
  switch(button) {
    case 0:
      padButton = BUTTON_1; // TODO: maybe use a direct mapping instead of switch/case
      break;
    case 1:
      padButton = BUTTON_2;
      break;
    case 2:
      padButton = BUTTON_3;
      break;
    case 3:
      padButton = BUTTON_4;
      break;
    default:
      return;
  }
  if (pressed) {
    bleGamepad.press(padButton);
  } else {
    bleGamepad.release(padButton);
  }
}

void BleGamepadManager::sendAxisValue(uint8_t axis, float value) {
  int16_t axisValue = (int16_t)(value * MAX_PAD_VALUE);
  switch(axis) {
    case 0:
      bleGamepad.setX(axisValue);
      break;
    case 1:
      bleGamepad.setY(axisValue);
      break;
    case 2:
      bleGamepad.setRX(axisValue);
      break;
    case 3:
      bleGamepad.setRY(axisValue);
      break;
    default:
      return;
  }
}
