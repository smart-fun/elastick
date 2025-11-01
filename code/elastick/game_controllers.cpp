#include "game_controllers.h"
#include "game_controller.h"

GameControllers& GameControllers::getInstance() {
    static GameControllers instance;
    return instance;
}

GameControllers::GameControllers() {
    controllers.reserve(8);
    controllers.push_back(&atariJoystickController);
    controllers.push_back(&apple2Controller);
    controllers.push_back(&atariPaddleController);
    controllers.push_back(&ibmController);
    controllers.push_back(&msxController);
    controllers.push_back(&masterSystemController);
    controllers.push_back(&cocoController);
}

int GameControllers::getCount() const {
    return controllers.size();
}

GameController* GameControllers::get(int index) {
    if (index < 0 || index >= controllers.size()) return nullptr;
    return controllers[index];
}

void GameControllers::setSelectedController(GameController * controller) {
    if (controller == nullptr) {
        Serial.println("clear selected Controller");
    } else {
        Serial.print("set selected Controller ");
        Serial.println(controller->getName());
    }
    selectedController = controller;
}

GameController * GameControllers::getSelectedController() {
    return selectedController;
}
