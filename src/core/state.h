#ifndef STATE_H
#define STATE_H

#include <cstdint>
#include <cmath>
#include <Arduino.h>

#define ON 1
#define OFF 0

struct WifiState {
    bool isConnected;
    bool isAttempting;
    uint16_t connectionAttempts;
};
struct ThingsBoardState {
    bool isConnected;
    bool isAttempting;
    uint16_t connectionAttempts;
    bool isServerRPC;
    bool isSharedAttributesUpdated;
    bool isSharedAttributesRequested;
    bool isSharedAttributesRequestProcessed;
    bool isOTACurrentFirmwareSent;
    bool isOTAUpdateRequestSent;
};

struct AirQualitySensorState {
    uint16_t connectionAttempt;         // Refer SensorConfig::maxConnectionAttemptMHZ19
    double co2;
};
struct LightSensorState {
    volatile SemaphoreHandle_t mutex;
    uint16_t connectionAttempt;         // Refer SensorConfig::maxConnectionAttemptBH1750
    double brightness;
};
struct MotionSensorState {
    uint16_t connectionAttempt;        // Refer SensorConfig::maxConnectionAttemptLD2410
    double motionDetected;
};
struct TempHumidSensorState {
    uint16_t connectionAttempt;        // Refer SensorConfig::maxConnectionAttemptDHT20
    double temperature;
    double humidity;
};

struct LightActuatorState {
    uint8_t mode;
};

struct {
    bool status = ON;
} buzzerState;
struct {
    bool status = ON;
} alertState;

extern volatile WifiState wifiState;
extern volatile ThingsBoardState thingsBoardState;

extern volatile TempHumidSensorState tempHumidSensorState;
extern volatile AirQualitySensorState airQualitySensorState;
extern volatile LightSensorState lightSensorState;
extern volatile MotionSensorState motionSensorState;

extern volatile LightActuatorState lightActuatorState;

#endif