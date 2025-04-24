void setup() {
  pinMode(8, OUTPUT);
}

void loop() {
  // T = 10,62us | f = 94,14kHz | FallTime = <20ns | RiseTime = <20ns
  delayMicroseconds(1);
  digitalWrite(8, !digitalRead(8));

  // T = 6,75us | f = 148,1kHz | FallTime = <20ns | RiseTime = <20ns
  /*delayMicroseconds(1);
  digitalWrite(8, 1);
  delayMicroseconds(1);
  digitalWrite(8, 0);*/

  // T = 1,251us | f = 799,6kHz | FallTime = <12ns | RiseTime = 20ns
  /*delayMicroseconds(1);
  if (PORTB & (1 << PORTB0)) {
    PORTB ^= (1 << PORT0);
  } else {
    PORTB |= (1 << PORT0);
  }*/

  // T = 1,251us | f = 799,6kHz | FallTime = 20ns | RiseTime = <16ns
  /*delayMicroseconds(1);
  if (testFlag(PORTB, PORTB0)) {
    PORTB ^= (1 << PORT0);
  } else {
    PORTB |= (1 << PORT0);
  }*/

  // T = 562,67ns | f = 1,777MHz | FallTime = 20ns | RiseTime = <16ns
  /*delayMicroseconds(1);
  PORTB ^= (1 << PORT0);
  delayMicroseconds(1);
  PORTB |= (1 << PORT0);*/
}

bool testFlag(int value, int flag) {
  return (value & (1 << flag)) == (1 << flag);
}
