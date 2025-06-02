#include "task_light.h"

void InitLight() {
  pinMode(ActuatorConfig::lightPin0, OUTPUT);
  pinMode(ActuatorConfig::lightPin1, OUTPUT);
  digitalWrite(ActuatorConfig::lightPin0, OFF);
  digitalWrite(ActuatorConfig::lightPin1, OFF);
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