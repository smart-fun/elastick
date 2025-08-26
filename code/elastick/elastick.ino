#include <Arduino.h>
#include <BleGamepad.h>
#include "pad_mapping.h"
#include "es_gpio.h"
//#include "es_display_manager.h"
//#include "es_input_button.h"
#include "es_menu_controller.h"

const uint16_t MAX_PAD_VALUE = 32767;

BleGamepad bleGamepad("IBM test", "Elastick", 100);
//PadMappings * padMappings = atari2600_joystick;
//PadMappings * padMappings = atari2600_paddle;
PadMappings * padMappings = ibm_pc_joystick;
//DisplayManager displayManager(ES_GPIO::ES_GPIO_SCL, ES_GPIO::ES_GPIO_SDA);
//InputButtons inputButtons;

void setup() {
  Serial.begin(115200);

//  displayManager.init();
//  displayManager.showWelcome();



  Serial.println("Starting BLE work!");

  BleGamepadConfiguration config;
  config.setAutoReport(true);
  config.setControllerType(CONTROLLER_TYPE_JOYSTICK); // or CONTROLLER_TYPE_GAMEPAD
  config.setButtonCount(padMappings->getNumButtons());
  config.setIncludeXAxis(padMappings->hasXAxis());
  config.setIncludeYAxis(padMappings->hasYAxis());
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


  PadMapping* mapping = padMappings->getMapping();
  uint8_t inputCount = padMappings->getInputCount();
  for(uint8_t i=0; i<inputCount; ++i) {
    uint8_t gpio = padMappings->getGpio(i);
    PadMapping padMapping = mapping[i];
    if (padMapping.axisMode == AxisMode::AXIS_DIGITAL) {
      pinMode(gpio, INPUT_PULLUP);
      Serial.print(gpio);
      Serial.println(" -> DIGITAL");
    } else if (padMapping.axisMode == AxisMode::AXIS_ANALOG) {
      pinMode(gpio, INPUT_PULLDOWN);
      Serial.print(gpio);
      Serial.println(" -> AXIS_ANALOG");
    } else if (padMapping.axisMode == AxisMode::POWER) {
      Serial.print(gpio);
      Serial.println(" -> POWER");
      pinMode(gpio, OUTPUT);
      if (padMapping.padButton == PadButton::PADBT_GND) {
        digitalWrite(gpio, LOW);
      } else if (padMapping.padButton == PadButton::PADBT_VCC) {
        digitalWrite(gpio, HIGH);
      }
    }
  }

  MenuController::getInstance().init();
  MenuController::getInstance().setCurrentMenu(MenuController::MenuID::ControllerList);
  //DisplayManager::getInstance().showControllerList(0);


}

void loop() {

  MenuController::getInstance().update();

  // inputButtons.update();
  // if (inputButtons.wasPressed(InputButtonName::Next)) {
  //   displayManager.showWelcome();
  // } else if (inputButtons.wasPressed(InputButtonName::Validate)) {
  //   displayManager.showControllerList(0);
  // }


  bool useDigitalXAxis = false;
  bool useDigitalYAxis = false;
  int16_t xAxis = 0;
  int16_t yAxis = 0;

  int16_t logValue = 0;

  PadMapping* mapping = padMappings->getMapping();
  uint8_t inputCount = padMappings->getInputCount();
  for(uint8_t i=0; i<inputCount; ++i) {
    int16_t rawValue = 0;
    uint8_t gpio = padMappings->getGpio(i);
    PadMapping padMapping = mapping[i];
    PadButton padButton = padMapping.padButton;
    if (padMapping.axisMode == AxisMode::AXIS_DIGITAL) {
      rawValue = digitalRead(gpio) == LOW ? 0 : 1;
      switch(padButton) {
        case PadButton::PADBT_LEFT:
          xAxis += rawValue * MAX_PAD_VALUE;
          useDigitalXAxis = true;
        break;
        case PadButton::PADBT_RIGHT:
          xAxis -= rawValue * MAX_PAD_VALUE;
          useDigitalXAxis = true;
        break;
        case PadButton::PADBT_UP:
          yAxis += rawValue * MAX_PAD_VALUE;
          useDigitalYAxis = true;
        break;
        case PadButton::PADBT_DOWN:
          yAxis -= rawValue * MAX_PAD_VALUE;
          useDigitalYAxis = true;
        break;
        case PadButton::PADBT_BUTTON_1:
          if (bleGamepad.isConnected()) {
            if (rawValue == 0) {
                bleGamepad.press(BUTTON_1);
            } else {
              bleGamepad.release(BUTTON_1);
            }
          }
        break;
        case PadButton::PADBT_BUTTON_2:
          if (bleGamepad.isConnected()) {
            if (rawValue == 0) {
                bleGamepad.press(BUTTON_2);
            } else {
              bleGamepad.release(BUTTON_2);
            }
          }
        break;
        case PadButton::PADBT_BUTTON_3:
          if (bleGamepad.isConnected()) {
            if (rawValue == 0) {
                bleGamepad.press(BUTTON_3);
            } else {
              bleGamepad.release(BUTTON_3);
            }
          }
        break;
      }
    } else if (padMapping.axisMode == AxisMode::AXIS_ANALOG) {
      rawValue = analogRead(gpio);
      logValue = rawValue;
      float finalX = rawValue;
      if (finalX < 100) {
        finalX = 100;
      }
      finalX = (finalX - 100) / (4095 - 100); // normalized [0;1]
      finalX = powf(finalX, 0.22f); // curve compensation
      finalX *= (MAX_PAD_VALUE * 2);
      finalX -= MAX_PAD_VALUE;  // centered
      if (bleGamepad.isConnected()) {
        switch(padButton) {
          case PadButton::PADBT_ANALOG_X_AXIS:
            bleGamepad.setX(finalX);
          break;
          case PadButton::PADBT_ANALOG_Y_AXIS:
            bleGamepad.setY(finalX);
          break;
        }
      }
    }
    
  }

  // Send to BLE
  if (bleGamepad.isConnected()) {
    if (useDigitalXAxis) {
      bleGamepad.setX(xAxis);
    }
    if (useDigitalYAxis) {
      bleGamepad.setY(yAxis);
    }
    delay(10);
  } else {
    delay(10);
  }

  delay(20);
}
