#include <U8g2lib.h>

// Exemple pour I2C avec ESP32 sur SDA=21, SCL=22
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup() {
  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_DigitalDisco_te);
  u8g2.drawStr(0,10,"ELASTICK ADAPTER");
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(0,24,"AMSTRAD CPC");
//  u8g2.drawLine(0,13, 127, 13);
//  u8g2.drawLine(0,14, 127, 14);
  u8g2.sendBuffer();
}

void loop() {}
