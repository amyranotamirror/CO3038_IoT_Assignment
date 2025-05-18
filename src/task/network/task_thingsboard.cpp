#include "task_thingsboard.h"

Arduino_MQTT_Client mqttClient(wifiClient);
ThingsBoard thingsboard(mqttClient, 512U, 512U, Default_Max_Stack_Size);

void InitThingsBoard() {
  Serial.print("Connecting to ThingsBoard ...");
  thingsboard.connect("app.coreiot.io", "DMeXarEe7JJzQKBEMwYC", 1883U);
  while (!thingsboard.connected()) {
    delay(500);
    Serial.print(".");
    thingsboard.connect("app.coreiot.io", "DMeXarEe7JJzQKBEMwYC", 1883U);
  }
  Serial.println(); Serial.println("Connected to ThingsBoard!");
}

void TaskThingsBoard(void *pvParameters) {
  while(1) {
    if (!thingsboard.connected()) {
      Serial.println("ThingsBoard disconnected, attempting to reconnect ...");
      InitThingsBoard();
    }
    vTaskDelay(5000);
  }
}