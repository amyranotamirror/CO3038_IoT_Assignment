#ifndef MOTION_SENSOR_H
#define MOTION_SENSOR_H

#include <MyLD2410.h>

#include "./core/config.h"
#include "./core/state.h"
#include "./core/utils.h"

extern MyLD2410 presenceSensor;

void InitPresenceSensor();
void TaskPresenceSensor(void *pvParameters);

#endif