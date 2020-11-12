#include <BH1750FVI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <Adafruit_NeoPixel.h>
#define NUMSLEDs 2
#define PINSLEDs 10
Adafruit_NeoPixel SLEDs =Adafruit_NeoPixel(NUMSLEDs,PINSLEDs,NEO_GRB + NEO_KHZ800);

#define SCREEN_W 128
#define SCREEN_H 64

Adafruit_SSD1306 display(SCREEN_W,SCREEN_H,&Wire,-1);
BH1750FVI LightSensor(BH1750FVI::k_DevModeContLowRes);
void setup() {
  // put your setup code here, to run once:
  pinMode(PINSLEDs,OUTPUT);
  Serial.begin(115200);
  LightSensor.begin();
  SLEDs.begin();//this initializes the neopixel liabrary
  SLEDs.show();//initialize all sleds to 'off'
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextColor(WHITE);  

}

void loop() {
  // put your main code here, to run repeatedly:
  uint16_t lux = LightSensor.GetLightIntensity();
  int intLux = (int)lux;
  int val=map(analogRead(A0),0,1023,0,255);
  SLEDs.setPixelColor(0,SLEDs.Color(val+lux,0+lux,0+lux));//adjust brightness,red color
  SLEDs.setPixelColor(1,SLEDs.Color(0+lux,0+lux,val+lux));//adjust brightness,blue color
  SLEDs.setBrightness(0,64);
  SLEDs.show();
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("Light: ");
  display.println(lux);
  display.display();
  delay(250);

}
