#pragma once

#include "ListMenu.h"

class CategoryMenu : public ListMenu {
public:
    CategoryMenu();
protected:
    const char * getTitle() override;
};
