#include "task_light_sensor.h"

BH1750 lightSensor;

void TaskLightSensor(void *pvParameters) {
  while(1) {
    float light = lightSensor.readLightLevel();
    lightSensorState.brightness = light;
    Serial.print("Light: "); Serial.print(light); Serial.println(" lux");
    vTaskDelay(SensorConfig::readBH1750Interval);
  }
}