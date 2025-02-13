const byte LED = 13;
const byte TL_PRE = 2;
unsigned long hodnota;

void preruseni() {
  volatile static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > 50) {
    digitalWrite(LED, !digitalRead(LED));
    Serial.println(++hodnota);
  }
  last_interrupt_time = interrupt_time;
}

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, 0);
  attachInterrupt(digitalPinToInterrupt(TL_PRE), &preruseni, CHANGE);
  pinMode(8, OUTPUT);
  digitalWrite(8, 1);
}

void loop() {
  delay(100000);
  // ...
}
