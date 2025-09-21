
// elastick gpio

#pragma once

// Lolin D32, ESP DevKitC-v4
enum ES_GPIO {
  // 2 pins for screen (i2c)
  ES_GPIO_SDA = 21,
  ES_GPIO_SCL = 22,
  
  // 3 pins for Rotary Switch
  ES_GPIO_BUTTON_VALIDATE = 5,
  ES_GPIO_ROTARY_ENCODER_A = 18,
  ES_GPIO_ROTARY_ENCODER_B = 19,
  
  // 9 pins for DE-9 connector
  ES_GPIO_DE9_DIGITAL_1 = 4,
  ES_GPIO_DE9_DIGITAL_2 = 17,
  ES_GPIO_DE9_DIGITAL_3 = 26,
  ES_GPIO_DE9_DIGITAL_4 = 14,
  ES_GPIO_DE9_ANALOG_5 = 13,
  ES_GPIO_DE9_DIGITAL_6 = 16,
  ES_GPIO_DE9_DIGITAL_7 = 25,
  ES_GPIO_DE9_DIGITAL_8 = 27,
  ES_GPIO_DE9_ANALOG_9 = 12,
};
