#include "task_wifi.h"

WiFiClient wifiClient;

void InitWiFi() {
  Serial.print("Connecting to WiFi ...");
  WiFi.begin(WiFiConfig::wifiSSID, WiFiConfig::wifiPassword);
  while (WiFi.status() != WL_CONNECTED) {
    delay(WiFiConfig::connectionAttemptInterval);
    Serial.print(".");
  }
  Serial.println(); Serial.println("Connected to WiFi!");
}

void TaskWiFi(void *pvParameters) {
  while(1) {
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("WiFi disconnected, attempting to reconnect ...");
      InitWiFi();
    }
    vTaskDelay(WiFiConfig::reconnectInterval);
  }
}