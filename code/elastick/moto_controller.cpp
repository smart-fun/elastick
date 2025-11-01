#include "moto_controller.h"

MoToController::MoToController()
    : AtariJoystickController("Thomson MO/TO") {
    Serial.println("MoToController created");
}

