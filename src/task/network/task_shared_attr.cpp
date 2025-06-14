#include "task_shared_attr.h"

const Shared_Attribute_Callback<RPCAttributeConfig::maxAttribute> shared_attribute_callback(&processSharedAttributeUpdate, shared_attribute_list);
const Attribute_Request_Callback<RPCAttributeConfig::maxAttribute> attribute_request_callback(&processSharedAttributeRequest, RPCAttributeConfig::requestTimeoutMicroseconds, &RequestTimedOut, shared_attribute_list);

void RequestTimedOut() {
  LogError("Attribute request callback", "timed out");
}

void processSharedAttributes(const JsonObjectConst &data) {
  for (auto it = data.begin(); it != data.end(); ++ it) {
    if (strcmp(it->key().c_str(), "curtainActuatorMode") == 0) {
      SetCurtainActuatorStatus(*it);
    } else if (strcmp(it->key().c_str(), "lightActuatorWhite") == 0) {
      SetLightActuatorWhiteStatus(*it);
    } else if (strcmp(it->key().c_str(), "lightActuatorWarm") == 0) {
      SetLightActuatorWarmStatus(*it);
    }
  }
}

void processSharedAttributeUpdate(const JsonObjectConst &data) {
  const size_t jsonSize = Helper::Measure_Json(data);
  char buffer[jsonSize];
  serializeJson(data, buffer, jsonSize);
  LogInfo("Shared attribute callback", buffer);
  processSharedAttributes(data);
}
void processSharedAttributeRequest(const JsonObjectConst &data) {
  const size_t jsonSize = Helper::Measure_Json(data);
  char buffer[jsonSize];
  serializeJson(data, buffer, jsonSize);
  LogInfo("Attribute request callback", buffer);
  processSharedAttributes(data);
  thingsBoardState.isSharedAttributesRequestProcessed = true;
  LogSuccess("Shared attributes", "request proccessed successfully");
}