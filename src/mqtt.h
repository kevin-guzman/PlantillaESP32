#include <PubSubClient.h>
#ifndef mqqt_h
#define mqqt_h

void setupMqtt(const char* MQTT_SERVER, int MQTT_PORT, String clientId);
void mqttLoop();
void sendMessage(const char* topic, String message);

#endif