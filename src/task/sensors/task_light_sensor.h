#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H

#include <HardwareSerial.h>
#include <BH1750.h>
#include "./core/config.h"

extern BH1750 lightSensor;

void TaskLightSensor(void *pvParameters);

#endif