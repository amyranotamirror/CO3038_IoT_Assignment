#include "task_shared_attr.h"

const Shared_Attribute_Callback<ThingsBoardConfig::maxAttribute> shared_attribute_callback(&processSharedAttributeUpdate, SHARED_ATTRIBUTES_LIST);
const Attribute_Request_Callback<ThingsBoardConfig::maxAttribute> attribute_request_callback(&processSharedAttributeRequest, 0U, nullptr, SHARED_ATTRIBUTES_LIST);

void processSharedAttributeUpdate(const JsonObjectConst &data) {
    // Info
    Serial.println("I don't want to stop being the person I am with her...");
    const size_t jsonSize = Helper::Measure_Json(data);
    char buffer[jsonSize];
    serializeJson(data, buffer, jsonSize);
    Serial.println(buffer);
}
void processSharedAttributeRequest(const JsonObjectConst &data) {
    // Info
    Serial.println("She makes me more but I don't make her more...");
    const size_t jsonSize = Helper::Measure_Json(data);
    char buffer[jsonSize];
    serializeJson(data, buffer, jsonSize);
    Serial.println(buffer);
}

// void processSharedAttributes(const JsonObjectConst &data) {
//   Serial.println("If I did then she would want to be my girlfriend...");
//   for (auto it = data.begin(); it != data.end(); ++ it) {
//     if (strcmp(it->key().c_str(), "lightActuatorStateStatus") == 0) {
//       SetLightActuatorStatus(*it);
//     }
//   }
// }