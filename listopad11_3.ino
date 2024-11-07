#include <CTimer_lib.h>

const int LED[] = {13, 12, 11, 10};

void setup() {
  for(byte i = 0; i < 4; i++){
    pinMode(LED[i], OUTPUT);
    digitalWrite(LED[i], HIGH);
  }
}

void loop() {
  static CTimer t[4];
  for(byte i = 0; i < 4; i++) {
    if (!t[i]) { t[i] = 250 * (i + 1); }
    if (t[i]) { digitalWrite(LED[i], !digitalRead(LED[i])); } 
  }
}
