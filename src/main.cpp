#include <HardwareSerial.h>
#include <Wire.h>

#include "task/network/task_wifi.h"
#include "task/network/task_thingsboard.h"
#include "task/network/task_rpc.h"
#include "task/ota/task_ota.h"
#include "task/sensors/task_air_quality_sensor.h"
#include "task/sensors/task_light_sensor.h"
#include "task/sensors/task_motion_sensor.h"
#include "task/sensors/task_temp_humid_sensor.h"
#include "task/actuators/task_light.h"

void TaskTest(void *pvParameters);
void InitSystem(){
  // Init connection
  InitWiFi();
  InitThingsBoard();
  // InitRPC();

  // Init actuators
  InitLight();

  // Create RTOS tasks
  xTaskCreate(TaskLightSensor, "LightSensor", 2048U, NULL, 2, NULL);
  xTaskCreate(TaskWiFi, "WiFi", 4096U, NULL, 2, NULL);
  xTaskCreate(TaskThingsBoard, "ThingsBoard", 4096U, NULL, 2, NULL);
  xTaskCreate(TaskTest, "Test", 2048U, NULL, 2, NULL);
  xTaskCreate(TaskOTAUpdate, "OTAupdate", 4096U, NULL, 1, NULL);
}
void TaskTest(void *pvParameters) {
  while(1) {
    double temperature = 1.0;
    Serial.print("Temperature: "); Serial.print(temperature); Serial.println(" *C");
    thingsboard.sendTelemetryData("temperature", temperature);
    vTaskDelay(3000);
  }
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
  lightSensor.begin();
}

void loop() {
  thingsboard.loop();
  // RPCLightActuatorControl(!lightActuatorState.status);
  vTaskDelay(pdMS_TO_TICKS(SystemConfig::defaultTaskDelay));
}