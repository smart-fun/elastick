#include "moto_controller.h"

MoToController::MoToController()
    : AtariJoystickController("Thomson MO/TO Stick") {
    Serial.println("MoToController created");
}

