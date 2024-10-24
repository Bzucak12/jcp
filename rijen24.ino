const int LED[] = {13, 12, 11, 10};
const int LED2[] = {10, 11, 12, 13};
const int TL[] = {A1, A2, A3};
byte stav = 0;

void setup() {
  for(byte i = 0; i < 4; i++){
    pinMode(LED[i], OUTPUT);
    digitalWrite(LED[i], HIGH);
  }
  for(byte i = 0; i < 3; i++) {
    pinMode(TL[i], INPUT_PULLUP);
  }
}

void loop() {
  if(!digitalRead(TL[0])) {
    stav++;
    for(byte i = 0; i < 4; i++){
      if((stav - i) > 0){
        digitalWrite(LED[i], LOW);
      }
    }
    for(byte i = 0; i < 4; i++){
      if((stav - i) > 4){
        digitalWrite(LED2[i], HIGH);
      }
    }
    delay(250);
  }
  if(stav >= 8) {
    stav = 0;
  }
}
