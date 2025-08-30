#include "es_game_controller.h"
//#include "physical_wiring.h"
//#include "es_mapping.h"

GameController::GameController(const char* controllerName)
    : name(controllerName) {}

const char* GameController::getName() const {
    return name;
}

void GameController::init() {
    Serial.println("init GameController");
    for (const PinConfig& rule : playRules) {
        int gpio = Mapping::getInstance().getGpioFromPlugPin(rule.plugPin);
        if (gpio >= 0) {
            pinMode(gpio, rule.mode);
            if (rule.value != UNUSED_VALUE) {
                digitalWrite(gpio, rule.value);
            }
        }
    }
}

void GameController::deinit() {
    Serial.println("deinit GameController");
    for (const PinConfig& rule : playRules) {
        int gpio = Mapping::getInstance().getGpioFromPlugPin(rule.plugPin);
        if (gpio >= 0) {
            pinMode(gpio, INPUT);
        }
    }
}

bool GameController::initDetection() {
    for (const PinConfig& rule : detectionRules) {
        int gpio = Mapping::getInstance().getGpioFromPlugPin(rule.plugPin);
        if (gpio >= 0) {
            pinMode(gpio, rule.mode);
        }
    }
    return true;
}

bool GameController::isDetected() {
    bool result = true;
    Serial.println("**********");
    for (const PinConfig& rule : detectionRules) {
        if (rule.mode == INPUT || rule.mode == INPUT_PULLUP) {
            int gpio = Mapping::getInstance().getGpioFromPlugPin(rule.plugPin);
            if (gpio >= 0) {
                int readValue = digitalRead(gpio);
                Serial.print("pin ");
                Serial.print(rule.plugPin);
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
                Serial.print(rule.plugPin);
                result = false;   // BAD RULE
            }
        }
    }
    return result;
}

void GameController::logPinValues() {
    for (const PinConfig& rule : playRules) {
        int gpio = Mapping::getInstance().getGpioFromPlugPin(rule.plugPin);
        if (gpio >= 0) {
            uint8_t value = digitalRead(gpio);
            Serial.print("pin ");
            Serial.print(rule.plugPin);
            Serial.print(" : ");
            Serial.println(value == HIGH ? "HIGH" : (value == LOW ? "LOW" : "UNKNOWN"));
        }
    }
}

uint8_t GameController::readPinValue(uint8_t plugPin) {
    int gpio = Mapping::getInstance().getGpioFromPlugPin(plugPin);
    if (gpio >= 0) {
        return digitalRead(gpio);
    }
    return UNUSED_VALUE;
}

unsigned long GameController::readChargingDuration(uint8_t plugPin, unsigned long timeoutMicros) {
    int gpio = Mapping::getInstance().getGpioFromPlugPin(plugPin);
    if (gpio >= 0) {
        // discharge capacitor
        pinMode(gpio, OUTPUT);
        digitalWrite(gpio, LOW);
        delay(5);
        // measure capacitor charge duration
        pinMode(gpio, INPUT);
        unsigned long start = micros();
        while (digitalRead(gpio) == LOW && micros() - start < timeoutMicros) {}
        return micros() - start;
    }
    return 0;
}

unsigned long GameController::readDischargingDuration(uint8_t plugPin, unsigned long timeoutMicros) {
    int gpio = Mapping::getInstance().getGpioFromPlugPin(plugPin);
    if (gpio >= 0) {
        // charge capacitor
        pinMode(gpio, OUTPUT);
        digitalWrite(gpio, HIGH);
        delay(5);
        // measure capacitor discharge duration
        pinMode(gpio, INPUT);
        unsigned long start = micros();
        while (digitalRead(gpio) == HIGH && micros() - start < timeoutMicros) {}
        return micros() - start;
    }
    return 0;
}
