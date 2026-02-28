#include "coco_controller.h"

#define button1Pin (4)
#define button2Pin (3)
#define xAxisPin (5)
#define yAxisPin (9)

#define dischargeTimeout (1300)
#define chargeTimeout (1300)

CocoGameController::CocoGameController()
    : AnalogGameController(ControllerCategory::JOY, "Tandy CoCo") {
    Serial.println("CocoGameController created");
}

void CocoGameController::init() {
    playRules.reserve(9);
    playRules.clear();
    playRules.push_back({1, INPUT_PULLUP, UNUSED_VALUE});
    playRules.push_back({2, INPUT_PULLUP, UNUSED_VALUE});
    playRules.push_back({3, INPUT_PULLUP, UNUSED_VALUE});
    playRules.push_back({4, INPUT_PULLUP, UNUSED_VALUE});
    playRules.push_back({5, INPUT_PULLUP, UNUSED_VALUE});
    playRules.push_back({6, INPUT_PULLUP, UNUSED_VALUE});
    playRules.push_back({7, OUTPUT, HIGH});     // VCC
    playRules.push_back({8, OUTPUT, LOW});      // GND
    playRules.push_back({9, INPUT_PULLUP, UNUSED_VALUE});
    GameController::init();
}

void CocoGameController::update() {
}

float CocoGameController::readAxis(uint8_t axisNumber) {
    uint8_t plugPin = (axisNumber == 0) ? xAxisPin : yAxisPin;
    unsigned long chargeDuration = readChargingDuration(plugPin, chargeTimeout);
    unsigned long dischargeDuration = readDischargingDuration(plugPin, dischargeTimeout);
    if (chargeDuration < dischargeDuration) {
        chargingDuration[axisNumber] = (chargeDuration > 65535) ? 65535 : chargeDuration;    // keep value for test/calibration
        float duration = chargeTimeout - chargeDuration;
        // if (duration < 0) {
        //     duration = 0;
        // }
        float value = (duration/(float)chargeTimeout);
        return (axisNumber == 0) ? value : -value;
    } else {
        chargingDuration[axisNumber] = (dischargeDuration > 65535) ? 65535 : dischargeDuration;    // keep value for test/calibration
        float duration = dischargeTimeout - dischargeDuration;
        // if (duration < 0) {
        //     duration = 0;
        // }
        float value = (-duration/(float)dischargeTimeout);
        return (axisNumber == 0) ? value : -value;
    }
}

uint8_t CocoGameController::readButton(uint8_t buttonNumber) {
    uint8_t buttonPin = (buttonNumber == 0) ? button1Pin : button2Pin;
    return (readPinValue(buttonPin) == LOW) ? 1 : 0;
}

