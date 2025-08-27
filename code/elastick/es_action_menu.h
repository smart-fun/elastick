#pragma once
#include "es_base_menu.h"

class ActionMenu : public BaseMenu {
public:
    ActionMenu();
    void show() override;
    void update() override;
    void onNext() override;
    void onValidate() override;

private:
    int actionIndex = 0;
};

