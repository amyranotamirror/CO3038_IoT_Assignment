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
  Serial.println("[INFO] WiFi: Initialized in STA mode.");
}

void TaskWiFi(void *pvParameters) {
  while(1) {
    if (WiFi.status() == WL_CONNECTED) {
      // Connection was established
      if (!wifiState.isConnected) {
        Serial.println();
        Serial.println("[INFO] WiFi: Established connection.");
        Serial.print("[INFO] IP address: "); Serial.println(WiFi.localIP());
      }
      // Maintain connection
      wifiState.isConnected = true;
      wifiState.isAttempting = false;
      wifiState.connectionAttempts = 0;
    } else {
      if (!wifiState.isAttempting) {
        // Initiate connection
        Serial.print("[UPDATE] Wifi: Connecting ...");
        WiFi.disconnect();
        WiFi.begin(WiFiConfig::wifiSSID, WiFiConfig::wifiPassword);
        // Maintain connection
        wifiState.isAttempting = true;
        wifiState.connectionAttempts = 0;
      } else {
        Serial.print(".");
        wifiState.connectionAttempts++;
        if (wifiState.connectionAttempts >= WiFiConfig::maxConnectionAttempt) {
          Serial.println();
          Serial.println("[ERROR] WiFi: Failed to connect. Will retry later.");
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