#include "task_telemetry.h"

void TaskTelemetry(void *pvParameters) {
  while(1) {
    if (isSystemReady()) {
      if (TakeMutex(airQualitySensorState.mutex, SystemConfig::mutexWaitTicks, "Air quality sensor")) {
        if (airQualitySensorState.connectionAttempt == 0) {
          thingsboard.sendTelemetryData(SensorConfig::co2Key, airQualitySensorState.co2);
          LogSend(SensorConfig::co2Key, String(airQualitySensorState.co2, 4).c_str());
        }
        GiveMutex(airQualitySensorState.mutex, "Air quality");
      }
      if (TakeMutex(lightSensorState.mutex, SystemConfig::mutexWaitTicks, "Light sensor")) {
        if (lightSensorState.connectionAttempt == 0) {
          thingsboard.sendTelemetryData(SensorConfig::brightnessKey, lightSensorState.brightness);
          LogSend(SensorConfig::brightnessKey, String(lightSensorState.brightness, 4).c_str());
        }
        GiveMutex(lightSensorState.mutex, "Light sensor");
      }
      if (TakeMutex(presenceSensorState.mutex, SystemConfig::mutexWaitTicks, "Presence sensor")) {
        if (presenceSensorState.connectionAttempt == 0) {
          thingsboard.sendTelemetryData(SensorConfig::presenceKey, presenceSensorState.presence);
          thingsboard.sendTelemetryData(SensorConfig::distanceKey, presenceSensorState.distance);
          LogSend(SensorConfig::presenceKey, String(presenceSensorState.presence).c_str());
          LogSend(SensorConfig::distanceKey, String(presenceSensorState.distance).c_str());
        }
        GiveMutex(presenceSensorState.mutex, "Presence sensor");
      }
      if (TakeMutex(tempHumidSensorState.mutex, SystemConfig::mutexWaitTicks, "Temperature humidity sensor")) {
        if (tempHumidSensorState.connectionAttempt == 0) {
          thingsboard.sendTelemetryData(SensorConfig::temperatureKey, tempHumidSensorState.temperature);
          thingsboard.sendTelemetryData(SensorConfig::humidityKey, tempHumidSensorState.humidity);
          LogSend(SensorConfig::temperatureKey, String(tempHumidSensorState.temperature, 4).c_str());
          LogSend(SensorConfig::humidityKey, String(tempHumidSensorState.humidity, 4).c_str());
        }
        GiveMutex(tempHumidSensorState.mutex, "Temperature humidity sensor");
      }
    }
    vTaskDelay(TelemetryConfig::sendInterval);
  }
}