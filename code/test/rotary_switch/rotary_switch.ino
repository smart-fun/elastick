#define ENCODER_A 18
#define ENCODER_B 19

volatile int encoderPosition = 0;

// void IRAM_ATTR handleEncoder() {
//   if (digitalRead(ENCODER_B) == LOW) {
//     encoderPosition += (digitalRead(ENCODER_A) == HIGH) ? 1 : -1;
//   }
// }
void IRAM_ATTR handleEncoder() {
  static unsigned long lastTime = 0;
  unsigned long now = millis();
  if (now - lastTime > 10) {
    if (digitalRead(ENCODER_B) == LOW) {
      encoderPosition += (digitalRead(ENCODER_A) == HIGH) ? -1 : 1;
    }
    lastTime = now;
  }
}


void setup() {
  Serial.begin(115200);
  pinMode(ENCODER_A, INPUT_PULLUP);
  pinMode(ENCODER_B, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ENCODER_B), handleEncoder, FALLING);
}

void loop() {
  static int lastPos = 0;
  if (encoderPosition != lastPos) {
    Serial.println(encoderPosition);
    lastPos = encoderPosition;
  }
}




// #define ENCODER_A 32
// #define ENCODER_B 33

// volatile int encoderPosition = 0;

// unsigned long lastTime = 0;
// const int debounceDelay = 0; // en ms

// void IRAM_ATTR handleEncoder() {
//   unsigned long now = millis();
//   if (now - lastTime > debounceDelay) {
//     bool bState = digitalRead(ENCODER_B);
//     encoderPosition += bState ? 1 : -1;
//     lastTime = now;
//   }
// }

// void setup() {
//   Serial.begin(115200);
//   pinMode(ENCODER_A, INPUT_PULLUP);
//   pinMode(ENCODER_B, INPUT_PULLUP);

//   attachInterrupt(digitalPinToInterrupt(ENCODER_A), handleEncoder, FALLING);
// }

// void loop() {
//   static int lastPos = 0;
//   if (encoderPosition != lastPos) {
//     Serial.println(encoderPosition);
//     lastPos = encoderPosition;
//   }
// }
