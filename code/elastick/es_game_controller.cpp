#include "es_game_controller.h"
#include "physical_wiring.h"

GameController::GameController(const char* controllerName)
    : name(controllerName) {}

const char* GameController::getName() const {
    return name;
}

void GameController::initDetection() {
    for (const Detection& rule : detectionRules) {
        int gpio = getGpioFromPlugPin(rule.db9Pin);
        if (gpio >= 0) {
            pinMode(gpio, rule.mode);
        }
    }
}

bool GameController::isDetected() {
    bool result = true;
    Serial.println("**********");
    for (const Detection& rule : detectionRules) {
        if (rule.mode == INPUT || rule.mode == INPUT_PULLUP) {
            int gpio = getGpioFromPlugPin(rule.db9Pin);
            if (gpio >= 0) {
                int readValue = digitalRead(gpio);
                Serial.print("pin ");
                Serial.print(rule.db9Pin);
                Serial.print(" ");
                Serial.print("gpio ");
                Serial.print(gpio);
                Serial.print(" -> ");
                Serial.println(readValue ? "HIGH" : "LOW");
                if (readValue != rule.value) {
                    result = false;
                }
            } else {
                Serial.print("BAD RULE pin");
                Serial.print(rule.db9Pin);
                result = false;   // BAD RULE
            }
        }
    }
    return result;
}
