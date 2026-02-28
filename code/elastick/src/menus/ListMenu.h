#pragma once
#include <vector>
#include "base_menu.h"
#include "MenuAction.h"
#include "ControllerCategory.h"

class GameController;

enum class MenuItemType {
    Action,
    Category,
    Controller
};

class MenuItem {
public:
    MenuItem(MenuAction menuAction, const char * displayText);
    MenuItem(ControllerCategory controllerCategory, const char * displayText);
    MenuItem(GameController* controller, const char * displayText);
    const char * displayText;
    MenuItemType type;
    union {
        MenuAction menuAction;
        ControllerCategory controllerCategory;  // type == Category
        GameController* controller;             // type == Controller
        } data;
private:
    MenuItem(MenuItemType type, const char * displayText);
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
private:
    void startControllersMenu(ControllerCategory category);
};

class CategoryMenu : public ListMenu {
public:
    CategoryMenu();
protected:
    const char * getTitle() override;
};
