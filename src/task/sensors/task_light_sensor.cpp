#include "task_light_sensor.h"

BH1750 lightSensor;

void TaskLightSensor(void *pvParameters) {
  while(1) {
    double brightness = lightSensor.readLightLevel();
    lightSensorState.brightness = brightness;
    Serial.print("Got "); Serial.print(SensorConfig::brightnessKey); Serial.print(": "); Serial.print(lightSensorState.brightness); Serial.println(" lux");
    vTaskDelay(SensorConfig::readBH1750Interval);
  }
}