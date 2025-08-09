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
    PADBT_ANALOG_Y_AXIS
};

enum class AxisMode { AXIS_DIGITAL, AXIS_ANALOG };

struct PadMapping {
    PadButton padButton;
    AxisMode axisMode;
    uint8_t plugPin;
};

struct PadMappings {
    const char* name;
    const PadConnector* connector;
    PadMapping* mapping;
    uint8_t inputCount;
};


static PadMapping atari2600_joystick_mapping[] = {
    { PadButton::PADBT_UP,       AxisMode::AXIS_DIGITAL, 1 },
    { PadButton::PADBT_DOWN,     AxisMode::AXIS_DIGITAL, 2 },
    { PadButton::PADBT_LEFT,     AxisMode::AXIS_DIGITAL, 3 },
    { PadButton::PADBT_RIGHT,    AxisMode::AXIS_DIGITAL, 4 },
    { PadButton::PADBT_BUTTON_1, AxisMode::AXIS_DIGITAL, 6 }
};

static PadMapping atari2600_paddle_mapping[] = {
    { PadButton::PADBT_ANALOG_X_AXIS, AxisMode::AXIS_ANALOG, 5 },
    { PadButton::PADBT_ANALOG_Y_AXIS, AxisMode::AXIS_ANALOG, 9 },
    { PadButton::PADBT_BUTTON_1,      AxisMode::AXIS_DIGITAL, 4 },
    { PadButton::PADBT_BUTTON_2,      AxisMode::AXIS_DIGITAL, 3 }
};

static const PadMappings atari2600_joystick = {
    "Atari 2600 Joystick", &CONNECTOR_DSUB9, atari2600_joystick_mapping, sizeof(atari2600_joystick_mapping)/sizeof(atari2600_joystick_mapping[0])
};

static const PadMappings atari2600_paddle = {
    "Atari 2600 Paddle", &CONNECTOR_DSUB9, atari2600_paddle_mapping, sizeof(atari2600_paddle_mapping)/sizeof(atari2600_paddle_mapping[0])
};
