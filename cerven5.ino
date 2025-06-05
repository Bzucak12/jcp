const int LED[] = {13, 12, 11, 10};
const byte TL = A1;
unsigned long stisk = 0;

void setup() {
  for(byte i = 0; i < 4; i++){
    pinMode(LED[i], OUTPUT);
    digitalWrite(LED[i], HIGH);
  }
  pinMode(TL, INPUT_PULLUP);
}

void loop() {
  if (!digitalRead(TL)) {
    stisk++;
    for(byte i = 0; i < 4; i++){
      digitalWrite(LED[i], !(stisk % 5 >= i+1));
    }
  }
  delay(100);
}
