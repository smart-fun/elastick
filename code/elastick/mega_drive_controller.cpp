#include "mega_drive_controller.h"

#define upPin (1)
#define downPin (2)
#define leftPin (3)
#define rightPin (4)
#define buttonABPin (6)
#define buttonStartCPin (9)

bool buttonUp = false;
bool buttonDown = false;
bool buttonLeft = false;
bool buttonRight = false;
bool buttonA = false;
bool buttonB = false;
bool buttonC = false;
bool buttonStart = false;

std::vector<PinConfig> mappingARules;
std::vector<PinConfig> mappingBRules;

MegaDriveController::MegaDriveController()
    : DigitalGameController("Sega Mega Drive") {
    Serial.println("MegaDriveController created");
}

void MegaDriveController::init() {
    playRules.reserve(9);
    playRules.clear();
    playRules.push_back({1, INPUT_PULLUP, UNUSED_VALUE});
    playRules.push_back({2, INPUT_PULLUP, UNUSED_VALUE});
    playRules.push_back({3, INPUT_PULLUP, UNUSED_VALUE});
    playRules.push_back({4, INPUT_PULLUP, UNUSED_VALUE});
    playRules.push_back({5, OUTPUT, HIGH});                 // VCC
    playRules.push_back({6, INPUT_PULLUP, UNUSED_VALUE});   // Button A / Button B
    playRules.push_back({7, INPUT_PULLUP, UNUSED_VALUE});   // Mapping Selector
    playRules.push_back({8, OUTPUT, LOW});                  // GND
    playRules.push_back({9, INPUT_PULLUP, UNUSED_VALUE});   // Button Start / Button C

    // Mapping A
    mappingARules.reserve(2);
    mappingARules.clear();
    mappingARules.push_back({7, OUTPUT, LOW});

    // Mapping B
    mappingBRules.reserve(2);
    mappingBRules.clear();
    mappingBRules.push_back({7, OUTPUT, HIGH});

    GameController::init();
}

void MegaDriveController::update() {
    applyRules(mappingARules);
    delay(10);
    buttonUp = (readPinValue(upPin) == LOW);
    buttonDown = (readPinValue(downPin) == LOW);
    buttonA = (readPinValue(buttonABPin) == LOW);
    buttonStart = (readPinValue(buttonStartCPin) == LOW);

    applyRules(mappingBRules);
    delay(10);
    buttonLeft = (readPinValue(leftPin) == LOW);
    buttonRight = (readPinValue(rightPin) == LOW);
    buttonB = (readPinValue(buttonABPin) == LOW);
    buttonC = (readPinValue(buttonStartCPin) == LOW);
}

float MegaDriveController::readAxis(uint8_t axisNumber) {
    if (axisNumber == 0) {
        if (buttonLeft) {
            return -1.f;
        } else if (buttonRight) {
            return 1.f;
        } else {
            return 0.f;
        }
    } else {
        if (buttonDown) {
            return -1.f;
        } else if (buttonUp) {
            return 1.f;
        } else {
            return 0.f;
        }
    }
}

uint8_t MegaDriveController::readButton(uint8_t buttonNumber) {
    switch(buttonNumber) {
        case 0:
            return buttonA ? 1 : 0;
        case 1:
            return buttonB ? 1 : 0;
        case 2:
            return buttonC ? 1 : 0;
        case 3:
            return buttonStart ? 1 : 0;
        default:
            return 0;
    }
}
