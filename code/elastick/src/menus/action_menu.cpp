#include "action_menu.h"
//#include "display_manager.h"
#include "game_controllers.h"
#include "game_controller.h"
//#include "menu_controller.h"

ActionMenu::ActionMenu()
    :ListMenu() {
    Serial.println("ActionMenu created");
    list.clear();
    list.reserve(3);

    list.push_back(new MenuItem(MenuAction::BACK_TO_CONTROLLERS_MENU, "<Back>"));
    list.push_back(new MenuItem(MenuAction::TEST, "Test Controller"));
    list.push_back(new MenuItem(MenuAction::PLAY, "Bluetooth to PC"));
}

void ActionMenu::init() {

}

void ActionMenu::deinit() {
    GameController* controller = GameControllers::getInstance().getSelectedController();
    controller->deinit();
}

const char * ActionMenu::getTitle() {
    GameController* controller = GameControllers::getInstance().getSelectedController();
    return controller->getName();
}

