#include <Arduino_JSON.h>
#include <WiFi.h>
#include "JSONobject.h"
#include "mqtt.h"

// Editables
int MQTT_PORT = 1883;
const char* MQTT_SERVER = "201.244.138.88";
String testerName = "Kevin";
String location = "Molinos";
const char* SSID = "No robes we";
const char* password = "@override";
const int baudRate = 115200;

// No editables
String clientId = "ESP32Client-" +  testerName + "-estacion " + location;

void setup(){
  Serial.begin(baudRate);
  Serial.println("");
  Serial.println("Proyect has started");
  Serial.println("Connecting to WiFi");

  JSONVar node;
  node["uuid"] = "uuid-"+testerName;
  node["username"] = clientId;
  node["name"] = testerName;
  node["hostname"] = location;
  node["pid"] = 12;
	setupObject(node);

  WiFi.begin(SSID, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(400);
    Serial.print(".");
  }

  if(WiFi.status() == WL_CONNECTED){
    setupMqtt(MQTT_SERVER, MQTT_PORT, clientId);
  }

  setMetric("temperature", 1, "C");
  setMetric("humidity", 30, "S");
  setMetric("wind", 90, "m/s");
}

void loop(){
  mqttLoop();
  delay(5000);
  sendMessage("node/message", getMessage());
}
