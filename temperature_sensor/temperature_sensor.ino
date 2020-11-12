#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define SCREEN_W 128
#define SCREEN_H 64
#define DHTTYPE DHT22
#define DHTPIN D4
DHT_Unified dht (DHTPIN,DHTTYPE);
Adafruit_SSD1306 display(SCREEN_W,SCREEN_H,&Wire,-1);

uint32_t delayMS;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
  if(!display.begin(SSD1306_SWITCHCAPVCC,0x3C)){
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextColor(WHITE);
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println(F("Humidity Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("------------------------------------"));
  /*dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);*/
  delayMS = sensor.min_delay / 1000;

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
  sensors_event_t event;
  Serial.println("test3");
  dht.temperature().getEvent(&event);//dht.readTemperature();
  dht.humidity().getEvent(&event);//dht.readHumidity();
  //float f = dht.readTemperature(true);
  if(isnan(event.temperature)||isnan(event.relative_humidity)/*||isnan(f)*/){
    Serial.println("Failed to read from DHT sensor!");
  }
  else{
    Serial.println("success to read from DHT sensor!");
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0,0);
    display.println(String("H: ")+ String(event.temperature)+" %");
    display.setCursor(0,30);
    display.print(String("T: ")+ String(event.relative_humidity)+" ");
    display.write(247);
    display.print("C");
    display.display();
  }
  

}
