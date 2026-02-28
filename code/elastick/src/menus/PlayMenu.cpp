#include <Arduino.h>
#include "PlayMenu.h"
#include "DisplayManager.h"
#include "MenuController.h"
#include "game_controllers.h"
#include "game_controller.h"
#include "ble_gamepad_manager.h"

int8_t batteryUpdateCount = 0;

PlayMenu::PlayMenu()
{
  Serial.println("PlayMenu created");
}

void PlayMenu::init()
{
  Serial.println("PlayMenu::init");
  GameController *controller = GameControllers::getInstance().getSelectedController();
  BleGamepadManager::getInstance().start(controller->getName(), controller->getNbAxis(), controller->getNbButtons());
}

void PlayMenu::deinit()
{
  BleGamepadManager::getInstance().stop();
}

void PlayMenu::show()
{
  DisplayManager::getInstance().showPlay(GameControllers::getInstance().getSelectedController(), isConnected);
}

void PlayMenu::update()
{
  bool connected = BleGamepadManager::getInstance().isConnected();
  if (isConnected != connected)
  {
    isConnected = connected;
    show();
  }
  if (connected)
  {
    GameController *controller = GameControllers::getInstance().getSelectedController();
    controller->update();
    // send Buttons
    for (uint8_t button = 0; button < controller->getNbButtons(); ++button)
    {
      uint8_t value = controller->readButton(button);
      BleGamepadManager::getInstance().sendButtonValue(button, value);
    }
    // send Axis
    for (uint8_t axis = 0; axis < controller->getNbAxis(); ++axis)
    {
      float value = controller->readAxis(axis);
      bool isVerticalAxis = (axis & 1);
      BleGamepadManager::getInstance().sendAxisValue(axis, isVerticalAxis ? -value : value);
    }
    --batteryUpdateCount;
    if (batteryUpdateCount <= 0)
    {
      batteryUpdateCount = 60;
      sendBatteryPercent();
    }
  }
}
void PlayMenu::onPrevious()
{
  // nothing to do
}

void PlayMenu::onNext()
{
  // nothing to do
}

void PlayMenu::onValidate()
{
  deinit();
  MenuController::getInstance().setCurrentMenu(MenuController::MenuID::Action);
}

void PlayMenu::sendBatteryPercent()
{
  const int8_t LOOP = 10;
  long sum = 0;
  for(int i=0; i<LOOP; ++i) {
    sum += analogRead(ES_GPIO_BATTERY_ADC);
  }
  float raw = (float)sum / LOOP;        // average
  float voltage = (raw / 4095.0) * 3.3; // ADC voltage
  float batteryVoltage = voltage * 2.0; // pont diviseur 100k/100k
  float percent = (batteryVoltage - 3.0) / (4.2 - 3.0);
  percent = constrain(percent, 0.0, 1.0);
  uint8_t batteryPercent = percent * 100;
  BleGamepadManager::getInstance().sendBatteryPercent(batteryPercent);
}
