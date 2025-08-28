#include "es_ibm_game_controller.h"

IBMGameController::IBMGameController()
    : GameController("IBM PC") {}

void IBMGameController::init() {
    playRules.reserve(9);
    playRules.clear();
    playRules.push_back({1, INPUT_PULLUP, UNUSED_VALUE});
    playRules.push_back({2, INPUT_PULLUP, UNUSED_VALUE});
    playRules.push_back({3, INPUT_PULLUP, UNUSED_VALUE});   // button 2
    playRules.push_back({4, INPUT_PULLUP, UNUSED_VALUE});   // button 1
    playRules.push_back({5, INPUT_PULLDOWN, UNUSED_VALUE});
    playRules.push_back({6, INPUT_PULLUP, UNUSED_VALUE});
    playRules.push_back({7, OUTPUT, HIGH});     // VCC
    playRules.push_back({8, OUTPUT, LOW});      // GND
    playRules.push_back({9, INPUT_PULLDOWN, UNUSED_VALUE});
    GameController::init();
}

void IBMGameController::update() {
}
