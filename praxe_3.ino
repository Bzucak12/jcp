const byte pinLatch = 4;
const byte pinClk = 7;
const byte pinData = 8;

const byte mapaSegment[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90, 0x08, 0x00, 0x46, 0x40, 0x06, 0x0E};
const byte velMapaSegment = sizeof(mapaSegment) / sizeof(mapaSegment[0]);
const byte mapaCisloSeg[] = {0xF1, 0xF2, 0xF4, 0xF8};
const byte velCisloSeg = sizeof(mapaCisloSeg) / sizeof(mapaCisloSeg[0]);

const byte LED[] = { 13, 12, 11, 10 };
const byte TL[] = { A1, A2, A3 };
short tl_stisk = 0;
byte zobrazeni = 0; // 0 - HEX  1 - DEC

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
  pinMode(pinLatch, OUTPUT);
  pinMode(pinClk, OUTPUT);
  pinMode(pinData, OUTPUT);
}

void loop() {
  cti_serial();
  cti_tl();
  vypis_na_seg();
}

void cti_tl() {
  if (readTL(0) == 1) {
    Serial.print("Počet stisknutí tlačítka: ");
    Serial.println(++tl_stisk);
  }
  if (readTL(1) == 1) {
    Serial.print("Počet stisknutí tlačítka: ");
    Serial.println(--tl_stisk);
  }
  if (readTL(2) == 1) {
    // if (tl_stisk != 0) {
    //   tl_stisk = 0;
    //   Serial.print("Počet stisknutí tlačítka: ");
    //   Serial.println(tl_stisk);
    // } else {
    //   Serial.println("Počet stisknutí je už: 0");
    // }
    zobrazeni = !zobrazeni;
    Serial.println("Zmena stavu");
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
  byte jednotky = 0;
  byte desitky = 0;
  byte stovky = 0;
  byte tisice = 0;
  if (!zobrazeni) {
    jednotky = tl_stisk & 0x000F;
    desitky = (tl_stisk & 0x00F0) >> 4;
    stovky = (tl_stisk & 0x0F00) >> 8;
    tisice = ((tl_stisk & 0xF000) >> 12);
  }
  if (zobrazeni) {
    jednotky = tl_stisk % 10;
    desitky = (tl_stisk / 10) % 10;
    stovky = (tl_stisk / 100) % 10;
    tisice = (tl_stisk / 1000);
  }

  zapisCisloNaSegment(3, jednotky);
  zapisCisloNaSegment(2, desitky);
  zapisCisloNaSegment(1, stovky);
  zapisCisloNaSegment(0, tisice);
}

void zapisCisloNaSegment(const byte segment, byte hodnota) {
  if ((segment >= velCisloSeg) || (hodnota >= velMapaSegment)){
    return;
  }
  digitalWrite(pinLatch, LOW);
  shiftOut(pinData, pinClk, MSBFIRST, mapaSegment[hodnota]);
  shiftOut(pinData, pinClk, MSBFIRST, mapaCisloSeg[segment]);
  digitalWrite(pinLatch, HIGH);
}
