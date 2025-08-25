#include "es_display_manager.h"
#include <Wire.h>

DisplayManager::DisplayManager(uint8_t sclPin, uint8_t sdaPin)
  : lcd(U8G2_R0, /* reset=*/ U8X8_PIN_NONE)
  , scl(sclPin), sda(sdaPin) {
}

void DisplayManager::init() {
    Wire.begin(sda, scl);
    lcd.begin();
    lcd.clearBuffer();
    lcd.sendBuffer();
}

void DisplayManager::showWelcome() {
  lcd.clearBuffer();
  lcd.setFont(u8g2_font_DigitalDisco_te);
  lcd.drawStr(0,10,"ELASTICK ADAPTER");
  lcd.setFont(u8g2_font_ncenB08_tr);
  lcd.drawStr(0,24,"AMSTRAD CPC");
  lcd.sendBuffer();
}

void DisplayManager::showControllerList() {
  lcd.clearBuffer();
  lcd.setFont(u8g2_font_DigitalDisco_te);
  lcd.drawStr(0,10,"CONTROLLERS");
  lcd.setFont(u8g2_font_ncenB08_tr);
  lcd.drawStr(0,24,"ATARI 2600");
  lcd.sendBuffer();
}
