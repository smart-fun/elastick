#pragma once

#include <vector>
#include "es_base_menu.h"

enum class Action {
    PLAY,
    CALIBRATE,
    TEST
};

struct ActionItem {
    Action action;
    const char * displayName;
};

class ActionMenu : public BaseMenu {
public:
    enum class ActionState {
        DetectController,
        DisplayMenu
    };
    ActionMenu();
    void show() override;
    void update() override;
    void onNext() override;
    void onValidate() override;

private:
    int actionIndex = 0;
    ActionState actionState = ActionState::DetectController;
    std::vector<ActionItem> actionItems;
};


