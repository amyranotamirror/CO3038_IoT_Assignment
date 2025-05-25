#include <HardwareSerial.h>

#include "task/network/task_wifi.h"
#include "task/network/task_thingsboard.h"
#include "task/ota/task_ota.h"

void TaskTest(void *pvParameters) {
  while(1) {
    double temperature = 1.0;
    Serial.print("Temperature: "); Serial.print(temperature); Serial.println(" *C");
    thingsboard.sendTelemetryData("temperature", temperature);
    vTaskDelay(3000);
  }
}

void setup() {
  // something
  Serial.begin(9600UL);
  Serial.println();
  // something
  InitWiFi();
  InitThingsBoard();
  // something
  xTaskCreate(TaskWiFi, "WiFi", 4096U, NULL, 2, NULL);
  xTaskCreate(TaskThingsBoard, "ThingsBoard", 4096U, NULL, 2, NULL);
  xTaskCreate(TaskTest, "Test", 2048, NULL, 2, NULL);
  xTaskCreate(TaskOTAUpdate, "OTAupdate", 4096U, NULL, 1, NULL);
}

void loop() {
  thingsboard.loop();
  vTaskDelay(pdMS_TO_TICKS(SystemConfig::defaultTaskDelay));
}