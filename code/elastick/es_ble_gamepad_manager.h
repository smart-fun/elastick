#pragma once
#include <BleGamepad.h>

class BleGamepadManager {
public:
    static BleGamepadManager& getInstance() {
        static BleGamepadManager instance;
        return instance;
    }
    void start();
    void stop();
    bool isConnected();
private:
    BleGamepadManager();
    BleGamepad bleGamepad;
    BleGamepadConfiguration config;
};

