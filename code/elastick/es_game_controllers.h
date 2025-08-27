#pragma once
#include <vector>

class GameController;

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
};
