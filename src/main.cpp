#include <HardwareSerial.h>
#include <Wire.h>
#include <MQ135.h>
#include <MyLD2410.h>

#include "task/network/task_ota.h"
#include "task/network/task_rpc.h"
#include "task/network/task_shared_attr.h"
#include "task/network/task_telemetry.h"
#include "task/network/task_thingsboard.h"
#include "task/network/task_wifi.h"

#include "task/sensors/task_air_quality_sensor.h"
#include "task/sensors/task_light_sensor.h"
#include "task/sensors/task_motion_sensor.h"
#include "task/sensors/task_temp_humid_sensor.h"

#include "task/actuators/task_alert.h"
#include "task/actuators/task_buzzer.h"
#include "task/actuators/task_curtain.h"
#include "task/actuators/task_light.h"

// MQ135 airQualitySensor = MQ135(GPIO_NUM_34);
// void TaskTest(void *pvParameters) {
//   while(1) {
//     float ppm = airQualitySensor.getPPM();
//     LogRead("air", String(ppm, 4).c_str(), "ppm");
//     vTaskDelay(SystemConfig::defaultTaskDelay * 5);
//   }
// }

MyLD2410 motion(Serial2);
void TaskTest(void *pvParameters) {
  while(1) {
    vTaskDelay(SystemConfig::defaultTaskDelay * 5);
    // bool presenceDetected = motion.presenceDetected();
    // bool movingDetected = motion.movingTargetDetected();
    // bool stationaryDetected = motion.stationaryTargetDetected();
    // uint16_t movingDistance = motion.movingTargetDistance();
    // uint16_t stationaryDistance = motion.stationaryTargetDistance();
    // LogRead("presenceDetected", String(presenceDetected).c_str(), "");
    // LogRead("movingDetected", String(movingDetected).c_str(), "");
    // LogRead("stationaryDetected", String(stationaryDetected).c_str(), "");
    // LogRead("movingDistance", String(movingDistance).c_str(), "");
    // LogRead("stationaryDistance", String(stationaryDistance).c_str(), "");

    motion.check();
    Serial.println(motion.statusString());
    // if (motion.presenceDetected()) {
      Serial.print(motion.presenceDetected() ? "presence" : " no thing presence");
      Serial.print(", distance: ");
      Serial.print(motion.detectedDistance());
      Serial.print("cm");
      Serial.println();
    // }
    // if (motion.movingTargetDetected()) {
      Serial.print(motion.movingTargetDetected() ? "moving" : " no thing moving");
      Serial.print(" MOVING    = ");
      Serial.print(motion.movingTargetSignal());
      Serial.print("@");
      Serial.print(motion.movingTargetDistance());
      Serial.print("cm ");
      Serial.println();
    // }
    // if (motion.stationaryTargetDetected()) {
      Serial.print(motion.stationaryTargetDetected() ? "stationary" : " no thing stationary");
      Serial.print(" STATIONARY= ");
      Serial.print(motion.stationaryTargetSignal());
      Serial.print("@");
      Serial.print(motion.stationaryTargetDistance());
      Serial.print("cm ");
      Serial.println();
    // }
    Serial.println();

    // vTaskDelay(SystemConfig::defaultTaskDelay * 5);
  }
}

void InitSystem(){
  // Init actuators
  InitAlert();
  InitBuzzer();
  InitLight();
  InitCurtain();
  
  // Init sensors
  InitLightSensor();
  InitTempHumidSensor();
  // bool check = motion.begin();
  // Serial.print("This is another check value "); Serial.print(check); Serial.println(" ok.");

  // Init connection
  InitWiFi();

  // Create RTOS tasks
  xTaskCreate(TaskWiFi, "WiFi", 4096U, NULL, 2, NULL);
  xTaskCreate(TaskThingsBoard, "ThingsBoard", 4096U, NULL, 2, NULL);
  xTaskCreate(TaskThingsBoardLoop, "ThingsBoardLoop", 4096U, NULL, 2, NULL);

  xTaskCreate(TaskLightSensor, "LightSensor", 4096U, NULL, 3, NULL);
  xTaskCreate(TaskTempHumidSensor, "TempHumidSensor", 4096U, NULL, 3, NULL);
  xTaskCreate(TaskTelemetry, "Telemetry", 4096U, NULL, 4, NULL);

  xTaskCreate(TaskBuzzer, "Buzzer", 4096U, NULL, 2, NULL);
  xTaskCreate(TaskAlert, "Alert", 4096U, NULL, 2, NULL);
  // xTaskCreate(TaskTest, "Test", 4096U, NULL, 3, NULL);
}

/* ========================================================================== */
/*                              PROGRAM EXECUTION                             */
/* ========================================================================== */
void setup() {
  // something
  Serial.begin(SystemConfig::serialDebugBaud);
  Serial2.begin(256000U, SERIAL_8N1, GPIO_NUM_16, GPIO_NUM_17);
  Serial.println();
  Serial.printf("\n=== IOT_ASSIGNMENT: %s_%s ===\n", OTAConfig::title, OTAConfig::version);
  Wire.begin(GPIO_NUM_21, GPIO_NUM_22);

  // something
  InitSystem();
  
}

void loop() {}