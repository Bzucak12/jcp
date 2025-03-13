void setup() {
  Serial.begin(9600);

  // Nastavit Timer1
  TCCR1A = 0;                                         // normální mód
  TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);  // CTC mód, prescaler 1024
  OCR1A = 3124;                                        // (16MHz / (64 * 1kHz)) -1

  TIMSK1 = (1 << OCIE1A);                             // Povolit porvnávání Timer1 a přerušení

  sei();                                              // Povolit globalní přerušení
}

ISR(TIMER1_COMPA_vect) {
  Serial.println("1u second elapsed!");
}

void loop() {
  
}
