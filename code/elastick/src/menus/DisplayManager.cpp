#include <Wire.h>
#include "DisplayManager.h"
#include "game_controllers.h"
#include "game_controller.h"
#include "ActionMenu.h"
#include "ListMenu.h"
#include "const.h"

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
  printTitle("ELASTICK ADAPTER");
  lcd.setFont(u8g2_font_ncenB08_tr);
  printCenterXY(APP_NAME);
  lcd.sendBuffer();
}

void DisplayManager::showList(const char * title, const std::vector<MenuItem*> &list, int currentIndex) {
  lcd.clearBuffer();
  printTitle(title);

  lcd.setFont(u8g2_font_ncenB08_tr);
  int size = list.size();
  int offset = (currentIndex < 4) ? 0 : currentIndex - 3;
  int x=12;
  int y=24;
  for(int i=0; i<4; ++i) {
    if (offset >= size) {
      break;
    }
    MenuItem * item = list[offset];
    if (offset == currentIndex) {
      if (item->type == MenuItemType::Action && (item->data.menuAction == MenuAction::BACK_TO_CATEGORY_MENU || item->data.menuAction == MenuAction::BACK_TO_CONTROLLERS_MENU) ) {
        lcd.drawStr(0, y, "<");
      } else {
        lcd.drawStr(0, y, ">");
      }
    }
    lcd.drawStr(x, y, item->displayText);
    y += 12;
    ++offset;
  }
  lcd.sendBuffer();
}

void DisplayManager::showTest(GameController * controller) {
  lcd.clearBuffer();
  printTitle(controller->getName());

  lcd.setFont(u8g2_font_ncenB08_tr);
  lcd.drawStr(0, 24, "<");
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

void DisplayManager::showPlay(GameController * controller, bool connected) {
  lcd.clearBuffer();
  printTitle(controller->getName());
  lcd.setFont(u8g2_font_ncenB08_tr);
  lcd.drawStr(0, 24, "<");
  lcd.drawStr(12, 24, "BACK");

  uint8_t y = 48;
  if (connected) {
    printCenterX("BT Connected!", y);
  } else {
    printCenterX("Bluetooth connection...", y);
  }

  lcd.sendBuffer();
}

void DisplayManager::printTitle(const char * title) {
//  lcd.setFont(u8g2_font_DigitalDisco_te);
  //lcd.setFont(u8g2_font_6x13_tf);
  lcd.setFont(u8g2_font_ncenB08_tr);
  printCenterX(title, 9);
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
