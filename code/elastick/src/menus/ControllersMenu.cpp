#include "ControllersMenu.h"
#include "game_controllers.h"

ControllersMenu::ControllersMenu(ControllerCategory controllerCategory)
    : ListMenu()
{

    this->controllerCategory = controllerCategory;

    list.clear();
    list.reserve(16);

    list.push_back(new MenuItem(MenuAction::START_CATEGORY_MENU, "<BACK>")); // Back

    GameControllers &gc = GameControllers::getInstance();
    int nbControllers = gc.getCount();
    for (int i = 0; i < nbControllers; ++i)
    {
        GameController *controller = gc.get(i);
        if (controller->getCategory() == controllerCategory)
        {
            list.push_back(new MenuItem(controller, controller->getName()));
        }
    }
}
