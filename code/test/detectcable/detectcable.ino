#include <Arduino.h>

// detect if apple 2 cabe is connected the wrong side / no joystick detected
// send GND to pin 8 of DE-9
// pullup everywhere else
// all pins should be HIGH except 3 + 4 (buttons)

// Structure pour associer chaque broche DE-9 à son GPIO
struct DsubPin {
  uint8_t de9_pin;   // Numéro de broche DE-9 (1 à 9)
  uint8_t gpio;      // GPIO correspondant
};

// Mapping DE-9 → GPIO selon ton adaptateur
static const DsubPin dsub9_pins[] = {
  { 1, 16 },
  { 2,  4 },
  { 3, 13 },
  { 4, 12 },
  { 5, 14 },
  { 6, 17 },
  { 7, 25 },
 //{ 8, 26 }
   { 9, 27 }
};

int nbpins = 8;

void setup() {
  Serial.begin(115200);
  Serial.println("Test de câble DE-9 — lecture passive");

  // Configure toutes les broches en INPUT_PULLUP
  for (int i = 0; i < nbpins; i++) {
    pinMode(dsub9_pins[i].gpio, INPUT_PULLUP);
  }

  pinMode(26, OUTPUT);
  digitalWrite(26, LOW);    // Fournit GND

}

void loop() {
  Serial.println("État des broches DE-9 :");

  for (int i = 0; i < nbpins; i++) {
    uint8_t de9 = dsub9_pins[i].de9_pin;
    uint8_t gpio = dsub9_pins[i].gpio;
    bool state = digitalRead(gpio); // HIGH = tiré vers le haut, LOW = connecté à GND

    Serial.print("  Broche ");
    Serial.print(de9);
    Serial.print(" : ");
    Serial.println(state ? "HIGH" : "LOW");
  }

  Serial.println("-----------------------------");
  delay(1000);
}
