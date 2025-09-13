#pragma once

#include "esp_attr.h" 

// class which handles Rotary encoder.

class InputRotary {
  public:
    static InputRotary& getInstance();
    InputRotary();
    int getAbsoluteRotation();
    int getDeltaRotation();
  private:
    friend void encoderInterrupt(); 
    void handleEncoder();
    int encoderPosition;
    int lastEncoderPosition;
    long lastChangeTime;
};
