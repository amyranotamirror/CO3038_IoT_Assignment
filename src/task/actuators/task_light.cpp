#include "task_light.h"

void InitLight(){
    pinMode(ActuatorConfig::lightPin, OUTPUT);
    digitalWrite(ActuatorConfig::lightPin, true);
}

void SetLightActuatorStatus(JsonPairConst json) {
  bool ledState = json.value().as<bool>();
  digitalWrite(ActuatorConfig::lightPin, ledState);
  Serial.print("Light state is updated to: "); Serial.println(ledState);
}

void RPCLightActuatorControl(const JsonVariantConst& variant, JsonDocument& document) {
    Serial.println("If I did then she would want to be my girlfriend...");
    const size_t jsonSize = Helper::Measure_Json(variant);
    char buffer[jsonSize];
    serializeJson(variant, buffer, jsonSize);
    Serial.println(buffer);

    lightActuatorState.status = variant["lightActuatorStateStatus"].as<bool>();
    digitalWrite(ActuatorConfig::lightPin, lightActuatorState.status);
}

bool GetLightActuatorStatus(){
    return lightActuatorState.status;
}