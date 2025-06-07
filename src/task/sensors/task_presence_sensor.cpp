#include "task_presence_sensor.h"

MyLD2410 presenceSensor(Serial2);

void InitPresenceSensor() {
  // Initialize the presence sensor with default settings
  LogInfo("Presence sensor", "initializing ...");
  if (!presenceSensor.begin()) {
    LogError("Presence sensor", "failed to initialize");
    return;
  }

  // Initialize the presence sensor mutex
  if (presenceSensorState.mutex == nullptr) {
    presenceSensorState.mutex = xSemaphoreCreateMutex();
    if (presenceSensorState.mutex == nullptr) {
      LogError("Presence sensor", "failed to create mutex");
      return;
    } else {
      LogSuccess("Presence sensor", "created mutex");
    }
  }

  // Initialize the presence sensor state
  presenceSensorState.isConnected = true;
  presenceSensorState.connectionAttempt = 0;
  presenceSensorState.presence = false;
  presenceSensorState.distance = 0;
  LogSuccess("Presence sensor", "initialized successfully");
}

void TaskPresenceSensor(void *pvParameters) {
  while(1) {
    if (isSystemReady()) {
      // Check if the presence sensor has been initialized
      if (!presenceSensorState.isConnected) {
        LogError("Presence sensor", "disconnected");
        InitPresenceSensor();
      }
      if (presenceSensorState.isConnected) {
        // Read the detected
        bool isConnected = presenceSensor.check() == MyLD2410::Response::DATA;
        bool newPresence = presenceSensor.presenceDetected();
        uint32_t newDistance = presenceSensor.detectedDistance();
        LogRead(SensorConfig::presenceKey, String(newPresence).c_str(), "");
        LogRead(SensorConfig::distanceKey, String(newDistance).c_str(), "cm");
        // Save read value
        if (TakeMutex(presenceSensorState.mutex, SystemConfig::mutexWaitTicks, "Presence sensor")) {
          if (!isConnected) {
            if (presenceSensorState.connectionAttempt < SensorConfig::maxConnectionAttemptLD2410) {
              presenceSensorState.connectionAttempt ++;
              LogWarn("Presence sensor", "measurement failed, retrying ...");
            } else {
              presenceSensorState.isConnected = false;
              LogError("Presence sensor", "failed to read after max attempts");
            }
          } else {
            presenceSensorState.connectionAttempt = 0;
          }
          presenceSensorState.presence = newPresence;
          presenceSensorState.distance = newDistance;
          GiveMutex(presenceSensorState.mutex, "Presence sensor");
        }
      }
    }
    vTaskDelay(SensorConfig::readLD2410Interval); // Use normal interval for next read
  }
}