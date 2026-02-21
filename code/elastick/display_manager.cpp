#include <Wire.h>
#include "display_manager.h"
#include "game_controllers.h"
#include "game_controller.h"
#include "action_menu.h"

uint8_t buttons[10];

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

void DisplayManager::clear() {
  lcd.clearBuffer();
  lcd.sendBuffer();
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

void DisplayManager::showDetecting(GameController * controller) {
  lcd.clearBuffer();
  lcd.setFont(u8g2_font_DigitalDisco_te);
  printCenterX(controller->getName(), 10);
  lcd.setFont(u8g2_font_ncenB08_tr);
  printCenterXY("detecting...");
  lcd.sendBuffer();
}

void DisplayManager::showActions(const char * menuName, std::vector<ActionItem*> & actionItems, int actionIndex) {
  lcd.clearBuffer();
  lcd.setFont(u8g2_font_DigitalDisco_te);
  printCenterX(menuName, 10);
  lcd.setFont(u8g2_font_ncenB08_tr);

  int count = actionItems.size();
  int x=12;
  int y=24;
  int index = actionIndex % count;
  int yMax = lcd.getDisplayHeight() + 10;
  lcd.drawStr(0, y, ">");
  do {
    lcd.drawStr(x, y, actionItems[index]->displayName);
    y += 12;
    index = (index + 1) % count;
  } while (y < yMax);

  lcd.sendBuffer();
}

void DisplayManager::showTest(GameController * controller) {
  lcd.clearBuffer();
  lcd.setFont(u8g2_font_DigitalDisco_te);
  printCenterX("TESTING", 10);
  lcd.setFont(u8g2_font_ncenB08_tr);
  lcd.drawStr(0, 24, ">");
  lcd.drawStr(12, 24, "BACK");

  //lcd.drawBox(0, 32, 32, 32);
  int halfSize = 16;
  int centerX = 64;
  int centerY = 64-halfSize;
  lcd.drawLine(centerX - halfSize, centerY, centerX + halfSize, centerY);
  lcd.drawLine(centerX, centerY - halfSize, centerX, centerY + halfSize);

  float x = controller->readAxis(0);
  float y = controller->readAxis(1);
  lcd.drawCircle(centerX + (x*halfSize), centerY - (y*halfSize), 3);

// Buttons
  uint8_t numButtons = controller->getNbButtons();
  for(uint8_t numButton = 0; numButton < numButtons; ++numButton) {
    buttons[numButton] = controller->readButton(numButton);
  }

  x = 100;
  y = 22;
  int radius = 5;
  int step = 10+6;
  for(uint8_t numButton = 0; numButton < numButtons; ++numButton) {
    if (buttons[numButton] == 1) {
      lcd.drawDisc(x, y, radius);
    } else {
      lcd.drawCircle(x, y, radius);
    }
    y += step;
    if (y + radius >= 64) {
      y = 22;
      x += step;
    }
  }

  // charging duration
  if (controller->isAnalog()) {
    AnalogGameController* analogController = (AnalogGameController*)controller;
    lcd.setFont(u8g2_font_squeezed_b7_tn); //u8g2_font_tiny5_tf);
    char buffer[16];
    long chargingDuration = analogController->getChargingDuration(0);
    sprintf(buffer, "%ld", chargingDuration);
    lcd.drawStr(0, 64 - 8, buffer); // X axis
    chargingDuration = analogController->getChargingDuration(1);
    sprintf(buffer, "%ld ms", chargingDuration);
    lcd.drawStr(0, 64, buffer); // Y axis
  }

  lcd.sendBuffer();
}

void DisplayManager::showPlay(bool connected) {
  lcd.clearBuffer();
  lcd.setFont(u8g2_font_DigitalDisco_te);
  printCenterX("PLAYING", 10);
  lcd.setFont(u8g2_font_ncenB08_tr);
  lcd.drawStr(0, 24, ">");
  lcd.drawStr(12, 24, "BACK");

  uint8_t y = 48;
  if (connected) {
    printCenterX("BT Connected!", y);
  } else {
    printCenterX("Bluetooth connection...", y);
  }

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
