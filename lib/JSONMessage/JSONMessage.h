#ifndef jsonmessage_h
#define jsonmessage_h
#include <Arduino.h>
#include <Arduino_JSON.h>

// void setupObject(JSONVar node);
// String getMessage();
// void setMetric(String type, int value, String unity);

class JSONMessage{
  public:
    JSONMessage();
    virtual ~JSONMessage();
    void setMetric(String type, int value, String unity);
    void init(JSONVar node);
    String get();
  private:
    JSONVar _message;
    JSONVar _metrics;
    String removeSemiColons(String str);
};


#endif