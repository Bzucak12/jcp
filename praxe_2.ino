const byte pinLatch = 4;
const byte pinClk = 7;
const byte pinData = 8;

const byte mapaSegment[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
const byte velMapaSegment = sizeof(mapaSegment) / sizeof(mapaSegment[0]);
const byte mapaCisloSeg[] = {0xF1, 0xF2, 0xF4, 0xF8};
const byte velCisloSeg = sizeof(mapaCisloSeg) / sizeof(mapaCisloSeg[0]);

void setup() {
  pinMode(pinLatch, OUTPUT);
  pinMode(pinClk, OUTPUT);
  pinMode(pinData, OUTPUT);
}

void loop() {

}

void zapisCisloNaSegmet(const byte segment, const byte hodnota) {
  if ((segment >= velMapaSegment) || (hodnota >= velCisloSeg)){
    return;
  }
  digitalWrite(pinLatch, LOW);
  shiftOut(pinData, pinClk, MSBFIRST, mapaSegment[hodnota]);
  shiftOut(pinData, pinClk, MSBFIRST, mapaCisloSeg[segment]);
  digitalWrite(pinLatch, HIGH);
}
