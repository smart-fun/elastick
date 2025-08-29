#pragma once
#include "es_base_menu.h"

class TestMenu : public BaseMenu {
public:
    TestMenu();
    void show() override;
    void update() override;
    void onNext() override;
    void onValidate() override;
};

