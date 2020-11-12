#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <stdio.h>

#define ANALOG_PIN A0
#define SCREEN_W 128
#define SCREEN_H 64
int analogValue =0;
Adafruit_SSD1306 display(SCREEN_W,SCREEN_H,&Wire,-1);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextColor(WHITE);

}

void loop() {
  // put your main code here, to run repeatedly:
  int temp;
  char str[5];
  analogValue = analogRead(ANALOG_PIN);
  temp = analogValue *3.3 /1023*1000;
  sprintf(str,"%4d",temp);
  
  display.clearDisplay();
  display.setTextSize(1);
  6;display.setCursor(0,0);
  display.print("Analog input0");

  display.setCursor(0,30);
  display.setTextSize(2);
  if(str[0]==' ')display.print("0");
  else display.print(str[0]);
  display.print(".");
  if(str[1]==' ')display.print("0");
  else display.print(str[1]);
  if(str[2]==' ')display.print("0");
  else display.print(str[2]);
  display.print(str[3]);
  display.print(" Vote");

  display.display();

  delay(1000);
}
