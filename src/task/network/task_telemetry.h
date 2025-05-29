#ifndef TASK_TELEMETRY_H
#define TASK_TELEMETRY_H

#include <HardwareSerial.h>
#include "./core/config.h"
#include "./core/state.h"
#include "../network/task_thingsboard.h"

void TaskTelemetry(void *pvParameters);

#endif
