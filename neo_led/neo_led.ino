#include <Adafruit_NeoPixel.h>
#define NUMSLEDs 2
#define PINSLEDs 10
Adafruit_NeoPixel SLEDs =Adafruit_NeoPixel(NUMSLEDs,PINSLEDs,NEO_RGB + NEO_KHZ800);
void setup() {
  // put your setup code here, to run once:
  pinMode(PINSLEDs,OUTPUT);
  SLEDs.begin();//this initializes the neopixel liabrary
  SLEDs.show();//initialize all sleds to 'off'
 
}

void loop() {
  // put your main code here, to run repeatedly:
  int val=map(analogRead(A0),0,1023,0,255);
  SLEDs.setPixelColor(0,SLEDs.Color(val,0,0));//adjust brightness,red color
  SLEDs.setPixelColor(1,SLEDs.Color(0,0,val));//adjust brightness,blue color
  SLEDs.show();
}
