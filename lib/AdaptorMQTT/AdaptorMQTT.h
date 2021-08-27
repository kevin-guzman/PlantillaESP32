#ifndef mqqt_h
#define mqqt_h
#include <Arduino.h>
#include <PubSubClient.h>

class AdaptorMQTT{
  public:
    AdaptorMQTT(const char* MQTT_SERVER, int MQTT_PORT, String clientId);
    virtual ~AdaptorMQTT();
    void loop();
    void send(const char* topic, String message);
    void connect();

  private:
    PubSubClient _client;
    String parsePayload(byte* payload, unsigned int length);
    void reconnect();
    String _clientId;
    const char* _MQTT_SERVER;
    int _MQTT_PORT;
};

// void setupMqtt(const char* MQTT_SERVER, int MQTT_PORT, String clientId);
// void mqttLoop();
// void sendMessage(const char* topic, String message);

#endif