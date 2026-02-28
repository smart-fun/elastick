#include <Arduino.h>
#include "JoystickMenu.h"

JoystickMenu::JoystickMenu()
    :ControllersMenu(ControllerCategory::JOY) {
    Serial.println("JoystickMenu created");
}

const char * JoystickMenu::getTitle() {
    return "STICKS & PADS";
}
