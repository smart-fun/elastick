#include "gpio.h"
#include "menu_controller.h"
#include "ble_gamepad_manager.h"
#include "display_manager.h"
bool firmwareUpdateMode = false;


const char *resetReasonName(esp_reset_reason_t r) {
  switch (r) {
    case ESP_RST_UNKNOWN:   return "Unknown";
    case ESP_RST_POWERON:   return "PowerOn";    //Power on or RST pin toggled
    case ESP_RST_EXT:       return "ExtPin";     //External pin - not applicable for ESP32
    case ESP_RST_SW:        return "Reboot";     //esp_restart()
    case ESP_RST_PANIC:     return "Crash";      //Exception/panic
    case ESP_RST_INT_WDT:   return "WDT_Int";    //Interrupt watchdog (software or hardware)
    case ESP_RST_TASK_WDT:  return "WDT_Task";   //Task watchdog
    case ESP_RST_WDT:       return "WDT_Other";  //Other watchdog
    case ESP_RST_DEEPSLEEP: return "Sleep";      //Reset after exiting deep sleep mode
    case ESP_RST_BROWNOUT:  return "BrownOut";   //Brownout reset (software or hardware)
    case ESP_RST_SDIO:      return "SDIO";       //Reset over SDIO
    default:                return "";
  }
}

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

  // Helps for debugging to know why the esp has (re)booted
  esp_reset_reason_t resetReason = esp_reset_reason();
  Serial.printf("\r\nReset reason %i - %s\r\n", resetReason, resetReasonName(resetReason));


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

