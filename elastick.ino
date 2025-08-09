#include <Arduino.h>
#include <BleGamepad.h>

const bool paddlesAreAnalog = true;

const int PIN_UP        = 16;
const int PIN_DOWN      = 4;
const int PIN_LEFT      = 13;
const int PIN_RIGHT     = 12;
const int PIN_PADDLE_B  = 14;
const int PIN_BUTTON_1  = 17;
const int PIN_PADDLE_A  = 27;

BleGamepad bleGamepad("Atari 2600", "Elastick", 100);

int axisX = 0;
int axisY = 0;
bool buttonPressed = false;

long previousTime = 0;
float smoothed = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");

  BleGamepadConfiguration config;
  config.setAutoReport(true);
  config.setControllerType(CONTROLLER_TYPE_JOYSTICK); // or CONTROLLER_TYPE_GAMEPAD
  config.setButtonCount(3);         // 3 buttons
  config.setIncludeXAxis(true);     // X-Axis
  config.setIncludeYAxis(true);     // Y-Axis
  config.setIncludeZAxis(false);
  config.setIncludeRxAxis(true);
  config.setIncludeRyAxis(true);
  config.setIncludeRzAxis(false);
  config.setIncludeSlider1(false);
  config.setIncludeSlider2(false);
  config.setHatSwitchCount(0);
  config.setAxesMin(0);
  config.setAxesMax(32767);
  bleGamepad.begin(&config);

  pinMode(PIN_UP,     INPUT_PULLUP);
  pinMode(PIN_DOWN,   INPUT_PULLUP);
  pinMode(PIN_LEFT,   INPUT_PULLUP);
  pinMode(PIN_RIGHT,  INPUT_PULLUP);

  
  pinMode(PIN_BUTTON_1, INPUT_PULLUP);

    pinMode(PIN_PADDLE_A, INPUT_PULLDOWN);
    pinMode(PIN_PADDLE_B, INPUT_PULLDOWN);
//  if (paddlesAreAnalog) {
//    // nothing here yet
//  } else {
//    pinMode(PIN_PADDLE_A, INPUT_PULLUP);
//    pinMode(PIN_PADDLE_B, INPUT_PULLUP);
//  }
}

void loop() {

  int16_t up    = digitalRead(PIN_UP)    == LOW ? -16384 : 0;
  int16_t down  = digitalRead(PIN_DOWN)  == LOW ? 32767 : 16384;
  int16_t left  = digitalRead(PIN_LEFT)  == LOW ? -16384 : 0;
  int16_t right = digitalRead(PIN_RIGHT) == LOW ? 32767 : 16384;

  axisX = right + left;
  axisY = down + up;

  bool btn1 = (digitalRead(PIN_BUTTON_1) == LOW);

  int16_t paddleX = 0;
  int16_t paddleY = 0;

  int16_t rawX = 0;
  int16_t rawY = 0;

  float finalX = 0;

  if (paddlesAreAnalog) {
    // Analog [0-4095] → [0-32767]
    rawX = analogRead(PIN_PADDLE_A);
    rawY = analogRead(PIN_PADDLE_B);
//    paddleX = map(analogRead(PIN_PADDLE_A), 0, 4095, 0, 32767);
//    paddleY = map(analogRead(PIN_PADDLE_B), 0, 4095, 0, 32767);

    finalX = rawX;
    if (finalX < 100) {
      finalX = 100;
    }
    finalX = (finalX - 100) / (4095 - 100); // normalized [0;1]

  // smoothed
//    smoothed = (smoothed * 0.75) + (finalX * 0.25);
//    finalX = smoothed;

    
    finalX = powf(finalX, 0.22f); // curve compensation
    finalX *= 32767;

  } else {
    // Digital
    paddleX = (digitalRead(PIN_PADDLE_A) == LOW) ? 32767 : 0;
    paddleY = (digitalRead(PIN_PADDLE_B) == LOW) ? 32767 : 0;
  }

  // Send to BLE
  if (bleGamepad.isConnected()) {
    bleGamepad.setX(axisX);
    bleGamepad.setY(axisY);
    bleGamepad.setRX((int16_t)finalX);
    bleGamepad.setRY(paddleY);
    if (btn1) {
      bleGamepad.press(BUTTON_1);
    } else {
      bleGamepad.release(BUTTON_1);
    }
  } else {
//    Serial.print("up: ");
//    Serial.print(up);
//    Serial.print(", down: ");
//    Serial.print(down);
//    Serial.print(", left: ");
//    Serial.print(left);
//    Serial.print(", right: ");
//    Serial.println(right);

    Serial.print("Paddle X: ");
    Serial.print(rawX);
    Serial.print(", finalX: ");
    Serial.println(finalX);

//    Serial.print("axisX: ");
//    Serial.print(axisX);
//    Serial.print(", axisY: ");
//    Serial.println(axisY);
    
    delay(1000);
  }


  delay(20);
}
