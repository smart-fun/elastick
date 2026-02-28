#include "atari_paddle_controller.h"

#define button1Pin (4)
#define button2Pin (3)
#define xAxisPin (5)
#define yAxisPin (9)

#define chargeTimeout (14000)

float smoothedAxis[2] = {0.f, 0.f};

// TODO: remove completely lower and higher values so that it comes to min/max much before the end of the paddle move
AtariPaddleGameController::AtariPaddleGameController()
    : AnalogGameController(ControllerCategory::PADDLE, "Atari VCS Paddles") {
    Serial.println("AtariPaddleGameController created");
}

void AtariPaddleGameController::init() {
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

void AtariPaddleGameController::update() {
}

float AtariPaddleGameController::readAxis(uint8_t axisNumber) {
    uint8_t plugPin = (axisNumber == 0) ? xAxisPin : yAxisPin;
    unsigned long duration = readChargingDuration(plugPin, chargeTimeout);
    chargingDuration[axisNumber] = (duration > 65535) ? 65535 : duration;    // keep value for test/calibration
    float result = (duration*2/(float)chargeTimeout) - 1.f;


// smooth result if not so far from current value
//    result = (smoothedAxis[axisNumber] * 0.75f) + (result * 0.25f);
    float diff = (result - smoothedAxis[axisNumber]) / 2.f;
    if (diff < 0) {
        diff = -diff;
    }
    // diff is from 0 to 1
    if (diff < 0.2f) {
        diff = 0.2f;
    }
    result = ((smoothedAxis[axisNumber] * (1.f - diff)) + (result * diff));

    smoothedAxis[axisNumber] = result;

    return (axisNumber == 0) ? -result : result;
}

uint8_t AtariPaddleGameController::readButton(uint8_t buttonNumber) {
    uint8_t buttonPin = (buttonNumber == 0) ? button1Pin : button2Pin;
    return (readPinValue(buttonPin) == LOW) ? 1 : 0;
}
