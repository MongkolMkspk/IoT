#include <Adafruit_NeoPixel.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define Pin 10
#define NumLed 2

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define DHTPIN D4
#define DHTTYPE    DHT22 

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NumLed, Pin, NEO_RGB + NEO_KHZ800);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Pin,OUTPUT);
  pixels.begin();
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3c)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  pixels.clear();
  display.clearDisplay();
  delayMS = sensor.min_delay / 1000;

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(delayMS);
  display.clearDisplay();
  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  float anaValTemp=map((event.temperature),0,100,0,255);
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,0);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
    display.println("Error reading temperature!");
  }
  else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
    display.print("Temperature: ");
    display.print(event.temperature);
    display.print(F("°C"));
    pixels.setPixelColor(0,pixels.Color(anaValTemp,0,255-anaValTemp));
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  float anaValHumidity=map((event.relative_humidity),0,100,0,255);
  display.setCursor(0,32);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
    display.print("Humidity: ");
    display.print(event.relative_humidity);
    display.print(F("%"));
    pixels.setPixelColor(1,pixels.Color(100,100,anaValHumidity));
  }
  pixels.show();
  display.display();

}
