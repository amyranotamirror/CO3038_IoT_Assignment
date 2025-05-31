#include "task_telemetry.h"

void TaskTelemetry(void *pvParameters) {
  while(1) {
    if (TakeMutex(lightSensorState.mutex, SystemConfig::mutexWaitTicks, "Light Sensor")) {
<<<<<<< HEAD
    thingsboard.sendTelemetryData(SensorConfig::brightnessKey, lightSensorState.brightness);
=======
      thingsboard.sendTelemetryData(SensorConfig::brightnessKey, lightSensorState.brightness);
>>>>>>> develop
      LogSend(SensorConfig::brightnessKey, String(lightSensorState.brightness, 4).c_str());
      GiveMutex(lightSensorState.mutex, "Light sensor");
    }
    vTaskDelay(TelemetryConfig::sendInterval);
  }
}