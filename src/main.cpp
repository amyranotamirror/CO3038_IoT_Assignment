#include <HardwareSerial.h>
#include <Wire.h>

#include "task/network/task_wifi.h"
#include "task/network/task_thingsboard.h"
#include "task/sensors/task_air_quality_sensor.h"
#include "task/sensors/task_light_sensor.h"
#include "task/sensors/task_motion_sensor.h"
#include "task/sensors/task_temp_humid_sensor.h"

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
}

void loop() {}