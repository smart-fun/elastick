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
  lcd.drawStr(0,10,"ELASTICK ADAPTER");
  lcd.setFont(u8g2_font_ncenB08_tr);
  lcd.drawStr(0,24,"WELCOME");
  lcd.sendBuffer();
}

void DisplayManager::showControllerList(int currentIndex) {
  lcd.clearBuffer();
 
  lcd.setFont(u8g2_font_DigitalDisco_te);
  lcd.drawStr(0,10,"CONTROLLERS");
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

