#pragma once

#include <Arduino.h>

// Manages physical button input, including debouncing and tracking press events for navigation and selection.

enum class InputButtonName {
  Next,
  Validate,
};

class InputButtons {
public:
  static InputButtons& getInstance(); // singleton
  void update();
  bool wasPressed(InputButtonName buttonName);

private:
  InputButtons();
  class ButtonInfo {
  public:
    ButtonInfo(uint8_t gpio);
    void update();
    bool wasPressed();
  private:
    uint8_t gpio;
    unsigned long pressedTime;
    bool pressedState;
  };
  ButtonInfo nextButton;
  ButtonInfo validateButton;
};
