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
        LogInfo("WiFi", "Connecting ...");
        WiFi.disconnect();
        WiFi.begin(WiFiConfig::wifiSSID, WiFiConfig::wifiPassword);
        // Maintain connection
        wifiState.isAttempting = true;
        wifiState.connectionAttempts = 0;
      } else {
        wifiState.connectionAttempts++;
        if (wifiState.connectionAttempts >= WiFiConfig::maxConnectionAttempt) {
          LogError("WiFi", "Failed to connect after max attempts");
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