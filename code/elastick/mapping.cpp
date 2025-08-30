
#include "mapping.h"

Mapping& Mapping::getInstance() {
    static Mapping instance;
    return instance;
}

Mapping::Mapping()
    : plugPinToGpio({
        {1, 16},
        {2,  4},
        {3, 13},
        {4, 12},
        {5, 14},
        {6, 17},
        {7, 25},
        {8, 26},
        {9, 27}
    })
{}

int Mapping::getGpioFromPlugPin(uint8_t plugPin) const {
    auto it = plugPinToGpio.find(plugPin);
    return (it != plugPinToGpio.end()) ? it->second : -1;
}
