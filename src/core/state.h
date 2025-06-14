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
    bool isConnected;
    volatile SemaphoreHandle_t mutex;
    uint16_t connectionAttempt;         // Refer SensorConfig::maxConnectionAttemptMQ135
    double co2;
};
struct LightSensorState {
    bool isConnected;
    volatile SemaphoreHandle_t mutex;
    uint16_t connectionAttempt;         // Refer SensorConfig::maxConnectionAttemptBH1750
    double brightness;
};
struct PresenceSensorState {
    bool isConnected;
    volatile SemaphoreHandle_t mutex;
    uint16_t connectionAttempt;         // Refer SensorConfig::maxConnectionAttemptLD2410
    bool presence;
    uint32_t distance;
};
struct TempHumidSensorState {
    bool isConnected;
    volatile SemaphoreHandle_t mutex;
    uint16_t connectionAttempt;         // Refer SensorConfig::maxConnectionAttemptDHT22
    double temperature;
    double humidity;
};

struct LightActuatorState {
    uint8_t mode;
    bool isWhiteMode;
    bool isWarmMode;
};
struct CurtainActuatorState {
    uint8_t mode;
};

struct BuzzerState {
    bool status;
};
struct AlertState {
    bool status;
};

extern volatile WifiState wifiState;
extern volatile ThingsBoardState thingsBoardState;

extern volatile TempHumidSensorState tempHumidSensorState;
extern volatile AirQualitySensorState airQualitySensorState;
extern volatile LightSensorState lightSensorState;
extern volatile PresenceSensorState presenceSensorState;

extern volatile LightActuatorState lightActuatorState;
extern volatile CurtainActuatorState curtainActuatorState;

extern volatile BuzzerState buzzerState;
extern volatile AlertState alertState;

bool isSystemReady();

#endif