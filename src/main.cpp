#include "main.h"
#include <MyLD2410.h>

MyLD2410 motion(Serial2);
void TaskTest(void *pvParameters) {
  while(1) {
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

    vTaskDelay(SystemConfig::defaultTaskDelay * 5);
  }
}

void InitSystem() {
  Serial.begin(SystemConfig::serialDebugBaud); // Initialize serial communication for debugging via the serial monitor
  Serial2.begin(256000U, SERIAL_8N1, GPIO_NUM_16, GPIO_NUM_17); // Initialize serial communication for motion sensor
  Wire.begin(GPIO_NUM_21, GPIO_NUM_22); // Initialize i2c communication for light sensor
  analogReadResolution(10); // Reconfigure adc resolution for air quality sensor
}

void InitDevices() {
  // Init actuators
  InitAlert();
  InitBuzzer();
  InitLight();
  InitCurtain();
  
  // Init sensors
  InitAirQualitySensor();
  InitLightSensor();
  InitTempHumidSensor();
  bool check = motion.begin();
  Serial.print("This is another check value "); Serial.print(check); Serial.println(" ok.");
}

void InitTasks() {
  // Init connection
  InitWiFi();

  // Create RTOS tasks
  xTaskCreate(TaskWiFi, "WiFi", 4096U, NULL, 2, NULL);
  xTaskCreate(TaskThingsBoard, "ThingsBoard", 4096U, NULL, 2, NULL);
  xTaskCreate(TaskThingsBoardLoop, "ThingsBoardLoop", 4096U, NULL, 2, NULL);

  xTaskCreate(TaskAirQualitySensor, "AirQualitySensor", 4096U, NULL, 3, NULL);
  xTaskCreate(TaskLightSensor, "LightSensor", 4096U, NULL, 3, NULL);
  xTaskCreate(TaskTempHumidSensor, "TempHumidSensor", 4096U, NULL, 3, NULL);
  xTaskCreate(TaskTelemetry, "Telemetry", 4096U, NULL, 4, NULL);

  xTaskCreate(TaskBuzzer, "Buzzer", 4096U, NULL, 2, NULL);
  xTaskCreate(TaskAlert, "Alert", 4096U, NULL, 2, NULL);
  xTaskCreate(TaskTest, "Test", 4096U, NULL, 3, NULL);
}

/* ========================================================================== */
/*                              PROGRAM EXECUTION                             */
/* ========================================================================== */
void setup() {
  InitSystem();
  Serial.printf("\n\n=== IOT_ASSIGNMENT: %s_%s ===\n", OTAConfig::title, OTAConfig::version);
  InitDevices();
  InitTasks();
}

void loop() {}