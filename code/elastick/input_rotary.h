#pragma once

#include "esp_attr.h"

// Class which handles the rotary encoder (quadrature decoding)

class InputRotary {
public:
    static InputRotary& getInstance();
    InputRotary();

    int getAbsoluteRotation();
    int getDeltaRotation();

private:
    friend void encoderInterrupt();
    void handleEncoder();

    volatile int encoderPosition;   // filtered, 1 step per detent
    int lastEncoderPosition;

    uint8_t prevState;              // previous quadrature state (00,01,11,10)
    int rawCount;                   // accumulates +1/-1 transitions until ±2
};
