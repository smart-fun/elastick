
// DEPRECATED

#pragma once

#include "physical_wiring.h"

enum class PadButton {
    PADBT_NONE,
    PADBT_UP,
    PADBT_DOWN,
    PADBT_LEFT,
    PADBT_RIGHT,
    PADBT_BUTTON_1,
    PADBT_BUTTON_2,
    PADBT_BUTTON_3,
    PADBT_ANALOG_X_AXIS,
    PADBT_ANALOG_Y_AXIS,
    PADBT_VCC,
    PADBT_GND
};

enum class AxisMode { AXIS_DIGITAL, AXIS_ANALOG, POWER };

struct PadMapping {
    PadButton padButton;
    AxisMode axisMode;
    uint8_t plugPin;
};

class PadMappings {
    const char* name;
    const PadConnector* connector;
    PadMapping* mapping;
    uint8_t inputCount;

public:
  PadMappings(const char* name, const PadConnector* connector, PadMapping* mapping, uint8_t inputCount) {
    this->name = name;
    this->connector = connector;
    this->mapping = mapping;
    this->inputCount = inputCount;
  }
  ~PadMappings() {
  }

  PadMapping* getMapping() {
    return mapping;
  }

  uint8_t getInputCount() {
    return inputCount;
  }

  uint8_t getNumButtons() {
    uint8_t result = 0;
    for(int i=0; i<inputCount; ++i) {
      PadButton padButton = mapping[i].padButton;
       if (padButton == PadButton::PADBT_BUTTON_1 || padButton == PadButton::PADBT_BUTTON_2 || padButton == PadButton::PADBT_BUTTON_3) {
         ++result;
       }
    }
    return result;
  }

  uint8_t getGpio(uint8_t mappingIndex) {
    PadMapping padMapping = mapping[mappingIndex];
    uint8_t plugPin = padMapping.plugPin;
    const EspPin* pins = connector->pins ;
    uint8_t numPins = connector->pinCount;
    for(uint8_t i=0; i<numPins; ++i) {
      EspPin pin = pins[i];
      if (pin.plugPin == plugPin) {
        return pin.gpio;
      }
    }
    return 0;
  }

  
  uint8_t hasXAxis() {
    for(int i=0; i<inputCount; ++i) {
      PadButton padButton = mapping[i].padButton;
       if (padButton == PadButton::PADBT_LEFT || padButton == PadButton::PADBT_ANALOG_X_AXIS) {
         return true;
       }
    }
    return false;
  }

  uint8_t hasYAxis() {
    for(int i=0; i<inputCount; ++i) {
      PadButton padButton = mapping[i].padButton;
       if (padButton == PadButton::PADBT_UP || padButton == PadButton::PADBT_ANALOG_Y_AXIS) {
         return true;
       }
    }
    return false;
  }
    
};


static PadMapping atari2600_joystick_mapping[] = {
    { PadButton::PADBT_UP,       AxisMode::AXIS_DIGITAL, 1 },
    { PadButton::PADBT_DOWN,     AxisMode::AXIS_DIGITAL, 2 },
    { PadButton::PADBT_LEFT,     AxisMode::AXIS_DIGITAL, 3 },
    { PadButton::PADBT_RIGHT,    AxisMode::AXIS_DIGITAL, 4 },
    { PadButton::PADBT_BUTTON_1, AxisMode::AXIS_DIGITAL, 6 },
//    { PadButton::PADBT_VCC,           AxisMode::POWER, 7 },
    { PadButton::PADBT_GND,      AxisMode::POWER, 8 },
    { PadButton::PADBT_BUTTON_2, AxisMode::AXIS_DIGITAL, 9 }  // test 2nd button for mame detection
};

static PadMapping atari2600_paddle_mapping[] = {
    { PadButton::PADBT_ANALOG_X_AXIS, AxisMode::AXIS_ANALOG, 5 },
    { PadButton::PADBT_ANALOG_Y_AXIS, AxisMode::AXIS_ANALOG, 9 },
    { PadButton::PADBT_BUTTON_1,      AxisMode::AXIS_DIGITAL, 4 },
    { PadButton::PADBT_BUTTON_2,      AxisMode::AXIS_DIGITAL, 3 },
    { PadButton::PADBT_VCC,           AxisMode::POWER, 7 },
    { PadButton::PADBT_GND,           AxisMode::POWER, 8 }
};

static PadMapping ibm_pc_mapping[] = {
    { PadButton::PADBT_ANALOG_X_AXIS, AxisMode::AXIS_ANALOG, 5 },
    { PadButton::PADBT_ANALOG_Y_AXIS, AxisMode::AXIS_ANALOG, 9 },
    { PadButton::PADBT_BUTTON_1,      AxisMode::AXIS_DIGITAL, 4 },
    { PadButton::PADBT_BUTTON_2,      AxisMode::AXIS_DIGITAL, 3 },
    { PadButton::PADBT_VCC,           AxisMode::POWER, 7 },
    { PadButton::PADBT_GND,           AxisMode::POWER, 8 }
};

static PadMappings * atari2600_joystick = new PadMappings(
    "Atari 2600 Joystick", &CONNECTOR_DSUB9, atari2600_joystick_mapping, sizeof(atari2600_joystick_mapping)/sizeof(atari2600_joystick_mapping[0])
);

static PadMappings * atari2600_paddle = new PadMappings(
    "Atari 2600 Paddle", &CONNECTOR_DSUB9, atari2600_paddle_mapping, sizeof(atari2600_paddle_mapping)/sizeof(atari2600_paddle_mapping[0])
);

static PadMappings * ibm_pc_joystick = new PadMappings(
    "IBM PC Joystick", &CONNECTOR_DSUB9, ibm_pc_mapping, sizeof(ibm_pc_mapping)/sizeof(ibm_pc_mapping[0])
);
