#pragma once
#include "es_game_controller.h"

class IBMGameController : public GameController {
public:
    IBMGameController();
    void init() override;
    void update() override;
};

