#pragma once
#include <BleGamepad.h>

class BleGamepadManager {
public:
    static BleGamepadManager& getInstance() {
        static BleGamepadManager instance;
        return instance;
    }
    void start(const char * deviceName, uint8_t nbAxis, uint8_t nbButtons);
    void stop();
    bool isConnected();
    //void sendValues(uint8_t button1, uint8_t button2, float x, float y);
    void sendButtonValue(uint8_t button, bool pressed);
    void sendAxisValue(uint8_t axis, float value);
private:
    BleGamepadManager();
    BleGamepad bleGamepad;
    BleGamepadConfiguration config;
};

