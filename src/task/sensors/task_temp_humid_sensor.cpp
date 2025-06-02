#include "task_temp_humid_sensor.h"

DHT tempHumidSensor;

void InitTempHumidSensor() {
  // Initialize the temperature humidity sensor with default settings
  LogInfo("Temperature Humidity Sensor", "Initializing ...");
  tempHumidSensor.setup(SensorConfig::DHT20Pin);

  // Initialize the temperature humidity sensor mutex
  tempHumidSensorState.mutex = xSemaphoreCreateMutex();
  if (tempHumidSensorState.mutex == nullptr) {
    LogError("Temperature Humidity Sensor", "Failed to create mutex");
    return;
  }

  // Initialize the temperature humidity sensor state
  tempHumidSensorState.connectionAttempt = 0;
  tempHumidSensorState.temperature = NAN;
  tempHumidSensorState.humidity = NAN;
  LogSuccess("Temperature Humidity Sensor", "Initialized successfully");
}

void TaskTempHumidSensor(void *pvParameters) {
  while(1) {
    // Check if the temperature humidity sensor has been initialized
    if (!TakeMutex(tempHumidSensorState.mutex, SystemConfig::mutexWaitTicks, "Temperature Humidity Sensor")) {
      InitTempHumidSensor();
      vTaskDelay(SensorConfig::readDHT22Interval); // Use normal interval for retry
      continue;
    }
    
    // // Check if the temperature humidity sensor is ready for measurement
    // if (!lightSensor.measurementReady()) {
    //   if (lightSensorState.connectionAttempt < SensorConfig::maxConnectionAttemptBH1750) {
    //     lightSensorState.connectionAttempt++;
    //     LogWarn("Light Sensor", "Measurement not ready, retrying ...");
    //     GiveMutex(lightSensorState.mutex, "Light Sensor");
    //     vTaskDelay(SensorConfig::connectAttemptBH1750Interval); // Use small interval for retry
    //   } else {
    //     LogError("Light Sensor", "Failed to read after max attempts.");
    //     lightSensorState.connectionAttempt = 0;
    //     GiveMutex(lightSensorState.mutex, "Light Sensor");
    //     vTaskDelay(SensorConfig::readBH1750Interval); // Use normal interval for retry
    //   }
    //   continue;
    // }

    // Read the temperature humidity level
    tempHumidSensorState.temperature = tempHumidSensor.getTemperature();
    tempHumidSensorState.humidity = tempHumidSensor.getHumidity();
    LogRead(SensorConfig::temperatureKey, String(tempHumidSensorState.temperature, 4).c_str(), "°C");
    LogRead(SensorConfig::humidityKey, String(tempHumidSensorState.humidity, 4).c_str(), "%");
    GiveMutex(tempHumidSensorState.mutex, "Temperature Humidity Sensor");

    vTaskDelay(SensorConfig::readDHT22Interval); // Use normal interval for next read
  }
}