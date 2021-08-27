#include <WiFi.h>
#include <JSONMessage.h>
#include <AdaptorMQTT.h>
#include "util/MetricTypes.h"
#include "util/UnityTypes.h"

// Editables
int MQTT_PORT = 1883;
const char* MQTT_SERVER = "201.244.138.88";
String testerName = "Kevin";
String location = "Molinos";
const char* SSID = "FAMILIA GUSMAN";
const char* password = "10218715F";
const int baudRate = 115200;

// No editables
String clientId = "ESP32Client-" +  testerName + "-estacion" + location;

AdaptorMQTT MQTT(MQTT_SERVER, MQTT_PORT, clientId);
JSONMessage JSONmessage;
MetricTypes MT;
UnityTypes UT;


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
  JSONmessage.init(node);

  WiFi.begin(SSID, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(400);
    Serial.print(".");
  }

  if(WiFi.status() == WL_CONNECTED){
    MQTT.connect();
  }
}

void loop(){
  MQTT.loop();
  delay(5000);
  JSONmessage.setMetric(MT.temperatura, 1, UT.tepertatura.centigrados);
  JSONmessage.setMetric(MT.humedad, 30, "9" + UT.humedad.porciento);
  JSONmessage.setMetric(MT.velocidad, 90, UT.velocidad.ms);
  // sendMessage("node/message", getMessage());
  Serial.println("Mensaje->");
  Serial.println(JSONmessage.get());
  // MQTT.send("node/message", JSONmessage.get());
}
