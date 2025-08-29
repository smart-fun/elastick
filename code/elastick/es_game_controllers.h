#pragma once
#include <vector>
#include "es_apple2_game_controller.h"
#include "es_atari_paddle_game_controller.h"
#include "es_ibm_game_controller.h"
#include "es_atari_joystick_game_controller.h"

class GameControllers {
public:
    static GameControllers& getInstance();
    int getCount() const;
    GameController * get(int index);
    void setSelectedController(GameController * controller);
    GameController * getSelectedController();
private:
    GameControllers();
    GameControllers(const GameControllers&) = delete;
    GameControllers& operator=(const GameControllers&) = delete;
    std::vector<GameController*> controllers;
    GameController * selectedController = nullptr;

    AtariJoystickController atariJoystickController;
    Apple2GameController apple2Controller;
    AtariPaddleGameController atariPaddleController;
    IBMGameController ibmController;
};
