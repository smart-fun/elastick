#include <Arduino.h>
#include "PaddleMenu.h"

PaddleMenu::PaddleMenu()
    :ControllersMenu(ControllerCategory::PADDLE) {
    Serial.println("PaddleMenu created");
}

const char * PaddleMenu::getTitle() {
    return "PADDLES";
}
