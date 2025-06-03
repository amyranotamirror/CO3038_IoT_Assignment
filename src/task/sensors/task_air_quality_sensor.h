#ifndef AIR_QUALITY_SENSOR_H
#define AIR_QUALITY_SENSOR_H

#include <MQ135.h>

#include "./core/config.h"
#include "./core/state.h"
#include "./core/utils.h"

extern MQ135 airQualitySensor;

void InitAirQualitySensor();
void TaskAirQualitySensor(void *pvParameters);

#endif