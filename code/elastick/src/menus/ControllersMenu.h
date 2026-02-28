#pragma once

#include "ListMenu.h"
#include "ControllerCategory.h"

class ControllersMenu : public ListMenu {
public:
    ControllersMenu(ControllerCategory controllerCategory);
private:
    ControllerCategory controllerCategory;
};