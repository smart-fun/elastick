#include "es_game_controllers.h"
#include "es_game_controller.h"

GameControllers& GameControllers::getInstance() {
    static GameControllers instance;
    return instance;
}

GameControllers::GameControllers() {
    controllers.reserve(16);
    controllers.push_back(&atariJoystickController);
    controllers.push_back(&apple2Controller);
    controllers.push_back(&atariPaddleController);
    controllers.push_back(&ibmController);
}

int GameControllers::getCount() const {
    return controllers.size();
}

GameController* GameControllers::get(int index) {
    if (index < 0 || index >= controllers.size()) return nullptr;
    return controllers[index];
}

void GameControllers::setSelectedController(GameController * controller) {
    selectedController = controller;
}

GameController * GameControllers::getSelectedController() {
    return selectedController;
}
