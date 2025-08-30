#include "apple2_controller.h"

#define button1Pin (4)
#define button2Pin (3)
#define xAxisPin (5)
#define yAxisPin (9)

#define chargeTimeout (1900)

Apple2GameController::Apple2GameController()
    : GameController("Apple II") {
    Serial.println("Apple2GameController created");
}

void Apple2GameController::init() {
    playRules.reserve(9);
    playRules.clear();
    playRules.push_back({1, INPUT_PULLUP, UNUSED_VALUE});
    playRules.push_back({2, INPUT_PULLUP, UNUSED_VALUE});
    playRules.push_back({3, INPUT_PULLUP, UNUSED_VALUE});
    playRules.push_back({4, INPUT_PULLUP, UNUSED_VALUE});
    playRules.push_back({5, INPUT_PULLDOWN, UNUSED_VALUE});
    playRules.push_back({6, INPUT_PULLUP, UNUSED_VALUE});
    playRules.push_back({7, OUTPUT, HIGH});     // VCC
    playRules.push_back({8, OUTPUT, LOW});      // GND
    playRules.push_back({9, INPUT_PULLDOWN, UNUSED_VALUE});
    GameController::init();
}

void Apple2GameController::update() {
}

bool Apple2GameController::initDetection() {
    detectionRules.reserve(9);
    detectionRules.clear();
    detectionRules.push_back({1, INPUT_PULLUP, HIGH});
    detectionRules.push_back({2, INPUT_PULLUP, HIGH});
    detectionRules.push_back({3, INPUT_PULLUP, LOW});   // button 1 low to detect
    detectionRules.push_back({4, INPUT_PULLUP, LOW});   // button 2 low to detect
    detectionRules.push_back({5, INPUT_PULLUP, HIGH});
    detectionRules.push_back({6, INPUT_PULLUP, HIGH});
    detectionRules.push_back({7, INPUT_PULLUP, HIGH});  // no VCC yet
    detectionRules.push_back({8, OUTPUT, LOW});         // GND
    detectionRules.push_back({9, INPUT_PULLUP, HIGH});
    return GameController::initDetection();
}

float Apple2GameController::readAxis(uint8_t axisNumber) {
    uint8_t plugPin = (axisNumber == 0) ? xAxisPin : yAxisPin;
    unsigned long duration = readChargingDuration(plugPin, chargeTimeout);
    float result = (duration*2/(float)chargeTimeout) - 1.f;
    return (axisNumber == 0) ? result : -result;
}

uint8_t Apple2GameController::readButton(uint8_t buttonNumber) {
    uint8_t buttonPin = (buttonNumber == 0) ? button1Pin : button2Pin;
    return (readPinValue(buttonPin) == HIGH) ? 1 : 0;
}

