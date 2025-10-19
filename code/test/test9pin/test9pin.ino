
#include <Arduino.h>

enum ES_GPIO {
  // 2 pins for screen (i2c)
  ES_GPIO_SDA = 21,
  ES_GPIO_SCL = 22,
  
  // 3 pins for Rotary Switch
  ES_GPIO_BUTTON_VALIDATE = 5,
  ES_GPIO_ROTARY_ENCODER_A = 18,
  ES_GPIO_ROTARY_ENCODER_B = 19,
  
  // 9 pins for DE-9 connector
  ES_GPIO_DE9_DIGITAL_1 = 4,
  ES_GPIO_DE9_DIGITAL_2 = 17,
  ES_GPIO_DE9_DIGITAL_3 = 26,
  ES_GPIO_DE9_DIGITAL_4 = 14,
  ES_GPIO_DE9_ANALOG_5 = 13,
  ES_GPIO_DE9_DIGITAL_6 = 16,
  ES_GPIO_DE9_DIGITAL_7 = 25,
  ES_GPIO_DE9_DIGITAL_8 = 27,
  ES_GPIO_DE9_ANALOG_9 = 12,
};

uint8_t nbpins = 9;
uint8_t VCC_GIPO = ES_GPIO_DE9_DIGITAL_7;
uint8_t GND_GIPO = ES_GPIO_DE9_DIGITAL_8;

struct DsubPin {
  uint8_t de9_pin;   // Numéro de broche DE-9 (1 à 9)
  uint8_t gpio;      // GPIO correspondant
};

static const DsubPin dsub9[] = {
  { 1, ES_GPIO::ES_GPIO_DE9_DIGITAL_1 },
  { 2, ES_GPIO::ES_GPIO_DE9_DIGITAL_2 },
  { 3, ES_GPIO::ES_GPIO_DE9_DIGITAL_3 },
  { 4, ES_GPIO::ES_GPIO_DE9_DIGITAL_4 },
  { 5, ES_GPIO::ES_GPIO_DE9_ANALOG_5 },
  { 6, ES_GPIO::ES_GPIO_DE9_DIGITAL_6 },
  { 7, ES_GPIO::ES_GPIO_DE9_DIGITAL_7 },
  { 8, ES_GPIO::ES_GPIO_DE9_DIGITAL_8 },
  { 9, ES_GPIO::ES_GPIO_DE9_ANALOG_9 }
};

void setup() {
  Serial.begin(115200);
  Serial.println("Test de câble DE-9");

  for (int i = 0; i < nbpins; i++) {
    uint8_t gpio = dsub9[i].gpio ;
    if (gpio != VCC_GIPO && gpio != GND_GIPO) {
      pinMode(gpio, INPUT_PULLUP);
    }
  }
  pinMode(VCC_GIPO, OUTPUT);
  digitalWrite(VCC_GIPO, HIGH);

  pinMode(GND_GIPO, OUTPUT);
  digitalWrite(GND_GIPO, LOW);
}

void loop() {
  Serial.println("État des broches DE-9 :");

  for (int i = 0; i < nbpins; i++) {
    uint8_t de9 = dsub9[i].de9_pin;
    uint8_t gpio = dsub9[i].gpio;
    bool state = digitalRead(gpio); // HIGH = tiré vers le haut, LOW = connecté à GND

    Serial.print("  Broche ");
    Serial.print(de9);
    Serial.print(" : ");
    Serial.println(state ? "HIGH" : "LOW");
  }

  Serial.println("-----------------------------");
  delay(1000);
}