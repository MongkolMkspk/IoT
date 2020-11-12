
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "OnePlus 7T Pro";
const char* password = "31d6b140b94a";
const char* mqtt_server = "broker.netpie.io";
const int mqtt_port = 1883;
const char* mqtt_Client = "e88710dc-19ce-4c9e-a9aa-433b16845c2c";
const char* mqtt_username = "gUryAhTcte1iXN5vHbcqaAnQYizmt3cE";
const char* mqtt_password = "nz2bAq~AdJ7pKe-OTB7CGwHZy#vjz#6I";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
int value = 0;

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
  // put your setup code here, to run once:
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
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!client.connected()) {
  reconnect();
}
client.loop();
long now = millis();
if (now - lastMsg > 2000) {
  lastMsg = now;
  ++value;
client.publish("@msg/test", "Hello NETPIE2020");
Serial.println("Hello NETPIE2020");
}
  delay(1);

}
