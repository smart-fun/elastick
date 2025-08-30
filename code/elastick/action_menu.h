#pragma once

#include <vector>
#include "base_menu.h"

enum class Action {
    PLAY,
    CALIBRATE,
    TEST,
    BACK
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
    void init() override;
    void deinit() override;
    void show() override;
    void update() override;
    void onNext() override;
    void onValidate() override;

private:
    int actionIndex = 0;
    ActionState actionState = ActionState::DetectController;
    std::vector<ActionItem*> actionItems;
    ActionItem actionPlay = {Action::PLAY, "PLAY"};
    ActionItem actionCalibrate = {Action::CALIBRATE, "CALIBRATE"};
    ActionItem actionTest = {Action::TEST, "TEST"};
    ActionItem actionBack = {Action::BACK, "BACK"};
};


