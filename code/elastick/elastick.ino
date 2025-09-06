#include "gpio.h"
#include "menu_controller.h"
#include "ble_gamepad_manager.h"
#include "display_manager.h"
bool firmwareUpdateMode = false;

void setup() {
  Serial.begin(115200);

  delay(200);
  uint8_t gpio = ES_GPIO::ES_GPIO_BUTTON_VALIDATE;
  pinMode(gpio, INPUT_PULLUP);
  firmwareUpdateMode = !digitalRead(gpio);
  if (firmwareUpdateMode) {
    Serial.println("Not starting anything");
    DisplayManager::getInstance().clear();
    return;
  }

  Serial.printf("Reset reason: %d\n", esp_reset_reason());  // see ESP_RST_POWERON

  // Create singletons ASAP
  Serial.println("create singletons");
  BleGamepadManager::getInstance();
  MenuController::getInstance();

  MenuController::getInstance().init();
  MenuController::getInstance().setCurrentMenu(MenuController::MenuID::Welcome);
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

