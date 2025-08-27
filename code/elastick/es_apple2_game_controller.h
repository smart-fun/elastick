#pragma once
#include "es_game_controller.h"

class Apple2GameController : public GameController {
public:
    Apple2GameController();
    void init() override;
    void update() override;
    bool isAnalog() const override { return true; };
    void initDetection() override;
};

