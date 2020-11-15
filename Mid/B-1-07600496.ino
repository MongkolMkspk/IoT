
#include <Adafruit_NeoPixel.h>

#define Pin 10
#define NumLed 2

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NumLed, Pin, NEO_RGB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  pinMode(Pin,OUTPUT);
  pixels.begin();
  pixels.clear();

}

void loop() {
  // put your main code here, to run repeatedly:

  int ana = analogRead(A0);
  float anaVal=map((A0),0,1023,0,255);
  float anadelay=ana*(3.3/1023);
  if(anadelay<0.5){
    anadelay=0.5;
  }
  float anadelayTrue=1000/anadelay;
  pixels.setPixelColor(0,pixels.Color(0,anaVal,0));
  pixels.setPixelColor(1,pixels.Color(0,0,0));
  pixels.show();
  delay(anadelayTrue);
  pixels.setPixelColor(0,pixels.Color(0,0,0));
  pixels.setPixelColor(1,pixels.Color(0,anaVal,0));
  pixels.show();
  
  delay(anadelayTrue);
  
}
