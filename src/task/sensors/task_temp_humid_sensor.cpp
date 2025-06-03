#include "task_temp_humid_sensor.h"

DHT tempHumidSensor;

void InitTempHumidSensor() {
  // Initialize the temperature humidity sensor with default settings
  LogInfo("Temperature humidity sensor", "initializing ...");
  tempHumidSensor.setup(SensorConfig::DHT22Pin);

  // Initialize the temperature humidity sensor mutex
  if (tempHumidSensorState.mutex == nullptr) {
    tempHumidSensorState.mutex = xSemaphoreCreateMutex();
    if (tempHumidSensorState.mutex == nullptr) {
      LogError("Temperature humidity sensor", "failed to create mutex");
      return;
    } else {
      LogSuccess("Temperature humidity sensor", "created mutex");
    }
  }

  // Initialize the temperature humidity sensor state
  tempHumidSensorState.isConnected = true;
  tempHumidSensorState.connectionAttempt = 0;
  tempHumidSensorState.temperature = NAN;
  tempHumidSensorState.humidity = NAN;
  LogSuccess("Temperature humidity sensor", "initialized successfully");
}

void TaskTempHumidSensor(void *pvParameters) {
  while(1) {
    if (isSystemReady()) {
      // Check if the temperature humidity sensor has been initialized
      if (!tempHumidSensorState.isConnected) {
        LogError("Temperature humidity sensor", "disconnected");
        InitTempHumidSensor();
      }
      if (tempHumidSensorState.isConnected) {
        // Read the temperature humidity level
        double newTemperature = tempHumidSensor.getTemperature();
        double newHumidity = tempHumidSensor.getHumidity();
        LogRead(SensorConfig::temperatureKey, String(newTemperature, 4).c_str(), "°C");
        LogRead(SensorConfig::humidityKey, String(newHumidity, 4).c_str(), "%");
        // Save read value
        TakeMutex(tempHumidSensorState.mutex, SystemConfig::mutexWaitTicks, "Temperature humidity sensor");
        if (newTemperature < 0 || newHumidity < 0 || isnan(newTemperature) || isnan(newHumidity)) {
          if (tempHumidSensorState.connectionAttempt < SensorConfig::maxConnectionAttemptDHT22) {
            tempHumidSensorState.connectionAttempt ++;
            LogWarn("Temperature humidity sensor", "measurement failed, retrying ...");
          } else {
            tempHumidSensorState.isConnected = false;
            LogError("Temperature humidity sensor", "failed to read after max attempts");
          }
        } else {
          tempHumidSensorState.connectionAttempt = 0;
        }
        tempHumidSensorState.temperature = newTemperature;
        tempHumidSensorState.humidity = newHumidity;
        GiveMutex(tempHumidSensorState.mutex, "Temperature humidity sensor");
      }
      vTaskDelay(SensorConfig::readDHT22Interval); // Use normal interval for next read
    }
  }
}