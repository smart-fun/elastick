#pragma once

#include "ControllersMenu.h"

class MouseMenu : public ControllersMenu {
public:
    MouseMenu();
protected:
    const char * getTitle() override;
};
