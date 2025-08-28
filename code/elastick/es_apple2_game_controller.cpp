#include "es_apple2_game_controller.h"

Apple2GameController::Apple2GameController()
    : GameController("Apple II") {}

void Apple2GameController::init() {
}

void Apple2GameController::update() {
}

bool Apple2GameController::initDetection() {
    detectionRules.clear();
    detectionRules.push_back({1, INPUT_PULLUP, HIGH});
    detectionRules.push_back({2, INPUT_PULLUP, HIGH});
    detectionRules.push_back({3, INPUT_PULLUP, LOW});   // button 1 detected
    detectionRules.push_back({4, INPUT_PULLUP, LOW});   // button 2 detected
    detectionRules.push_back({5, INPUT_PULLUP, HIGH});
    detectionRules.push_back({6, INPUT_PULLUP, HIGH});
    detectionRules.push_back({7, INPUT_PULLUP, HIGH});
    detectionRules.push_back({8, OUTPUT, LOW});         // GND
    detectionRules.push_back({9, INPUT_PULLUP, HIGH});
    return GameController::initDetection();
}

