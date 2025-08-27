#pragma once
#include "es_base_menu.h"

class ActionMenu : public BaseMenu {
public:
    enum class ActionState {
        DetectController,
        DisplayMenu,
    };
    ActionMenu();
    void show() override;
    void update() override;
    void onNext() override;
    void onValidate() override;

private:
    int actionIndex = 0;
    ActionState actionState = ActionState::DetectController;
};
