#include <HardwareSerial.h>
#include <Wire.h>

#include "task/network/task_wifi.h"
#include "task/network/task_thingsboard.h"
#include "task/network/task_rpc.h"
#include "task/network/task_shared_attr.h"
#include "task/network/task_telemetry.h"
#include "task/ota/task_ota.h"
#include "task/sensors/task_air_quality_sensor.h"
#include "task/sensors/task_light_sensor.h"
#include "task/sensors/task_motion_sensor.h"
#include "task/sensors/task_temp_humid_sensor.h"
#include "task/actuators/task_light.h"
#include "task/actuators/task_buzzer.h"

void TaskTest(void *pvParameters) {
  while(1) {
    thingsboard.loop();
    vTaskDelay(SystemConfig::defaultTaskDelay);
  }
}
void InitSystem(){
  // Init connection
  InitWiFi();

  // Init actuators
  InitLight();
  InitBuzzer();
  
  // Init sensors
  // InitLightSensor();
  

  // Create RTOS tasks
  xTaskCreate(TaskWiFi, "WiFi", 4096U, NULL, 2, NULL);
  xTaskCreate(TaskThingsBoard, "ThingsBoard", 4096U, NULL, 2, NULL);
  xTaskCreate(TaskThingsBoardLoop, "ThingsBoardLoop", 4096U, NULL, 2, NULL);
  xTaskCreate(TaskOTAUpdate, "OTAUpdate", 4096U, NULL, 1, NULL);

  // xTaskCreate(TaskLightSensor, "LightSensor", 4096U, NULL, 2, NULL);
  // xTaskCreate(TaskTelemetry, "Telemetry", 4096U, NULL, 2, NULL);
  // xTaskCreate(TaskTest, "Test", 4096U, NULL, 2, NULL);
}

/* ========================================================================== */
/*                              PROGRAM EXECUTION                             */
/* ========================================================================== */
void setup() {
  // something
  Serial.begin(SystemConfig::serialDebugBaud);
  Serial.println();
  Serial.println("\n=== IOT ASSIGNMENT: SMART OFFICE ===");
  Wire.begin(GPIO_NUM_21, GPIO_NUM_22);

  // something
  InitSystem();
  
}

void loop() {}