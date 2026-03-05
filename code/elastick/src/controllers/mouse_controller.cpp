#include "mouse_controller.h"
#include "mapping.h"

#define LIMIT (100)

// Quadrature table
static const int8_t quadTable[16] = {
    0,  -1, +1,  0,
   +1,   0,  0, -1,
   -1,   0,  0, +1,
    0,  +1, -1,  0
};

static inline uint8_t fastRead(uint8_t pin) {
  return (GPIO.in >> pin) & 1;
}

// Initialize static instance pointer
MouseController* MouseController::instance = nullptr;

void IRAM_ATTR interruptMouseX() {
  if (MouseController::instance == nullptr) return;
  
  uint8_t A = fastRead(MouseController::instance->x1Gpio);
  uint8_t B = fastRead(MouseController::instance->x2Gpio);
  uint8_t s = (A << 1) | B;

  uint8_t index = (MouseController::instance->prevX << 2) | s;
  int8_t mv = quadTable[index];
  MouseController::instance->rawX += mv;

  if (MouseController::instance->rawX >= 2) { 
    MouseController::instance->mouseX++; 
    MouseController::instance->rawX -= 2; 
  }
  else if (MouseController::instance->rawX <= -2) { 
    MouseController::instance->mouseX--; 
    MouseController::instance->rawX += 2; 
  }

  if (MouseController::instance->mouseX > LIMIT) {
    MouseController::instance->mouseX = LIMIT;
  } else if (MouseController::instance->mouseX < -LIMIT) {
    MouseController::instance->mouseX = -LIMIT;
  }

  MouseController::instance->prevX = s;
}

void IRAM_ATTR interruptMouseY() {
  if (MouseController::instance == nullptr) return;
  
  uint8_t A = fastRead(MouseController::instance->y1Gpio);
  uint8_t B = fastRead(MouseController::instance->y2Gpio);
  uint8_t s = (A << 1) | B;

  uint8_t index = (MouseController::instance->prevY << 2) | s;
  int8_t mv = quadTable[index];
  MouseController::instance->rawY += mv;

  if (MouseController::instance->rawY >= 2) { 
    MouseController::instance->mouseY++; 
    MouseController::instance->rawY -= 2; 
  }
  else if (MouseController::instance->rawY <= -2) { 
    MouseController::instance->mouseY--; 
    MouseController::instance->rawY += 2; 
  }

  if (MouseController::instance->mouseY > LIMIT) {
    MouseController::instance->mouseY = LIMIT;
  } else if (MouseController::instance->mouseY < -LIMIT) {
    MouseController::instance->mouseY = -LIMIT;
  }

  MouseController::instance->prevY = s;
}

MouseController::MouseController(const char* controllerName)
    : DigitalGameController(ControllerCategory::MOUSE, controllerName) {
}

void MouseController::init() {
  DigitalGameController::init();

  uint8_t x1Pin, x2Pin, y1Pin, y2Pin;
  getMouseDirectionPins(x1Pin, x2Pin, y1Pin, y2Pin);
  Mapping &mapping = Mapping::getInstance();
  x1Gpio = mapping.getGpioFromPlugPin(x1Pin);
  x2Gpio = mapping.getGpioFromPlugPin(x2Pin);
  y1Gpio = mapping.getGpioFromPlugPin(y1Pin);
  y2Gpio = mapping.getGpioFromPlugPin(y2Pin);
  getMouseButtonPins(button1Pin, button2Pin, button3Pin);

  mouseX = 0;
  mouseY = 0;
  
  // Register this instance for interrupt handlers
  MouseController::instance = this;
  
  attachInterrupt(x1Gpio, interruptMouseX, CHANGE);
  attachInterrupt(x2Gpio, interruptMouseX, CHANGE);
  attachInterrupt(y1Gpio, interruptMouseY, CHANGE);
  attachInterrupt(y2Gpio, interruptMouseY, CHANGE);
}

void MouseController::deinit() {
  detachInterrupt(x1Gpio);
  detachInterrupt(x2Gpio);
  detachInterrupt(y1Gpio);
  detachInterrupt(y2Gpio);
  
  // Clear instance pointer
  MouseController::instance = nullptr;
  
  DigitalGameController::deinit();
}

float MouseController::readAxis(uint8_t axisNumber) {
    if (axisNumber == 0) {
        return mouseX / (float)LIMIT;
    } else {
        return mouseY / (float)LIMIT;
    }
}

uint8_t MouseController::readButton(uint8_t buttonNumber) {
    uint8_t buttonPin;
    switch(buttonNumber) {
        case 0:
            buttonPin = button1Pin;
            break;
        case 1:
            buttonPin = button2Pin;
            break;
        case 2:
        default:
            buttonPin = button3Pin;
            break;
    }
    return (readPinValue(buttonPin) == LOW) ? 1 : 0;
}
