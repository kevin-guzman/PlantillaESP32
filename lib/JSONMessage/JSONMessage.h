#ifndef jsonmessage_h
#define jsonmessage_h
#include <Arduino_JSON.h>

class JSONMessage{
  public:
    JSONMessage();
    virtual ~JSONMessage();
    void setMetric(String type, double value, String unity);
    void init(JSONVar node);
    String get();
  private:
    JSONVar _message;
    JSONVar _metrics;
    String removeSemiColons(String str);
};


#endif