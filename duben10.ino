const byte LED = 13;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(11, OUTPUT);
  Serial.begin(9600);
  PORTB = 0b11010111;
}

void loop() {
  delay(1000);

  if (PORTB & 0b00101000) {
    PORTB &= 0b11010111;
  }
  else {
    PORTB |= 0b00101000;
  }
}
