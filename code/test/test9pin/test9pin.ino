#include <Arduino.h>

/* --------------------------------------------------------------------------
   Mapping GPIO ↔ DE-9
   -------------------------------------------------------------------------- */

enum ES_GPIO {
  ES_GPIO_DE9_DIGITAL_1 = 4,   // Y2
  ES_GPIO_DE9_DIGITAL_2 = 17,  // X1
  ES_GPIO_DE9_DIGITAL_3 = 26,  // Y1
  ES_GPIO_DE9_DIGITAL_4 = 14,  // X2
  ES_GPIO_DE9_ANALOG_5  = 13,
  ES_GPIO_DE9_DIGITAL_6 = 16,  // Button 1
  ES_GPIO_DE9_DIGITAL_7 = 25,  // VCC
  ES_GPIO_DE9_DIGITAL_8 = 27,  // GND
  ES_GPIO_DE9_ANALOG_9  = 12
};

// Souris Amiga/Atari
#define PIN_X1 ES_GPIO_DE9_DIGITAL_2
#define PIN_X2 ES_GPIO_DE9_DIGITAL_4
#define PIN_Y1 ES_GPIO_DE9_DIGITAL_3
#define PIN_Y2 ES_GPIO_DE9_DIGITAL_1
#define PIN_BTN1 ES_GPIO_DE9_DIGITAL_6

/* --------------------------------------------------------------------------
   Quadrature table
   -------------------------------------------------------------------------- */

static const int8_t quadTable[16] = {
    0,  -1, +1,  0,
   +1,   0,  0, -1,
   -1,   0,  0, +1,
    0,  +1, -1,  0
};

/* --------------------------------------------------------------------------
   États quadrature + compteurs
   -------------------------------------------------------------------------- */

volatile uint8_t prevX = 0;
volatile uint8_t prevY = 0;

volatile int rawX = 0;
volatile int rawY = 0;

volatile int mouseX = 0;
volatile int mouseY = 0;

volatile int x1Changed = 0;
volatile int x2Changed = 0;
volatile int y1Changed = 0;
volatile int y2Changed = 0;

void IRAM_ATTR irX1() {
  ++x1Changed;
}
void IRAM_ATTR irX2() {
  ++x2Changed;
}
void IRAM_ATTR irY1() {
  ++y1Changed;
}
void IRAM_ATTR irY2() {
  ++y2Changed;
}

/* --------------------------------------------------------------------------
   Lecture GPIO ultra rapide
   -------------------------------------------------------------------------- */

static inline uint8_t fastRead(uint8_t pin) {
  return (GPIO.in >> pin) & 1;
}

/* --------------------------------------------------------------------------
   ISR X (une seule ISR pour X1)
   -------------------------------------------------------------------------- */

void IRAM_ATTR isrX() {
  uint8_t A = fastRead(PIN_X1);
  uint8_t B = fastRead(PIN_X2);
  uint8_t s = (A << 1) | B;

  uint8_t index = (prevX << 2) | s;
  int8_t mv = quadTable[index];
  rawX += mv;

  if (rawX >= 2) { mouseX++; rawX -= 2; }
  else if (rawX <= -2) { mouseX--; rawX += 2; }

  prevX = s;
}

/* --------------------------------------------------------------------------
   ISR Y (une seule ISR pour Y1)
   -------------------------------------------------------------------------- */

void IRAM_ATTR isrY() {
  uint8_t A = fastRead(PIN_Y1);
  uint8_t B = fastRead(PIN_Y2);
  uint8_t s = (A << 1) | B;

  uint8_t index = (prevY << 2) | s;
  int8_t mv = quadTable[index];
  rawY += mv;

  if (rawY >= 2) { mouseY++; rawY -= 2; }
  else if (rawY <= -2) { mouseY--; rawY += 2; }

  prevY = s;
}

/* --------------------------------------------------------------------------
   Table DE-9 pour affichage
   -------------------------------------------------------------------------- */

struct DsubPin {
  uint8_t de9_pin;
  uint8_t gpio;
};

static const DsubPin dsub9[] = {
  { 1, ES_GPIO_DE9_DIGITAL_1 },
  { 2, ES_GPIO_DE9_DIGITAL_2 },
  { 3, ES_GPIO_DE9_DIGITAL_3 },
  { 4, ES_GPIO_DE9_DIGITAL_4 },
  { 5, ES_GPIO_DE9_ANALOG_5 },
  { 6, ES_GPIO_DE9_DIGITAL_6 },
  { 7, ES_GPIO_DE9_DIGITAL_7 },
  { 8, ES_GPIO_DE9_DIGITAL_8 },
  { 9, ES_GPIO_DE9_ANALOG_9 }
};

uint8_t nbpins = 9;

/* --------------------------------------------------------------------------
   SETUP
   -------------------------------------------------------------------------- */

void setup() {
  Serial.begin(115200);
  Serial.println("Test DE-9 + Mouse Quadrature (version stable)");

  // Configure pins
  for (int i = 0; i < nbpins; i++) {
    uint8_t gpio = dsub9[i].gpio;
    if (gpio != ES_GPIO_DE9_DIGITAL_7 && gpio != ES_GPIO_DE9_DIGITAL_8) {
      pinMode(gpio, INPUT_PULLUP);
    }
  }

  pinMode(ES_GPIO_DE9_DIGITAL_7, OUTPUT);
  digitalWrite(ES_GPIO_DE9_DIGITAL_7, HIGH);

  pinMode(ES_GPIO_DE9_DIGITAL_8, OUTPUT);
  digitalWrite(ES_GPIO_DE9_DIGITAL_8, LOW);

  // Init quadrature states
  prevX = (fastRead(PIN_X1) << 1) | fastRead(PIN_X2);
  prevY = (fastRead(PIN_Y1) << 1) | fastRead(PIN_Y2);

  // Interruptions (une seule par axe)
  attachInterrupt(digitalPinToInterrupt(PIN_X1), isrX, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_X2), isrX, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_Y1), isrY, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_Y2), isrY, CHANGE);
/*
  attachInterrupt(digitalPinToInterrupt(PIN_X1), irX1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_X2), irX2, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_Y1), irY1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_Y2), irY2, CHANGE);
  */
}

/* --------------------------------------------------------------------------
   LOOP
   -------------------------------------------------------------------------- */

void loop() {
  Serial.println("État des broches DE-9 :");

  for (int i = 0; i < nbpins; i++) {
    uint8_t de9 = dsub9[i].de9_pin;
    uint8_t gpio = dsub9[i].gpio;
    bool state = fastRead(gpio);

    Serial.print("  Broche ");
    Serial.print(de9);
    Serial.print(" : ");
    Serial.println(state ? "HIGH" : "LOW");

    // Reset X,Y with button 1 or 2 (pin 6/9)
    if ((de9 == 6 || de9 == 9) && !state) {
      mouseX = 0;
      mouseY = 0;
      x1Changed = 0;
      x2Changed = 0;
      y1Changed = 0;
      y2Changed = 0;
    }
  }

  Serial.print("Mouse X = ");
  Serial.print(mouseX);
  Serial.print("   Y = ");
  Serial.println(mouseY);
/*
  Serial.print("x1Changed = ");
  Serial.print(x1Changed);
  Serial.print(",x2 = ");
  Serial.print(x2Changed);
  Serial.print(",y1 = ");
  Serial.print(y1Changed);
  Serial.print(",y2 = ");
  Serial.println(y1Changed);
*/
  

  Serial.println("-----------------------------");
  delay(1000);
}
