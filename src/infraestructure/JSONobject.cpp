#include <Arduino_JSON.h>

JSONVar message;
JSONVar metrics;

void setupObject(JSONVar node){
  message["node"] = node;
}

String removeSemiColons(String str){
  String aux;
  for (int i = 0; i < str.length(); i++){
    if(str[i] != '"'){
      aux+=str[i];
    }
  }
  return aux;
}

void setMetric(String type, int value, String unity){
  const int length = metrics.length(); 
  bool alreadyExist = false;
  int index = 0;
  if(length > -1){
    for(int i=0; i < length; i++){
      JSONVar element = metrics[i];
      const String metricType = removeSemiColons(JSON.stringify(element["type"]));
      if(metricType == type){
        alreadyExist=true;
        index=i;
      }
    }
  }
  JSONVar metric;
  metric["type"] = type;
  metric["value"] = value;
  metric["unity"] = unity;
  const int indexInMetrics = alreadyExist?index: length == -1 ? 0 : length;
  metrics[indexInMetrics] = metric;
}

String getMessage(){
  message["metrics"] = metrics;
  return JSON.stringify(message);
}

