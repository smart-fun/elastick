#include "mouse_controller.h"
#include "mapping.h"


#define LIMIT (100)

uint8_t x1Gpio = 0;
uint8_t x2Gpio = 0;
uint8_t y1Gpio = 0;
uint8_t y2Gpio = 0;

volatile uint8_t prevX = 0;
volatile uint8_t prevY = 0;

volatile int rawX = 0;
volatile int rawY = 0;

volatile int mouseX = 0;
volatile int mouseY = 0;

/* --------------------------------------------------------------------------
   Quadrature table
   -------------------------------------------------------------------------- */
static const int8_t quadTable[16] = {
    0,  -1, +1,  0,
   +1,   0,  0, -1,
   -1,   0,  0, +1,
    0,  +1, -1,  0
};

static inline uint8_t fastRead(uint8_t pin) {
  return (GPIO.in >> pin) & 1;
}

void IRAM_ATTR interruptMouseX() {
  uint8_t A = fastRead(x1Gpio);
  uint8_t B = fastRead(x2Gpio);
  uint8_t s = (A << 1) | B;

  uint8_t index = (prevX << 2) | s;
  int8_t mv = quadTable[index];
  rawX += mv;

  if (rawX >= 2) { mouseX++; rawX -= 2; }
  else if (rawX <= -2) { mouseX--; rawX += 2; }

  if (mouseX > LIMIT) {
    mouseX = LIMIT;
  } else if (mouseX < -LIMIT) {
    mouseX = -LIMIT;
  }

  prevX = s;
}

void IRAM_ATTR interruptMouseY() {
  uint8_t A = fastRead(y1Gpio);
  uint8_t B = fastRead(y2Gpio);
  uint8_t s = (A << 1) | B;

  uint8_t index = (prevY << 2) | s;
  int8_t mv = quadTable[index];
  rawY += mv;

  if (rawY >= 2) { mouseY++; rawY -= 2; }
  else if (rawY <= -2) { mouseY--; rawY += 2; }

  if (mouseY > LIMIT) {
    mouseY = LIMIT;
  } else if (mouseY < -LIMIT) {
    mouseY = -LIMIT;
  }

  prevY = s;
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
  attachInterrupt(x1Gpio, interruptMouseX, CHANGE);
  attachInterrupt(x2Gpio, interruptMouseX, CHANGE);
  attachInterrupt(y1Gpio, interruptMouseY, CHANGE);
  attachInterrupt(y2Gpio, interruptMouseY, CHANGE);
}

void MouseController::deinit() {
  DigitalGameController::deinit();

  detachInterrupt(x1Gpio);
  detachInterrupt(x2Gpio);
  detachInterrupt(y1Gpio);
  detachInterrupt(y2Gpio);
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
