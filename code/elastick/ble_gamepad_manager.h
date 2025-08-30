#pragma once
#include <BleGamepad.h>

class BleGamepadManager {
public:
    static BleGamepadManager& getInstance() {
        static BleGamepadManager instance;
        return instance;
    }
    void start(const char * deviceName);
    void stop();
    bool isConnected();
    void sendValues(uint8_t button1, uint8_t button2, float x, float y);
private:
    BleGamepadManager();
    BleGamepad bleGamepad;
    BleGamepadConfiguration config;
};

