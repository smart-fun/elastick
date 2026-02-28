#pragma once
#include "BaseMenu.h"

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


