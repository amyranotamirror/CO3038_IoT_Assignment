#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H

#include <BH1750.h>

#include "./core/config.h"
#include "./core/state.h"
#include "./core/utils.h"

extern BH1750 lightSensor;

void InitLightSensor();
void TaskLightSensor(void *pvParameters);

#endif