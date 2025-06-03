#include "task_alert.h"

void InitAlert() {
  LogInfo("Alert actuator", "initializing ...");
  pinMode(ActuatorConfig::alertPin, OUTPUT);
  digitalWrite(ActuatorConfig::alertPin, OFF);
  LogSuccess("Alert actuator", "initialized successfully");
}

void TaskAlert(void *pvParameters) {
  while(1) {
    digitalWrite(ActuatorConfig::alertPin, alertState.status);
    vTaskDelay(SystemConfig::tinyTaskDelay);
  }
}

void AlertCo2DetectedControl(const JsonVariantConst& variant) {
  bool newStatus = variant["co2Detected"].as<bool>();
  LogUpdate("Alert status", "updated to", String(newStatus).c_str(), "");
  alertState.status = newStatus;
}