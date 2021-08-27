#include <Arduino_JSON.h>
#include <Arduino.h>
#include "JSONMessage.h"
// JSONVar message;
// JSONVar metrics;

// void setupObject(JSONVar node){
//   message["node"] = node;
// }

// String removeSemiColons(String str){
//   String aux;
//   for (int i = 0; i < str.length(); i++){
//     if(str[i] != '"'){
//       aux+=str[i];
//     }
//   }
//   return aux;
// }

// void setMetric(String type, int value, String unity){
//   const int length = metrics.length(); 
//   bool alreadyExist = false;
//   int index = 0;
//   if(length > -1){
//     for(int i=0; i < length; i++){
//       JSONVar element = metrics[i];
//       const String metricType = removeSemiColons(JSON.stringify(element["type"]));
//       if(metricType == type){
//         alreadyExist=true;
//         index=i;
//       }
//     }
//   }
//   JSONVar metric;
//   metric["type"] = type;
//   metric["value"] = value;
//   metric["unity"] = unity;
//   const int indexInMetrics = alreadyExist?index: length == -1 ? 0 : length;
//   metrics[indexInMetrics] = metric;
// }

// String getMessage(){
//   message["metrics"] = metrics;
//   return JSON.stringify(message);
// }

// class JSONMessage{
//   private:
//     JSONVar message;
//     JSONVar metrics;
//     String removeSemiColons(String str){
//       String removedSemicolonsChain;
//       for (int i = 0; i < str.length(); i++){
//         if(str[i] != '"'){
//           removedSemicolonsChain+=str[i];
//         }
//       }
//       return removedSemicolonsChain;
//     }
//   public:
//     JSONMessage();
//     ~JSONMessage();
//     void setMetric(String type, int value, String unity){
//       const int length = metrics.length(); 
//       bool alreadyExist = false;
//       int index = 0;
//       if(length > -1){
//         for(int i=0; i < length; i++){
//           JSONVar element = metrics[i];
//           const String metricType = removeSemiColons(JSON.stringify(element["type"]));
//           if(metricType == type){
//             alreadyExist=true;
//             index=i;
//           }
//         }
//       }
//       JSONVar metric;
//       metric["type"] = type;
//       metric["value"] = value;
//       metric["unity"] = unity;
//       const int indexInMetrics = alreadyExist?index: length == -1 ? 0 : length;
//       metrics[indexInMetrics] = metric;
//     };
//     void init(JSONVar node){
//       message["node"] = node;
//     };
//     String get(){
//       message["metrics"] = metrics;
//       return JSON.stringify(message);
//     };

// };

// JSONMessage::JSONMessage(){
// }

// JSONMessage::~JSONMessage(){
// }

JSONMessage::JSONMessage(){
  JSONVar _message;
  JSONVar _metrics;
}

JSONMessage::~JSONMessage(){
}

String JSONMessage::removeSemiColons(String str){
  String removedSemicolonsChain;
  for (int i = 0; i < str.length(); i++){
    if(str[i] != '"'){
      removedSemicolonsChain+=str[i];
    }
  }
  return removedSemicolonsChain;
}
void JSONMessage::setMetric(String type, int value, String unity){
  const int length = _metrics.length(); 
  bool alreadyExist = false;
  int index = 0;
  if(length > -1){
    for(int i=0; i < length; i++){
      JSONVar element = _metrics[i];
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
  _metrics[indexInMetrics] = metric;
};
void JSONMessage::init(JSONVar node){
  _message["node"] = node;
};
String JSONMessage::get(){
  _message["metrics"] = _metrics;
  return JSON.stringify(_message);
};




