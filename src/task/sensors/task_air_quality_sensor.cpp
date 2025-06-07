#include "task_air_quality_sensor.h"

MQ135 airQualitySensor = MQ135(SensorConfig::MQ135Pin, SensorConfig::MQ135RZero, SensorConfig::MQ135RLoad);

void InitAirQualitySensor() {
  // Initialize the air quality sensor with default settings
  LogInfo("Air quality sensor", "initializing ...");

  // Initialize the air quality sensor mutex
  if (airQualitySensorState.mutex == nullptr) {
    airQualitySensorState.mutex = xSemaphoreCreateMutex();
    if (airQualitySensorState.mutex == nullptr) {
      LogError("Air quality sensor", "failed to create mutex");
      return;
    } else {
      LogSuccess("Air quality sensor", "created mutex");
    }
  }

  // Initialize the air quality sensor state
  airQualitySensorState.isConnected = true;
  airQualitySensorState.connectionAttempt = 0;
  airQualitySensorState.co2 = NAN;
  LogSuccess("Air quality sensor", "initialized successfully");
}

void TaskAirQualitySensor(void *pvParameters) {
  while(1) {
    if (isSystemReady()) {
      // Check if the air quality sensor has been initialized
      if (!airQualitySensorState.isConnected) {
        LogError("Air quality sensor", "disconnected");
        InitAirQualitySensor();
      }
      if (airQualitySensorState.isConnected) {
        // Read the air quality level
        double newTemperature = NAN;
        double newHumidity = NAN;
        if (TakeMutex(tempHumidSensorState.mutex, SystemConfig::mutexWaitTicks, "Temperature humidity sensor")) {
          newTemperature = tempHumidSensorState.temperature;
          newHumidity = tempHumidSensorState.humidity;
          GiveMutex(tempHumidSensorState.mutex, "Temperature humidity sensor");
        }
        double newCo2 = airQualitySensor.getCorrectedPPM(newTemperature, newHumidity);
        LogRead(SensorConfig::co2Key, String(newCo2, 4).c_str(), "ppm");
        // Save read value
        if (TakeMutex(airQualitySensorState.mutex, SystemConfig::mutexWaitTicks, "Air quality sensor")) {
          if (newCo2 < 0 || isnan(newCo2)) {
            if (airQualitySensorState.connectionAttempt < SensorConfig::maxConnectionAttemptMQ135) {
              airQualitySensorState.connectionAttempt ++;
              LogWarn("Air quality sensor", "measurement failed, retrying ...");
            } else {
              airQualitySensorState.isConnected = false;
              LogError("Air quality sensor", "failed to read after max attempts");
            }
          } else {
            airQualitySensorState.connectionAttempt = 0;
          }
          airQualitySensorState.co2 = newCo2;
          GiveMutex(airQualitySensorState.mutex, "Air quality sensor");
        }
      }
    }
    vTaskDelay(SensorConfig::readMQ135Interval); // Use normal interval for next read
  }
}