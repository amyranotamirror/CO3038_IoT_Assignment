#ifndef STATE_H
#define STATE_H

#include <cstdint>
#include <cmath>

struct WiFiState {
    bool isConnected = false;
    bool isAttempting = false;
    uint16_t connectionAttempts = 0;    // Refer WiFiConfig::maxConnectionAttempt
    uint32_t lastAttemptTime = 0;
};

struct OTAUpdateState {
    bool shared_update_subscribed = false;
    bool currentFWSent = false;
    bool updateRequestSent = false;
    bool requestedShared = false;
};
struct TempHumidSensorState {
    uint16_t connectionAttempt = 0;     // Refer SensorConfig::maxConnectionAttemptDHT20
    uint32_t temperature = NAN;
    uint32_t humidity = NAN;
};
struct AirQualitySensorState {
    uint16_t connectionAttempt = 0;     // Refer SensorConfig::maxConnectionAttemptMQ135
    uint32_t co2 = NAN;
};

struct LightSensorState {
    uint16_t connectionAttempt = 0;     // Refer SensorConfig::maxConnectionAttemptBH1750
    uint32_t brightness = NAN;
};

struct MotionSensorState {
    uint16_t connectionAttempt = 0;     // Refer SensorConfig::maxConnectionAttemptLD2410
    uint32_t motionDetected = NAN;
};

#endif