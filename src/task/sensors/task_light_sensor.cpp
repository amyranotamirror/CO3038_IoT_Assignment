#include "task_light_sensor.h"

BH1750 lightSensor;

void InitLightSensor() {
  // Initialize the light sensor with default settings
  LogInfo("Light Sensor", "Initializing ...");
  if(!lightSensor.begin()) {
    LogError("Light Sensor", "Failed to initialize.");
    return;
  }

  // Initialize the light sensor mutex
  lightSensorState.mutex = xSemaphoreCreateMutex();
  if (lightSensorState.mutex == nullptr) {
    LogError("Light Sensor", "Failed to create mutex.");
    return;
  }

  // Initialize the light sensor state
  lightSensorState.connectionAttempt = 0;
  lightSensorState.brightness = NAN;
  LogSuccess("Light Sensor", "Initialized successfully.");
}

void TaskLightSensor(void *pvParameters) {
  while(1) {
    // Check if the light sensor has been initialized
    if (!TakeMutex(lightSensorState.mutex, SystemConfig::mutexWaitTicks, "Light Sensor")) {
      InitLightSensor();
      vTaskDelay(SensorConfig::readBH1750Interval); // Use normal interval for retry
      continue;
    }
    
    // Check if the light sensor is ready for measurement
    if (!lightSensor.measurementReady()) {
      if (lightSensorState.connectionAttempt < SensorConfig::maxConnectionAttemptBH1750) {
        lightSensorState.connectionAttempt++;
        LogWarn("Light Sensor", "Measurement not ready, retrying ...");
        GiveMutex(lightSensorState.mutex, "Light Sensor");
        vTaskDelay(SensorConfig::connectAttemptBH1750Interval); // Use small interval for retry
      } else {
        LogError("Light Sensor", "Failed to read after max attempts.");
        lightSensorState.connectionAttempt = 0;
        GiveMutex(lightSensorState.mutex, "Light Sensor");
        vTaskDelay(SensorConfig::readBH1750Interval); // Use normal interval for retry
      }
      continue;
    }

    // Read the light level
    lightSensorState.brightness = lightSensor.readLightLevel();
    LogRead(SensorConfig::brightnessKey, String(lightSensorState.brightness, 4).c_str(), "lux");
    GiveMutex(lightSensorState.mutex, "Light sensor");

    vTaskDelay(SensorConfig::readBH1750Interval); // Use normal interval for next read
  }
}