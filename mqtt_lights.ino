#include <SPI.h>
#include <WiFiNINA.h>
#include <PubSubClient.h>

// setting up WiFi credentials
const char* ssid = "wifi name";
const char* password = "password";

// MQTT broker setup
const char* mqtt_server = "broker.emqx.io";

WiFiClient wifiClient;
PubSubClient client(wifiClient);

//defining the pins
#define TRIG 9
#define ECHO 10
#define LED1 5
#define LED2 6

long duration;
int distance;

// WIFI cinnection function
void connectWiFi() {
  while (WiFi.begin(ssid, password) != WL_CONNECTED) {
    delay(2000);
  }
}

// MQTT callback function
void callback(char* topic, byte* payload, unsigned int length) {
  String msg = "";
  for (int i = 0; i < length; i++) {
    msg += (char)payload[i];
  }

  Serial.println(msg);

  if (String(topic) == "ES/Wave") {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
  }

  if (String(topic) == "ES/Pat") {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
  }
}

// Function to reconnect MQTT
void reconnect() {
  while (!client.connected()) {
    if (client.connect("Nano33Client")) {
      client.subscribe("ES/Wave");
      client.subscribe("ES/Pat");
    }
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  connectWiFi();

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  // Ultrasonic
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH);
  distance = duration * 0.034 / 2;

  Serial.println(distance);

  if (distance < 10) {
    client.publish("ES/Wave", "Jeremy");
    delay(2000);
  } else if (distance < 20) {
    client.publish("ES/Pat", "Jeremy");
    delay(2000);
  }
}