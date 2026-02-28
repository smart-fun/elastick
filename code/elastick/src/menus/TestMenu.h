#pragma once
#include "BaseMenu.h"

class TestMenu : public BaseMenu {
public:
    TestMenu();
    void show() override;
    void update() override;
    void onPrevious() override;
    void onNext() override;
    void onValidate() override;
};

