#include <Wire.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HIGH 64

Adafruit_SSD1306 display(SCREEN_WIDTH,SCREEN_HIGH,&Wire,-1);
void setup() {
  // put your setup code here, to run once:
  if(!display.begin(SSD1306_SWITCHCAPVCC,0x3C){
    Serial.println(F("SSD1306_allocation failed"));
  }
  display.setTextColor(WHITE);
}

void loop() {
  // put your main code here, to run repeatedly:
  display
}
