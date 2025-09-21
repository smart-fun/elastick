
#include "mapping.h"
#include "gpio.h"

Mapping& Mapping::getInstance() {
    static Mapping instance;
    return instance;
}

Mapping::Mapping()
    : plugPinToGpio({
        {1, ES_GPIO_DE9_DIGITAL_1},
        {2, ES_GPIO_DE9_DIGITAL_2},
        {3, ES_GPIO_DE9_DIGITAL_3},
        {4, ES_GPIO_DE9_DIGITAL_4},
        {5, ES_GPIO_DE9_ANALOG_5},
        {6, ES_GPIO_DE9_DIGITAL_6},
        {7, ES_GPIO_DE9_DIGITAL_7},
        {8, ES_GPIO_DE9_DIGITAL_8},
        {9, ES_GPIO_DE9_ANALOG_9}
    })
{}

int Mapping::getGpioFromPlugPin(uint8_t plugPin) const {
    auto it = plugPinToGpio.find(plugPin);
    return (it != plugPinToGpio.end()) ? it->second : -1;
}
