#include "task_telemetry.h"

void TaskTelemetry(void *pvParameters) {
  while(1) {
    if (isSystemReady()) {
      if (TakeMutex(lightSensorState.mutex, SystemConfig::mutexWaitTicks, "Light sensor")) {
        if (lightSensorState.brightness >= 0 && !isnan(lightSensorState.brightness)) {
          thingsboard.sendTelemetryData(SensorConfig::brightnessKey, lightSensorState.brightness);
          LogSend(SensorConfig::brightnessKey, String(lightSensorState.brightness, 4).c_str());
        }
        GiveMutex(lightSensorState.mutex, "Light sensor");
      }
      if (TakeMutex(tempHumidSensorState.mutex, SystemConfig::mutexWaitTicks, "Temperature humidity sensor")) {
        if (tempHumidSensorState.temperature >= 0 && !isnan(tempHumidSensorState.temperature)) {
          thingsboard.sendTelemetryData(SensorConfig::temperatureKey, tempHumidSensorState.temperature);
          LogSend(SensorConfig::temperatureKey, String(tempHumidSensorState.temperature, 4).c_str());
        }
        if (tempHumidSensorState.humidity >= 0 && !isnan(tempHumidSensorState.humidity)) {
          thingsboard.sendTelemetryData(SensorConfig::humidityKey, tempHumidSensorState.humidity);
          LogSend(SensorConfig::humidityKey, String(tempHumidSensorState.humidity, 4).c_str());
        }
        GiveMutex(tempHumidSensorState.mutex, "Temperature humidity sensor");
      }
    }
    if (TakeMutex(airQualitySensorState.mutex, SystemConfig::mutexWaitTicks, "Air quality sensor")) {
        if (airQualitySensorState.co2 >= 0 && !isnan(airQualitySensorState.co2)) {
          thingsboard.sendTelemetryData(SensorConfig::co2Key, airQualitySensorState.co2);
          LogSend(SensorConfig::co2Key, String(airQualitySensorState.co2, 4).c_str());
        }
        GiveMutex(airQualitySensorState.mutex, "Air quality");
    }
    vTaskDelay(TelemetryConfig::sendInterval);
  }
}