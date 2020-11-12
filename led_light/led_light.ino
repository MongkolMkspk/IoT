const int red = D0;
void setup() {
  // put your setup code here, to run once:
  pinMode(red,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int brightness;
  for(brightness=0;brightness<1024;brightness+=5){
    analogWrite(red,brightness);
    delay(30);
  }
  for(brightness;brightness>-1;brightness-=5){
    analogWrite(red,brightness);
    delay(30);
  }
}
