#include <Arduino.h>
#include "input_rotary.h"
#include "gpio.h"

// Quadrature lookup table:
// gives the valid movements (0 = no move) depending on previous & current state of A & B
static const int8_t quadTable[16] = {
    0,  -1, +1,  0,
   +1,  0,  0, -1,
   -1,  0,  0, +1,
    0, +1, -1,  0
};

void IRAM_ATTR encoderInterrupt() {
    InputRotary::getInstance().handleEncoder();
}

InputRotary& InputRotary::getInstance() {
    static InputRotary instance;
    return instance;
}

InputRotary::InputRotary()
    : encoderPosition(0)
    , lastEncoderPosition(0)
    , prevState(0)
    , rawCount(0)
{
    pinMode(ES_GPIO_ROTARY_ENCODER_A, INPUT_PULLUP);
    pinMode(ES_GPIO_ROTARY_ENCODER_B, INPUT_PULLUP);

    // Read initial state
    uint8_t A = digitalRead(ES_GPIO_ROTARY_ENCODER_A);
    uint8_t B = digitalRead(ES_GPIO_ROTARY_ENCODER_B);
    prevState = (A << 1) | B;

    // Interrupt on ANY change on A or B
    attachInterrupt(digitalPinToInterrupt(ES_GPIO_ROTARY_ENCODER_A), encoderInterrupt, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ES_GPIO_ROTARY_ENCODER_B), encoderInterrupt, CHANGE);
}

void InputRotary::handleEncoder() {
    uint8_t A = digitalRead(ES_GPIO_ROTARY_ENCODER_A);
    uint8_t B = digitalRead(ES_GPIO_ROTARY_ENCODER_B);

    uint8_t newState = (A << 1) | B;
    uint8_t index = (prevState << 2) | newState;
    int8_t movement = quadTable[index];

    rawCount += movement;

    // EC11 = 2 transitions per detent
    if (rawCount >= 2) {
        encoderPosition++;
        rawCount -= 2;
    } else if (rawCount <= -2) {
        encoderPosition--;
        rawCount += 2;
    }

    prevState = newState;
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
