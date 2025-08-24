#include <Arduino.h>

// RC Test Sample Reads analog joystick positions using capacitor charge/discharge timing.
// Also checks button states.
// Behavior adapts to different joystick types (Apple II, CoCo, PC) via config flags.
// Typical RC times (µs):
// Apple II: ~2000
// CoCo: ~1300
// PC: ~2000
// Atari Paddle: ~14000

bool coco = false;
bool pc = true;  // pc or atari paddle
bool apple = false;


#define pinH (14)
#define pinV (27)
#define vcc (25)
#define gnd (26)

#define BT1 (12)
#define BT2 (13)

unsigned long timeoutMs = 500;
unsigned long timeoutMicros = timeoutMs * 1000;


void setup() {
  Serial.begin(115200);
  Serial.println("Starting");
  
  pinMode(gnd, OUTPUT);
  digitalWrite(gnd, LOW);

  pinMode(vcc, OUTPUT);
  digitalWrite(vcc, HIGH);
  
}


void loop() {

  unsigned long durationX = 0;
  unsigned long durationY = 0;

  if (coco) {
      durationX = mesureTempsChargeDecharge(pinH);
      durationY = mesureTempsChargeDecharge(pinV);
  } else if (pc || apple) {
    decharge(pinH);
    durationX = durationToHigh(pinH);
    delayMicroseconds(100);
    decharge(pinV);
    durationY = durationToHigh(pinV);
    delayMicroseconds(100);
  } else {
    Serial.println("no type selected");
  }

  Serial.print("X: ");
  Serial.print(durationX);
  Serial.print(", Y: ");
  Serial.println(durationY);

  bool b1 = false;
  bool b2 = false;
  if (apple) {
    pinMode(BT1, INPUT);
    pinMode(BT2, INPUT);
    b1 = digitalRead(BT1) == HIGH;
    b2 = digitalRead(BT2) == HIGH;
  } else {    
    pinMode(BT1, INPUT_PULLUP);
    pinMode(BT2, INPUT_PULLUP);
    b1 = digitalRead(BT1) == LOW;
    b2 = digitalRead(BT2) == LOW;
    
  }
  Serial.print("Button 1 : ");
  Serial.println(b1 ? "Pressed" : "Released");
  Serial.print("Button 2 : ");
  Serial.println(b2 ? "Pressed" : "Released");


  delay(1000);
}

void charge(int pin) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);
  delay(5);
}

void decharge(int pin) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  delay(5);
}

unsigned long durationToHigh(int pin) {
  pinMode(pin, INPUT);
  unsigned long start = micros();
  while (digitalRead(pin) == LOW && micros() - start < timeoutMicros) {}
  return micros() - start;
}

unsigned long durationToLow(int pin) {
  pinMode(pin, INPUT);
  unsigned long start = micros();
  while (digitalRead(pin) == HIGH && micros() - start < timeoutMicros) {}
  return micros() - start;
}

unsigned long mesureTempsChargeDecharge(int pin) {
    charge(pin);
    unsigned long durationDecharge = durationToLow(pin);
    delayMicroseconds(100);
    decharge(pin);
    unsigned long durationCharge = durationToHigh(pin);
    delayMicroseconds(100);
    // TO BE IMPROVED as returns symetrical values for left/right, but should keep separation for charge=right/discharge=left
    return (durationDecharge < durationCharge ? durationDecharge : durationCharge);
}
