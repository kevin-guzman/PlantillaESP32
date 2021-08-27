#include <Arduino_JSON.h>
#ifndef JSONobject_h
#define JSONobject_h

void setupObject(JSONVar node);
String getMessage();
void setMetric(String type, int value, String unity);

#endif