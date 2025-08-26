#pragma once
#include "es_game_controller.h"

class AtariPaddleGameController : public GameController {
public:
    AtariPaddleGameController();
    void init() override;
    void update() override;
};

