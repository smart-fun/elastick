#pragma once
#include <vector>
#include "amiga_mouse_controller.h"
#include "apple2_controller.h"
#include "atari_joystick_controller.h"
#include "atari_paddle_controller.h"
#include "coco_controller.h"
#include "ibm_controller.h"
#include "master_system_controller.h"
#include "mega_drive_controller.h"
#include "moto_controller.h"
#include "msx_controller.h"

class GameControllers {
public:
    static GameControllers& getInstance();
    int getCount() const;
    GameController * get(int index);
    void setSelectedController(GameController * controller);
    GameController * getSelectedController();
private:
    GameControllers();
    GameControllers(const GameControllers&) = delete;
    GameControllers& operator=(const GameControllers&) = delete;
    std::vector<GameController*> controllers;
    GameController * selectedController = nullptr;

    AtariJoystickController atariJoystickController;
    Apple2GameController apple2Controller;
    AtariPaddleGameController atariPaddleController;
    IBMGameController ibmController;
    MSXGameController msxController;
    CocoGameController cocoController;
    MoToController motoController;
    MasterSystemController masterSystemController;
    MegaDriveController megaDriveController;
    AmigaMouseController amigaMouseController;
};
