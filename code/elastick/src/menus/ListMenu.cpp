#include "ListMenu.h"
#include "display_manager.h"
#include "game_controllers.h"
#include "menu_controller.h"

MenuItem::MenuItem(MenuItemType type, const char * displayText) {
    this->type = type;
    this->displayText = displayText;
}

MenuItem::MenuItem(MenuAction menuAction, const char * displayText)
    : MenuItem(MenuItemType::Action, displayText) {
        data.menuAction = menuAction;
}

MenuItem::MenuItem(ControllerCategory controllerCategory, const char * displayText)
    : MenuItem(MenuItemType::Category, displayText) {
        data.controllerCategory = controllerCategory;
}

MenuItem::MenuItem(GameController* controller, const char * displayText)
    : MenuItem(MenuItemType::Controller, displayText) {
        data.controller = controller;
}

CategoryMenu::CategoryMenu()
    :ListMenu() {
    Serial.println("CategoryMenu created");
    list.clear();
    list.reserve(3);
    list.push_back(new MenuItem(ControllerCategory::JOY, "Joysticks / Pads"));
    list.push_back(new MenuItem(ControllerCategory::MOUSE, "Mouses"));
    list.push_back(new MenuItem(ControllerCategory::PADDLE, "Paddles"));
}

const char * CategoryMenu::getTitle() {
    return "CONTROLLER";
}

ListMenu::ListMenu() {
}

void ListMenu::show() {
    DisplayManager::getInstance().showList(getTitle(), list, selectedIndex);
}

void ListMenu::update() {
    // nothing to do so far
}

void ListMenu::onPrevious() {
    if (selectedIndex > 0) {
        --selectedIndex;
    }
    show();
}

void ListMenu::onNext() {
    if (selectedIndex < list.size() - 1) {
        ++selectedIndex;
    }
    show();
}

void ListMenu::onValidate() {
    MenuItem * menuItem = list[selectedIndex];
    switch(menuItem->type) {
        case MenuItemType::Action: {
            MenuAction menuAction = menuItem->data.menuAction;
            if (menuAction == MenuAction::START_CATEGORY_MENU) {
                MenuController::getInstance().setCurrentMenu(MenuController::MenuID::Category);
            }
            break;
        }
        case MenuItemType::Category: {
            ControllerCategory controllerCategory = menuItem->data.controllerCategory;
            if (controllerCategory == ControllerCategory::JOY) {
                MenuController::getInstance().setCurrentMenu(MenuController::MenuID::JoystickList);
            } else {
                MenuController::getInstance().setCurrentMenu(MenuController::MenuID::ControllerList);
            }
            break;
        }
        case MenuItemType::Controller: {
            GameController * controller = menuItem->data.controller;
            GameControllers::getInstance().setSelectedController(controller);
            //selected->init();
            MenuController::getInstance().setCurrentMenu(MenuController::MenuID::Action);
            break;
        }
    }
}