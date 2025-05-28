#ifndef TASK_TELEMETRY_H
#define TASK_TELEMETRY_H

#include <HardwareSerial.h>
#include "../network/task_thingsboard.h"
#include "./core/config.h"
#include "./core/state.h"

void TaskTelemetry(void *pvParameters);

#endif
