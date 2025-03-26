/*
Clock Select Bits (CS12, CS11, CS10) - Timer Prescaler Settings:
 
CS12 | CS11 | CS10 | Prescaler / Clock Source
0    |  0   |  0   | No clock (Timer Stopped)
0    |  0   |  1   | No prescaler (Direct Clock)
0    |  1   |  0   | Prescaler = 8
0    |  1   |  1   | Prescaler = 64
1    |  0   |  0   | Prescaler = 256
1    |  0   |  1   | Prescaler = 1024
1    |  1   |  0   | External clock (falling edge)
1    |  1   |  1   | External clock (rising edge)
 
Waveform Generation Mode (WGM12, WGM11, WGM10) - Timer Mode Settings:
 
WGM12 | WGM11 | WGM10 | Mode                       | Description
0     |  0    |  0    | Normal                     | Timer counts up to MAX
0     |  0    |  1    | PWM, Phase Correct 8-bit   | PWM with phase-correct behavior
0     |  1    |  0    | PWM, Phase Correct 9-bit   |
0     |  1    |  1    | PWM, Phase Correct 10-bit  |
1     |  0    |  0    | CTC (Clear Timer on Compare Match) | Timer resets at OCR1A match
1     |  0    |  1    | Fast PWM 8-bit             |
1     |  1    |  0    | Fast PWM 9-bit             |
1     |  1    |  1    | Fast PWM 10-bit            |
*/

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

  // Nastavení časovače/čítače 1
  TCCR1A = 0; // Nastavíme že čítač jde od 0
  TCCR1B = 0; // Nulování módu čítače
  TCCR1B |= (1 << WGM12); // Nastavení CTC módu -> if (a == b) {}
  // Nastavení frekvence
  // Frekvence arduina je 16 MHz
  // Výsledná frekvence (16 MHz / prescaler)
  // Příklad chceme předděličku 1024
  TCCR1B |= ((1 << CS12) | (1 << CS10)); // Nastavujeme předděličku
  OCR1A = 15625; // Nastavení hodnoty kdy dojde k přerušení
  TIMSK1 = (1 << OCIE1A); // Zapnutí Timer1/čítač1 porovnávání
  sei(); // Zapnutí globáních čítačů a interruptů
}

// Definujeme si pomocnou proměnnou
volatile unsigned long g_counter = 0;
// Definice funkce přerušení
ISR(TIMER1_COMPA_vect) {
    g_counter++; // add g_counter, 1
}

void loop() {
  if (g_counter >= 10) {
    Serial.println("10 seconds elapsed!");
    g_counter = 0;
  }
}
