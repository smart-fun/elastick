
// elastick gpio

#pragma once

// Lolin D32, ESP DevKitC-v4
enum ES_GPIO {
  // 2 pins for screen (i2c)
  ES_GPIO_SDA = 21,
  ES_GPIO_SCL = 22,
  
  // 2 pins for user buttons
  ES_GPIO_BUTTON_NEXT = 32,
  ES_GPIO_BUTTON_VALIDATE = 33,
  
  // 9 pins for DE-9 connector
  ES_GPIO_DE9_DIGITAL_1 = 16,
  ES_GPIO_DE9_DIGITAL_2 = 4,
  ES_GPIO_DE9_DIGITAL_3 = 13,
  ES_GPIO_DE9_DIGITAL_4 = 12,
  ES_GPIO_DE9_ANALOG_5 = 14,
  ES_GPIO_DE9_DIGITAL_6 = 17,
  ES_GPIO_DE9_DIGITAL_7 = 25,
  ES_GPIO_DE9_DIGITAL_8 = 26,
  ES_GPIO_DE9_ANALOG_9 = 27,
};
