#pragma once
#include <vector>
#include "base_menu.h"

class MenuItem {
public:
    MenuItem(const char * displayText);
    const char * displayText;
private:
    // MenuItem(const MenuItem&) = delete;
    // MenuItem& operator=(const MenuItem&) = delete;
};

class ListMenu : public BaseMenu {
public:
    ListMenu();
    void show() override;
    void update() override;
    void onPrevious() override;
    void onNext() override;
    void onValidate() override;
protected:
    void addItem(const char * displayText);
    int selectedIndex = 0;
    virtual const char * getTitle() = 0;
    std::vector<MenuItem *> list;
};

class CategoryMenu : public ListMenu {
public:
    CategoryMenu();
protected:
    const char * getTitle() override;
};
