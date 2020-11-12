#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
//#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1/*OLED_RESET*/);
void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  //display.setTextColor(BLACK,WHITE);//bg white , alphabet black
  display.setTextColor(WHITE);
}

void loop() {
  // put your main code here, to run repeatedly:
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0,0);
  
  display.print("I'll kill You!");
  display.setTextSize(1);
  display.setCursor(64,30);
  display.print("BUT");

  display.setTextSize(1);
  display.setCursor(0,55);
  display.print("I'm Your Father");
  
  display.display();
}
