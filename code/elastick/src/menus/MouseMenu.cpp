#include <Arduino.h>
#include "MouseMenu.h"

MouseMenu::MouseMenu()
    :ControllersMenu(ControllerCategory::MOUSE) {
    Serial.println("MouseMenu created");
}

const char * MouseMenu::getTitle() {
    return "MOUSES";
}
