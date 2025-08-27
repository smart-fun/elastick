#include <Wire.h>
#include "es_display_manager.h"
#include "es_game_controllers.h"
#include "es_game_controller.h"

DisplayManager& DisplayManager::getInstance() {
    static DisplayManager instance;
    return instance;
}

DisplayManager::DisplayManager() {
    lcd.begin();
    lcd.clearBuffer();
    lcd.sendBuffer();
}

void DisplayManager::init() {
}

void DisplayManager::showWelcome() {
  lcd.clearBuffer();
  lcd.setFont(u8g2_font_DigitalDisco_te);
  printCenterX("ELASTICK ADAPTER", 10);
  lcd.setFont(u8g2_font_ncenB08_tr);
  printCenterXY("Version 0.2");
  lcd.sendBuffer();
}

void DisplayManager::showControllerList(int currentIndex) {
  lcd.clearBuffer();
 
  lcd.setFont(u8g2_font_DigitalDisco_te);
  printCenterX("CONTROLLERS", 10);
  lcd.setFont(u8g2_font_ncenB08_tr);

  GameControllers & gc = GameControllers::getInstance();
  int nbControllers = gc.getCount();
  int x=12;
  int y=24;
  int index = currentIndex % nbControllers;
  int yMax = lcd.getDisplayHeight() + 10;
  lcd.drawStr(0, y, ">");
  do {
    lcd.drawStr(x, y, gc.get(index)->getName());
    y += 12;
    index = (index + 1) % nbControllers;
  } while (y < yMax);
  lcd.sendBuffer();
}

void DisplayManager::showActions(GameController * controller, int actionIndex) {
  lcd.clearBuffer();
  lcd.setFont(u8g2_font_DigitalDisco_te);
  printCenterX(controller->getName(), 10);
  // lcd.setFont(u8g2_font_ncenB08_tr);
  // printCenterXY("Version 0.2");
  lcd.sendBuffer();
}


void DisplayManager::printCenterX(const char * text, int y) {
  u8g2_uint_t screenWidth = lcd.getDisplayWidth();
  u8g2_uint_t textWidth = lcd.getStrWidth(text);
  u8g2_uint_t x = (screenWidth - textWidth) / 2;
  lcd.drawStr(x, y, text);
}

void DisplayManager::printCenterXY(const char * text) {
  u8g2_uint_t screenHeight = lcd.getDisplayHeight();
  u8g2_uint_t textHeight = lcd.getMaxCharHeight();
  u8g2_uint_t y = (screenHeight + textHeight) / 2;
  printCenterX(text, y);
}
