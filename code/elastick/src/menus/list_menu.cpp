#include "list_menu.h"
#include "display_manager.h"
//#include "game_controllers.h"
#include "menu_controller.h"

MenuItem::MenuItem(const char * displayText) {
    this->displayText = displayText;
}

CategoryMenu::CategoryMenu()
    :ListMenu() {
    Serial.println("CategoryMenu created");
    list.clear();
    list.reserve(10);
    list.push_back(new MenuItem("Joystick & Pad"));
    list.push_back(new MenuItem("Mouse"));
    list.push_back(new MenuItem("Paddle"));
}

const char * CategoryMenu::getTitle() {
    return "CONTROLLER";
}

ListMenu::ListMenu() {
//    Serial.println("ListMenu created");
    // list.clear();
    // list.reserve(10);
    // list.push_back(new MenuItem("One"));
    // list.push_back(new MenuItem("Two"));
    // list.push_back(new MenuItem("Three"));
    // list.push_back(new MenuItem("Four"));
    // list.push_back(new MenuItem("Five"));
    // list.push_back(new MenuItem("Six"));
    // list.push_back(new MenuItem("Seven"));
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
//    } else {
//        selectedIndex = GameControllers::getInstance().getCount() - 1;
    }
    show();
}

void ListMenu::onNext() {
    if (selectedIndex < list.size() - 1) {
        ++selectedIndex;
    }
//    selectedIndex = (selectedIndex + 1) % GameControllers::getInstance().getCount();
    show();
}

void ListMenu::onValidate() {
//    GameController* selected = GameControllers::getInstance().get(selectedIndex);
//    GameControllers::getInstance().setSelectedController(selected);
    //selected->init();
    MenuController::getInstance().setCurrentMenu(MenuController::MenuID::ControllerList);
}