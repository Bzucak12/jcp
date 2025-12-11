#include <TimerOne.h>
#include <Wire.h>
#include <MultiFuncShield.h>

const int LED[] = { 13, 12, 11, 10 };
const int TL[] = { A1, A2, A3 };
unsigned long tl_stisk = 0;

const int nabezna_hrana = 0;
const int sestupna_hrana = 1;
const int trvale_sepnuto = 2;
const int trvale_rozepnuto = 3;

int readTL(const byte tlacitko) {
  static bool sepnuto[3] = { false, false, false };
  if (!digitalRead(TL[tlacitko])) {
    if (!sepnuto[tlacitko]) {
      sepnuto[tlacitko] = true;
      return nabezna_hrana;
    } else {
      return trvale_sepnuto;
    }
  } else {
    if (sepnuto[tlacitko]) {
      sepnuto[tlacitko] = false;
      return sestupna_hrana;
    } else {
      return trvale_rozepnuto;
    }
  }
}

void setup() {
  Serial.begin(9600);
  for (byte i = 0; i < 4; i++) {
    pinMode(LED[i], OUTPUT);
    digitalWrite(LED[i], HIGH);
  }
  for (byte i = 0; i < 3; i++) {
    pinMode(TL[i], INPUT_PULLUP);
  }
  Timer1.initialize();
  MFS.initialize(&Timer1);
}

void loop() {
  cti_serial();
  cti_tl();
  vypis_na_seg();
}

void cti_tl() {
  if (readTL(0) == 1) {
    if (tl_stisk >= 65535) {
      tl_stisk = 0;
      Serial.println("Počet stisknutí tlačítka: 0");
    } else {
      Serial.print("Počet stisknutí tlačítka: ");
      Serial.println(++tl_stisk);
    }
  }
  if (readTL(1) == 1) {
    if (tl_stisk) {
      Serial.print("Počet stisknutí tlačítka: ");
      Serial.println(--tl_stisk);
    }
  }
  if (readTL(2) == 1) {
    if (tl_stisk != 0) {
      tl_stisk = 0;
      Serial.print("Počet stisknutí tlačítka: ");
      Serial.println(tl_stisk);
    } else {
      Serial.println("Počet stisknutí je už: 0");
    }
  }
}

void cti_serial() {
  if (Serial.available() > 0) {
    tl_stisk = Serial.parseInt();

    if (tl_stisk >= 65536) {
      Serial.println("Zadaný počet stisknutí je mimo rozsah!");
      tl_stisk = 0;
    }
    if (Serial.read() == '\n') {
      Serial.print("Počet stisknutí tlačítka: ");
      Serial.println(tl_stisk);
    }
  }
}

void vypis_na_seg() {
  String DisNum = String(tl_stisk, HEX);
  MFS.write(DisNum.c_str());
}
