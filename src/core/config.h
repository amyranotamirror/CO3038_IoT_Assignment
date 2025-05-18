#ifndef CONFIG_H
#define CONFIG_H

#include <cstdint>

struct SystemConfig {
    static constexpr uint32_t serialDebugBaud = 115200U;
    // Timing
    static constexpr uint32_t smallTaskDelay = 500U;
    static constexpr uint32_t defaultTaskDelay = 1000U;
    static constexpr uint32_t mutexWaitTicks = 100U;
};
struct WiFiConfig {
    static constexpr const char* wifiSSID = "AN COFFEE";
    static constexpr const char* wifiPassword = "Ancoffeexinchao";
    static constexpr uint16_t maxConnectionAttempt = 20U;
    //Timing
    static constexpr uint32_t reconnectInterval = SystemConfig::defaultTaskDelay * 5;
    static constexpr uint32_t connectionAttemptInterval = SystemConfig::smallTaskDelay;
};
struct MessageConfig {
    static constexpr uint16_t maxMessageSendSize = 512U;
    static constexpr uint16_t maxMessageReceiveSize = 512U;
    static constexpr uint8_t maxAttributes = 2U;
};

struct ThingsBoardConfig {
    static constexpr const char* server = "app.coreiot.io";
    static constexpr const char* token = "DMeXarEe7JJzQKBEMwYC";
    static constexpr uint16_t port = 1883U; 
    // Timing
    static constexpr uint32_t reconnectInterval = SystemConfig::defaultTaskDelay * 5;
    static constexpr uint32_t connectionAttemptInterval = SystemConfig::smallTaskDelay;
};
struct TelemetryConfig {
    // Timing
    static constexpr uint32_t sendInterval = 10000U;
    static constexpr uint64_t requestTimeoutMicroseconds = 10000U * 1000U;
};
struct OTAConfig {
    static constexpr const char* server = "SMART_OFFICE";
    static constexpr const char* version = "1.0";
    static constexpr uint8_t maxFailureAttempt = 12U;
    static constexpr uint16_t firmwarePacketSize = 4096U;
    // Timing
    static constexpr uint32_t otaUpdateInterval = SystemConfig::defaultTaskDelay * 5;
};

struct SensorConfig {
    static constexpr const char* temperatureKey = "temperature";
    static constexpr const char* humidityKey = "humidity";
    static constexpr const char* brightnessKey = "brightness";
    static constexpr const char* motionKey = "motion";
    static constexpr const char* co2Key = "co2";

    static constexpr uint16_t maxConnectionAttemptDHT20 = 20U;
    static constexpr uint16_t maxConnectionAttemptLD2410 = 20U;
    static constexpr uint16_t maxConnectionAttemptBH1750 = 20U;
    static constexpr uint16_t maxConnectionAttemptMQ135 = 20U;
    // Timing
    static constexpr uint32_t readDHT20Interval = SystemConfig::defaultTaskDelay * 5;
    static constexpr uint32_t readLD2410Interval = SystemConfig::defaultTaskDelay * 5;
    static constexpr uint32_t readBH1750Interval = SystemConfig::defaultTaskDelay * 5;
    static constexpr uint32_t readMQ135Interval = SystemConfig::defaultTaskDelay * 5;

    static constexpr uint32_t connectAttemptDHT20Interval = SystemConfig::defaultTaskDelay;
    static constexpr uint32_t connectAttemptLD2410Interval = SystemConfig::defaultTaskDelay;
    static constexpr uint32_t connectAttemptBH1750Interval = SystemConfig::defaultTaskDelay;
    static constexpr uint32_t connectAttemptMQ135Interval = SystemConfig::defaultTaskDelay;
};

struct ActuatorConfig {
    static constexpr const char* lightingKey = "lighting";
    static constexpr const char* curtainKey = "curtain";
    static constexpr const char* buzzerKey = "buzzer";
    static constexpr const char* indicatorLightKey = "indicator";
};

#endif