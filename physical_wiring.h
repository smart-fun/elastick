#pragma once

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
    // 7 is VCC
    // 8 is Ground
    { 9, 27, true  }
};


// DIN-6: all supported joysticks use the same mapping
static const EspPin din6_pins[] = {
    { 2, 16, false },   // button
    { 4, 14, true  },   // x-axis
    { 5, 27, true  }    // y-axis
};

// DA-15 only PC Game port supported
static const EspPin da15_pins[] = {
    { 1, 14, true  },   // x-axis
    { 2, 27, true  },   // y-axis
    { 6, 16, false },   // button 1
    { 7, 13, false },   // button 2
    { 13,12, false }    // button 3
};

static const PadConnector CONNECTOR_DSUB9   = { "DE-9", dsub9_pins, sizeof(dsub9_pins)/sizeof(dsub9_pins[0]) };
static const PadConnector CONNECTOR_DIN6    = { "DIN-6", din6_pins, sizeof(din6_pins)/sizeof(din6_pins[0]) };
static const PadConnector CONNECTOR_ASUB15  = { "DA-15", da15_pins, sizeof(da15_pins)/sizeof(da15_pins[0]) };
