#include "ibm_controller.h"

#define button1Pin (4)
#define button2Pin (3)
#define xAxisPin (5)
#define yAxisPin (9)

#define chargeTimeout (1400)

IBMGameController::IBMGameController()
    : AnalogGameController("IBM PC") {
    Serial.println("IBMGameController created");
}

void IBMGameController::init() {
    playRules.reserve(9);
    playRules.clear();
    playRules.push_back({1, INPUT_PULLUP, UNUSED_VALUE});
    playRules.push_back({2, INPUT_PULLUP, UNUSED_VALUE});
    playRules.push_back({3, INPUT_PULLUP, UNUSED_VALUE});   // button 2
    playRules.push_back({4, INPUT_PULLUP, UNUSED_VALUE});   // button 1
    playRules.push_back({5, INPUT_PULLDOWN, UNUSED_VALUE});
    playRules.push_back({6, INPUT_PULLUP, UNUSED_VALUE});
    playRules.push_back({7, OUTPUT, HIGH});     // VCC
    playRules.push_back({8, OUTPUT, LOW});      // GND
    playRules.push_back({9, INPUT_PULLDOWN, UNUSED_VALUE});
    GameController::init();
}

void IBMGameController::update() {
}

float IBMGameController::readAxis(uint8_t axisNumber) {
    if (axisNumber >= 2) { // not handled yet
        return 0;
    }
    uint8_t plugPin = (axisNumber == 0) ? xAxisPin : yAxisPin;
    unsigned long duration = readChargingDuration(plugPin, chargeTimeout);
    chargingDuration[axisNumber] = (duration > 65535) ? 65535 : duration;    // keep value for test/calibration
    float result = (duration*2/(float)chargeTimeout) - 1.f;
    return (axisNumber == 0) ? result : -result;
}

uint8_t IBMGameController::readButton(uint8_t buttonNumber) {
    if (buttonNumber >= 2) { // not handled yet
        return 0;
    }
    uint8_t buttonPin = (buttonNumber == 0) ? button1Pin : button2Pin;
    return (readPinValue(buttonPin) == LOW) ? 1 : 0;
}
