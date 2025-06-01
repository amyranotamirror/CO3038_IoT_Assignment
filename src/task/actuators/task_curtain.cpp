#include "task_curtain.h"

Servo curtain;

void InitCurtain() {
  curtain.attach(ActuatorConfig::curtainPin, ActuatorConfig::curtainPWMChannel);
  curtain.write(0);
}

void SetCurtainActuatorStatus(JsonPairConst json) {
  curtainActuatorState.mode = json.value().as<uint8_t>();
  switch (curtainActuatorState.mode) {
  case 1:
    curtain.write(180);
    break;
  default:
    curtain.write(0);
    break;
  }
  LogUpdate("Curtain mode", "updated to", String(curtainActuatorState.mode).c_str(), "");
}