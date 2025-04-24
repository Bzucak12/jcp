void setup() {
  pinMode(8, OUTPUT);
}

void loop() {
  // T = 10,62us | f = 94,14kHz
  /*delayMicroseconds(1);
  digitalWrite(8, !digitalRead(8));*/

  // T = 6,75us | f = 148,1kHz
  /*delayMicroseconds(1);
  digitalWrite(8, 1);
  delayMicroseconds(1);
  digitalWrite(8, 0);*/

  // T = 1,249us | f= 800,9kHz
  /*delayMicroseconds(1);
  if (PORTB & (1 << PORTB0)) {
    PORTB ^= (1 << PORT0);
  } else {
    PORTB |= (1 << PORT0);
  }*/

  // T = 1,249us | f = 800,9kHz
  /*delayMicroseconds(1);
  if (testFlag(PORTB, PORTB0)) {
    PORTB ^= (1 << PORT0);
  } else {
    PORTB |= (1 << PORT0);
  }*/

  // T = 562,35ns | f = 1,778MHz
  /*delayMicroseconds(1);
  PORTB ^= (1 << PORT0);
  delayMicroseconds(1);
  PORTB |= (1 << PORT0);*/
}

bool testFlag(int value, int flag) {
  return (value & (1 << flag)) == (1 << flag);
}
