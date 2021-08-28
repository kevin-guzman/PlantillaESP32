#include <WiFi.h>
#include <JSONMessage.h>
#include <AdaptorMQTT.h>
#include "util/MetricTypes.h"
#include "util/UnityTypes.h"
#include "util/ParseFunctions.h"

// Editables
int MQTT_PORT = 1883;
const char* MQTT_SERVER = "192.168.0.17";
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

void onTopicMessage(char* _topic, byte* _payload, unsigned int length){
  String payload = byteToString(_payload, length);
  String topic = String(_topic);
  Serial.println(topic);
  Serial.println(payload);
}


void setup(){
  Serial.begin(baudRate);
  delay(200);
  Serial.println("");
  Serial.println("Proyect has started");
  Serial.println("Connecting to WiFi");

  MQTT.setTopics("node/connected,topico,p");

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
    MQTT.connect(onTopicMessage);
  }
}

void loop(){
  MQTT.loop();
  // delay(5000);
  // JSONmessage.setMetric(MT.temperatura, 1, UT.tepertatura.centigrados);
  // JSONmessage.setMetric(MT.humedad, 30, "9" + UT.humedad.porciento);
  // JSONmessage.setMetric(MT.velocidad, 90, UT.velocidad.ms);

  // Serial.println("Mensaje->");
  // Serial.println(JSONmessage.get());
  // MQTT.send("node/message", JSONmessage.get());
}
