#pragma once

#include <unordered_map>
#include <cstdint>

constexpr uint8_t UNUSED_VALUE = 255;

struct PinConfig {
    uint8_t plugPin;  // pin 1-9 of DE-9 plug
    uint8_t mode;     // INPUT_PULLUP, OUTPUT, etc.
    uint8_t value;    // value (input and/or output depending on the context)
};

class Mapping {
public:
    static Mapping& getInstance();

    int getGpioFromPlugPin(uint8_t plugPin) const;

private:
    Mapping();

    const std::unordered_map<uint8_t, uint8_t> plugPinToGpio;

    Mapping(const Mapping&) = delete;
    Mapping& operator=(const Mapping&) = delete;
};
