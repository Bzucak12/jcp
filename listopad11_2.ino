const int LED[] = {13, 12, 11, 10};

void setup() {
  for(byte i = 0; i < 4; i++){
    pinMode(LED[i], OUTPUT);
    digitalWrite(LED[i], HIGH);
  }
}

void loop() {
  static const int interval[] = {250, 500, 750, 1000};
  static unsigned long t[] = {millis(), millis(), millis(), millis()};
  for(byte i = 0; i < 4; i++) {
     if (myMillis(t[i], interval[i])) { digitalWrite(LED[i], !digitalRead(LED[i])); } 
  }
}

bool myMillis(unsigned long& start, unsigned long ms) {
  if (!start) {
    start = millis();
  }
  unsigned long now = millis();
  if ((now - start) < ms) {
    return false;
  }
  start = now;
  return true;
}
