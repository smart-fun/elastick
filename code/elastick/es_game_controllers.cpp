#include "es_game_controllers.h"
#include "es_game_controller.h"
#include "es_apple2_game_controller.h"
#include "es_atari_paddle_game_controller.h"
#include "es_ibm_game_controller.h"

GameControllers& GameControllers::getInstance() {
    static GameControllers instance;
    return instance;
}

GameControllers::GameControllers() {
    controllers.reserve(16);
    controllers.push_back(new Apple2GameController());
    controllers.push_back(new AtariPaddleGameController());
    controllers.push_back(new IBMGameController());
}

int GameControllers::getCount() const {
    return controllers.size();
}

GameController* GameControllers::get(int index) {
    if (index < 0 || index >= controllers.size()) return nullptr;
    return controllers[index];
}

