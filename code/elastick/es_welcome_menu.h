#pragma once
#include "es_base_menu.h"

class WelcomeMenu : public BaseMenu {
public:
    WelcomeMenu();
    void show() override;
    void update() override;
    void onNext() override;
    void onValidate() override;
private:
    unsigned long startTime;
};


