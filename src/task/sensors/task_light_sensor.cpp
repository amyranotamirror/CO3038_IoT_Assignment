#include "task_light_sensor.h"

BH1750 lightSensor;

// void InitLightSensor() {
//   // Initialize the light sensor with default settings
//   LogInfo("Light sensor", "Initializing ...");
//   if(!lightSensor.begin()) {
//     LogError("Light sensor", "Failed to initialize");
//     return;
//   }

//   // Initialize the light sensor mutex
//   // lightSensorState.mutex = xSemaphoreCreateMutex();
//   if (lightSensorState.mutex == nullptr) {
//     lightSensorState.mutex = xSemaphoreCreateMutex();
//   }
//   if (lightSensorState.mutex == nullptr) {
//     LogError("Light sensor", "Failed to create mutex");
//     return;
//   }

//   // Initialize the light sensor state
//   lightSensorState.isConnected = true;
//   lightSensorState.connectionAttempt = 0;
//   lightSensorState.brightness = NAN;
//   LogSuccess("Light sensor", "Initialized successfully");
// }

// void TaskLightSensor(void *pvParameters) {
//   while(1) {if (isSystemReady()) {
//     // Check if the light sensor has been initialized
//     // if (!TakeMutex(lightSensorState.mutex, SystemConfig::mutexWaitTicks, "Light Sensor")) {
//     if (!lightSensorState.isConnected) {
//       InitLightSensor();
//     } else {
//       TakeMutex(lightSensorState.mutex, SystemConfig::mutexWaitTicks, "Light Sensor");
//       // Read the light level
//       double newBrightness = lightSensor.readLightLevel();
//       if (newBrightness < 0) {
//         if (lightSensorState.connectionAttempt < SensorConfig::maxConnectionAttemptBH1750) {
//           lightSensorState.connectionAttempt ++;
//           LogWarn("Light sensor", "Measurement failed, retrying ...");
//         } else {
//           lightSensorState.connectionAttempt = 0;
//           lightSensorState.brightness = NAN;
//           LogError("Light sensor", "Failed to read after max attempts");
//           InitLightSensor();
//         }
//       } else {
//         lightSensorState.brightness = newBrightness;
//         LogRead(SensorConfig::brightnessKey, String(lightSensorState.brightness, 4).c_str(), "lux");
//       }
//       GiveMutex(lightSensorState.mutex, "Light sensor");
//     }
//     vTaskDelay(SensorConfig::readBH1750Interval); // Use normal interval for next read
//   }}
// }

void InitLightSensor() {
  // Initialize the light sensor mutex
  lightSensorState.mutex = xSemaphoreCreateMutex();
  if (lightSensorState.mutex == nullptr) {
    LogError("Light sensor", "Failed to create mutex");
  } else {
    LogSuccess("Light sensor", "Created mutex");
  }
}

void TaskLightSensor(void *pvParameters) {
  while(1) {
    if (isSystemReady()) {
      // Check if the light sensor has been initialized
      if (!lightSensorState.isConnected) {
        // Initialize the light sensor with default settings
        LogInfo("Light sensor", "Initializing ...");
        if (!lightSensor.begin()) {
          LogError("Light sensor", "Failed to initialize");
        } else {
          // Initialize the light sensor state
          lightSensorState.isConnected = true;
          lightSensorState.connectionAttempt = 0;
          lightSensorState.brightness = NAN;
          LogSuccess("Light sensor", "Initialized successfully");
        }
      } else {
        TakeMutex(lightSensorState.mutex, SystemConfig::mutexWaitTicks, "Light Sensor");
        // Read the light level
        double newBrightness = lightSensor.readLightLevel();
        if (newBrightness < 0) {
          if (lightSensorState.connectionAttempt < SensorConfig::maxConnectionAttemptBH1750) {
            lightSensorState.connectionAttempt ++;
            LogWarn("Light sensor", "Measurement failed, retrying ...");
          } else {
            lightSensorState.isConnected = false;
            LogError("Light sensor", "Failed to read after max attempts");
          }
        } else {
          lightSensorState.brightness = newBrightness;
          LogRead(SensorConfig::brightnessKey, String(lightSensorState.brightness, 4).c_str(), "lux");
        }
        GiveMutex(lightSensorState.mutex, "Light sensor");
      }
      vTaskDelay(SensorConfig::readBH1750Interval); // Use normal interval for next read
    }
  }
}