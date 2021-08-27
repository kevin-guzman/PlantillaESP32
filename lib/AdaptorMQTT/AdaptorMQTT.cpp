#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "AdaptorMQTT.h"

WiFiClient espClient;

AdaptorMQTT::AdaptorMQTT(const char* MQTT_SERVER, int MQTT_PORT, String clientId){
  _clientId = clientId;
  _MQTT_SERVER = MQTT_SERVER;
  _MQTT_PORT = MQTT_PORT;
}

AdaptorMQTT::~AdaptorMQTT(){}

String parsePayload(byte* payload, unsigned int length){
  String value;
  for (int i = 0; i < length; i++) {
    value+=((char)payload[i]);
  }
  return value;
}

void onMQTTClient(char* _topic, byte* _payload, unsigned int length){
  String payload = parsePayload(_payload, length);
  String topic = String(_topic);
}

void AdaptorMQTT::connect(){
  PubSubClient client(espClient);
  _client = client;
  _client.setServer(_MQTT_SERVER, _MQTT_PORT);
  _client.setCallback(onMQTTClient);
}

void AdaptorMQTT::loop(){
  if (!_client.connected()) {
    this->reconnect();
  }else{
    _client.loop();
  }
}

void AdaptorMQTT::send(const char* topic, String message){
  if(_client.connected()){
    if (_client.connect(_clientId.c_str())) {
      Serial.println("sending message ->");
      const int json_str_len = message.length();
      const int cut = 100;
      if (json_str_len > cut){
        _client.beginPublish(topic, json_str_len, true);
        int count = json_str_len / cut;
        for (int i = 0; i < (count-1); i++){
          const String cuttedString = message.substring(i * cut, (i * cut + cut));
          _client.print(cuttedString);
        }
        const String lastString = message.substring(cut * (count - 1));
        _client.print(lastString);
        _client.endPublish();
      }
      else{
        _client.publish(topic, message.c_str());
      }
      Serial.println("sended message successfuly ---->");
    }
  }
}

void AdaptorMQTT::reconnect() {
  while (!_client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (_client.connect( _clientId.c_str() )){
      Serial.println("connected");
      _client.subscribe("node/message");
    } else {
      Serial.print("failed, reconnection");
      Serial.print(_client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

// WiFiClient espClient;
// PubSubClient client(espClient);
// String clientID = "";

// String parsePayload(byte* payload, unsigned int length){
//   String value;
//   for (int i = 0; i < length; i++) {
//     value+=((char)payload[i]);
//   }
//   return value;
// }

// void onMQTTClient(char* _topic, byte* _payload, unsigned int length){
//   String payload = parsePayload(_payload, length);
//   String topic = String(_topic);
// }

// void setupMqtt(const char* MQTT_SERVER, int MQTT_PORT, String clientId){
//   clientID = clientId;
//   client.setServer(MQTT_SERVER, MQTT_PORT);
//   client.setCallback(onMQTTClient);
// }

// void reconnect() {
//   while (!client.connected()) {
//     Serial.print("Attempting MQTT connection...");
//     if (client.connect(clientID.c_str())) {
//       Serial.println("connected");
//       client.subscribe("node/message");
//     } else {
//       Serial.print("failed, reconnection");
//       Serial.print(client.state());
//       Serial.println(" try again in 5 seconds");
//       delay(5000);
//     }
//   }
// }

// void mqttLoop(){
//   if (!client.connected()) {
//     reconnect();
//   }
//   client.loop();
// }

// void sendMessage(const char* topic, String message){
//   if(client.connected()){
//     String clientId = "ESP8266Client-" + String(random(0xffff), HEX);
//     if (client.connect(clientId.c_str())) {
//       Serial.println("sending message ->");
//       const int json_str_len = message.length();
//       const int cut = 100;
//       if (json_str_len > cut){
//         client.beginPublish(topic, json_str_len, true);
//         int count = json_str_len / cut;
//         for (int i = 0; i < (count-1); i++){
//           const String cuttedString = message.substring(i * cut, (i * cut + cut));
//           client.print(cuttedString);
//         }
//         const String lastString = message.substring(cut * (count - 1));
//         client.print(lastString);
//         client.endPublish();
//       }
//       else{
//         client.publish(topic, message.c_str());
//       }
//       Serial.println("sended message successfuly ---->");
//     }
//   }
// }


