#pragma once
#include <cstdint>

struct SystemConfig {
    static constexpr uint32_t serialDebugBaud = 115200U;
    // Timing
    static constexpr uint32_t defaultTaskDelay = 1000U;
    static constexpr uint32_t mutexWaitTicks = 100U;
};
struct WiFiConfig {
    static constexpr uint16_t maxConnectionAttempt = 20U;
    //Timing
    static constexpr uint32_t reconnectInterval = SystemConfig::defaultTaskDelay;
    static constexpr uint32_t connectionAttemptInterval = 250U;
};
struct MessageConfig {
    static constexpr uint16_t maxMessageSendSize = 512U;
    static constexpr uint16_t maxMessageReceiveSize = 512U;
    static constexpr uint8_t maxAttributes = 2U;
}
struct TelemetryConfig {
    // Timing
    static constexpr uint32_t sendInterval = 10000U;
    static constexpr uint32_t serverCheckInterval = 1000U;
    static constexpr uint64_t requestTimeoutMicroseconds = 10000U * 1000U;
};
struct OTAConfig {
    static constexpr char firmwareTitle[];          // "SMART_OFFICE"
    static constexpr char firmwareVersion[];        // "1.0"
    static constexpr uint8_t maxFailureAttempt = 12U;
    static constexpr uint16_t firmwarePacketSize = 4096U;
    // Timing
    static constexpr uint32_t otaUpdateInterval = SystemConfig::defaultTaskDelay * 5;
};
constexpr const char OTAConfig::firmwareTitle = "SMART_OFFICE";
constexpr const char OTAConfig::firmwareVersion = "1.0";

struct SensorConfig {
    static constexpr char temperatureKey[];     // "temperature";
    static constexpr char humidityKey[];        // "humidity";
    static constexpr char brightnessKey[];      // "brightness";
    static constexpr char motionKey[];          // "motion";
    static constexpr char co2Key[];             // "co2";

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
constexpr const char SensorConfig::temperatureKey[] = "temperature";
constexpr const char SensorConfig::humidityKey[] = "humidity";
constexpr const char SensorConfig::brightnessKey[] = "brightness";
constexpr const char SensorConfig::motionKey[] = "motion";
constexpr const char SensorConfig::co2Key[] = "co2";

struct ActuatorConfig {
    static constexpr char lightingKey[];    // "lighting"
    static constexpr char curtainKey[];     // "curtain"
    static constexpr char buzzerKey[];      // "buzzer"
}

constexpr const char ActuatorConfig::lightingKey = "lighting";
constexpr const char ActuatorConfig::curtainKey = "curtain";
constexpr const char ActuatorConfig::buzzerKey = "buzzer";
