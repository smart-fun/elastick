#include "amiga_mouse_controller.h"
#include "mapping.h"

#define PIN_BUTTON_1 (6)
#define PIN_BUTTON_2 (9)
#define PIN_BUTTON_3 (5)
#define PIN_X1 (2)
#define PIN_X2 (4)
#define PIN_Y1 (3)
#define PIN_Y2 (1)

AmigaMouseController::AmigaMouseController()
    : MouseController("Amiga Mouse") {
    Serial.println("AmigaMouseController created");
}

// for derivated controllers
AmigaMouseController::AmigaMouseController(const char * name)
    : MouseController(name) {
}

void AmigaMouseController::getMouseDirectionPins(uint8_t &x1Pin, uint8_t &x2Pin, uint8_t &y1Pin, uint8_t &y2Pin) {
  x1Pin = PIN_X1;
  x2Pin = PIN_X2;
  y1Pin = PIN_Y1;
  y2Pin = PIN_Y2;
}

void AmigaMouseController::getMouseButtonPins(uint8_t &button1Pin, uint8_t &button2Pin, uint8_t &button3Pin) {
  button1Pin = PIN_BUTTON_1;
  button2Pin = PIN_BUTTON_2;
  button3Pin = PIN_BUTTON_3;
}

void AmigaMouseController::init() {
    playRules.reserve(9);
    playRules.clear();
    playRules.push_back({1, INPUT_PULLUP, UNUSED_VALUE});
    playRules.push_back({2, INPUT_PULLUP, UNUSED_VALUE});
    playRules.push_back({3, INPUT_PULLUP, UNUSED_VALUE});
    playRules.push_back({4, INPUT_PULLUP, UNUSED_VALUE});
    playRules.push_back({5, INPUT_PULLUP, UNUSED_VALUE});
    playRules.push_back({6, INPUT_PULLUP, UNUSED_VALUE});
    playRules.push_back({7, OUTPUT, HIGH});     // No VCC
    playRules.push_back({8, OUTPUT, LOW});      // GND
    playRules.push_back({9, INPUT_PULLUP, UNUSED_VALUE});
    MouseController::init();
}

void AmigaMouseController::deinit() {
    MouseController::deinit();
}

void AmigaMouseController::update() {
}
