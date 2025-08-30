#include "es_menu_controller.h"
#include "es_ble_gamepad_manager.h"

void setup() {
  Serial.begin(115200);

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
  unsigned long start = millis();
  MenuController::getInstance().update();
  long wait = 16 - (millis() - start);
  if ((wait > 0) && (wait <= 16)) {
    delay(wait);  // tries to keep 60fps
  }
}

