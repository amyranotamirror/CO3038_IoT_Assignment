#include "task_alert.h"

void InitAlert() {
  pinMode(ActuatorConfig::alertPin, OUTPUT);
  digitalWrite(ActuatorConfig::alertPin, OFF);
}

void TaskAlert(void *pvParameters) {
  while(1) {
    digitalWrite(ActuatorConfig::alertPin, alertState.status);
    vTaskDelay(SystemConfig::tinyTaskDelay);
  }
}

void AlertCO2DetectedControl(const JsonVariantConst& variant) {
  alertState.status = variant["CO2Detected"].as<bool>();
  LogUpdate("Alert status", "updated to", String(alertState.status).c_str(), "");
}