#ifndef TEMP_HUMID_SENSOR_H
#define TEMP_HUMID_SENSOR_H

#include <DHT.h>

#include "./core/config.h"
#include "./core/state.h"
#include "./core/utils.h"

extern DHT tempHumidSensor;

void InitTempHumidSensor();
void TaskTempHumidSensor(void *pvParameters);

#endif