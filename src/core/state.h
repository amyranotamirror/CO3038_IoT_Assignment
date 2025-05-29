#ifndef STATE_H
#define STATE_H

#include <cstdint>
#include <cmath>

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
};

struct {
    bool shared_update_subscribed = false;
    bool currentFWSent = false;
    bool updateRequestSent = false;
    bool requestedShared = false;
} otaUpdateState;

struct AirQualitySensorState {
    uint16_t connectionAttempt;        // Refer SensorConfig::maxConnectionAttemptMQ135
    double co2;
};
struct LightSensorState {
    uint16_t connectionAttempt;        // Refer SensorConfig::maxConnectionAttemptBH1750
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

struct {
    bool status = ON;
} buzzerState;
struct {
    bool status = ON;
} lightActuatorState;

extern volatile WifiState wifiState;
extern volatile ThingsBoardState thingsBoardState;

extern volatile TempHumidSensorState tempHumidSensorState;
extern volatile AirQualitySensorState airQualitySensorState;
extern volatile LightSensorState lightSensorState;
extern volatile MotionSensorState motionSensorState;

#endif