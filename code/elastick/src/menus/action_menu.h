#pragma once

#include "ListMenu.h"

class ActionMenu : public ListMenu {
public:
    enum class ActionState {
        DetectController,
        DisplayMenu
    };
    ActionMenu();
    void init() override;
    void deinit() override;
protected:
    const char * getTitle() override;
};


