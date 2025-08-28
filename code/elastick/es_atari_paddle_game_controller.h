#pragma once
#include "es_game_controller.h"

class AtariPaddleGameController : public GameController {
public:
    AtariPaddleGameController();
    void init() override;
    void update() override;
    bool isAnalog() const override { return true; };
    bool initDetection() override { return false; };
};

