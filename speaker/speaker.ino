const int pinTone = D8;

void setup() {
  // put your setup code here, to run once:
  analogWrite(pinTone,255);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWriteFreq(440);
  delay(500);
  analogWriteFreq(587);
  delay(500);
}
