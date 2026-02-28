#pragma once
#include "BaseMenu.h"

class PlayMenu : public BaseMenu {
public:
    PlayMenu();
    void init() override;
    void deinit() override;
    void show() override;
    void update() override;
    void onPrevious() override;
    void onNext() override;
    void onValidate() override;
private:
    bool isConnected = false;
};


