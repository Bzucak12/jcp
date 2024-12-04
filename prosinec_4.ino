#include <TimerOne.h>
#include <Wire.h>
#include <MultiFuncShield.h>

const int LED[] = {13, 12, 11, 10};
const int TL[] = {A1, A2, A3};
unsigned long tl_stisk = 0;

void setup() {
  Serial.begin(9600);
  for(byte i = 0; i < 4; i++){
    pinMode(LED[i], OUTPUT);
    digitalWrite(LED[i], HIGH);
  }
  for(byte i = 0; i < 3; i++){
    pinMode(TL[i], INPUT_PULLUP);
  }
  Timer1.initialize();
  MFS.initialize(&Timer1);
}

void loop() {
  if (!digitalRead(TL[0])) {
    Serial.print("Počet stisknutí tlačítka: ");
    Serial.println(++tl_stisk);

    while (!digitalRead(TL[0])) {
      delay(10);
    }
  }
  if (!digitalRead(TL[1]) && tl_stisk) {
    Serial.print("Počet stisknutí tlačítka: ");
    Serial.println(--tl_stisk);

    while (!digitalRead(TL[1])) {
      delay(10);
    }
  }
  if (!digitalRead(TL[2])) {
    if (tl_stisk != 0) {
      tl_stisk = 0;
      Serial.print("Počet stisknutí tlačítka: ");
      Serial.println(tl_stisk);
    } else {
      Serial.println("Počet stisknutí je už: 0");
    }

    while (!digitalRead(TL[2])) {
      delay(10);
    }
  }
  MFS.write((int)tl_stisk);
}
