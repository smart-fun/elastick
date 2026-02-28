#pragma once

#include "ControllersMenu.h"

class PaddleMenu : public ControllersMenu {
public:
    PaddleMenu();
protected:
    const char * getTitle() override;
};
