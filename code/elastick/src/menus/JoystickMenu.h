#pragma once

#include "ListMenu.h"

class JoystickMenu : public ListMenu {
public:
    JoystickMenu();
protected:
    const char * getTitle() override;
};
