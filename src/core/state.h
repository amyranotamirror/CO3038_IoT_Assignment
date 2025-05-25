#ifndef STATE_H
#define STATE_H

#include <cstdint>
#include <cmath>

#define ON 1
#define OFF 0
struct {
    bool isConnected = false;
    bool isAttempting = false;
    uint16_t connectionAttempts = 0;    // Refer WiFiConfig::maxConnectionAttempt
    uint32_t lastAttemptTime = 0;
} wifiState;

struct {
    bool shared_update_subscribed = false;
    bool currentFWSent = false;
    bool updateRequestSent = false;
    bool requestedShared = false;
} otaUpdateState;
struct {
    uint16_t connectionAttempt = 0;     // Refer SensorConfig::maxConnectionAttemptDHT20
    double temperature = NAN;
    double humidity = NAN;
} tempHumidSensorState;
struct {
    uint16_t connectionAttempt = 0;     // Refer SensorConfig::maxConnectionAttemptMQ135
    double co2 = NAN;
} airQualitySensorState;

struct {
    uint16_t connectionAttempt = 0;     // Refer SensorConfig::maxConnectionAttemptBH1750
    double brightness = NAN;
} lightSensorState;

struct {
    uint16_t connectionAttempt = 0;     // Refer SensorConfig::maxConnectionAttemptLD2410
    double motionDetected = NAN;
} motionSensorState;

struct {
    bool status = ON;
} lightActuatorState;

#endif