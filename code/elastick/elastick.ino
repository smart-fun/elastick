#include "es_gpio.h"
#include "es_menu_controller.h"
#include "es_ble_gamepad_manager.h"

bool firmwareUpdateMode = false;

void setup() {
  Serial.begin(115200);

  uint8_t gpio = ES_GPIO::ES_GPIO_BUTTON_VALIDATE;
  pinMode(gpio, INPUT_PULLUP);
  firmwareUpdateMode = !digitalRead(gpio);
  if (firmwareUpdateMode) {
    Serial.println("Not starting anything");
    return;
  }


  // Create singletons ASAP
  Serial.println("create singletons");
  BleGamepadManager::getInstance();
  MenuController::getInstance();

  // first boot, create all and force reboot, otherwise it will do it much more later when starting BLE
  if (esp_reset_reason() == ESP_RST_POWERON) {
    MenuController::getInstance().init();
    MenuController::getInstance().setCurrentMenu(MenuController::MenuID::Welcome);
    Serial.println("First boot → force restart after BLE init");
    BleGamepadManager::getInstance().start("Elastick");
    delay(500);
    BleGamepadManager::getInstance().stop();
    delay(500);
    ESP.restart();
    return;
  }
  MenuController::getInstance().init();
  MenuController::getInstance().setCurrentMenu(MenuController::MenuID::ControllerList);
}

void loop() {

  if (firmwareUpdateMode) {
    Serial.println("Doing nothing");
    delay(1000);
    return;
  }


  unsigned long start = millis();
  MenuController::getInstance().update();
  long wait = 16 - (millis() - start);
  if ((wait > 0) && (wait <= 16)) {
    delay(wait);  // tries to keep 60fps
  }
}

