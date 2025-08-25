#include "es_gpio.h"
#include "es_input_button.h"

#define PRESS_HYSTERESIS (50)

InputButtons::InputButtons()
    : nextButton(ES_GPIO::ES_GPIO_BUTTON_NEXT),
      validateButton(ES_GPIO::ES_GPIO_BUTTON_VALIDATE) {}

void InputButtons::update() {
  nextButton.update();
  validateButton.update();
}

bool InputButtons::wasPressed(InputButtonName buttonName) {
  switch(buttonName) {
    case InputButtonName::Next:
      return nextButton.wasPressed();
    case InputButtonName::Validate:
      return validateButton.wasPressed();
    default:
      return false;
  }
}

// *** ButtonInfo ***

InputButtons::ButtonInfo::ButtonInfo(uint8_t gpio) {
  this->gpio = gpio;
  this->pressedTime = 0;
  this->pressedState = false;
  pinMode(gpio, INPUT_PULLUP);
}

void InputButtons::ButtonInfo::update() {
  pressedState = false; // don't keep state more than the current frame
  long now = millis();
  bool buttonState = digitalRead(gpio);
  if (buttonState == LOW) {
    pressedTime = now;
  } else {
    if ((pressedTime != 0) && now > pressedTime + PRESS_HYSTERESIS) {
      if (buttonState == HIGH) {
        pressedState = true;
        pressedTime = 0;
      }
    }
  }
}

bool InputButtons::ButtonInfo::wasPressed() {
  return pressedState;
}

