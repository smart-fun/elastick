#include "master_system_controller.h"

#define button1Pin (6)
#define button2Pin (9)
#define upPin (1)
#define downPin (2)
#define leftPin (3)
#define rightPin (4)

MasterSystemController::MasterSystemController()
    : DigitalGameController(ControllerCategory::JOY, "Sega Master System Pad") {
    Serial.println("MasterSystemController created");
}

void MasterSystemController::init() {
    playRules.reserve(9);
    playRules.clear();
    playRules.push_back({1, INPUT_PULLUP, UNUSED_VALUE});
    playRules.push_back({2, INPUT_PULLUP, UNUSED_VALUE});
    playRules.push_back({3, INPUT_PULLUP, UNUSED_VALUE});
    playRules.push_back({4, INPUT_PULLUP, UNUSED_VALUE});
    playRules.push_back({5, OUTPUT, LOW});  // No VCC
    playRules.push_back({6, INPUT_PULLUP, UNUSED_VALUE});
    playRules.push_back({7, INPUT_PULLUP, UNUSED_VALUE});   // light phaser button
    playRules.push_back({8, OUTPUT, LOW});      // GND
    playRules.push_back({9, INPUT_PULLUP, UNUSED_VALUE});
    GameController::init();
}

void MasterSystemController::update() {
}

float MasterSystemController::readAxis(uint8_t axisNumber) {
    uint8_t first = (axisNumber == 0) ? leftPin : upPin;
    uint8_t second = (axisNumber == 0) ? rightPin : downPin;
    if (readPinValue(first) == LOW) {
        return (axisNumber == 0) ? -1.f : 1.f;
    } else if (readPinValue(second) == LOW) {
        return (axisNumber == 0) ? 1.f : -1.f;
    }
    return 0.f;
}

uint8_t MasterSystemController::readButton(uint8_t buttonNumber) {
    uint8_t buttonPin = (buttonNumber == 0) ? button1Pin : button2Pin;
    return (readPinValue(buttonPin) == LOW) ? 1 : 0;
}
