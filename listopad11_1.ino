const int LED[] = {13, 12, 11, 10};
const int interval[] = {250, 500, 750, 1000};
unsigned long predMills[] = {0, 0, 0, 0};

void setup() {
  for(byte i = 0; i < 4; i++){
    pinMode(LED[i], OUTPUT);
    digitalWrite(LED[i], HIGH);
  }
}

void loop() {
  unsigned long aktMills = millis();
  for(byte i = 0; i < 4; i++){
    if (aktMills - predMills[i] >= interval[i]) {
      predMills[i] = aktMills;
      digitalWrite(LED[i], !digitalRead(LED[i]));
    }
  }
}
