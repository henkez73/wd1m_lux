#include <ESP8266WiFi.h>
#include <Wire.h>
#include <PubSubClient.h>
#include <BH1750.h>

#define wifi_ssid "your_wifi_ssid"
#define wifi_password "your_wifi_pwd"

#define mqtt_server "your_mqtt_server"
#define mqtt_user "your_username"
#define mqtt_password "your_password"

#define lux_topic "/sensor/lux"

BH1750 lightMeter;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  lightMeter.begin();
  Serial.println("Running...");
  }

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);

  WiFi.begin(wifi_ssid, wifi_password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    // If you do not want to use a username and password, change next line to
      if (client.connect("ESP8266Client")) {
    // if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  
  uint16_t lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.println(String(lux).c_str());
  // Serial.print(lux);
  // Serial.println(" lx");
  delay(10000);
  client.publish(lux_topic, String(lux).c_str(), true);
}
