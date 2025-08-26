#pragma once
#include "es_base_menu.h"

class ControllerListMenu : public BaseMenu {
public:
    ControllerListMenu();
    void show() override;
    void onNext() override;
    void onValidate() override;

private:
    int selectedIndex = 0;
};

