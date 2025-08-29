#pragma once

// DEPRECATED
/*
struct EspPin {
  uint8_t plugPin;
  uint8_t gpio;
  bool supportsAnalog;  // TODO: check if really iuseful
};

struct PadConnector {
  const char* name;
  const EspPin* pins;
  uint8_t pinCount;
};


// D-SUB 9: mapping vary
static const EspPin dsub9_pins[] = {
    { 1, 16, false },
    { 2,  4, false },
    { 3, 13, false },
    { 4, 12, false },
    { 5, 14, true  },
    { 6, 17, false },
    { 7, 25, false },
    { 8, 26, false },
    { 9, 27, true  }
};

static const PadConnector CONNECTOR_DSUB9   = { "DE-9", dsub9_pins, sizeof(dsub9_pins)/sizeof(dsub9_pins[0]) };
*/