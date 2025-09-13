#pragma once
#include "base_menu.h"

class ControllerListMenu : public BaseMenu {
public:
    ControllerListMenu();
    void show() override;
    void update() override;
    void onPrevious() override;
    void onNext() override;
    void onValidate() override;

private:
    int selectedIndex = 0;
};

