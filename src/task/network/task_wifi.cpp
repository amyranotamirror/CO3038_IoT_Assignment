#include "task_wifi.h"

WiFiClient wifiClient;

// void InitWiFi() {
//   Serial.print("Connecting to WiFi ...");
//   WiFi.disconnect();
//   WiFi.begin(WiFiConfig::wifiSSID, WiFiConfig::wifiPassword);
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(WiFiConfig::connectionAttemptInterval);
//     Serial.print(".");
//   }
//   Serial.println(); Serial.println("Connected to WiFi!");
// }

// void TaskWiFi(void *pvParameters) {
//   while(1) {
//     if (WiFi.status() != WL_CONNECTED) {
//       Serial.println("WiFi disconnected, attempting to reconnect ...");
//       InitWiFi();
//     }
//     vTaskDelay(WiFiConfig::reconnectInterval);
//   }
// }

void InitWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.setAutoReconnect(false);
  LogInfo("WiFi", "Initialized in STA mode.");
}

void TaskWiFi(void *pvParameters) {
  while(1) {
    if (WiFi.status() == WL_CONNECTED) {
      // Connection was established
      if (!wifiState.isConnected) {
        Serial.println();
        LogSuccess("WiFi", "Connected successfully.");
      }
      // Maintain connection
      wifiState.isConnected = true;
      wifiState.isAttempting = false;
      wifiState.connectionAttempts = 0;
    } else {
      if (!wifiState.isAttempting) {
        // Initiate connection
        // LogInfo("WiFi", "Connecting ...");
        WiFi.disconnect();
        WiFi.begin(WiFiConfig::wifiSSID, WiFiConfig::wifiPassword);
        // Maintain connection
        wifiState.isAttempting = true;
        wifiState.connectionAttempts = 0;
      } else {
        // Serial.print(".");
        wifiState.connectionAttempts++;
        if (wifiState.connectionAttempts >= WiFiConfig::maxConnectionAttempt) {
          LogError("WiFi", "Failed to connect. Maximum connection attempts reached.");
          WiFi.disconnect();
          wifiState.isAttempting = false;
        }
      }
      wifiState.isConnected = false;
    }
    if (wifiState.isAttempting) {
      vTaskDelay(WiFiConfig::connectionAttemptInterval);
    } else {
      vTaskDelay(WiFiConfig::reconnectInterval);
    }
  }
}