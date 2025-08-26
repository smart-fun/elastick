#include "es_game_controller.h"

GameController::GameController(const char* controllerName)
    : name(controllerName) {}

const char* GameController::getName() const {
    return name;
}