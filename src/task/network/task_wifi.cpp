#include "task_wifi.h"

WiFiClient wifiClient;

void InitWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.setAutoReconnect(false);
  LogInfo("WiFi", "Initialized in STA mode");
}

void TaskWiFi(void *pvParameters) {
  while(1) {
    if (WiFi.status() == WL_CONNECTED) {
      // Connection was established
      if (!wifiState.isConnected) {
        Serial.println();
        LogInfo("WiFi", "Established connection");
        LogInfo("IP address", WiFi.localIP().toString().c_str());
      }
      // Maintain connection
      wifiState.isConnected = true;
      wifiState.isAttempting = false;
      wifiState.connectionAttempts = 0;
    } else {
      if (!wifiState.isAttempting) {
        // Initiate connection
        Serial.print("[UPDATE] WiFi: Connecting ...");
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
          LogError("WiFi", "Failed to connect");
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