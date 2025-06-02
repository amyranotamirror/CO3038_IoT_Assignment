#ifndef CONFIG_H
#define CONFIG_H

#include <ThingsBoard.h>
#include <cstdint>

struct SystemConfig {
    static constexpr uint32_t serialDebugBaud = 9600U;
    // Timing
    static constexpr uint32_t tinyTaskDelay = 10U;
    static constexpr uint32_t smallTaskDelay = 500U;
    static constexpr uint32_t defaultTaskDelay = 1000U;
    static constexpr uint32_t mutexWaitTicks = 100U;
};
struct WiFiConfig {
    // Amyra 2.4GHz WiFi
    // static constexpr const char* wifiSSID = "AMYRANGUYEN 2995";
    // static constexpr const char* wifiPassword = "@s0T5278";
    // Harw 2.4GHz WiFi
    static constexpr const char* wifiSSID = "Harw";
    static constexpr const char* wifiPassword = "baohan1107";

    static constexpr uint16_t maxConnectionAttempt = 20U;
    //Timing
    static constexpr uint32_t reconnectInterval = SystemConfig::defaultTaskDelay * 5;
    static constexpr uint32_t connectionAttemptInterval = SystemConfig::smallTaskDelay;
};
struct MessageConfig {
    static constexpr uint16_t maxMessageSendSize = 512U;
    static constexpr uint16_t maxMessageReceiveSize = 512U;
};

struct ThingsBoardConfig {
    // Token
    // static constexpr const char* token = "EUhiYO2k6GAw35PIHa0K"; // Training room 1
    static constexpr const char* token = "aS2UTXnwxrgjfzSY4oRw"; // Training room 2
    // Server
    static constexpr const char* server = "app.coreiot.io";
    static constexpr uint16_t port = 1883U; 
    // Timing
    static constexpr uint16_t maxConnectionAttempt = 20U;
    static constexpr uint32_t reconnectInterval = SystemConfig::defaultTaskDelay * 5;
    static constexpr uint32_t connectionAttemptInterval = SystemConfig::smallTaskDelay;
};
struct TelemetryConfig {
    // Timing
    static constexpr uint32_t sendInterval = 10000U;
};
struct RPCAttributeConfig {
    static constexpr uint8_t MaxRPC = 0U;
    static constexpr uint8_t MaxRequestRPC = 2U;
    static constexpr uint8_t MaxSubscription = 1U;
    static constexpr uint8_t maxAttribute = 2U;
    static constexpr uint64_t requestTimeoutMicroseconds = 10000U * 1000U;
};
struct OTAConfig {
    static constexpr const char* title = "SMART_OFFICE";
    static constexpr const char* version = "8.0";
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

    static constexpr uint16_t maxConnectionAttemptDHT22 = 5U;
    static constexpr uint16_t maxConnectionAttemptLD2410 = 5U;
    static constexpr uint16_t maxConnectionAttemptBH1750 = 5U;
    static constexpr uint16_t maxConnectionAttemptMQ135 = 5U;
    // Timing
    static constexpr uint32_t readDHT22Interval = SystemConfig::defaultTaskDelay * 5;
    static constexpr uint32_t readLD2410Interval = SystemConfig::defaultTaskDelay * 5;
    static constexpr uint32_t readBH1750Interval = SystemConfig::defaultTaskDelay * 5;
    static constexpr uint32_t readMQ135Interval = SystemConfig::defaultTaskDelay * 5;

    static constexpr uint32_t connectAttemptDHT22Interval = SystemConfig::defaultTaskDelay;
    static constexpr uint32_t connectAttemptLD2410Interval = SystemConfig::defaultTaskDelay;
    static constexpr uint32_t connectAttemptBH1750Interval = SystemConfig::defaultTaskDelay;
    static constexpr uint32_t connectAttemptMQ135Interval = SystemConfig::defaultTaskDelay;

    static constexpr gpio_num_t DHT20Pin = GPIO_NUM_14
    ;
};

struct ActuatorConfig {
    static constexpr const char* lightingKey = "lighting";
    static constexpr const char* curtainKey = "curtain";
    static constexpr const char* buzzerKey = "buzzer";
    static constexpr const char* indicatorLightKey = "indicator";

    static constexpr gpio_num_t lightPin0 = GPIO_NUM_18;
    static constexpr gpio_num_t lightPin1 = GPIO_NUM_19;
    static constexpr gpio_num_t curtainPin = GPIO_NUM_23;
    static constexpr uint8_t curtainPWMChannel = 2;

    static constexpr gpio_num_t buzzerPin = GPIO_NUM_5;
    static constexpr uint8_t buzzerPWMChannel = 1;
    static constexpr gpio_num_t alertPin = GPIO_NUM_13;
};

#endif