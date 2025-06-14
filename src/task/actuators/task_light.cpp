#include "task_light.h"

void InitLight() {
  LogInfo("Light actuator", "initializing ...");
  pinMode(ActuatorConfig::lightPin0, OUTPUT);
  pinMode(ActuatorConfig::lightPin1, OUTPUT);
  digitalWrite(ActuatorConfig::lightPin0, OFF);
  digitalWrite(ActuatorConfig::lightPin1, OFF);
  LogSuccess("Light actuator", "initialized successfully");
}

void SetLightActuatorStatus(JsonPairConst json) {
  uint8_t newMode = json.value().as<uint8_t>();
  switch (newMode) {
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
  LogUpdate("Light mode", "updated to", String(newMode).c_str(), "");
  lightActuatorState.mode = newMode;
}

void SetLightActuatorWhiteStatus(JsonPairConst json) {
  uint8_t newMode = json.value().as<bool>();
  if (newMode) {
    digitalWrite(ActuatorConfig::lightPin0, ON);
  } else {
    digitalWrite(ActuatorConfig::lightPin0, OFF);
  }
  LogUpdate("Light white mode", "updated to", String(newMode).c_str(), "");
  lightActuatorState.isWhiteMode = newMode;
}

void SetLightActuatorWarmStatus(JsonPairConst json) {
  uint8_t newMode = json.value().as<bool>();
  if (newMode) {
    digitalWrite(ActuatorConfig::lightPin1, ON);
  } else {
    digitalWrite(ActuatorConfig::lightPin1, OFF);
  }
  LogUpdate("Light warm mode", "updated to", String(newMode).c_str(), "");
  lightActuatorState.isWarmMode = newMode;
}