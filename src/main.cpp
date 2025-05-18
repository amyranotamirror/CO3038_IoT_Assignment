#include <HardwareSerial.h>
#include <Wire.h>

#include "task/network/task_wifi.h"
#include "task/network/task_thingsboard.h"
#include "task/sensors/task_air_quality_sensor.h"
#include "task/sensors/task_light_sensor.h"
#include "task/sensors/task_motion_sensor.h"
#include "task/sensors/task_temp_humid_sensor.h"
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
  Wire.begin(GPIO_NUM_21, GPIO_NUM_22);

  // something
  InitWiFi();
  InitThingsBoard();
  lightSensor.begin();

  // something
  xTaskCreate(TaskWiFi, "WiFi", 2048, NULL, 2, NULL);
  xTaskCreate(TaskThingsBoard, "ThingsBoard", 2048, NULL, 2, NULL);
  xTaskCreate(TaskLightSensor, "LightSensor", 2048, NULL, 2, NULL);
  xTaskCreate(TaskTest, "Test", 2048, NULL, 2, NULL);
  xTaskCreate(TaskOTAUpdate, "OTAupdate", 4096U, NULL, 1, NULL);
}

void loop() {}