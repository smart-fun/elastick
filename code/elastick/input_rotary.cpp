#include <Arduino.h> 
#include "input_rotary.h"
#include "gpio.h"

void IRAM_ATTR encoderInterrupt() {
    InputRotary::getInstance().handleEncoder();
}

InputRotary& InputRotary::getInstance() {
  static InputRotary inputRotary;
  return inputRotary;
}

InputRotary::InputRotary()
  : encoderPosition(0)
  , lastEncoderPosition(0)
  , lastChangeTime(0) {
    pinMode(ES_GPIO_ROTARY_ENCODER_A, INPUT_PULLUP);
    pinMode(ES_GPIO_ROTARY_ENCODER_B, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(ES_GPIO_ROTARY_ENCODER_B), encoderInterrupt, FALLING);
}

void InputRotary::handleEncoder() {
  unsigned long now = millis();
  if (now - lastChangeTime > 10) {
    if (digitalRead(ES_GPIO_ROTARY_ENCODER_B) == LOW) {
      encoderPosition += (digitalRead(ES_GPIO_ROTARY_ENCODER_A) == HIGH) ? -1 : 1;
    }
    lastChangeTime = now;
  }
}

int InputRotary::getAbsoluteRotation() {
  lastEncoderPosition = encoderPosition;
  return encoderPosition;
}

int InputRotary::getDeltaRotation() {
  int diff = encoderPosition - lastEncoderPosition;
  lastEncoderPosition = encoderPosition;
  return diff;
}
