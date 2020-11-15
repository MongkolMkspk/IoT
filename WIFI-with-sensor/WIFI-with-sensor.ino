#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <SPI.h>

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#define DHTTYPE DHT22
#define DHTPIN D4
DHT_Unified dht(DHTPIN, DHTTYPE);


#define LED1 16


const char* ssid = "PREIPhone";
const char* password = "prellss3011";
const char* mqtt_server = "broker.netpie.io";
const int mqtt_port = 1883;
const char* mqtt_Client = "d6889291-be33-4302-a94e-1f499c4e9d9b";
const char* mqtt_username = "dCdPuGAAq4YpngvMhq8gmKP1qT8U5WvF";
const char* mqtt_password = "dEl4r5qMJS7v7f_p#AeUmckUb9lY1ntg";
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HIGHTH 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HIGHTH, &Wire, -1);
uint32_t delayMS;

WiFiClient espClient;
PubSubClient client(espClient);
char msg[100];
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection…");
    if (client.connect(mqtt_Client, mqtt_username, mqtt_password)) {
      Serial.println("connected");
    }
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println("try again in 5 seconds");
      delay(5000);
    }
  }
}
void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  client.setServer(mqtt_server, mqtt_port);
  dht.begin();
  sensor_t sensor;
  if(display.begin(SSD1306_SWITCHCAPVCC ,0x3C)){
    Serial.println(F("SSD1306 allocation Failed"));
  }
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
  delayMS = sensor.min_delay / 1000;
}
void loop() {
  delay(delayMS);

  sensors_event_t event;
  dht.temperature().getEvent(&event);

  display.clearDisplay();
  display.setTextColor(WHITE);
  float h = 0;
  float t = 0;

  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    t = event.temperature;
    Serial.println(F("°C"));
    display.setCursor(0,30);
    display.print(String("T: ")+ String(t,0) + " ");
    display.write(247);
    display.print("C");
  }
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    h = event.relative_humidity;
    Serial.println(F("%"));
    display.setCursor(0,0);
    display.setTextSize(2);
    display.println(String("H: ")+ String(h,0) + " %");
  }
  Serial.println(t);
  Serial.println(h);
  display.display();
    if (!client.connected()) {
    reconnect();
  }
  client.loop();
  String data = " humidity:" + String(h) + ", temperature:" + String(t) + " ";
  Serial.println(data);
  data.toCharArray(msg, (data.length() + 1));
  client.publish("@msg/test", msg);
  //delay(2000);
  
}
