#include "main.h"

void InitSystem() {
  Serial.begin(SystemConfig::serialDebugBaud); // Initialize serial communication for debugging via the serial monitor
  Serial2.begin(SystemConfig::serialPresenceSensorBaud, SystemConfig::serialPresenceSensorConfig, SystemConfig::serial2RxPin, SystemConfig::serial2TxPin); // Initialize serial communication for presence sensor
  Wire.begin(SystemConfig::sdaPin, SystemConfig::sclPin); // Initialize i2c communication for light sensor
  analogReadResolution(SystemConfig::analogAirQualityResolution); // Reconfigure adc resolution for air quality sensor
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
  InitPresenceSensor();
  InitTempHumidSensor();
}

void InitTasks() {
  // Init connection
  InitWiFi();

  // Create RTOS tasks
  xTaskCreate(TaskWiFi, "WiFi", 4096U, NULL, 2, NULL);
  xTaskCreate(TaskThingsBoard, "ThingsBoard", 4096U, NULL, 2, NULL);
  xTaskCreate(TaskThingsBoardLoop, "ThingsBoardLoop", 4096U, NULL, 2, NULL);

  xTaskCreate(TaskAlert, "Alert", 4096U, NULL, 2, NULL);
  xTaskCreate(TaskBuzzer, "Buzzer", 4096U, NULL, 2, NULL);

  xTaskCreate(TaskAirQualitySensor, "AirQualitySensor", 4096U, NULL, 3, NULL);
  xTaskCreate(TaskLightSensor, "LightSensor", 4096U, NULL, 3, NULL);
  xTaskCreate(TaskPresenceSensor, "PresenceSensor", 4096U, NULL, 3, NULL);
  xTaskCreate(TaskTempHumidSensor, "TempHumidSensor", 4096U, NULL, 3, NULL);
  xTaskCreate(TaskTelemetry, "Telemetry", 4096U, NULL, 4, NULL);
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