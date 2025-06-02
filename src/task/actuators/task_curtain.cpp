#include "task_curtain.h"

Servo curtain;

void InitCurtain() {
  curtain.attach(ActuatorConfig::curtainPin, ActuatorConfig::curtainPWMChannel);
  curtain.write(0);
}

void SetCurtainActuatorStatus(JsonPairConst json) {
  uint8_t newMode = json.value().as<uint8_t>();
  switch (newMode) {
  case 1:
    curtain.write(180);
    break;
  default:
    curtain.write(0);
    break;
  }
  LogUpdate("Curtain mode", "updated to", String(newMode).c_str(), "");
  curtainActuatorState.mode = newMode;
}