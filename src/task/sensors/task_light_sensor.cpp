#include "task_light_sensor.h"

BH1750 lightSensor;

void InitLightSensor() {
  // Initialize the light sensor with default settings
  LogInfo("Light sensor", "initializing ...");
  if (!lightSensor.begin()) {
    LogError("Light sensor", "failed to initialize");
    return;
  }

  // Initialize the light sensor mutex
  if (lightSensorState.mutex == nullptr) {
    lightSensorState.mutex = xSemaphoreCreateMutex();
    if (lightSensorState.mutex == nullptr) {
      LogError("Light sensor", "failed to create mutex");
      return;
    } else {
      LogSuccess("Light sensor", "created mutex");
    }
  }

  // Initialize the light sensor state
  lightSensorState.isConnected = true;
  lightSensorState.connectionAttempt = 0;
  lightSensorState.brightness = NAN;
  LogSuccess("Light sensor", "initialized successfully");
}

void TaskLightSensor(void *pvParameters) {
  while(1) {
    if (isSystemReady()) {
      // Check if the light sensor has been initialized
      if (!lightSensorState.isConnected) {
        LogError("Light sensor", "disconnected");
        InitLightSensor();
      }
      if (lightSensorState.isConnected) {
        // Read the light level
        double newBrightness = lightSensor.readLightLevel();
        LogRead(SensorConfig::brightnessKey, String(newBrightness, 4).c_str(), "lux");
        // Save read value
        if (TakeMutex(lightSensorState.mutex, SystemConfig::mutexWaitTicks, "Light sensor")) {
          if (newBrightness < 0 || isnan(newBrightness)) {
            if (lightSensorState.connectionAttempt < SensorConfig::maxConnectionAttemptBH1750) {
              lightSensorState.connectionAttempt ++;
              LogWarn("Light sensor", "measurement failed, retrying ...");
            } else {
              lightSensorState.isConnected = false;
              LogError("Light sensor", "failed to read after max attempts");
            }
          } else {
            lightSensorState.connectionAttempt = 0;
          }
          lightSensorState.brightness = newBrightness;
          GiveMutex(lightSensorState.mutex, "Light sensor");
        }
      }
    }
    vTaskDelay(SensorConfig::readBH1750Interval); // Use normal interval for next read
  }
}