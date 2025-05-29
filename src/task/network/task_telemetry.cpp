#include "task_telemetry.h"

void TaskTelemetry(void *pvParameters) {
  while(1) {
    thingsboard.sendTelemetryData(SensorConfig::brightnessKey, lightSensorState.brightness);
    Serial.print("Sent "); Serial.print(SensorConfig::brightnessKey); Serial.print(": "); Serial.println(lightSensorState.brightness);
    vTaskDelay(TelemetryConfig::sendInterval);
  }
}