#include <Arduino.h>
#include "CategoryMenu.h"
#include "const.h"

CategoryMenu::CategoryMenu()
    : ListMenu()
{
    Serial.println("CategoryMenu created");
    list.clear();
    list.reserve(3);
    list.push_back(new MenuItem(ControllerCategory::JOY, "Joysticks / Pads"));
    list.push_back(new MenuItem(ControllerCategory::MOUSE, "Mouses"));
    list.push_back(new MenuItem(ControllerCategory::PADDLE, "Paddles"));
}

const char *CategoryMenu::getTitle()
{
    return APP_NAME;
}