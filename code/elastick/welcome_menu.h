#pragma once
#include "base_menu.h"

class WelcomeMenu : public BaseMenu {
public:
    WelcomeMenu();
    void show() override;
    void update() override;
    void onPrevious() override;
    void onNext() override;
    void onValidate() override;
private:
    unsigned long startTime;
};


