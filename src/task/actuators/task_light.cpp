#include "task_light.h"

void InitLight() {
  pinMode(ActuatorConfig::lightPin0, OUTPUT);
  pinMode(ActuatorConfig::lightPin1, OUTPUT);
  digitalWrite(ActuatorConfig::lightPin0, OFF);
  digitalWrite(ActuatorConfig::lightPin1, OFF);
}

void SetLightActuatorStatus(JsonPairConst json) {
  lightActuatorState.mode = json.value().as<uint8_t>();
  switch (lightActuatorState.mode) {
  case 1:
    digitalWrite(ActuatorConfig::lightPin0, ON);
    digitalWrite(ActuatorConfig::lightPin1, OFF);
    break;
  case 2:
    digitalWrite(ActuatorConfig::lightPin0, OFF);
    digitalWrite(ActuatorConfig::lightPin1, ON);
    break;
  case 3:
    digitalWrite(ActuatorConfig::lightPin0, ON);
    digitalWrite(ActuatorConfig::lightPin1, ON);
    break;
  default:
    digitalWrite(ActuatorConfig::lightPin0, OFF);
    digitalWrite(ActuatorConfig::lightPin1, OFF);
    break;
  }
  LogUpdate("Light mode", "updated to ", String(lightActuatorState.mode).c_str());
}

// void RPCLightActuatorControl(const JsonVariantConst& variant, JsonDocument& document) {
//   Serial.println("If I did then she would want to be my girlfriend...");
//   const size_t jsonSize = Helper::Measure_Json(variant);
//   char buffer[jsonSize];
//   serializeJson(variant, buffer, jsonSize);
//   Serial.println(buffer);
//   if (variant.containsKey("lightActuatorMode")) {
//     lightActuatorState.status = variant["lightActuatorMode"].as<bool>();
//     digitalWrite(ActuatorConfig::lightPin, lightActuatorState.status);
//  }
// }

void RPCLightActuatorControl(const JsonVariantConst& variant, JsonDocument& document) {
  Serial.println("RPCLightActuatorControl is called");
  const size_t jsonSize = Helper::Measure_Json(variant);
  char buffer[jsonSize];
  serializeJson(variant, buffer, jsonSize);
  Serial.println(buffer);
  alertState.status = variant.as<bool>();
  digitalWrite(ActuatorConfig::lightPin, alertState.status);
}